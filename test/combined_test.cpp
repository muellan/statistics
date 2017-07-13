/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2016 André Müller
 *
 *****************************************************************************/

#include "../include/combined.h"

#include <iostream>
#include <vector>

using namespace am::stat;

//-------------------------------------------------------------------
void test_combined_accumulation()
{
    stat::combined_accumulator<
        stat::initial_value_accumulator<double>,
        stat::current_value_accumulator<double>,
        stat::reversible_min_accumulator<double>,
        stat::reversible_max_accumulator<double>,
        stat::sum_accumulator<double>,
        stat::compensated_sum_accumulator<double>,
        stat::moments_accumulator<double,4>,
        stat::uniform_histogram_accumulator<double>
    > a;

    auto v = std::vector<double>{
        1.0, 2.0, 3.0, 10.0, 11.0, 2.5, 3.0, 4.0, 6.6, 8.92, 15.1, 18.0, 13.0,
        14.0, 1.0, 20.0, 0.0, 0.01, 19.99, 5.2, 1.001, 5.0};

    for(const auto x : v) {
        a += x;
    }

}


//-------------------------------------------------------------------
int main()
{
    try {
        test_combined_accumulation();
    }
    catch(std::exception& e) {
        std::cerr << e.what();
        return 1;
    }
}
