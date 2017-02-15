using System;
using System.IO;
using ImageSharp;

using ImageSharp.Formats;
using ImageSharp.Processing;
using ImageSharp.Colors;
using ImageSharp.Quantizers;
using ImageSharp.Drawing;

namespace ImageLib
{
    public class ImageMaker
    {
        private static Image waterMark = null;

        public static bool StartImageServer(string waterMarkImagePath ){
            return SetWaterMark(waterMarkImagePath);
        }

        private static bool SetWaterMark(string path){
            try {
                waterMark= new Image(path);
            } catch {
                return false;
            }
            return true;
        }


        public static string MakeImage(string path)
        {
            var fileName = System.IO.Path.GetRandomFileName() + ".png";

            using(var image = new Image(path)){
                image.Blend(waterMark);
                image.Save(fileName);
            }

            return fileName;
        }
    }
}
