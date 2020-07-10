#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/opencv.hpp>

class Image
{
  cv::Mat img;

  // Sobel kernels
  static const int sobelGx[3][3];
  static const int sobelGy[3][3];

  static int sumProduct(const int G[3][3], cv::Mat A);
  static int normalize(int px);

  public:
    Image(std::string imgpath): img(cv::imread(imgpath)) {};

    void grayscale(cv::Mat &imgGray);
    void sobel(cv::Mat &imgSobel, bool binary);
};

#endif