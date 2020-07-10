// g++ --std=c++11 Image.cpp main.cpp -o main `pkg-config --cflags --libs opencv` && ./main image_path

#include <iostream>
#include "Image.h"
#include "Graph.h"

int main( int argc, char** argv )
{
  if( argc != 2)
  {
    std::cout <<"Image path required\n";
    return -1;
  }

  // Set files
  const std::string filepath = argv[1];
  const std::string filename = filepath.substr(filepath.find_last_of("/\\") + 1);
  const std::string outdir = "../output";

  // Apply sobel mask to image
  cv::Mat img = cv::imread(filepath);
  cv::Mat imgSobel;
  Image::sobel(img, imgSobel);
  cv::imwrite(outdir + "/sobel-" + filename, imgSobel);
  std::cout << "Sobel applied to image: " << outdir << "/sobel-" << filename << "\n";

  // Draw a square with diagonals from a graph
  Graph<int, int, int> g;

  g.addNode(1, 1, 10, 10);
  g.addNode(2, 2, 40, 10);
  g.addNode(3, 3, 40, 40);
  g.addNode(4, 4, 10, 40);
  g.addEdge(1, 2, 0);
  g.addEdge(2, 3, 0);
  g.addEdge(3, 4, 0);
  g.addEdge(4, 1, 0);
  g.addEdge(1, 3, 0);
  g.addEdge(2, 4, 0);

  cv::Mat blackImg = cv::Mat::zeros(cv::Size(50,50), CV_8UC3);
  cv::Mat imgGraph;
  Image::overlapGraph(blackImg, imgGraph, g);
  cv::imwrite(outdir + "/graph.png", imgGraph);
  std::cout << "Graph drawn (square with diagonals): " << outdir + "/graph.png\n";

  return 0;
}
