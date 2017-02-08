using System;
using System.Drawing;

namespace ImageLib
{
    public class ImageMaker
    {
        public static string MakeImage(string text)
        {
            using (Bitmap img = new Bitmap(100, 50))
            {
                using (Graphics grh = Graphics.FromImage(img))
                {
                    using (var font = new Font("Arial", 8))
                    {
                        grh.DrawString(text, font, Brushes.Red, 0, 0);
                    }
                }
                var fileName = System.IO.Path.GetRandomFileName() + ".png";

                img.Save(fileName, System.Drawing.Imaging.ImageFormat.Png);

            }

            return string.Empty;
        }
    }
}
