#ifndef CENTROID_POINT_HPP_
#define CENTROID_POINT_HPP_

#include <cassert>

#include "detail/RunningAverage.hpp"


namespace IV {
template <typename Specification>
class CentroidPoint {
public:
  using Point = typename Specification::Point;
  using Scalar = typename Specification::Scalar;

  void
  Update(Point point)
  {
    x(point.x);
    y(point.y);
    z(point.z);
  }

  Point
  Centroid()
  {
    assert(x.size() > 0);
    assert(y.size() > 0);
    assert(z.size() > 0);

    Point point;
    point.x = x.mean();
    point.y = y.mean();
    point.z = z.mean();
    return point;
  }

private:
  RunningAverage<Scalar> x;
  RunningAverage<Scalar> y;
  RunningAverage<Scalar> z;
};
} // ns IV

#endif // CENTROID_POINT_HPP_
