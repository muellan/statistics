#ifndef AMLIB_STATISTICS_HISTOGRAM_ACCUMULATOR_H_
#define AMLIB_STATISTICS_HISTOGRAM_ACCUMULATOR_H_


#include "uniform_histogram.h"


namespace am {
namespace stat {


/****************************************************************************
 *
 *
 *
 ****************************************************************************/
template<
    class Histogram,
    class SizeT = typename Histogram::value_type
>
class histogram_accumulator
{
public:

    //---------------------------------------------------------------
    using result_type = Histogram;
    using size_type = SizeT;
    //-----------------------------------------------------
    using argument_type = typename result_type::argument_type;


    //---------------------------------------------------------------
    histogram_accumulator():
        histo_()
    {}
    //-----------------------------------------------------
    explicit
    histogram_accumulator(argument_type binWidth):
        histo_(std::move(binWidth))
    {}
    //-----------------------------------------------------
    explicit
    histogram_accumulator(result_type histo):
        histo_(std::move(histo))
    {}
    //-----------------------------------------------------
    histogram_accumulator(const histogram_accumulator& source):
        histo_(source.histo_)
    {}
    //-----------------------------------------------------
    histogram_accumulator(histogram_accumulator&& source) noexcept :
        histo_(std::move(source.histo_))
    {}


    //---------------------------------------------------------------
    histogram_accumulator&
    operator = (const histogram_accumulator& source) {
        histo_ = source.histo_;
        return *this;
    }
    //-----------------------------------------------------
    histogram_accumulator&
    operator = (histogram_accumulator&& source) noexcept {
        histo_ = std::move(source.histo_);
        return *this;
    }


    //---------------------------------------------------------------
    void
    clear() {
        histo_.clear();
    }
    //-----------------------------------------------------
    void
    reset(argument_type binWidth) {
        histo_ = result_type(std::move(binWidth));
    }
    //-----------------------------------------------------
    histogram_accumulator&
    operator = (const result_type& histo) {
        histo_ = histo;
        return *this;
    }


    //---------------------------------------------------------------
    void
    push(const argument_type& x) {
        if(!histo_.range_includes(x)) {
            histo_.expand_include(x);
        }
        histo_.insert(x);
    }
    //-----------------------------------------------------
    histogram_accumulator&
    operator += (const argument_type& x) {
        push(x);
        return *this;
    }


    //---------------------------------------------------------------
    size_type
    size() const {
        return histo_.total();
    }
    //-----------------------------------------------------
    size_type
    empty() const {
        return (size() < 1);
    }

    //-----------------------------------------------------
    const result_type&
    result() const noexcept {
        return histo_;
    }


private:
    //---------------------------------------------------------------
    result_type histo_;
};






/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<
    class Argument,
    class Bins = std::vector<std::uint_least32_t>
>
class uniform_histogram_accumulator :
    public histogram_accumulator<uniform_histogram<Argument,Bins>>
{};



} //namespace stat
}  // namespace am

#endif
