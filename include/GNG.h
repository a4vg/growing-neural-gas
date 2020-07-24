#ifndef GNG_H
#define GNG_H

#include <opencv2/opencv.hpp>
#include <opencv2/video/video.hpp>

#include <string>
#include <vector>

#include <random>

#include "Image.h" // includes "Graph/Graph.h"

struct GNGTraits
{
  // Move winners by fractions of ..
  float eb = 0.05;
  float en = 0.03;

  int maxAge = 10;
  int lambda = 10; // Add point each .. iterations

  // Decrease local error in each iteration by factors..
  float alpha = 0.01;
  float beta = 0.02;
};

class GNG
{
  typedef Graph<int, float, int> graph;

  GNGTraits traits;

  graph g; // <id type, node data type (error), edge data type (age)>
  cv::Mat img;
  std::vector<cv::Point> inputs;

  // Train
  int currentX = 0;
  int currentY = 0;

  // Video and image output
  std::string outvideoPath;
  std::string outimgPath;
  cv::VideoWriter video;

  void initVideo(int fps, char fourcc[4]);
  void init();
  bool getNextInput(int &x, int &y);

public:
  GNG(GNGTraits _traits, std::string imgpath, std::string outdir);
  void train(int maxIterations=100, int lineThick=2, bool exportMP4=true, int fps=5);
};

#endif