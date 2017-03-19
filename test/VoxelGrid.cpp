#include <gtest/gtest.h>
#include <glog/logging.h>

#include "Point.hpp"
#include "VoxelGrid.hpp"


using namespace IV;

TEST(VoxelGrid, Test0) {
  using Quantizer = IV::Quantizer<Specification>;
  using CountPoint = IV::CountPoint<Specification>;
  VoxelGrid<Specification, CountPoint> grid(Quantizer(0.5));

  //for (double x = -10.0; x <= +10.0; x += .05)
  for (double y = -10.0 - .05; y <= +10.0 + .05; y += .25) {
    IV::DefaultPoint pt;
    pt.x = 0;
    pt.y = y;
    pt.z = 0;

    grid(pt);
  }

  for (const auto& elem: grid) {
    auto value = elem.second;
    //ASSERT_EQ(value.Count(), 5);
    LOG(INFO) << value
              << ":"
              << elem.first.ijk.j;
  }
}

