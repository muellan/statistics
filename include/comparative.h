#ifndef AMLIB_STATISTICS_COMPARATIVE_TRACER_H_
#define AMLIB_STATISTICS_COMPARATIVE_TRACER_H_

#include <set>


namespace am {
namespace stat {


/****************************************************************************
 *
 *
 *
 ****************************************************************************/
template<
    class Arg,
    class Comparator
>
class comparative_accumulator
{
public:
    //---------------------------------------------------------------
    using comparator = Comparator;
    using argument_type = Arg;
    using result_type = Arg;


    //---------------------------------------------------------------
    constexpr
    comparative_accumulator() = default;
    //-----------------------------------------------------
    explicit constexpr
    comparative_accumulator(const argument_type& init):
        cur_{init}, comp_{}
    {}
    //-----------------------------------------------------
    explicit constexpr
    comparative_accumulator(
        const argument_type& init, const comparator& comp)
    :
        cur_{init}, comp_{comp}
    {}


    //---------------------------------------------------------------
    comparative_accumulator&
    operator = (const comparative_accumulator&) = default;
    //-----------------------------------------------------
    comparative_accumulator&
    operator = (const argument_type& x) {
        cur_ = x;
        return *this;
    }


    //---------------------------------------------------------------
    comparative_accumulator&
    operator += (const argument_type& x) {
        push(x);
        return *this;
    }
    //-----------------------------------------------------
    void
    push(const argument_type& x) {
        if(comp_(x, cur_)) {
            cur_ = x;
        }
    }


    //---------------------------------------------------------------
    const result_type&
    result() const {
        return cur_;
    }


private:
    argument_type cur_;
    comparator comp_;
};






/****************************************************************************
 *
 *
 *
 ****************************************************************************/
template<
    class Arg,
    class Comparator
>
class reversible_comparative_accumulator
{
public:
    //---------------------------------------------------------------
    using comparator = Comparator;
    using argument_type = Arg;
    using result_type = Arg;


    //---------------------------------------------------------------
    constexpr
    reversible_comparative_accumulator() = default;
    //-----------------------------------------------------
    explicit
    reversible_comparative_accumulator(const argument_type& init):
        pq_{init}
    {}


    //---------------------------------------------------------------
    reversible_comparative_accumulator&
    operator = (const reversible_comparative_accumulator&) = default;
    //-----------------------------------------------------
    reversible_comparative_accumulator&
    operator = (const argument_type& x) {
        pq_.clear();
        pq_.insert(x);
        return *this;
    }


    //---------------------------------------------------------------
    reversible_comparative_accumulator&
    operator += (const argument_type& x) {
        push(x);
        return *this;
    }
    //-----------------------------------------------------
    reversible_comparative_accumulator&
    operator -= (const argument_type& x) {
        pop(x);
        return *this;
    }

    //-----------------------------------------------------
    void
    push(const argument_type& x) {
        pq_.insert(x);
    }
    //-----------------------------------------------------
    void
    pop(const argument_type& x) {
        auto it = pq_.find(x);
        if(it != pq_.end()) {
            pq_.erase(it);
        }
    }


    //---------------------------------------------------------------
    const result_type&
    result() const {
        return *pq_.begin();
    }


private:
    std::multiset<Arg,Comparator> pq_;
};





/*****************************************************************************
 *
 *
 *****************************************************************************/
template<class Arg, class Comp>
inline decltype(auto)
result(const comparative_accumulator<Arg,Comp>& a) {
    return a.result();
}


template<class Arg, class Comp>
inline decltype(auto)
result(const reversible_comparative_accumulator<Arg,Comp>& a) {
    return a.result();
}



} //namespace stat
}  // namespace am


#endif
