#ifndef DETAIL_RUNNING_REGRESSION_HPP_
#define DETAIL_RUNNING_REGRESSION_HPP_

#include <cmath>
#include <limits>
#include <glog/logging.h>
#include "detail/RunningAverage.hpp"


namespace IV { namespace detail {
template <typename Number>
class RunningRegression {
public:
  RunningRegression()
    : S_ij(0) {}

  void
  operator()(Number i, Number j)
  {
    if (iRunning.Initialized())
      S_ij += ((iRunning.Mean() - i) * (jRunning.Mean() - j))
            * (Number(Size()) / Number(Size() + 1));

    iRunning(i);
    jRunning(j);
  }

  std::size_t
  Size() const
  {
    DCHECK_EQ(iRunning.Size(), jRunning.Size());
    return iRunning.Size();
  }

  Number
  Slope() const
  {
    auto S_ii = iRunning.Variance() * (Number(Size()) - 1.0);
    return S_ij / S_ii;
  }

  Number
  Intercept() const
  {
    return jRunning.Mean() - (Slope() * iRunning.Mean());
  }

  Number
  CovarianceII() const
  {
    return std::pow(iRunning.Variance(), 2);
  }

  Number
  CovarianceIJ() const
  {
    return S_ij / (Size() - 1);
  }

  Number
  CovarianceJJ() const
  {
    return std::pow(jRunning.Variance(), 2);
  }

  Number
  Covariance() const
  {
    return CovarianceIJ();
  }

  Number
  Correlation() const
  {
    auto c = iRunning.StandardDeviation()
           * jRunning.StandardDeviation();

    if (c <= std::numeric_limits<Number>::epsilon())
      return 0;
    else
      return S_ij / ((Size() - 1) * c);
  }

private:
  RunningAverage<Number> iRunning;
  RunningAverage<Number> jRunning;
  Number S_ij;
};
} // ns detail
} // ns IV


#endif // DETAIL_RUNNING_REGRESSION_HPP_
