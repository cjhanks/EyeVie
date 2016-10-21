#include <gtest/gtest.h>
#include <vector>
#include <type_traits>

#include "CentroidPoint.hpp"
#include "VoxelGrid.hpp"


struct Point {
  double x;
  double y;
  double z;

  struct {} data;
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
