#ifndef IV_SPECIFICATION_HPP_
#define IV_SPECIFICATION_HPP_

#include "Point.hpp"
#include "Voxel.hpp"


namespace IV {
struct Specification {
  using Point = DefaultPoint;
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

} // ns IV

#endif // IV_SPECIFICATION_HPP_
