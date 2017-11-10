/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2016 André Müller
 *
 *****************************************************************************/

#include "combined.h"
#include "initial.h"
#include "current.h"
#include "min_max_moments.h"
#include "total.h"
#include "histogram_accumulator.h"

#include <iostream>
#include <vector>

//-------------------------------------------------------------------
void test_combined_accumulation()
{
    using namespace am;
    using namespace am::stat;

    combined_accumulator<
        initial_value_accumulator<double>,
        current_value_accumulator<double>,
        reversible_min_accumulator<double>,
        reversible_max_accumulator<double>,
        sum_accumulator<double>,
        compensated_sum_accumulator<double>,
        moments_accumulator<double,4>,
        uniform_histogram_accumulator<double>
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
