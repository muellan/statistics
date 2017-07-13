#ifndef AMLIB_STATISTICS_EXTRACT_MAXIMUM_H_
#define AMLIB_STATISTICS_EXTRACT_MAXIMUM_H_


#include "comparative.h"


namespace am {
namespace stat {


/*****************************************************************************
 *
 *
 *****************************************************************************/
template<class Arg>
class max_accumulator :
    public comparative_accumulator<Arg,std::greater<Arg> >
{
    using base_t_ = comparative_accumulator<Arg,std::greater<Arg> >;
public:

    //---------------------------------------------------------------
    constexpr
    max_accumulator():
        base_t_{-std::numeric_limits<Arg>::max()}
    {}
    //-----------------------------------------------------
    explicit constexpr
    max_accumulator(const Arg& init):
        base_t_{init}
    {}


    //---------------------------------------------------------------
    void
    clear() {
        base_t_::operator  = (-std::numeric_limits<Arg>::max());
    }
};






/*****************************************************************************
 *
 *
 *****************************************************************************/
template<class Arg>
class reversible_max_accumulator :
    public reversible_comparative_accumulator<Arg,std::greater<Arg> >
{
    using base_t_ = reversible_comparative_accumulator<Arg,std::greater<Arg> >;
public:

    //---------------------------------------------------------------
    constexpr
    reversible_max_accumulator():
        base_t_{-std::numeric_limits<Arg>::max()}
    {}
    //-----------------------------------------------------
    explicit constexpr
    reversible_max_accumulator(const Arg& init):
        base_t_{init}
    {}


    //---------------------------------------------------------------
    void
    clear() {
        base_t_::operator  = (-std::numeric_limits<Arg>::max());
    }
};



} //namespace stat
}  // namespace am


#endif
