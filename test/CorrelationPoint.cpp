#include <gtest/gtest.h>
#include <Eigen/Eigen>

#include "MetricSpace.hpp"
#include "Point/CorrelationPoint.hpp"

using namespace IV;


template <typename Exporter>
void
debug(Exporter data)
{
  Eigen::EigenSolver<Eigen::Matrix3f> solver(data.CovarianceMatrix());
  LOG(INFO) << data.CovarianceMatrix();
  LOG(INFO) << solver.eigenvalues().real();
  LOG(INFO) << solver.eigenvectors().real();
}

TEST(CorrelationPoint, Test0) {
  using Specification = IV::Specification;
  using Point = typename Specification::Point;

  IV::CorrelationPoint<Specification> crossCorrelation;

  for (size_t j = 0; j < 10; ++j) {
    Point point;
    point.x = 0;
    point.y = j;
    point.z = 0;

    crossCorrelation(point);
  }

  debug(crossCorrelation);
}


TEST(CorrelationPoint, Test1) {
  using Specification = IV::Specification;
  using Point = typename Specification::Point;

  IV::CorrelationPoint<Specification> crossCorrelation;

  for (size_t i = 0; i < 10; ++i)
  for (size_t j = 0; j < 10; ++j) {
    Point point;
    point.x = i;
    point.y = j;
    point.z = 0;

    crossCorrelation(point);
  }

  debug(crossCorrelation);
}

#if 0
TEST(CorrelationPoint, Test2) {
  using Specification = IV::Specification;
  using Point = typename Specification::Point;

  IV::CorrelationPoint<Specification> crossCorrelation;

  // Two lines.
  for (size_t i = 0; i < 10; ++i)
  for (size_t k = 0; k < 10; ++k) {
    Point point;
    point.x = i;
    point.y = 0;
    point.z = k;

    crossCorrelation(point);
  }

  for (size_t j = 0; j < 10; ++j)
  for (size_t k = 0; k < 10; ++k) {
    Point point;
    point.x = 0;
    point.y = j;
    point.z = k;

    crossCorrelation(point);
  }

  // -
  debug(crossCorrelation);
}
#endif

#if 0
TEST(CorrelationPoint, Test2) {
  using Specification = IV::Specification;
  using Point = typename Specification::Point;

  IV::CorrelationPoint<Specification> crossCorrelation;

  // draw box
  for (size_t i = 0; i < 10; ++i) {
    Point point;
    point.x = i;
    point.y = 0;
    point.z = 0;

    crossCorrelation(point);
  }

  for (size_t j = 0; j < 10; ++j) {
    Point point;
    point.x = 0;
    point.y = j;
    point.z = 1;

    crossCorrelation(point);
  }

  LOG(INFO) << crossCorrelation.CovarianceMatrix();
}

TEST(CorrelationPoint, Test3) {
  using Specification = IV::Specification;
  using Point = typename Specification::Point;

  IV::CorrelationPoint<Specification> crossCorrelation;

  // draw box
  for (size_t i = 0; i < 10; ++i)
  for (size_t j = 0; j < 10; ++j) {
    Point point;
    point.x = i;
    point.y = j;
    point.z = 0;

    crossCorrelation(point);
  }

  LOG(INFO) << crossCorrelation.CovarianceMatrix();
}


TEST(CorrelationPoint, Test4) {
  using Specification = IV::Specification;
  using Point = typename Specification::Point;

  IV::CorrelationPoint<Specification> crossCorrelation;

  // draw dense sphere
  for (double t = -M_PI; t < +M_PI; t += .1)
  for (double p = -M_PI; p < +M_PI; p += .1)
  for (double r = 0; r < 1; r += .25) {
    Point point;
    point.x = r * std::sin(p) * std::cos(t);
    point.y = r * std::sin(p) * std::sin(t);
    point.z = r * std::cos(t);

    crossCorrelation(point);
  }

  LOG(INFO) << crossCorrelation.CovarianceMatrix();
}
#endif
