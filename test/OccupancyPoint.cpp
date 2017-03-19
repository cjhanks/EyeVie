#include <gtest/gtest.h>
#include <glog/logging.h>

#include "Point.hpp"
#include "Quantization.hpp"
#include "Specification.hpp"


using namespace IV;


TEST(OccupancyPoint, Test0) {
  Quantizer<Specification> q(0.16);

  for (double i = -5; i <= +5; ++i) {
    DefaultPoint pt;
    pt.x = i;
    pt.y = 0;
    pt.z = 0;

    auto corner = q.Corner(pt);
    LOG(INFO) << corner.x << ":" << pt.x;
  }

  //OccupancyPoint<Specification, 4, 4, 4> pt;
}
