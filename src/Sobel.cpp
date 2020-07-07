#ifndef SOBEL_CPP
#define SOBEL_CPP

#include "Sobel.h"
#include <cmath>

const int Sobel::Gx[3][3] ={{1, 0, -1},
                            {2, 0, -2},
                            {1, 0, -1}};
const int Sobel::Gy[3][3] ={{1, 2, 1},
                            {0, 0, 0},
                            {-1, -2, -1}};

int Sobel::sumProduct(const int G[3][3], cv::Mat A)
{
  int result = 0;
  for (int i=0; i<3; ++i)
    for (int j=0; j<3; ++j)
    result += G[i][j]*A.at<uchar>(i, j);
  return result;
}
int Sobel::normalize(int px)
{
  return px>255? 255 : px;
}

void Sobel::grayscale(cv::Mat img, cv::Mat &imgGray)
{
  imgGray = cv::Mat::zeros(img.size(), CV_8UC1);
  for (int i=0; i<img.rows; ++i)
    for (int j=0; j<img.cols; ++j)
    {
      cv::Vec3b & color = img.at<cv::Vec3b>(i,j);
      imgGray.at<uchar>(i, j) = (color[0]+color[1]+color[2])/3;
    }
}

void Sobel::sobel(cv::Mat &img, cv::Mat &imgSobel, bool binary)
{
  imgSobel = cv::Mat::zeros(img.size(), CV_8UC1);

  // Get grayscale image
  cv::Mat imgGray;
  Sobel::grayscale(img, imgGray);

  // Iterate through matrix
  for (int i=0; i<img.rows-2; ++i)
    for (int j=0; j<img.cols-2; ++j)
    {
      int gx = sumProduct(Gx, imgGray(cv::Rect(j, i, 3, 3)));
      int gy = sumProduct(Gy, imgGray(cv::Rect(j, i, 3, 3)));
      
      // Euclidean distance
      int newPx = Sobel::normalize(std::sqrt(gx*gx + gy*gy));
      if (binary)
        newPx = std::round(newPx/255)*255;
      imgSobel.at<uchar>(i, j) = newPx;
    }
}

#endif