#define cimg_display 0
#define cimg_use_jpeg
#define cimg_use_png
#include "cimg/CImg.h"

#include <iostream>
#include <cstdio>
#include <metacall/metacall.h>

#define NATIVE_CACHE
#define NATIVE_IMAGE

using namespace std;
using namespace cimg_library;
#include <stdio.h> 

#ifdef WINDOWS

#include <windows.h>

string getexepath()
{
  char result[ MAX_PATH ];
  return string( result, GetModuleFileName( NULL, result, MAX_PATH ) );
}

#else

#include <limits.h>
#include <unistd.h>

string getexepath()
{
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return string( result, (count > 0) ? count : 0 );
}
#endif

string get_current_path(){
	string full_path = getexepath();
	
	string::size_type pos = string( full_path ).find_last_of( "\\/" );
    return string( full_path ).substr( 0, pos);
}

/* stubs */
#ifdef NATIVE_CACHE
char c_cache_key[0xFF]="";
char c_cache_value[0xFF]="";
void * c_cache_get(void * args[])
{
	if(strcmp(c_cache_key,(char *)args[0])==0)
	{
		return metacall_value_create_string(c_cache_value, strlen(c_cache_value));
	}

	return metacall_value_create_string(" ", 1);
}

void * c_cache_set(void * args[])
{
	strcpy(c_cache_key,(char * ) args[0]);
	strcpy(c_cache_value,(char * ) args[1]);
	return  metacall_value_create_bool(true);
}
#endif

void * get_image(void * args[])
{
	char * id;
	char * image_path;
	id= (char *)args[0];
	image_path= (char *)args[1];

	void * cached_path = metacall("cache_get",id);

	if(cached_path){
		char * cache_path = metacall_value_to_string(cached_path);
		if(cache_path[0] ==' '){
			cout << "Making image!" << endl;
			cached_path = metacall("MakeImage",image_path);
			cache_path = metacall_value_to_string(cached_path);
			metacall("cache_set",id,cache_path);
		}else{
			cout << "Image from cache!" << endl;
		}
	}else{
		cout << "error calling cache_get" << endl;
	}

	return cached_path;
}

void * complex_algorithm(void * args[])
{
	size_t length = metacall_value_size(args[0]) - 1;

	char * str = metacall_value_to_string(args[0]);

	size_t left = 0, right = length - 1;

	while (left < right)
	{
		char old_left = str[left];

		str[left] = str[right];

		str[right] = old_left;

		++left;

		--right;
	}

	return metacall_value_create_string(str, length);
}

void rb_test(void)
{
	/* Test */
	{
		const char key[] = "hello";

		const char value[] = "world";

		metacall("cache_set", key, value);

		void * result = metacall("cache_has_key", key);

		if (result != NULL)
		{
			boolean b = metacall_value_to_bool(result);

			if (b == 1)
			{
				cout << "Value exists" << endl;
			}

			metacall_value_destroy(result);
		}
		else
		{
			cout << "Invalid has key" << endl;
		}

		result = metacall("cache_get", key);

		if (result != NULL)
		{
			const char * str = metacall_value_to_string(result);

			cout << "Value " << str << " == " << value << endl;

			metacall_value_destroy(result);
		}
		else
		{
			cout << "Invalid get" << endl;
		}
	}
}
#ifdef NATIVE_IMAGE
CImg<unsigned char> cimg_water_mark;

void * image_start(void * args[]){
	char * image= (char *) args[0];
	cimg_water_mark.load(image);
	return metacall_value_create_bool(true);
}

void * blend_image(void * args[]){
	char * image= (char *) args[0];

	 CImg<unsigned char> tmp_img(image);
	 tmp_img.draw_image(0,0,cimg_water_mark,0.5f);

	string output_name = std::tmpnam(NULL);
	output_name = output_name.append(".jpg");
	tmp_img.save(output_name.c_str());
	return metacall_value_create_string(output_name.c_str(),output_name.length());
}
#endif
int main(int argc, char * argv[])
{
	char * watermark_file;
	int port = 0;

	if(argc != 3){
		printf("Usage: <server-port> <full-image-path>\n");
		return 1;
	}else{
		port = atoi(argv[1]);

		if(port<=0){
			printf("invalid port %d\n",port);
			return 1;
		}

		watermark_file = argv[2];
		printf("port:%d\nwatermark image:%s\n",port, watermark_file);
	}

	const char * rb_scripts[] =
	{
		"cache.rb"
	};

	const char * py_scripts[] =
	{
		"frontend.py"
	};

	string cs_package = get_current_path().append("/scripts/image.dll");
	
	/* Initialize MetaCall */
	if (metacall_initialize() != 0)
	{
		cout << "Error initializing metacall" << endl;

		return 1;
	}

	/* Register complex algorithm into MetaCall */
	if (metacall_register("complex_algorithm", &complex_algorithm, METACALL_STRING, 1, METACALL_STRING) != 0)
	{
		cout << "Invalid function register" << endl;

		return 1;
	}
	if (metacall_register("get_image", &get_image, METACALL_STRING, 2, METACALL_STRING,METACALL_STRING) != 0)
	{
		cout << "Invalid function register" << endl;

		return 1;
	}
#ifdef NATIVE_IMAGE
	if (metacall_register("StartImageServer", &image_start, METACALL_BOOL, 1, METACALL_STRING) != 0)
	{
		cout << "Invalid function register" << endl;

		return 1;
	}
	
	if (metacall_register("MakeImage", &blend_image, METACALL_STRING, 1, METACALL_STRING) != 0)
	{
		cout << "Invalid function register" << endl;

		return 1;
	}
#endif

#ifdef NATIVE_CACHE
	if (metacall_register("cache_set", &c_cache_set, METACALL_BOOL, 2, METACALL_STRING, METACALL_STRING) != 0)
	{
		cout << "Invalid function register" << endl;

		return 1;
	}

	if (metacall_register("cache_get", &c_cache_get, METACALL_STRING, 1, METACALL_STRING) != 0)
	{
		cout << "Invalid function register" << endl;

		return 1;
	}
#else
	/* Load ruby script */
	if (metacall_load_from_file("rb", rb_scripts, sizeof(rb_scripts) / sizeof(rb_scripts[0])) != 0)
	{
		cout << "Invalid ruby script load" << endl;

		return 1;
	}
	/* Initialize ruby cache */
	metacall("cache_initialize");
#endif

	/* Ruby test */
	/* rb_test(); */
#ifndef NATIVE_IMAGE
	if (metacall_load_from_package("cs", cs_package.c_str()) != 0){
		cout << "Invalid cs package load" << endl;
		
		return 1;
	}
#endif
	void * image_server_status = NULL;
	
	image_server_status = metacall("StartImageServer",watermark_file);
	
	if(image_server_status==NULL){
		cout << "StartImageServer error" << endl;
	
		return 1;
	}else{
		bool status = metacall_value_to_bool(image_server_status);
		
		metacall_value_destroy(image_server_status);
		
		if(status){
		
			cout << "Image Server start!" << endl;
			
			/* metacall("MakeImage","/tmp/image.jpg");*/
		
		}else{
		
			cout << "Image Server start error!" << endl;
	
			return 1;
		}
	}
	/* Test */
	
	void * vpath = metacall("get_image","comida","/tmp/image.jpg");

	char * image_path;
	if(vpath){
		image_path= metacall_value_to_string(vpath);
		cout << image_path << endl;
		metacall_value_destroy(vpath);
	}

	vpath = metacall("get_image","comida","/tmp/image.jpg");

	if(vpath){
		 image_path= metacall_value_to_string(vpath);
		cout << image_path << endl;
		metacall_value_destroy(vpath);
	}

	return 0;
	
	/* Load python script */
	if (metacall_load_from_file("py", py_scripts, sizeof(py_scripts) / sizeof(py_scripts[0])) != 0)
	{
		cout << "Invalid python script load" << endl;

		return 1;
	}

	/* Initialize python frontend */
	void * result = metacall("frontend_initialize", port);

	if (result != NULL)
	{
		/* ... */

		metacall_value_destroy(result);
	}
	else
	{
		cout << "Invalid frontend initialization" << endl;
	}

	return metacall_destroy();
}
