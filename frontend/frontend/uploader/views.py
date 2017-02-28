from django.shortcuts import render
from django.template import RequestContext
from django.http import HttpResponseRedirect
from django.core.urlresolvers import reverse

from frontend.uploader.models import Document
from frontend.uploader.forms import DocumentForm

import os.path

from _py_portd import metacall, metacall_function
#import _py_port import metacall, metacall_function

def list(request):
	# Handle file upload
	if request.method == 'POST':
		form = DocumentForm(request.POST, request.FILES);
		if form.is_valid():
			newdoc = Document(docfile=request.FILES['docfile']);
			filepath = os.path.dirname(newdoc.docfile.path) + '/' + newdoc.path + newdoc.docfile.name;

			print('Document path: ' + filepath)

			func = metacall_function('cache_has_key');

			print('Result: ' + str(func));

			result = metacall('cache_has_key', newdoc.docfile.name);

			print('Result: ' + str(result));

			if metacall('cache_has_key', newdoc.docfile.name) == True:
				print('File found in cache');
				#metacall('
			else:
				print('File not found in cache');
				#metacall('

			newdoc.save();

			# Redirect to the document list after POST
			return HttpResponseRedirect(reverse('list'))
	else:
		form = DocumentForm();	# A empty, unbound form

	# Load documents for the list page
	documents = Document.objects.all();

	# Render list page with the documents and the form
	return render(
		request,
		'list.html',
		{ 'documents': documents, 'form': form }
	);
