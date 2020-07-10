#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/opencv.hpp>
#include "Graph.h"

class Image
{
  cv::Mat img;

  // Sobel kernels
  static const int sobelGx[3][3];
  static const int sobelGy[3][3];

  static int sumProduct(const int G[3][3], cv::Mat A);
  static int normalize(int px);

  public:
    Image(cv::Mat _img): img(_img) {};
    Image(std::string imgpath): img(cv::imread(imgpath)) {};

    void grayscale(cv::Mat &imgGray);
    void sobel(cv::Mat &imgSobel, bool binary);

    template <typename G>
    void overlapGraph(cv::Mat &imgGraph, G& g);
};

template <typename G>
void Image::overlapGraph(cv::Mat &imgGraph, G& g)
{
  const int thickness = 2;
  const cv::Scalar colorRGB = cv::Scalar(0, 0, 255); // red
  imgGraph = this->img.clone();

  for (auto& node: g)
    for (auto& edge: node.second->getEdges())
    {
      cv::Point start = cv::Point(edge->nodes[0]->x, edge->nodes[0]->y);
      cv::Point end = cv::Point(edge->nodes[1]->x, edge->nodes[1]->y);
      cv::line(imgGraph, start, end, colorRGB, thickness);
    }
}

#endif