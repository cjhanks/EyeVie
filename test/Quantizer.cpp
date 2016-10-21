#include <gtest/gtest.h>
#include <glog/logging.h>

#include "Quantizer.hpp"
#include "VoxelContainer.hpp"
#include "VoxelGrid.hpp"


struct Point {
  double x;
  double y;
  double z;
};

TEST(Quantizer, MulX_5) {
  using Specification = IV::VoxelSpecifications<Point, 100, 100, 50>;
  using IndexMapper = IV::VoxelGridIndexMapper<Specification>;
  using Quantizer = IV::Quantizer<IndexMapper>;
  using VoxelContainer = IV::VoxelContainer<Quantizer, int>;

  VoxelContainer container(Quantizer(5));

  for (size_t i = 0; i < 5; ++i) {
    Point pt;
    pt.x = i;
    pt.y = i;
    pt.z = i;

    container[pt]++;
  }

  ASSERT_EQ((container[{0, 0, 0}]), 5);
}

TEST(Quantizer, MulX_2_5) {
  using Specification = IV::VoxelSpecifications<Point, 100, 100, 50>;
  using IndexMapper = IV::VoxelGridIndexMapper<Specification>;
  using Quantizer = IV::Quantizer<IndexMapper>;
  using VoxelContainer = IV::VoxelContainer<Quantizer, int>;

  VoxelContainer container(Quantizer(2.5));

  for (size_t i = 0; i < 5; ++i) {
    Point pt;
    pt.x = i;
    pt.y = i;
    pt.z = i;
    container[pt]++;
  }

  ASSERT_EQ((container[{0.0, 0.0, 0.0}]), 3);
  ASSERT_EQ((container[{2.5, 2.5, 2.5}]), 2);
}
