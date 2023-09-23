#include <gtest/gtest.h>
#include <glog/logging.h>

#include "VoxelGrid.hpp"


struct Point {
  double x;
  double y;
  double z;
};

TEST(VoxelGrid, BitsUndefinedIs0) {
  using Specification = IV::VoxelSpecifications<Point, 2, 2, 1>;
  using IndexMapper = IV::VoxelGridIndexMapper<Specification>;
  using VoxelIndex = typename IndexMapper::VoxelIndex;

  LOG(INFO)
    << VoxelIndex::BitsI << ", "
    << VoxelIndex::BitsJ << ", "
    << VoxelIndex::BitsK << ", "
    << VoxelIndex::BitsUndefined;
}

TEST(VoxelGrid, Mapping) {
  using Specification = IV::VoxelSpecifications<Point, 10, 10, 10>;
  using IndexMapper = IV::VoxelGridIndexMapper<Specification>;

  //LOG(INFO)
  //  << IndexMapper::VoxelTraits::DepthI << ", "
  //  << IndexMapper::VoxelTraits::DepthJ << ", "
  //  << IndexMapper::VoxelTraits::DepthK;

  // The 0 element always maps to 0 id.
  ASSERT_EQ(IndexMapper::MapPoint(
              {0.0,
               0.0,
               0.0}).id, 0);

#if !defined(NDEBUG)
  ASSERT_THROW(IndexMapper::MapPoint({11.0, 0.0, 0.0}),
               std::out_of_range);
#endif
}
