using System;

namespace ImageLib
{
    public class EntryPoint
    {
        public static void Main(string[] args)
        {
            if(ImageLib.ImageMaker.StartImageServer("/tmp/water.jpg")){
                Console.WriteLine( ImageLib.ImageMaker.MakeImage("/tmp/image.jpg"));
            }
        }
    }
}
