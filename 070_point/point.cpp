#include "point.h"

#include <cmath>
#include <cstdio>

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  double answer;
  answer = (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
  answer = sqrt(answer);
  return answer;
}
