#ifndef IV_METRIC_SPACE_HPP_
#define IV_METRIC_SPACE_HPP_

#include "Point.hpp"
#include "Voxel.hpp"


namespace IV {
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
struct Specification {
  using Point = DefaultPoint;
  using PointData = DefaultPointData;
  using PointAccessor = IV::PointAccessor<Point>;

  /// {
  static constexpr std::size_t MaxUnitsX = 1000;
  static constexpr std::size_t MaxUnitsY = 1000;
  static constexpr std::size_t MaxUnitsZ =  100;
  /// }

  /// {
  /// LOP = <0, 0, 0> :: No additional bits of precision are stored
  ///                    for points.
  /// LOP = <3, 3, 2> :: 3 bits per point for i/j, 2 bits per k which rounds
  ///                    to a uint8_t per point in a voxel.
  /// LOP = <3, 3, 3> :: 3 bits per point for i/j/k adding 9 bits overhead
  ///                    which rounds up to a uint16_t per point in a voxel.
  static constexpr std::size_t SubPrecisionI = 0;
  static constexpr std::size_t SubPrecisionJ = 0;
  static constexpr std::size_t SubPrecisionK = 0;
  /// }

  using VoxelIndex = IV::VoxelIndex<MaxUnitsX, MaxUnitsY, MaxUnitsZ>;
};

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

#endif // IV_METRIC_SPACE_HPP_
