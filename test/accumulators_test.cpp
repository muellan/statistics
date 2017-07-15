/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2016 André Müller
 *
 *****************************************************************************/

#include "initial.h"
#include "min.h"
#include "max.h"
#include "total.h"
#include "current.h"
#include "moments.h"
#include "min_max_moments.h"

#include <iostream>
#include <vector>


using namespace am::stat;


//-------------------------------------------------------------------
template<class T>
void fp_accumulation()
{
    static_assert(std::is_floating_point<T>::value,
        "test expects builtin floating point type");

    using std::abs;
    constexpr auto eps = 0.1;

    initial_value_accumulator<T> iniacc;
    current_value_accumulator<T> curacc;
    reversible_min_accumulator<T> minacc;
    reversible_max_accumulator<T> maxacc;
    sum_accumulator<T> sumacc;
    compensated_sum_accumulator<T> csumacc;
    moments_accumulator<T,4> m4acc;
    min_max_moments_reversible_accumulator<T,4> mmm;

    auto v = std::vector<T>{
        1, 2, 3, 10, 11, T(2.5), 3, 4, T(6.6), T(8.92), T(15.1), 18, 13, 14,
        T(1.0), 20, 0, T(0.01), T(19.99), T(5.2), T(1.001), T(5.0)};

    for(const auto y : v)
    {
        auto x = static_cast<T>(y);
        iniacc += x;
        curacc += x;
        minacc += x;
        maxacc += x;
        sumacc += x;
        csumacc += x;
        m4acc += x;
        mmm += x;
    }
    
    if(!(abs(iniacc.result() -  1) < eps)) {
        throw std::logic_error("initial_value_accumulator result");
    }

    if(!(abs(curacc.result() -  5) < eps)) {
        throw std::logic_error("current_value_accumulator result");
    }

    if(!(abs(minacc.result() -  0) < eps) &&
        (abs(minacc.result() - mmm.min()) < eps))
    {
        throw std::logic_error("reversible_min_accumulator result");
    }
    if(!(abs(maxacc.result() -  20) < eps) &&
        (abs(maxacc.result() - mmm.max()) < eps))
    {
        throw std::logic_error("reversible_max_accumulator result");
    }

    if(!(abs(sumacc.result() -  164.321) < eps) &&
        (abs(sumacc.result() - mmm.sum()) < eps))
    {
        throw std::logic_error("sum_accumulator result");
    }

    if(!(abs(csumacc.result() -  164.321) < eps) &&
        (abs(csumacc.result() - mmm.sum()) < eps))
    {
        throw std::logic_error("compensated_sum_accumulator result");
    }

    if(!(  (abs(m4acc.raw_moment_1() - 7.46914) < eps)
        && (abs(m4acc.raw_moment_2() - 98.1831) < eps)
        && (abs(m4acc.raw_moment_3() - 1542.84) < eps)
        && (abs(m4acc.raw_moment_4() - 26287.4) < eps)
        && (abs(m4acc.central_moment_1() - 0) < eps)
        && (abs(m4acc.central_moment_2() - 44.4139) < eps)
        && (abs(m4acc.central_moment_3() - 176.184) < eps)
        && (abs(m4acc.central_moment_4() - 3720.51) < eps))    )
    {
        throw std::logic_error("moments_accumulator_4 results");
    }

    if(!(  (abs(mmm.mean() - 7.46914) < eps)
        && (abs(mmm.raw_moment_2() - 98.1831) < eps)
        && (abs(mmm.raw_moment_3() - 1542.84) < eps)
        && (abs(mmm.raw_moment_4() - 26287.4) < eps)
        && (abs(mmm.variance() - 44.4139) < eps)
        && (abs(mmm.central_moment_3() - 176.184) < eps)
        && (abs(mmm.central_moment_4() - 3720.51) < eps))    )
    {
        throw std::logic_error("min_max_moments_reversible_accumulator results");
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
