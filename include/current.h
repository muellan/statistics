#ifndef AMLIB_STATISTICS_ACCUMULATORS_CURRENT_H_
#define AMLIB_STATISTICS_ACCUMULATORS_CURRENT_H_

#include <cstddef>


namespace am {
namespace stat {


/****************************************************************************
 *
 *
 *
 ****************************************************************************/
template<class Arg>
class current_value_accumulator
{
public:
    //---------------------------------------------------------------
    using argument_type = Arg;
    using result_type = Arg;
    using size_type = std::size_t;


    //---------------------------------------------------------------
    constexpr
    current_value_accumulator():
        cur_(0)
    {}
    //-----------------------------------------------------
    explicit constexpr
    current_value_accumulator(const argument_type& init):
        cur_{init}
    {}
    //-----------------------------------------------------
    current_value_accumulator(const current_value_accumulator&) = default;


    //---------------------------------------------------------------
    current_value_accumulator&
    operator = (const current_value_accumulator&) = default;

    //-----------------------------------------------------
    current_value_accumulator&
    operator = (const argument_type& x)    {
        cur_ = x;
        return *this;
    }

    //-----------------------------------------------------
    void
    clear() {
        cur_ = argument_type(0);
    }


    //---------------------------------------------------------------
    current_value_accumulator&
    operator += (const argument_type& x) {
        cur_ = x;
        return *this;
    }
    //-----------------------------------------------------
    void
    push(const argument_type& x) {
        cur_ = x;
    }


    //---------------------------------------------------------------
    const result_type&
    result() const {
        return cur_;
    }

    //-----------------------------------------------------
    static size_type
    size() noexcept {
        return 1;
    }
    //-----------------------------------------------------
    static bool
    empty() {
        return false;
    }


private:
    argument_type cur_;
};



/*****************************************************************************
 *
 *
 *****************************************************************************/
template<class Arg>
inline decltype(auto)
result(const current_value_accumulator<Arg>& a) {
    return a.result();
}


} //namspace stat
}  // namespace am


#endif
