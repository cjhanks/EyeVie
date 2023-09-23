#include <gtest/gtest.h>
#include <glog/logging.h>

#include "detail/RunningRegression.hpp"

using namespace IV::detail;

TEST(RunningRegression, Test0) {
  RunningRegression<double> reg;

  for (size_t i = 2; i < 12; ++i) {
    reg(i, i);
  }

  ASSERT_NEAR(reg.Slope(), 1.0, 1e-9);
  ASSERT_NEAR(reg.Intercept(), 0.0, 1e-9);
}

TEST(RunningRegression, Test1) {
  RunningRegression<double> reg;

  for (size_t i = 2; i < 12; ++i) {
    reg(i, i + 5);
  }

  ASSERT_NEAR(reg.Slope(), 1.0, 1e-9);
  ASSERT_NEAR(reg.Intercept(), 5.0, 1e-9);
}

TEST(RunningRegression, Test2) {
  RunningRegression<double> reg;

  for (size_t i = 2; i < 12; ++i) {
    reg(i, i * 2);
  }

  ASSERT_NEAR(reg.Slope(), 2.0, 1e-9);
  ASSERT_NEAR(reg.Intercept(), 0.0, 1e-9);
}

TEST(RunningRegression, Test3) {
  RunningRegression<double> reg;

  for (size_t i = 2; i < 12; ++i) {
    reg(i, i * 2 + 5);
  }

  ASSERT_NEAR(reg.Slope(), 2.0, 1e-9);
  ASSERT_NEAR(reg.Intercept(), 5.0, 1e-9);
}

TEST(RunningRegression, Test4) {
  RunningRegression<double> reg;

  for (ssize_t i = 2; i < 12; ++i) {
    reg(i, -i);
  }

  ASSERT_NEAR(reg.Slope(), -1.0, 1e-9);
  ASSERT_NEAR(reg.Intercept(), 0.0, 1e-9);
}


TEST(RunningRegression, Test5) {
  RunningRegression<double> reg;

  for (ssize_t i = 2; i < 12; ++i) {
    reg(i, -i + 5);
  }

  ASSERT_NEAR(reg.Slope(), -1.0, 1e-9);
  ASSERT_NEAR(reg.Intercept(), 5.0, 1e-9);
}

TEST(RunningRegression, Test6) {
  RunningRegression<double> reg;

  for (ssize_t i = 2; i < 12; ++i) {
    reg(i, 5);
  }

  ASSERT_NEAR(reg.Slope(), 0.0, 1e-9);
  ASSERT_NEAR(reg.Intercept(), 5.0, 1e-9);
}
