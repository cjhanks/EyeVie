#ifndef IV_POINT_OCCUPANCY_POINT_HPP_
#define IV_POINT_OCCUPANCY_POINT_HPP_

#include <bitset>
#include "Quantization.hpp"


namespace IV {
template <
  typename Specification,
  std::size_t X,
  std::size_t Y,
  std::size_t Z
>
class OccupancyPoint {
public:
  using Point = typename Specification::Point;
  using PointAccessor = typename Specification::PointAccessor;
  using Number = typename Point::Number;

  void
  operator()(Point point, const Quantizer<Specification>& quantizer)
  {
    auto corner = quantizer.Corner(point);
    //auto dx = PointAccessor::GetX(point) - PointAccessor::GetX(center);
    //auto dy = PointAccessor::GetY(point) - PointAccessor::GetY(center);
    //auto dz = PointAccessor::GetZ(point) - PointAccessor::GetZ(center);
  }

private:
  std::bitset<X * Y * Z> bitset;
};
} // ns IV

#endif // IV_POINT_OCCUPANCY_POINT_HPP_
