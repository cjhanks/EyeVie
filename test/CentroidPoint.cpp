#include <gtest/gtest.h>
#include <vector>
#include <type_traits>

#include "CentroidPoint.hpp"
#include "VoxelContainer.hpp"


struct Point {
  double x;
  double y;
  double z;
};

TEST(CentroidPoint, Simple2) {
  using Spec = IV::VoxelSpecifications<Point, 10, 10, 10>;
  using Centroid = IV::CentroidPoint<Spec>;

  do {
    Point p0 {0, 0, 0};
    Point p1 {2, 2, 2};
    Centroid c0;

    c0.Update(p0);
    c0.Update(p1);

    ASSERT_NEAR(c0.Centroid().x, 1, 1e-5);
    ASSERT_NEAR(c0.Centroid().y, 1, 1e-5);
    ASSERT_NEAR(c0.Centroid().z, 1, 1e-5);
  } while (0);

  do {
    Point p0 {-1e5, -1e5, -1e5};
    Point p1 {+1e5, +1e5, +1e5};
    Centroid c0;

    c0.Update(p0);
    c0.Update(p1);

    ASSERT_NEAR(c0.Centroid().x, 0, 1e-5);
    ASSERT_NEAR(c0.Centroid().y, 0, 1e-5);
    ASSERT_NEAR(c0.Centroid().z, 0, 1e-5);
  } while (0);
}

TEST(CentroidPoint, VoxelContainer) {
  using Spec = IV::VoxelSpecifications<Point, 10, 10, 10>;
  using Centroid = IV::CentroidPoint<Spec>;
  using VoxelContainer = IV::VoxelContainer<Spec, Centroid>;

  VoxelContainer container;

  for (ssize_t i = -10; i <= 10; ++i) {
    Point pt;
    pt.x = i;
    pt.y = i;
    pt.z = i;
    container[pt].Update(pt);
  }

  ASSERT_EQ(container.Size(), 21);

  for (const auto& elem: container) {
    auto centroid = elem.second.Centroid();
    ASSERT_NEAR(centroid.x, centroid.y, 1e-5);
    ASSERT_NEAR(centroid.y, centroid.z, 1e-5);
  }
}
