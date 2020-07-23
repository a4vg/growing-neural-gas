#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/opencv.hpp>
#include <vector>
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
    static void overlapGraph(cv::Mat &img, cv::Mat &imgGraph, G& g, int x, int y);
    static bool isPixelOn(int px, int t=127) { return px>t; }; // 127 = 255/2
    static void updateToNextPixelOn(cv::Mat &img1channel, int &x, int &y);
    static void getAllPixelsOn(cv::Mat &imgSobel, std::vector<cv::Point>& pixels);
};

template <typename G>
void Image::overlapGraph(cv::Mat &img, cv::Mat &imgGraph, G& g, int x, int y)
{
  const int thickness = 2;
  const cv::Scalar colorRGB = cv::Scalar(0, 0, 255); // red
  imgGraph = img.clone();

  for (auto& node: g)
    for (auto& edge: node.second->getEdges())
    {
      cv::Point start = cv::Point(edge->nodes[0]->y, edge->nodes[0]->x);
      cv::Point end = cv::Point(edge->nodes[1]->y, edge->nodes[1]->x);
      cv::line(imgGraph, start, end, colorRGB, thickness);
    }

  // Input point
  cv::Point p = cv::Point(y, x);
  cv::circle(imgGraph, p, 5, cv::Scalar(0, 0, 255), -1);
}

#endif