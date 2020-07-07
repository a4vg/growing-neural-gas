#ifndef SOBEL_H
#define SOBEL_H

#include <opencv2/opencv.hpp>

class Sobel
{
  // Sobel kernels
  static const int Gx[3][3];
  static const int Gy[3][3];

  static int sumProduct(const int G[3][3], cv::Mat A);
  static int normalize(int px);

  public:
    static void grayscale(cv::Mat img, cv::Mat &imgGray);
    static void sobel(cv::Mat &img, cv::Mat &imgSobel, bool binary);
};

#endif