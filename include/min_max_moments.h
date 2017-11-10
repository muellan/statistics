#ifndef AMLIB_STATISTICS_MIN_MAX_MOMENTS_H_
#define AMLIB_STATISTICS_MIN_MAX_MOMENTS_H_


#include "min.h"
#include "max.h"
#include "moments.h"


namespace am {
namespace stat {


/*************************************************************************//****
 *
 * @brief
 *
 *****************************************************************************/
template<
    class Argument,
    int maxMoment = 2,
    class Size = std::uint_least64_t
>
class min_max_moments_accumulator
{
    using moments_acc_t_ = moments_accumulator<Argument,maxMoment,Size>;

public:
    //---------------------------------------------------------------
    using argument_type = Argument;
    using result_type   = typename moments_acc_t_::result_type;
    using size_type     = typename moments_acc_t_::size_type;


    //---------------------------------------------------------------
    void
    clear() {
        min_.clear();
        max_.clear();
        moments_.clear();
    }


    //---------------------------------------------------------------
    min_max_moments_accumulator&
    operator += (const argument_type& x) {
        push(x);
        return *this;
    }

    //-----------------------------------------------------
    void
    push(const argument_type& x) {
        min_ += x;
        max_ += x;
        moments_ += x;
    }


    //---------------------------------------------------------------
    result_type
    min() const {
        return min_.result();
    }
    //-----------------------------------------------------
    result_type
    max() const {
        return max_.result();
    }


    //---------------------------------------------------------------
    size_type
    size() const {
        return moments_.size();
    }


    //---------------------------------------------------------------
    // 1st order
    //---------------------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 0),T>::type>
    result_type
    sum() const {
        return moments_.sum();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 0),T>::type>
    result_type
    mean() const {
        return moments_.mean();
    }


    //---------------------------------------------------------------
    // 2nd order
    //---------------------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 1),T>::type>
    result_type
    sum_2() const {
        return moments_.sum_2();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 1),T>::type>
    result_type
    raw_moment_2() const {
        return moments_.raw_moment_2();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 1),T>::type>
    result_type
    central_moment_2() const {
        return moments_.central_moment_2();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 1),T>::type>
    result_type
    variance() const {
        return moments_.variance();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 1),T>::type>
    result_type
    stddev() const {
        return moments_.stddev();
    }


    //---------------------------------------------------------------
    // 3rd order
    //---------------------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 2),T>::type>
    result_type
    sum_3() const {
        return moments_.sum_3();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 2),T>::type>
    result_type
    raw_moment_3() const {
        return moments_.raw_moment_3();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 2),T>::type>
    result_type
    central_moment_3() const {
        return moments_.central_moment_3();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 2),T>::type>
    result_type
    skewness() const {
        return moments_.skewness();
    }


    //---------------------------------------------------------------
    // 4th order
    //---------------------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 3),T>::type>
    result_type
    sum_4() const {
        return moments_.sum_4();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 3),T>::type>
    result_type
    raw_moment_4() const {
        return moments_.raw_moment_4();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 3),T>::type>
    result_type
    central_moment_4() const {
        return moments_.central_moment_4();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 3),T>::type>
    result_type
    kurtosis() const {
        return moments_.kurtosis();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 3),T>::type>
    result_type
    kurtosis_excess() const {
        return moments_.kurtosis_excess();
    }


private:
    min_accumulator<argument_type> min_;
    max_accumulator<argument_type> max_;
    moments_acc_t_ moments_;
};






/*****************************************************************************
 *
 *
 *
 *
 *****************************************************************************/
template<class Argument, int maxMoment = 2, class Size = std::uint_least64_t>
class reversible_min_max_moments_accumulator
{
    using moments_acc_t_ = moments_accumulator<Argument,maxMoment,Size>;

public:
    //---------------------------------------------------------------
    using argument_type = Argument;
    using result_type = typename moments_acc_t_::result_type;
    using size_type = typename moments_acc_t_::size_type;


    //---------------------------------------------------------------
    void
    clear() {
        min_.clear();
        max_.clear();
        moments_.clear();
    }


    //---------------------------------------------------------------
    reversible_min_max_moments_accumulator&
    operator += (const argument_type& x) {
        push(x);
        return *this;
    }
    //-----------------------------------------------------
    reversible_min_max_moments_accumulator&
    operator -= (const argument_type& x) {
        pop(x);
        return *this;
    }

    //-----------------------------------------------------
    void
    push(const argument_type& x) {
        min_ += x;
        max_ += x;
        moments_ += x;
    }
    //-----------------------------------------------------
    void
    pop(const argument_type& x) {
        min_ -= x;
        max_ -= x;
        moments_ -= x;
    }


    //---------------------------------------------------------------
    result_type
    min() const {
        return min_.result();
    }
    //-----------------------------------------------------
    result_type
    max() const {
        return max_.result();
    }


    //---------------------------------------------------------------
    size_type
    size() const {
        return moments_.size();
    }


    //---------------------------------------------------------------
    // 1st order
    //---------------------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 0),T>::type>
    result_type
    sum() const {
        return moments_.sum();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 0),T>::type>
    result_type
    mean() const {
        return moments_.mean();
    }


    //---------------------------------------------------------------
    // 2nd order
    //---------------------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 1),T>::type>
    result_type
    sum_2() const {
        return moments_.sum_2();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 1),T>::type>
    result_type
    raw_moment_2() const {
        return moments_.raw_moment_2();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 1),T>::type>
    result_type
    central_moment_2() const {
        return moments_.central_moment_2();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 1),T>::type>
    result_type
    variance() const {
        return moments_.variance();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 1),T>::type>
    result_type
    stddev() const {
        return moments_.stddev();
    }


    //---------------------------------------------------------------
    // 3rd order
    //---------------------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 2),T>::type>
    result_type
    sum_3() const {
        return moments_.sum_3();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 2),T>::type>
    result_type
    raw_moment_3() const {
        return moments_.raw_moment_3();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 2),T>::type>
    result_type
    central_moment_3() const {
        return moments_.central_moment_3();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 2),T>::type>
    result_type
    skewness() const {
        return moments_.skewness();
    }


    //---------------------------------------------------------------
    // 4th order
    //---------------------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 3),T>::type>
    result_type
    sum_4() const {
        return moments_.sum_4();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 3),T>::type>
    result_type
    raw_moment_4() const {
        return moments_.raw_moment_4();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 3),T>::type>
    result_type
    central_moment_4() const {
        return moments_.central_moment_4();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 3),T>::type>
    result_type
    kurtosis() const {
        return moments_.kurtosis();
    }
    //-----------------------------------------------------
    template<class T = int, class = typename
        std::enable_if<(maxMoment > 3),T>::type>
    result_type
    kurtosis_excess() const {
        return moments_.kurtosis_excess();
    }



private:
    reversible_min_accumulator<argument_type> min_;
    reversible_max_accumulator<argument_type> max_;
    moments_acc_t_ moments_;
};






/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<class T, class Size = std::uint_least64_t>
using min_max_mean_accumulator = min_max_moments_accumulator<T,1,Size>;

template<class T, class Size = std::uint_least64_t>
using min_max_variance_accumulator = min_max_moments_accumulator<T,2,Size>;

template<class T, class Size = std::uint_least64_t>
using min_max_skewness_accumulator = min_max_moments_accumulator<T,3,Size>;

template<class T, class Size = std::uint_least64_t>
using min_max_kurtosis_accumulator = min_max_moments_accumulator<T,4,Size>;



} //namespace stat
}  // namespace am


#endif
