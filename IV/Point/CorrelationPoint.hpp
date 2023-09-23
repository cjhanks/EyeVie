#ifndef IV_CORRELATION_CENTROID_HPP_
#define IV_CORRELATION_CENTROID_HPP_

#include <Eigen/Eigen>
#include <glog/logging.h>

#include "detail/RunningRegression.hpp"


namespace IV {
template <typename Specification>
class CorrelationPoint {
public:
  using Point = typename Specification::Point;
  using PointAccessor = typename Specification::PointAccessor;
  using Number = typename Point::Number;
  using Matrix = Eigen::Matrix<Number, 3, 3>;
  using Vector = Eigen::Matrix<Number, 3, 1>;

  void
  operator()(Point point)
  {
    const auto& x = PointAccessor::GetX(point);
    const auto& y = PointAccessor::GetY(point);
    const auto& z = PointAccessor::GetZ(point);

    xy(x, y);
    xz(x, z);
    yz(y, z);
  }

  Matrix
  CovarianceMatrix() const
  {
    // -
    auto cxx = xy.CovarianceII();
    auto cxy = xy.CovarianceIJ();
    auto cxz = xz.CovarianceJJ();

    // -
    auto cyx = cxy;
    auto cyy = yz.CovarianceII();
    auto cyz = yz.CovarianceIJ();

    // -
    auto czx = cxz;
    auto czy = cyz;
    auto czz = yz.CovarianceJJ();

    // =
    Matrix m;
    m << cxx, cxy, cxz,
         cyx, cyy, cyz,
         czx, czy, czz;
    return m;
  }

  Matrix
  CorrelationMatrix() const
  {
    auto cxy = xy.Correlation();
    auto cxz = xz.Correlation();
    auto cyz = yz.Correlation();

    Matrix m;
    m <<  1, cxy,  cxz,
        cxy,   1,  cyz,
        cxz, cxy,    1;
    return m;
  }

  std::size_t
  Size() const
  {
    DCHECK_EQ(xy.Size(), xz.Size());
    DCHECK_EQ(xz.Size(), yz.Size());
    return xy.Size();
  }

private:
  detail::RunningRegression<Number> xy;
  detail::RunningRegression<Number> xz;
  detail::RunningRegression<Number> yz;
};
} // ns IV

#endif // IV_CORRELATION_CENTROID_HPP_
