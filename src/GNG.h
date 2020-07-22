#ifndef GNG_H
#define GNG_H

#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/video/video.hpp>

#include "Graph.h"

struct GNGTraits
{
  float eb = 0.05;
  float en = 0.0005;
  int maxAge = 25;
  int lambda = 100;
  float alpha = 0.5;
  float beta = 0.0005;
};

class GNG
{
  GNGTraits traits;

  Graph<int, float, int> g; // <id type, node data type (error), edge data type (age)>
  cv::Mat img;

  // Video and image output
  std::string outvideoPath;
  std::string outimgPath;
  cv::VideoWriter video;

  void initVideo(int fps, char fourcc[4]);
  public:
    GNG(GNGTraits _traits, std::string imgpath, std::string outdir);
};


GNG::GNG(GNGTraits _traits, std::string imgpath, std::string outdir)
: traits(_traits)
{
  // Set video and img output filename
  // Get filename from path
  std::string filename = imgpath.substr(imgpath.find_last_of("/\\") + 1);

  this->outvideoPath = outdir + "/gng-" + filename.substr(0, filename.find_last_of(".")) + ".mp4";
  this->outimgPath = outdir + "/gng-" + filename;

  // Read image
  this->img = cv::imread(imgpath);

  // Initialize VideoWriter
  char fourcc[4] = {'m','p','4','v'}; 
  this->initVideo(10, fourcc);
};

void GNG::initVideo(int fps, char fourcc[4])
{
  std::cout << "Initializing video\n";

  this->video.open(
    this->outvideoPath, 
    cv::VideoWriter::fourcc(fourcc[0], fourcc[1], fourcc[2], fourcc[3]), // codec
    fps,
    this->img.size()
  );

  if (!video.isOpened())
    throw std::runtime_error("Could not open the output video");
}

#endif