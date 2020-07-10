// g++ --std=c++11 Image.cpp main.cpp -o main `pkg-config --cflags --libs opencv` && ./main image_path

#include <iostream>
#include "Image.h"

int main( int argc, char** argv )
{
  if( argc != 2)
  {
    std::cout <<"Image path required\n";
    return -1;
  }

  const std::string filepath = argv[1];
  const std::string filename = filepath.substr(filepath.find_last_of("/\\") + 1);
  const std::string outdir = "../output";

  Image img(filepath);
  cv::Mat imgSobel;
  img.sobel(imgSobel, true);
  cv::imwrite(outdir + "/sobel-" + filename, imgSobel);

  return 0;
}
