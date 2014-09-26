#include <iostream>
#include <boost/random.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include "parameter.h"

__int64 GetTimeStamp()
{
	namespace pt = boost::posix_time;
	namespace gg = boost::gregorian;

	typedef boost::date_time::c_local_adjustor<pt::ptime> local_adj;

	auto epoch = local_adj::utc_to_local(pt::ptime(gg::date(1970, 1, 1)));
	auto diff = pt::microsec_clock::local_time() - epoch;

	return diff.total_microseconds();
}

int *initialize(int min, int max)
{
	boost::random::mt19937 gen(GetTimeStamp());
	boost::random::uniform_int_distribution<> dist(min, max);

	int result[RANDOM_MAX];

	for(int i=0; i<RANDOM_MAX; i++)
	{
		result[i] = dist(gen);
	}

	return result;
}

int main()
{
	int *result;

	result = initialize(-90, 90);


	for(int i=0; i<RANDOM_MAX; i++)
	{
		std::cout << "result:" << result[i] << std::endl;
	}

	return 0;
}