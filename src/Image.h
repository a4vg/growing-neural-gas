#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/opencv.hpp>
#include "Graph.h"

class Image
{
  // Sobel kernels
  static const int sobelGx[3][3];
  static const int sobelGy[3][3];

  static int sumProduct(const int G[3][3], cv::Mat A);
  static int normalize(int px) { return px>255? 255 : px; };

  public:
    static void grayscale(cv::Mat &img, cv::Mat &imgGray);
    static void sobel(cv::Mat &img, cv::Mat &imgSobel);

    template <typename G>
    static void overlapGraph(cv::Mat &img, cv::Mat &imgGraph, G& g);
    static bool isPixelOn(uchar px) { return (bool) std::round(px/255); };
    static void updateToNextPixelOn(cv::Mat &img1channel, int &x, int &y);
};

template <typename G>
void Image::overlapGraph(cv::Mat &img, cv::Mat &imgGraph, G& g)
{
  const int thickness = 2;
  const cv::Scalar colorRGB = cv::Scalar(0, 0, 255); // red
  imgGraph = img.clone();

  for (auto& node: g)
    for (auto& edge: node.second->getEdges())
    {
      cv::Point start = cv::Point(edge->nodes[0]->x, edge->nodes[0]->y);
      cv::Point end = cv::Point(edge->nodes[1]->x, edge->nodes[1]->y);
      cv::line(imgGraph, start, end, colorRGB, thickness);
    }
}

#endif