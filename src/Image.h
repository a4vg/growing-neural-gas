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
    static void overlapGraph(cv::Mat &img, cv::Mat &imgGraph, G& g, int x, int y);
    static bool isPixelOn(int px) { return (bool) std::round( (float) px/255); };
    static void updateToNextPixelOn(cv::Mat &img1channel, int &x, int &y);
};

template <typename G>
void Image::overlapGraph(cv::Mat &img, cv::Mat &imgGraph, G& g, int x, int y)
{
  const int thickness = 10;
  const cv::Scalar colorRGB = cv::Scalar(0, 0, 255); // red
  const cv::Scalar colorRGBP = cv::Scalar(0, 255, 0); // green
  imgGraph = img.clone();

  for (auto& node: g){
    for (auto& edge: node.second->getEdges())
    {
      cv::Point start = cv::Point(edge->nodes[0]->y, edge->nodes[0]->x);
      cv::Point end = cv::Point(edge->nodes[1]->y, edge->nodes[1]->x);
      cv::line(imgGraph, start, end, colorRGB, thickness);
    }
    cv::Point np = cv::Point(node.second->y, node.second->x);
    cv::circle(imgGraph, np, thickness, colorRGBP, -1);
  }

  const cv::Scalar othercolor = cv::Scalar(255, 0, 0); // blue
  cv::Point p = cv::Point(y, x);
  cv::circle(imgGraph, p, 10, othercolor, -1);
  std::cout << "Point in " << x << ", " << y << "\n";
}

#endif