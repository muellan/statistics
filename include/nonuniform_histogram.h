#ifndef AMLIB_STATISTICS_NONUNIFORM_HISTOGRAM_H_
#define AMLIB_STATISTICS_NONUNIFORM_HISTOGRAM_H_

#include <vector>
#include <utility>
#include <cstdint>
#include <numeric>
#include <algorithm>


namespace am {
namespace stat {


/*****************************************************************************
 *
 * @brief holds a vector of bin counts
 *        bins can have different widths
 *        insert(x) increases the count of the bin that x falls in
 *        operator()(x) returns the count of the bin that x falls in
 *
 *
 *****************************************************************************/
template<
    class Argument,
    class Count = std::uint_least32_t
>
class nonuniform_histogram
{
public:
    //---------------------------------------------------------------
    using argument_type = Argument;
    using count_type    = Count;
    //-----------------------------------------------------
    using bins_type  = std::vector<std::pair<argument_type,count_type>>;
    using value_type = typename bins_type::value_type;
    //-----------------------------------------------------
    using size_type = typename bins_type::size_type;
    //-----------------------------------------------------
    using const_iterator = typename bins_type::const_iterator;
    using       iterator = typename bins_type::iterator;
    //-----------------------------------------------------
    using numeric_type = argument_type;


    //---------------------------------------------------------------
    explicit
    nonuniform_histogram():
        bins_()
    {}
    //-----------------------------------------------------
    explicit
    nonuniform_histogram(bins_type bins) :
        bins_(std::move(bins))
    {
        using std::begin;
        using std::end;
        std::sort(bins_.begin(), bins_.end());
        bins_.erase(std::unique(bins_.begin(), bins_.end()), bins_.end());
    }
    //-----------------------------------------------------
    template<class T>
    explicit
    nonuniform_histogram(std::initializer_list<T> binMins) :
        bins_()
    {
        reset(binMins.begin(), binMins.end());
    }
    //-----------------------------------------------------
    template<class InputIterator>
    explicit
    nonuniform_histogram(InputIterator binMinFirst, InputIterator binMinLast) :
        bins_()
    {
        reset(binMinFirst, binMinLast);
    }


    //-----------------------------------------------------
    nonuniform_histogram(const nonuniform_histogram&) = default;
    nonuniform_histogram(nonuniform_histogram&&)      = default;


    //---------------------------------------------------------------
    nonuniform_histogram& operator = (const nonuniform_histogram&) = default;
    nonuniform_histogram& operator = (nonuniform_histogram&&)      = default;


    //---------------------------------------------------------------
    void
    clear() {
        for(auto& x : bins_) {
            x.second = count_type(0);
        }
    }


    //---------------------------------------------------------------
    void
    insert(const argument_type& x) {
        const auto binsBeg = bins_.begin();
        const auto binsEnd = bins_.end();

        if((binsBeg != binsEnd) && (x >= binsBeg->first))
        {
            auto it = std::lower_bound(binsBeg, binsEnd, value_type{x,0},
                [](const value_type& a, const value_type& b) {
                    return a.first < b.first;
                });

            if(it != binsEnd) {
                if(it->first > x) {
                    --it;
                }
                ++(it->second);
            }
        }
    }
    //-----------------------------------------------------
    template<class InputIterator>
    void
    insert(InputIterator begin, InputIterator end) {
        for(; begin != end; ++begin) {
            insert(*begin);
        }
    }


    //---------------------------------------------------------------
    /// @brief lookup
    count_type
    operator () (const argument_type& x) const {
        //find x's bin and return current count
        const auto it = find(x);
        return (it != end()) ? it->second : value_type(0);
    }
    //-----------------------------------------------------
    bool
    range_includes(const argument_type& x) const
    {
        return (find(x) != end());
    }
    //-----------------------------------------------------
    iterator
    find(const argument_type& x) const
    {
        if((begin() == end()) || (x < begin()->first)) {
            return end();
        }

        return std::lower_bound(begin(), end(), value_type{x,0},
            [](const value_type& a, const value_type& b) {
                return a.first < b.first;
            });
    }


    //---------------------------------------------------------------
    const value_type&
    operator [] (size_type idx) const noexcept {
        return bins_[idx];
    }
    value_type&
    operator [] (size_type idx) noexcept {
        return bins_[idx];
    }


    //---------------------------------------------------------------
    size_type
    size() const noexcept {
        using std::distance;
        return size_type(distance(begin(), end()));
    }
    //-----------------------------------------------------
    bool
    empty() const noexcept {
        return bins_.empty();
    }

    //-----------------------------------------------------
    count_type
    total() const {
        return std::accumulate(begin(), end(), count_type(0),
            [](count_type sum, const value_type& b) {
                return sum + b.second;
            });
    }


    //---------------------------------------------------------------
    iterator
    begin() noexcept {
        return bins_.begin();
    }
    //-----------------------------------------------------
    const_iterator
    begin() const noexcept {
        return bins_.begin();
    }
    //-----------------------------------------------------
    const_iterator
    cbegin() const noexcept {
        return bins_.begin();
    }

    //-----------------------------------------------------
    iterator
    end() noexcept {
        return bins_.end();
    }
    //-----------------------------------------------------
    const_iterator
    end() const noexcept {
        return bins_.end();
    }
    //-----------------------------------------------------
    const_iterator
    cend() const noexcept {
        return bins_.end();
    }


private:
    //-----------------------------------------------------
    template<class InputIterator>
    void
    reset(InputIterator binMinFirst, InputIterator binMinLast)
    {
        using std::begin;
        using std::end;
        using std::distance;

        bins_.resize(distance(binMinFirst, binMinLast));

        for(auto& x : bins_) {
             x.first = *binMinFirst;
             x.second = count_type(0);
            ++binMinFirst;
        }
        std::sort(bins_.begin(), bins_.end());
        bins_.erase(std::unique(bins_.begin(), bins_.end()), bins_.end());
    }


    //---------------------------------------------------------------
    bins_type bins_;
};






/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<class Argument, class Count>
inline decltype(auto)
begin(const nonuniform_histogram<Argument,Count>& h)
{
    return h.begin();
}
//---------------------------------------------------------
template<class Argument, class Count>
inline decltype(auto)
cbegin(const nonuniform_histogram<Argument,Count>& h)
{
    return h.begin();
}

//---------------------------------------------------------
template<class Argument, class Count>
inline decltype(auto)
end(const nonuniform_histogram<Argument,Count>& h)
{
    return h.end();
}
//---------------------------------------------------------
template<class Argument, class Count>
inline decltype(auto)
cend(const nonuniform_histogram<Argument,Count>& h)
{
    return h.end();
}



//-------------------------------------------------------------------
template<class Argument, class Count>
inline decltype(auto)
min(const nonuniform_histogram<Argument,Count>& h)
{
    return h.min();
}

//---------------------------------------------------------
template<class Argument, class Count>
inline decltype(auto)
max(const nonuniform_histogram<Argument,Count>& h)
{
    return h.max();
}



//---------------------------------------------------------------
template<class Ostream, class Argument, class Count>
Ostream&
print(Ostream& os, const nonuniform_histogram<Argument,Count>& h)
{
    using std::distance;

    auto it = h.begin();
    const auto end = h.end();

    if(distance(it,end) < 1) return os;

    os << "{(" << it->first << "," << it->second << ")";
    ++it;
    for(; it != end; ++it) {
        os << ",(" << it->first << "," << it->second << ")";
    }
    return os << '}';
}


} //namespace stat
}  // namespace am

#endif
