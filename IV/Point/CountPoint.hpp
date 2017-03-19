#ifndef IV_POINTS_COUNT_POINT_HPP_
#define IV_POINTS_COUNT_POINT_HPP_

#include <cstring>


namespace IV {
template <typename Specification>
class CountPoint {
public:
  CountPoint()
    : count(0) {}

  void
  operator()()
  { ++count; }

  std::size_t
  Count() const
  { return count; }

  operator std::size_t() const
  { return count; }

private:
  std::size_t count;
};

} // ns IV

#endif // IV_POINTS_COUNT_POINT_HPP_
