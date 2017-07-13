#ifndef AMLIB_STATISTICS_EXPECTANCY_ACCUMULATOR_H_
#define AMLIB_STATISTICS_EXPECTANCY_ACCUMULATOR_H_

#include <cstddef>
#include <type_traits>
#include <array>
#include <utility>


namespace am {
namespace stat {


/****************************************************************************
 *
 *
 *
 ****************************************************************************/
template<
    std::size_t n,
    class NumberT = double,
    class SampleSize = std::size_t
>
class expectancy_accumulator
{
public:

    //---------------------------------------------------------------
    using size_type = std::size_t;
    //-----------------------------------------------------
    using numeric_type = NumberT;
    using floating_point_type = std::common_type_t<NumberT,double>;
    //-----------------------------------------------------
    using argument_type = std::pair<std::size_t,numeric_type>;
    using result_type = std::array<floating_point_type,n>;


    //---------------------------------------------------------------
    constexpr
    expectancy_accumulator():
        n_(0), totRes_(0), count_(0), res_(0)
    {}
    //-----------------------------------------------------
    explicit
    expectancy_accumulator(const argument_type& init):
        n_(0), totRes_{init.second}, count_(0), res_(0)
    {
        count_[init.first] = 0;
        res_[init.first] = init.second;
    }


    //---------------------------------------------------------------
    void
    clear() {
        n_ = 0;
        totRes_ = 0;
        count_ = 0;
        res_ = 0;
    }
    //-----------------------------------------------------
    expectancy_accumulator&
    operator = (const argument_type& init) {
        n_ = 0;
        totRes_ = init.second;
        count_[init.first] = 0;
        res_[init.first] = init.second;
        return *this;
    }


    //---------------------------------------------------------------
    expectancy_accumulator&
    operator += (const argument_type& x) {
        push(x);
        return *this;
    }
    //-----------------------------------------------------
    void
    push(const argument_type& x) {
        ++n_;
        totRes_ += x.second;
        ++count_[x.first];
        res_[x.first] += x.second;
    }

    //---------------------------------------------------------------
    size_type
    size() const noexcept {
        return n_;
    }

    //-----------------------------------------------------
    const result_type&
    absolute_frequencies() const {
        return count_;
    }

    //-----------------------------------------------------
    result_type
    relative_frequencies() const {
        result_type res;
        for(std::size_t i = 0; i < n;++i) {
            res[i] = count_[i] / static_cast<floating_point_type>(n_);
        }
        return res;
    }

    //-----------------------------------------------------
    floating_point_type
    total_expectancy() const {
        return (totRes_ / static_cast<floating_point_type>(n_));
    }

    //-----------------------------------------------------
    result_type
    expectancies() const {
        result_type res;
        for(std::size_t i = 0; i < n;++i) {
            res[i] = res_[i] / count_[i];
        }
        return res;
    }


private:
    //---------------------------------------------------------------
    size_type n_;
    numeric_type totRes_;
    result_type count_;
    result_type res_;
};



} //namespace stat
}  // namespace am


#endif
