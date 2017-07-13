#ifndef AMLIB_STATISTICS_ACCUMULATE_REVERSIBLE_H_
#define AMLIB_STATISTICS_ACCUMULATE_REVERSIBLE_H_


#include <stack>


namespace am {
namespace stat {


/****************************************************************************
 *
 * @brief decorator class adding undo operations (pop, -=, -)
 * to statistics accumulators without history (moving minimum, current, ...)
 *
 ****************************************************************************/
template<class Accumulator>
class reversible
{
public:
    //---------------------------------------------------------------
    using result_type = Accumulator;
    using argument_type = typename Accumulator::argument_type;
    using value_type = argument_type;


    //---------------------------------------------------------------
    reversible():
        Accumulator{}, stack_{}
    {}
    //-----------------------------------------------------
    explicit
    reversible(const argument_type& v):
        Accumulator{v}, stack_{v}
    {}


    //---------------------------------------------------------------
    void
    clear() {
        acc_.clear();
        stack_.clear();
    }
    //-----------------------------------------------------
    reversible&
    operator = (const argument_type& x) {
        acc_ = (x);
        stack_.push(x);
        return *this;
    }


    //---------------------------------------------------------------
    reversible&
    operator += (const argument_type& x) {
        acc_ += (x);
        stack_.push(x);
        return *this;
    }
    //-----------------------------------------------------
    reversible&
    push(const argument_type& x) {
        acc_ += (x);
        stack_.push(x);
        return *this;
    }


    //---------------------------------------------------------------
    const argument_type&
    top() const noexcept {
        return stack_.top();
    }

    //---------------------------------------------------------------
    bool
    pop() {
        if(stack_.empty()) return false;
        acc_ = stack_.top();
        stack_.pop();
        return true;
    }


    //---------------------------------------------------------------
    const result_type&
    result() const noexcept {
        return acc_;
    }


private:
    Accumulator acc_;
    std::stack<argument_type> stack_;
};



//-------------------------------------------------------------------
template<>
class reversible<void>
{};


} //namespace stat
}  // namespace am


#endif
