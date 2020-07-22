#include "GNG.h"

int main(int argc, char const *argv[])
{
  GNGTraits traits;

  GNG gng(traits, "../sample-imgs/lena.jpg", "../output");

  return 0; 
}