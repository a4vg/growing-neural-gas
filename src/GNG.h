#ifndef GNG_H
#define GNG_H

#include <opencv2/opencv.hpp>
#include <opencv2/video/video.hpp>

#include <limits>
#include <random>

#include <string>
#include <vector>

#include "Graph.h"
#include "Image.h"

int const INFINITE=std::numeric_limits<float>::max();

std::random_device dev;
std::mt19937 gen(dev());

struct GNGTraits
{
  // Move winners by fractions of ..
  float eb = 0.05;
  float en = 0.03;

  int maxAge = 20;
  int lambda = 5; // Add point each .. iterations

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

  // Train
  int currentX = 0;
  int currentY = 0;

  // Video and image output
  std::string outvideoPath;
  std::string outimgPath;
  cv::VideoWriter video;

  void initVideo(int fps, char fourcc[4]);
  void init();

public:
  GNG(GNGTraits _traits, std::string imgpath, std::string outdir);
  void train(int maxIterations=100, bool exportMP4=true, int fps=5);
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


void GNG::init()
{
  /* Start with two units at random positions */
  // Random generator
  std::uniform_int_distribution<std::mt19937::result_type> randX(0, img.rows-1);
  std::uniform_int_distribution<std::mt19937::result_type> randY(0, img.cols-1);

  int x1, y1, x2, y2;
  x1 = randX(gen);
  y1 = randY(gen);
  do
  {
    x2 = randX(gen);
    y2 = randY(gen);
  } while (x1==x2 && y1==y2);

  g.addNode(1, 0, x1, y1); // id, error, coordinates
  g.addNode(2, 0, x2, y2);

  std::cout << "Random point1 in " << x1 << ", " << y1 << "\n";
  std::cout << "Random point2 in " << x2 << ", " << y2 << "\n";
}

void GNG::train(int maxIterations, bool exportMP4, int fps)
{
  if (exportMP4)
  {
    // Initialize VideoWriter
    char fourcc[4] = {'m','p','4','v'}; 
    this->initVideo(fps, fourcc);
  }
  
  std::cout << "Beggining training\n";
  this->init();

  /* Add new input from input data */
  Image::updateToNextPixelOn(this->img, this->currentX, this->currentY);
  std::cout << "Current pixel: (" << this->currentX << ", " << this->currentY << ")\n";

  for (int iteration=0; iteration<maxIterations && this->currentX!=-1 && this->currentY!=-1; ++iteration)
  {
    std::cout << "\nIteration #" <<  iteration << " ======================\n";

    // cv::Mat imgWithGraph;
    // Image::overlapGraph<graph>(this->img, imgWithGraph, g, currentX, currentY);
    // cv::imwrite(this->outimgPath + "train" + std::to_string(iteration) + ".png", imgWithGraph);

    if (exportMP4)
    {
      cv::Mat imgWithGraph;
      Image::overlapGraph<graph>(this->img, imgWithGraph, g, currentX, currentY);
      this->video << imgWithGraph;
    }
  

    /* Find first two winner nodes w1 and w2 */
    std::vector<int> winners = g.knn(2, this->currentX, this->currentY);
    std::cout << "There are: " << winners.size() << " winners" << "\n";

    graph::node* w1 = g.getNode(winners[0]);
    graph::node* w2 = g.getNode(winners[1]);


    std::cout << "Winner 1: " << w1->getId() << "\n";
    std::cout << "Winner 2: " << w2->getId() << "\n";

    /* Increment age of edges emanating from w1 */
    for (graph::edge* edge: w1->getEdges())
      edge->setWeight(edge->weight+1);

    std::cout << "Edges age incremented\n";

    /* Update local error of w1 */
    w1->data = pow(w1->distance(this->currentX, this->currentY), 2);
    std::cout << "Updated local error of w1. Error is " << w1->data << "\n";

    /* Move w1 and all nodes connected to it */
    w1->move(w1->x + ((this->currentX - w1->x) * traits.eb), w1->y + ((this->currentY - w1->y) * traits.eb));
    std::cout << "w1 has been moved\n";
    for (auto& edge: w1->getEdges())
    {
      auto n = edge->nodes[1];
      n->move(n->x + ((this->currentX - n->x) * traits.en), n->y + ((this->currentY - n->y) * traits.en));
    }
    std::cout << "All nodes connected to w1 have been moved\n";

    /* Refresh age (weight) of edge between winners or create one */
    graph::edge* winnersEdge = g.getEdge(w1->getId(), w2->getId());
    if (winnersEdge){
      winnersEdge->setWeight(0);
      std::cout << "Edge refreshed\n";
    }
    else{
      g.addEdge(w1->getId(), w2->getId(), 0);
      std::cout << "Edge added\n";
    }

    /* Remove edges exceding the maximum age */
    for (auto itNode = g.begin(); itNode != g.end();)
    {
      std::vector<graph::node*> edgesToRemove;
      // itNode->first: node id, node ptr
      auto edges = itNode->second->getEdges();
      for (auto itEdge = edges.begin(); itEdge != edges.end(); ++itEdge)
        if ((*itEdge)->weight > traits.maxAge)
          edgesToRemove.push_back((*itEdge)->nodes[1]);
      
      for (auto& nodeEnd: edgesToRemove){
        std::cout << "Removing edge with max age connecting " << itNode->first << " and " << nodeEnd->getId() << "\n";
        g.removeEdge(itNode->second, nodeEnd);
      }


    /* Remove nodes without emanating edges */
      if (itNode->second->alone()){
        std::cout << "Node " << itNode->first << " is alone, erasing\n";
        itNode = g.removeNode(itNode->second);
      }
      else
         ++itNode;
    }

    std::cout << "Edges with maximum age removed and alone nodes too\n";

    // /* If number of inputs presented is a multiple of lambda, insert new node */
    if (iteration%traits.lambda == 0)
    {
      /* Determine node q with largest error */
      float largestErrorQ = -1;
      graph::node* q = nullptr;
      for (auto itNode = g.begin(); itNode != g.end(); ++itNode)
        if (itNode->second->data > largestErrorQ)
        {
          q = itNode->second;
          largestErrorQ = q->data;
        }
      std::cout << "Node q with largest error determined. Is " <<  q->getId() << " and has a data of " <<  q->data << "\n";

      /* Among nodes connected to q, find node f with largest error */
      float largestErrorF = -1;
      graph::node* f = nullptr;
      for (auto& qEdge: q->getEdges())
      {
        if (qEdge->nodes[1]->data > largestErrorF)
        {
          f = qEdge->nodes[1];
          largestErrorF = f->data;
        }
      }
      std::cout << "Node f connected to q determined. Is " <<  f->getId() <<  "\n";

      /* Insert a node r between q and f */
      int rX = (q->x + f->x)/2;
      int rY = (q->y + f->y)/2;
      std::cout << "Q coordinates: " << q->x << ", " << q->y << "\n";
      std::cout << "F coordinates: " << f->x << ", " << f->y << "\n";
      
      const int rId = g.addNode(g.getNextId(), 0, rX, rY);
      std::cout << "R id: " << rId << "." << " coordinates : " << rX << ", " << rY << "\n";

      /* Remove edge between q and f and create edges with r with age=0 */
      g.removeEdge(q, f);
      g.addEdge(q->getId(), rId, 0);
      g.addEdge(f->getId(), rId, 0);

      /* Decrease local error of q and f by multiplying them with alpha */
      q->data = q->data * traits.alpha;
      f->data = f->data * traits.alpha;

      /* Set r error with new q error */
      g.getNode(rId)->data = q->data;
    }

    /* Decrease local error of all nodes by a factor beta */
    for (auto itNode = g.begin(); itNode != g.end(); ++itNode)
      itNode->second->data = itNode->second->data * traits.beta;

    std::cout << "Graph has: " << g.size()[0] << " nodes" << "\n";
    std::cout << "Graph has: " << g.size()[1] << " edges" << "\n";

    
    /* Add new input from input data */
    Image::updateToNextPixelOn(this->img, this->currentX, this->currentY);
    std::cout << "Current pixel: (" << this->currentX << ", " << this->currentY << ")\n";
  }
  std::cout << "\nTraining ended";
  if (exportMP4)
    this->video.release();
  else
  {
    cv::Mat imgWithGraph;
    Image::overlapGraph<graph>(this->img, imgWithGraph, g, currentX, currentY);
    cv::imwrite(this->outimgPath, imgWithGraph);
    std::cout << "Final image in: " << this->outimgPath << "\n";
  }
}

#endif