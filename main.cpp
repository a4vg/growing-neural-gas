#include "GNG.h" // also includes "Image.h"

#include <string>
#include <iostream>

int main(int argc, char const *argv[])
{

  if( argc != 3)
  {
    std::cout <<"Image path and output directory required\n";
    return -1;
  }

  /* Set files */
  const std::string imgpath = argv[1];
  const std::string filename = imgpath.substr(imgpath.find_last_of("/\\") + 1);
  const std::string outdir = argv[2];

  /* Apply sobel */
  cv::Mat img = cv::imread(imgpath);
  cv::Mat imgSobel;
  std::cout << "\nApplying sobel mask to image: " << outdir << "/sobel-" << filename;
  Image::sobel(img, imgSobel);
  cv::imwrite(outdir + "/sobel-" + filename, imgSobel);

  /* Train GNG with image with sobel mask */
  GNGTraits traits; // using default traits

  /* Example custom traits:
     traits.eb = 0.005;
     traits.en = 0.003;

     traits.maxAge = 20;
     traits.lambda = 10;

     traits.alpha = 0.01;
     traits.beta = 0.02;
  */

  std::cout << "\nBeggining training\n";
  GNG gng(traits, outdir + "/sobel-" + filename, outdir);
  gng.train(10000, 3, true, 80); // maxIterations, lineThick, exportMP4, int fps
  std::cout << "\nTraining ended";

  return 0; 
}