#ifndef IV_QUANTIZATION_HPP_
#define IV_QUANTIZATION_HPP_

#include "Voxel.hpp"


namespace IV {
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
template <typename Specification>
class Quantizer {
public:
  using Point = typename Specification::Point;
  using PointAccessor = typename Specification::PointAccessor;
  using Number = typename Point::Number;
  using VoxelIndex = typename Specification::VoxelIndex;


  Quantizer(Number quantizationX, Number quantizationY, Number quantizationZ)
    : quantizationX(quantizationX)
    , quantizationY(quantizationY)
    , quantizationZ(quantizationZ)
    , offsetX(0)
    , offsetY(0)
    , offsetZ(0)
  {}

  explicit Quantizer(Number quantization)
    : Quantizer(quantization, quantization, quantization)
  {}

  Quantizer()
    : Quantizer(1, 1, 1)
  {}

  // {
  void
  SetOffset(Number offsetX_, Number offsetY_, Number offsetZ_)
  {
    offsetX = offsetX_;
    offsetY = offsetY_;
    offsetZ = offsetZ_;
  }

  void
  SetOffset(Number uniformOffset)
  {
    SetOffset(uniformOffset, uniformOffset, uniformOffset);
  }
  // }

  // {
  VoxelIndex
  MapPoint(Number x, Number y, Number z) const
  {
    return VoxelIndex(std::round((x - offsetX) / quantizationX),
                      std::round((y - offsetY) / quantizationY),
                      std::round((z - offsetZ) / quantizationZ));
  }

  VoxelIndex
  MapPoint(Point point) const
  {
    return MapPoint(PointAccessor::GetX(point),
                    PointAccessor::GetY(point),
                    PointAccessor::GetZ(point));
  }

  Point
  UnmapIndex(VoxelIndex index) const
  {
    Point point;
    PointAccessor::GetX(point) = (index.ijk.i * quantizationX) + offsetX;
    PointAccessor::GetY(point) = (index.ijk.j * quantizationY) + offsetY;
    PointAccessor::GetZ(point) = (index.ijk.k * quantizationZ) + offsetZ;
    return point;
  }
  // }
private:
  /// {
  /// The decimation/quantization of values along the integer space defined by
  /// <MaxUnitsI, MaxUnitsJ, MaxUnitsK>;
  ///
  /// <1, 1, 1>   :: No quantization should be done.
  /// <5, 5, 5>   :: [0,  5) belongs to 0
  ///                [5, 10) belongs to 1 ...
  Number quantizationX;
  Number quantizationY;
  Number quantizationZ;

  Number offsetX;
  Number offsetY;
  Number offsetZ;
  /// }
};
} // ns IV


#endif // IV_QUANTIZATION_HPP_
