#ifndef AMLIB_STATISTICS_PARTIAL_SUMS_H_
#define AMLIB_STATISTICS_PARTIAL_SUMS_H_


#include <vector>
#include <cstdint>
#include <limits>
#include <type_traits>


namespace am {
namespace stat {


/*****************************************************************************
 *
 * @brief    efficiently query partial sums on a mutable vector of integers
 *
 * @details  implemented as Fenwick tree
 *
 *****************************************************************************/
template<class IntegralT = std::int_least64_t>
class partial_sum_counter
{
    static_assert(std::is_integral<IntegralT>::value &&
                  std::is_signed<IntegralT>::value,
        "partial_sum_accumulator<T>: T must be a signed builtin integral type");

public:
    //---------------------------------------------------------------
    using argument_type = IntegralT;
    using size_type = argument_type;


    //---------------------------------------------------------------
    constexpr
    partial_sum_counter():
        store_{}
    {}
    //-----------------------------------------------------
    explicit constexpr
    partial_sum_counter(size_type size):
        store_(size, 0)
    {}


    //---------------------------------------------------------------
    void
    reserve(size_type size) {
        if(size > 0) store_.reserve(size);
    }
    void
    resize(size_type size) {
        if(size > 0) store_.resize(size, argument_type(0));
    }


    //---------------------------------------------------------------
    /// @brief increases the value of k-th element by inc.
    void
    increase(size_type idx, argument_type inc = 1) {
        for(; idx < static_cast<size_type>(store_.size()); idx |= idx + 1) {
            store_[idx] += inc;
        }
    }


    //---------------------------------------------------------------
    size_type
    size() const noexcept {
        return store_.size();
    }

    //-----------------------------------------------------
    /// @brief returns the frequency of one element
    argument_type
    operator [] (size_type idx) const noexcept {
        return total(idx,idx);
    }


    //-----------------------------------------------------
    /// @brief returns the total of elements in index range [0,idx]
    argument_type
    total(size_type idx) const noexcept {
        auto s = argument_type(0);
        for(; idx >= 0; idx = (idx & (idx + 1)) - 1) {
          s += store_[idx];
        }
        return s;
    }
    //-----------------------------------------------------
    /// @brief returns the total of elements in index range [a,b]
    argument_type
    total(size_type a, size_type b) const {
        return ((a == 0) ? total(b) : (total(0, b) - total(0, a-1)) );
    }

private:
    //store_[i] = total of elements in index range [i&(i+1), i]
    std::vector<IntegralT> store_;
};



}  // namespace stat
}  // namespace am


#endif
