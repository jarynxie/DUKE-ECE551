#include "vector.hpp"

#include <cmath>
#include <cstdio>

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D returnVector;
  returnVector.x = 0;
  returnVector.y = 0;
  returnVector.x = x + rhs.x;
  returnVector.y = y + rhs.y;
  return returnVector;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
  return x * rhs.x + y * rhs.y;
}
