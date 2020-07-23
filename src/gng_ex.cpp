#include "GNG.h"

int main(int argc, char const *argv[])
{
  GNGTraits traits;

  GNG gng(traits, "../output/sobel-apple.jpg", "../output");
  // GNG gng(traits, "../output/sobel-utec_2.png", "../output");
  // GNG gng(traits, "../output/sobel-lena.jpg", "../output");
  gng.train(10000, true, 50);

  return 0; 
}