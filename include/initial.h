#ifndef AMLIB_STATISTICS_ACCUMULATE_INITIAL_H_
#define AMLIB_STATISTICS_ACCUMULATE_INITIAL_H_

#include <cstddef>


namespace am {
namespace stat {


/****************************************************************************
 *
 *
 *
 ****************************************************************************/
template<class Arg>
class initial_value_accumulator
{
public:
    //---------------------------------------------------------------
    using argument_type = Arg;
    using result_type = Arg;
    using size_type = std::size_t;


    //---------------------------------------------------------------
    constexpr
    initial_value_accumulator():
        cur_{}, cleared_(true)
    {}
    //-----------------------------------------------------
    explicit constexpr
    initial_value_accumulator(const argument_type& init):
        cur_{init}, cleared_(true)
    {}


    //---------------------------------------------------------------
    void
    clear() {
        cleared_ = true;
    }
    //-----------------------------------------------------
    initial_value_accumulator&
    operator = (const argument_type& init) {
        cur_ = init;
        cleared_ = true;
        return *this;
    }


    //---------------------------------------------------------------
    initial_value_accumulator&
    operator += (const argument_type& x) {
        push(x);
        return *this;
    }
    //-----------------------------------------------------
    void
    push(const argument_type& x) {
        if(cleared_) {
            cur_ = x;
            cleared_ = false;
        }
    }


    //---------------------------------------------------------------
    const result_type&
    result() const {
        return cur_;
    }

    //-----------------------------------------------------
    size_type
    size() const {
        return (cleared_ ? 0 : 1);
    }
    //-----------------------------------------------------
    bool
    empty() const {
        return !cleared_;
    }


private:
    //---------------------------------------------------------------
    argument_type cur_;
    bool cleared_;
};



} //namspace stat
}  // namespace am

#endif
