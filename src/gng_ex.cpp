#include "GNG.h"

int main(int argc, char const *argv[])
{
  GNGTraits traits; // using default traits

  /* Example custom traits:
     traits.eb = 0.005;
     traits.en = 0.003;

     traits.maxAge = 20;
     traits.lambda = 10;

     traits.alpha = 0.01;
     traits.beta = 0.02;
  */

  GNG gng(traits, "../output/sobel-apple.jpg", "../output");
  gng.train(10000, 5, true, 80); // maxIterations, lineThick, exportMP4, int fps

  return 0; 
}