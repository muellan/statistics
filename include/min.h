#ifndef AMLIB_STATISTICS_EXTRACT_MINIMUM_H_
#define AMLIB_STATISTICS_EXTRACT_MINIMUM_H_


#include "comparative.h"


namespace am {
namespace stat {


/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<class Arg>
class min_accumulator :
    public comparative_accumulator<Arg,std::less<Arg> >
{
    using base_t_ = comparative_accumulator<Arg,std::less<Arg> >;
public:

    //---------------------------------------------------------------
    constexpr
    min_accumulator():
        base_t_{std::numeric_limits<Arg>::max()}
    {}
    //-----------------------------------------------------
    explicit constexpr
    min_accumulator(const Arg& init):
        base_t_{init}
    {}


    //---------------------------------------------------------------
    void
    clear() {
        base_t_::operator=(std::numeric_limits<Arg>::max());
    }
};






/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<class Arg>
class reversible_min_accumulator :
    public reversible_comparative_accumulator<Arg,std::less<Arg> >
{
    using base_t_ = reversible_comparative_accumulator<Arg,std::less<Arg> >;
public:

    //---------------------------------------------------------------
    constexpr
    reversible_min_accumulator():
        base_t_{std::numeric_limits<Arg>::max()}
    {}
    //-----------------------------------------------------
    explicit constexpr
    reversible_min_accumulator(const Arg& init):
        base_t_{init}
    {}


    //---------------------------------------------------------------
    void
    clear() {
        base_t_::operator=(std::numeric_limits<Arg>::max());
    }
};



} //namespace stat
}  // namespace am

#endif
