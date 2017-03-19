#include <gtest/gtest.h>
#include "detail/Static.hpp"


using namespace IV::detail;


TEST(Static, Test0) {
  struct T0 {
    void
    operator()(double) {}
  };

  struct T1 {
    void
    operator()(double, double) {}
  };

  struct T2 {
    void
    operator()(double, double, double) {}
  };

  ASSERT_TRUE ((HasOp<T0, void(double)>::Yes));
  ASSERT_FALSE((HasOp<T0, void(double, double)>::Yes));
  ASSERT_FALSE((HasOp<T0, void(double, double, double)>::Yes));

  ASSERT_FALSE((HasOp<T1, void(double)>::Yes));
  ASSERT_TRUE ((HasOp<T1, void(double, double)>::Yes));
  ASSERT_FALSE((HasOp<T1, void(double, double, double)>::Yes));

  ASSERT_FALSE((HasOp<T2, void(double)>::Yes));
  ASSERT_FALSE((HasOp<T2, void(double, double)>::Yes));
  ASSERT_TRUE ((HasOp<T2, void(double, double, double)>::Yes));
}

TEST(Static, Test1) {
  struct T0 {
    void
    operator()(double t_) { t = t_; }

    double t;
  };

  struct T1 {
    void
    operator()(double t_, double u_) {
      t = t_;
      u = u_;
    }

    double t, u;
  };

  // -
  T0 t0;
  for (size_t i = 0; i < 100; ++i) {
    PerformOp<T0, void(double)>::Op(t0, i);
    ASSERT_EQ(t0.t, i);
  }
  PerformOp<T0, void(double)>::Op(t0, 3.0);
  PerformOp<T0, void(double, double)>::Op(t0, 4.0, 4.0);
  ASSERT_EQ(t0.t, 3.0);

  // -
  T1 t1;
  for (size_t i = 0; i < 100; ++i) {
    PerformOp<T1, void(double, double)>::Op(t1, i, i);
    ASSERT_EQ(t1.t, i);
    ASSERT_EQ(t1.u, i);
  }

  PerformOp<T1, void(double, double)>::Op(t1, 0.0, 0.0);
  PerformOp<T1, void(double)>::Op(t1, 3.0);
  ASSERT_EQ(t1.t, 0.0);
  ASSERT_EQ(t1.u, 0.0);
}
