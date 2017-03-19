#ifndef QUANTIZER_HPP_
#define QUANTIZER_HPP_

#include "VoxelGrid.hpp"

namespace IV {
template <typename VoxelGridIndexMapper_>
class Quantizer {
public:
  using VoxelGridIndexMapper = VoxelGridIndexMapper_;
  using Specification = typename VoxelGridIndexMapper::Specification;

  using PointTraits = typename Specification::PointTraits;
  using Scalar = typename PointTraits::Scalar;
  using Point = typename PointTraits::Point;

  using VoxelTraits = typename Specification::VoxelTraits;
  using VoxelIndex = typename VoxelTraits::Index;


  Quantizer(Scalar upsampleX, Scalar upsampleY, Scalar upsampleZ)
    : upsampleX(upsampleX)
    , upsampleY(upsampleY)
    , upsampleZ(upsampleZ)
  {}

  explicit Quantizer(Scalar upsampleUniform)
    : Quantizer(upsampleUniform,
                upsampleUniform,
                upsampleUniform)
  {}

  inline VoxelIndex
  MapPoint(Point point) const
  { return MapPoint(point.x, point.y, point.z); }

  inline VoxelIndex
  MapPoint(Scalar x, Scalar y, Scalar z) const
  {
    return mapper.MapPoint(std::floor(x / upsampleX),
                           std::floor(y / upsampleY),
                           std::floor(z / upsampleZ));
  }

private:
  VoxelGridIndexMapper mapper;
  const Scalar upsampleX;
  const Scalar upsampleY;
  const Scalar upsampleZ;
};

} // ns IV

#endif // QUANTIZER_HPP_
