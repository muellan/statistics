#ifndef AMLIB_STATISTICS_EXTRACT_TOTAL_H_
#define AMLIB_STATISTICS_EXTRACT_TOTAL_H_


#include <type_traits>
#include <numeric>


namespace am {
namespace stat {


/*************************************************************************//***
 *
 * @brief sum of iterator range
 *
 ****************************************************************************/
template<class InputIterator>
inline auto
sum(InputIterator begin, InputIterator end)
{
    using res_t = std::decay_t<decltype(*begin)>;
    return std::accumulate(begin,  end, res_t(0));
}



/*************************************************************************//***
 *
 * @brief compute sum of iterator range using Kahan summation algorithm
 *
 *****************************************************************************/
template<class InputIterator>
inline auto
sum_kahan(InputIterator begin, InputIterator end)
{
    using res_t = std::decay_t<decltype(*begin)>;

    auto sum = res_t(0);
    auto err = res_t(0);

    for(; begin != end; ++begin) {
        const auto y =  *begin - err;
        const auto t = sum + y;
        err = (t - sum) - y;
        sum = t;
    }

    return sum;
}




/*************************************************************************//***
 *
 * @brief sum accumulator
 *
 ****************************************************************************/
template<class Arg>
class sum_accumulator
{
public:
    //---------------------------------------------------------------
    using argument_type = Arg;
    using result_type = Arg;


    //---------------------------------------------------------------
    constexpr
    sum_accumulator():
        tot_(0)
    {}
    //-----------------------------------------------------
    explicit constexpr
    sum_accumulator(const argument_type& init):
        tot_(init)
    {}
    //-----------------------------------------------------
    sum_accumulator(const sum_accumulator&) = default;


    //---------------------------------------------------------------
    void
    clear() {
        tot_ = argument_type(0);
    }
    //-----------------------------------------------------
    sum_accumulator&
    operator = (const argument_type& x) {
        tot_ = x;
        return *this;
    }


    //---------------------------------------------------------------
    sum_accumulator&
    operator += (const argument_type& x) {
        push(x);
        return *this;
    }
    //-----------------------------------------------------
    sum_accumulator&
    operator -= (const argument_type& x) {
        pop(x);
        return *this;
    }


    //---------------------------------------------------------------
    void
    push(const argument_type& x) {
        tot_ += x;
    }
    //-----------------------------------------------------
    void
    pop(const argument_type& x) {
        tot_ -= x;
    }


    //---------------------------------------------------------------
    const result_type&
    result() const {
        return tot_;
    }
    //-----------------------------------------------------
    const result_type&
    sum() const {
        return tot_;
    }


private:
    argument_type tot_;
};






/****************************************************************************
 *
 * @brief compensated sum accumulator
 *        computes running sum using the Kahan summation algorithm
 *
 ****************************************************************************/
template<class Arg>
class compensated_sum_accumulator
{
public:
    //---------------------------------------------------------------
    using argument_type = Arg;
    using result_type = Arg;


    //---------------------------------------------------------------
    constexpr
    compensated_sum_accumulator():
        tot_(0),
        err_(0)
    {}
    //-----------------------------------------------------
    explicit constexpr
    compensated_sum_accumulator(const argument_type& init):
        tot_(init),
        err_(0)
    {}


    //---------------------------------------------------------------
    void
    clear() {
        tot_ = argument_type(0);
        err_ = argument_type(0);
    }
    //-----------------------------------------------------
    compensated_sum_accumulator&
    operator = (const argument_type& x) {
        tot_ = x;
        err_ = static_cast<argument_type>(0);
        return *this;
    }


    //---------------------------------------------------------------
    compensated_sum_accumulator&
    operator += (const argument_type& x) {
        push(x);
        return *this;
    }
    //-----------------------------------------------------
    compensated_sum_accumulator&
    operator -= (const argument_type& x) {
        pop(x);
        return *this;
    }


    //---------------------------------------------------------------
    void
    push(const argument_type& x) {
        const auto y = x - err_;
        const auto t = tot_ + y;

        err_ = (t - tot_) - y;
        tot_ = t;
    }
    //-----------------------------------------------------
    void
    pop(const argument_type& x) {
        push(-x);
    }


    //---------------------------------------------------------------
    const result_type&
    sum() const {
        return tot_;
    }
    //-----------------------------------------------------
    const result_type&
    result() const {
        return tot_;
    }


private:
    argument_type tot_, err_;
};





/*****************************************************************************
 *
 *
 *****************************************************************************/
template<class Arg>
inline decltype(auto)
result(const sum_accumulator<Arg>& a) {
    return a.result();
}

template<class Arg>
inline decltype(auto)
result(const compensated_sum_accumulator<Arg>& a) {
    return a.result();
}


} //namespace stat
}  // namespace am


#endif
