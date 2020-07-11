#ifndef GNG_H
#define GNG_H

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
  public:
    GNG(GNGTraits _traits) : traits(_traits) {};
};

#endif