#ifndef AMLIB_STATISTICS_COMBINED_ACCUMULATOR_H_
#define AMLIB_STATISTICS_COMBINED_ACCUMULATOR_H_

#include <tuple>
#include <type_traits>
#include <utility>
#include <cstdint>


namespace am {
namespace stat {

namespace detail {


/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<class Tuple>
inline void
reset_helper(Tuple&&, std::index_sequence<>)
{}

//-----------------------------------------------------
template<class Tuple, std::size_t n, std::size_t... ns>
inline void
reset_helper(Tuple&& fs, std::index_sequence<n,ns...>)
{
    std::get<n>(fs).clear();
    reset_helper(std::forward<Tuple>(fs), std::index_sequence<ns...>{});
}

//-----------------------------------------------------
template<class... Fs>
inline void
reset(std::tuple<Fs...>& fs)
{
    detail::reset_helper(fs, std::make_index_sequence<sizeof...(Fs)>{});
}




/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<class Tuple, class... Args>
inline void
push_helper(Tuple&&, std::index_sequence<>, Args&&...)
{}

//-----------------------------------------------------
template<class Tuple, std::size_t n, std::size_t... ns, class... Args>
inline void
push_helper(Tuple&& fs, std::index_sequence<n,ns...>, Args&&... args)
{
    std::get<n>(fs).operator+=(args...);
    push_helper(
        std::forward<Tuple>(fs), std::index_sequence<ns...>{},
        std::forward<Args>(args)...);
}

//---------------------------------------------------------
template< class...Args>
inline void
push(std::tuple<>, Args&&...)
{}

//-----------------------------------------------------
template<class... Fs, class...Args>
inline void
push(std::tuple<Fs...>& fs, Args&&... args)
{
    detail::push_helper(fs,
        std::make_index_sequence<sizeof...(Fs)>{},
        std::forward<Args>(args)...);
}




/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<class Tuple, class... Args>
inline void
init_helper(Tuple&&, std::index_sequence<>, Args&&...)
{}

//-----------------------------------------------------
template<class Tuple, std::size_t n, std::size_t... ns, class... Args>
inline void
init_helper(Tuple&& fs, std::index_sequence<n,ns...>, Args&&... args)
{
    std::get<n>(fs).init(args...);
    init_helper(
        std::forward<Tuple>(fs), std::index_sequence<ns...>{},
        std::forward<Args>(args)...);
}

//---------------------------------------------------------
template< class...Args>
inline void
init(std::tuple<>, Args&&...)
{}

//-----------------------------------------------------
template<class... Fs, class...Args>
inline void
init(std::tuple<Fs...>& fs, Args&&... args)
{
    detail::init_helper(fs,
        std::make_index_sequence<sizeof...(Fs)>{},
        std::forward<Args>(args)...);
}


}  // namespace detail








/*****************************************************************************
 *
 * @brief combines several accumulators into one
 *
 *
 *****************************************************************************/
template<class... Accumulators>
class combined_accumulator
{
    using acc_t_ = std::tuple<Accumulators...>;

public:
    //---------------------------------------------------------------
    using size_type = std::size_t;


    //---------------------------------------------------------------
    combined_accumulator():
        size_(0), acc_()
    {}

    //-----------------------------------------------------
    template<class... Args>
    combined_accumulator(const Args&... args):
        size_(0), acc_()
    {
        detail::init(args...);
    }


    //---------------------------------------------------------------
    combined_accumulator&
    clear() {
        detail::reset(acc_);
        return *this;
    }
    //-----------------------------------------------------
    template<class Arg>
    combined_accumulator&
    operator = (const Arg& arg) {
        detail::init(arg);
        return *this;
    }


    //---------------------------------------------------------------
    template<class Args>
    combined_accumulator&
    operator += (const Args& arg) {
        detail::push(acc_, arg);
        return *this;
    }
    //-----------------------------------------------------
    template<class Args>
    void
    push(const Args& arg) {
        detail::push(acc_, arg);
    }


    //---------------------------------------------------------------
    template<std::size_t index>
    decltype(auto)
    get() const {
        return std::get<index>(acc_);
    }


    //-----------------------------------------------------
    size_type
    size() const noexcept {
        return size_;
    }
    //-----------------------------------------------------
    bool
    empty() const noexcept {
        return (size_ > 0);
    }


private:
    std::size_t size_;
    acc_t_ acc_;
};


}  // namespace stat
}  // namespace am


#endif
