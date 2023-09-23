#include <gtest/gtest.h>

#include "Specification.hpp"
#include "Quantization.hpp"

#include <glog/logging.h>


TEST(MetricSpace, Simple) {
  using Specification = IV::Specification;
  using Point = typename Specification::Point;
  using Quantizer = IV::Quantizer<Specification>;

  Quantizer quantizer(1.0);

  for (ssize_t i = -100; i <= +100; ++i)
  for (ssize_t j = -100; j <= +100; ++j)
  for (ssize_t k = -100; k <= +100; ++k) {
    Point pt;
    pt.x = i;
    pt.y = j;
    pt.z = k;

    auto index = quantizer.MapPoint(pt);
    ASSERT_EQ(index.ijk.i, i);
    ASSERT_EQ(index.ijk.j, j);
    ASSERT_EQ(index.ijk.k, k);
  }
}

TEST(MetricSpace, Quantized) {
  using Specification = IV::Specification;
  using Point = typename Specification::Point;
  using Quantizer = IV::Quantizer<Specification>;

  Quantizer quantizer(0.01);

  for (ssize_t i = -5; i <= +5; ++i)
  for (ssize_t j = -5; j <= +5; ++j)
  for (ssize_t k = -1; k <= +1; ++k) {
    Point pt;
    pt.x = i;
    pt.y = j;
    pt.z = k;

    auto index = quantizer.MapPoint(pt);

    ASSERT_EQ(index.ijk.i, i * (1 / .01))
        << "<" << i << ", " << j << ", " << k << ">" << "::"
        << "<" << index.ijk.i << ", "
               << index.ijk.j << ", "
               << index.ijk.k << ">";
    ASSERT_EQ(index.ijk.j, j * (1 / .01))
        << "<" << i << ", " << j << ", " << k << ">" << "::"
        << "<" << index.ijk.i << ", "
               << index.ijk.j << ", "
               << index.ijk.k << ">";
    ASSERT_EQ(index.ijk.k, k * (1 / .01))
        << "<" << i << ", " << j << ", " << k << ">" << "::"
        << "<" << index.ijk.i << ", "
               << index.ijk.j << ", "
               << index.ijk.k << ">";
  }
}

