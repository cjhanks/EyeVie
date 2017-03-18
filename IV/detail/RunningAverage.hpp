#ifndef DETAIL_RUNNING_AVERAGE_HPP_
#define DETAIL_RUNNING_AVERAGE_HPP_

#include <cmath>
#include <glog/logging.h>


namespace IV { namespace detail {
template <typename Number>
class RunningAverage {
public:
  RunningAverage()
    : prevM(0)
    , prevS(0)
    , currM(0)
    , currS(0)
    , count(0)
  {}

  void
  operator()(Number value)
  {
    bool initialized = Initialized();
    ++count;

    if (initialized) {
      currM = prevM + (value - prevM) / count;
      currS = prevS + (value - prevM) * (value - currM);

      prevM = currM;
      prevS = currS;
    } else {
      prevM = currM = value;
      prevS = 0;
    }
  }

  bool
  Initialized() const
  { return Size() != 0; }

  std::size_t
  Size() const
  { return count; }

  Number
  Mean() const
  {
    DCHECK(Initialized());
    return currM;
  }

  Number
  Variance() const
  {
    DCHECK(Initialized());
    if (Size() > 1)
      return currS / (Size() - 1);
    else
      return 0;
  }

  Number
  StandardDeviation() const
  {
    return std::sqrt(Variance());
  }

private:
  Number prevM;
  Number prevS;
  Number currM;
  Number currS;
  std::size_t count;
};
} // ns detail
} // ns IV

#endif // DETAIL_RUNNING_AVERAGE_HPP_
