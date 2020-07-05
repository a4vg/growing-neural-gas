// g++ --std=c++11 Sobel.cpp main.cpp -o main `pkg-config --cflags --libs opencv` && ./main image_path

#include <iostream>
#include <string>
#include "Sobel.h"

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

  cv::Mat img = cv::imread(filepath);
  cv::Mat imgSobel;
  Sobel::sobel(img, imgSobel);
  cv::imwrite(outdir + "/sobel-" + filename, imgSobel);

  return 0;
}
