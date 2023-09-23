#ifndef IV_POINTS_CENTROID_HPP_
#define IV_POINTS_CENTROID_HPP_

#include "detail/RunningAverage.hpp"

namespace IV {
template <typename Specification>
class CentroidPoint {
public:
  using Point = typename Specification::Point;
  using PointAccessor = typename Specification::PointAccessor;
  using Number = typename Point::Number;

  void
  operator()(Point point)
  {
    x(PointAccessor::GetX(point));
    y(PointAccessor::GetY(point));
    z(PointAccessor::GetZ(point));
  }

  Point
  Centroid() const
  {
    Point point;
    PointAccessor::GetX(point) = x.Mean();
    PointAccessor::GetY(point) = y.Mean();
    PointAccessor::GetZ(point) = z.Mean();
    return point;
  }

  operator Point() const
  { return Centroid(); }

private:
  detail::RunningAverage<Number> x;
  detail::RunningAverage<Number> y;
  detail::RunningAverage<Number> z;
};

} // ns IV

#endif // IV_POINTS_CENTROID_HPP_
