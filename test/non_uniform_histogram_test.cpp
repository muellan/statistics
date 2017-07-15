/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2016 André Müller
 *
 *****************************************************************************/

#include "nonuniform_histogram.h"

#include <iostream>
#include <random>
#include <functional>


using namespace am::stat;


//-------------------------------------------------------------------
int main()
{
    using std::begin;

    auto h = stat::non_uniform_histogram<double>{
        -1.0, -0.5, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.5, 1.0};

    auto rnd = std::bind(
        std::normal_distribution<double>{0.0, 0.5}, std::mt19937{});

    for(int i = 0; i < 1000; ++i) {
        const auto x = rnd();
        h.insert(x);
    }

//    std::cout << h.size() << " " << h.total() <<"\n"<< pretty(h) << std::endl;

}

