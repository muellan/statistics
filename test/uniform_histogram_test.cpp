/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2016 André Müller
 *
 *****************************************************************************/

#include "../include/uniform_histogram.h"

#include <iostream>
#include <random>
#include <functional>


using namespace am::stat;


//-------------------------------------------------------------------
template<class T>
void fp_accumulation()
{
    static_assert(std::is_floating_point<T>::value,
        "test expects builtin floating point type");

    using std::abs;
    constexpr auto eps = 0.1;

    auto uh = uniform_histogram<T>{0, 20, 0.5};

    auto v = std::vector<T>{
        1, 2, 3, 10, 11, T(2.5), 3, 4, T(6.6), T(8.92), T(15.1), 18, 13, 14,
        T(1.0), 20, 0, T(0.01), T(19.99), T(5.2), T(1.001), T(5.0)};

    for(const auto y : v) {
        uh.insert(static_cast<T>(y));
    }
   
    if( !( (abs(uh.total() - 21) < eps)
        && (abs(uh.size() - 40) < eps)
        && (abs(uh[ 0] - 2) < eps)
        && (abs(uh[ 1] - 0) < eps)
        && (abs(uh[ 2] - 3) < eps)
        && (abs(uh[ 3] - 0) < eps)
        && (abs(uh[ 4] - 1) < eps)
        && (abs(uh[ 5] - 1) < eps)
        && (abs(uh[ 6] - 2) < eps)
        && (abs(uh[ 7] - 0) < eps)
        && (abs(uh[ 8] - 1) < eps)
        && (abs(uh[ 9] - 0) < eps)
        && (abs(uh[10] - 2) < eps)
        && (abs(uh[11] - 0) < eps)
        && (abs(uh[12] - 0) < eps)
        && (abs(uh[13] - 1) < eps)
        && (abs(uh[14] - 0) < eps)
        && (abs(uh[15] - 0) < eps)
        && (abs(uh[16] - 0) < eps)
        && (abs(uh[17] - 1) < eps)
        && (abs(uh[18] - 0) < eps)
        && (abs(uh[19] - 0) < eps)
        && (abs(uh[20] - 1) < eps)
        && (abs(uh[21] - 0) < eps)
        && (abs(uh[22] - 1) < eps)
        && (abs(uh[23] - 0) < eps)
        && (abs(uh[24] - 0) < eps)
        && (abs(uh[25] - 0) < eps)
        && (abs(uh[26] - 1) < eps)
        && (abs(uh[27] - 0) < eps)
        && (abs(uh[28] - 1) < eps)
        && (abs(uh[29] - 0) < eps)
        && (abs(uh[30] - 1) < eps)
        && (abs(uh[31] - 0) < eps)
        && (abs(uh[32] - 0) < eps)
        && (abs(uh[33] - 0) < eps)
        && (abs(uh[34] - 0) < eps)
        && (abs(uh[35] - 0) < eps)
        && (abs(uh[36] - 1) < eps)
        && (abs(uh[37] - 0) < eps)
        && (abs(uh[38] - 0) < eps)
        && (abs(uh[39] - 1) < eps) ))
    {
        throw std::logic_error("uniform_histogram result");
    }
}



//-------------------------------------------------------------------
int main()
{
    try {
        fp_accumulation<float>();
        fp_accumulation<double>();
        fp_accumulation<long double>();
    }
    catch(std::exception& e) {
        std::cerr << "wrong " << e.what();
        return 1;
    }
}
