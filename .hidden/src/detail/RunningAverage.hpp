#ifndef RUNNING_AVERAGE_H_
#define RUNNING_AVERAGE_H_

#include <cmath>


namespace IV { namespace detail {
template <typename Scalar>
class RunningAverage {
public:
	RunningAverage()
		: previous_M(0)
		, previous_S(0)
		, current_M(0)
		, current_S(0)
		, number_of_elements(0)
	{}

	void
	operator()(Scalar value)
	{
		bool initialized = (number_of_elements != 0);

		++number_of_elements;
		if (!initialized) {
			previous_M = current_M = value;
			previous_S = Scalar(0);
		} else {
			current_M = previous_M
			          + (value - previous_M) / number_of_elements;
			current_S = previous_S
				  + (value - previous_M) * (value - current_M);

			previous_M = current_M;
			previous_S = current_S;
		}

	}

	Scalar
	mean() const
	{ return current_M; }

	Scalar
	variance() const
	{
		if (number_of_elements > 1) {
			return current_S / (number_of_elements - 1);
		} else {
			return Scalar(0);

		}
	}

	Scalar
	stdev() const
	{
		return std::sqrt(variance());
	}

	size_t
	size() const
	{
		return number_of_elements;
	}

private:
	Scalar previous_M;
	Scalar previous_S;
	Scalar current_M;
	Scalar current_S;
	size_t number_of_elements;
};

} // ns detail
} // ns IV

#endif // RUNNING_AVERAGE_H_
