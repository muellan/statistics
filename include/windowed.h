#ifndef AMLIB_STATISTICS_WINDOWED_ACCUMULATOR_H_
#define AMLIB_STATISTICS_WINDOWED_ACCUMULATOR_H_

#include <queue>

#include "window_buffer.h"


namespace am {
namespace stat {


/****************************************************************************
 *
 * @brief accumulator decorator that restricts an accumulator to a fixed
 *        maximum number of values
 *
 ****************************************************************************/
template<class Accumulator>
class windowed
{
public:
    //---------------------------------------------------------------
    using argument_type = typename Accumulator::argument_type;
    using result_type   = Accumulator;
    using size_type     = std::size_t;


    //---------------------------------------------------------------
    constexpr
    windowed():
        acc_{}, queue_{}, windowSize_(10)
    {}
    //-----------------------------------------------------
    explicit constexpr
    windowed(const argument_type& init):
        acc_{init}, queue_{init}, windowSize_(10)
    {}

    //-----------------------------------------------------
    windowed(const windowed&) = default;
    windowed(windowed&&) = default;


    //---------------------------------------------------------------
    windowed& operator = (const windowed&) = default;
    windowed& operator = (windowed&&) = default;


    //---------------------------------------------------------------
    size_type
    window_size() const noexcept {
        return windowSize_;
    }
    //-----------------------------------------------------
    void
    resize_window(size_type size) {
        for(size_type i = windowSize_; i > size && !queue_.empty(); --i) {
            acc_ -= queue_.front();
            queue_.pop();
        }
        windowSize_ = size;
    }


    //---------------------------------------------------------------
    void
    clear() {
        acc_.clear();
        queue_.clear();
    }
    //-----------------------------------------------------
    windowed&
    operator = (const argument_type& x) {
        acc_ = x;
        queue_.clear();
        queue_.push(x);
        return *this;
    }


    //---------------------------------------------------------------
    const argument_type&
    top() const {
        return queue_.back();
    }


    //---------------------------------------------------------------
    windowed&
    operator += (const argument_type& x) {
        push(x);
        return *this;
    }
    //-----------------------------------------------------
    void
    push(const argument_type& x) {
        if(queue_.size() >= window_size()) {
            acc_ -= queue_.front();
            queue_.pop();
        }
        acc_ += x;
        queue_.push(x);
    }


    //---------------------------------------------------------------
    void
    pop() {
        if(!queue_.empty()) {
            acc_ -= queue_.front();
            queue_.pop();
        }
    }


    //---------------------------------------------------------------
    const result_type&
    result() const noexcept {
        return acc_;
    }


private:
    Accumulator acc_;
    std::queue<argument_type> queue_;
    size_type windowSize_;
};






/****************************************************************************
 *
 * @brief accumulator decorator that restricts an accumulator to a fixed
 *        static maximum number of values
 *
 ****************************************************************************/
template<class Accumulator, std::size_t windowSize>
class fixed_windowed
{
public:
    //---------------------------------------------------------------
    using argument_type = typename Accumulator::argument_type;
    using result_type   = Accumulator;
    using size_type     = std::size_t;


    //---------------------------------------------------------------
    constexpr
    fixed_windowed():
        acc_{}, buffer_{}
    {}
    //-----------------------------------------------------
    explicit constexpr
    fixed_windowed(const argument_type& init):
        acc_{init}, buffer_{init}
    {}

    //-----------------------------------------------------
    fixed_windowed(const fixed_windowed&) = default;
    fixed_windowed(fixed_windowed&&) = default;


    //---------------------------------------------------------------
    fixed_windowed& operator = (const fixed_windowed&) = default;
    fixed_windowed& operator = (fixed_windowed&&) = default;


    //---------------------------------------------------------------
    static constexpr size_type
    window_size() noexcept {
        return windowSize;
    }


    //---------------------------------------------------------------
    void
    clear() {
        acc_.clear();
        buffer_.clear();
    }
    //-----------------------------------------------------
    fixed_windowed&
    operator = (const argument_type& x) {
        acc_ = x;
        buffer_.clear();
        buffer_.push(x);
        return *this;
    }


    //---------------------------------------------------------------
    const argument_type&
    top() const {
        return buffer_.back();
    }


    //---------------------------------------------------------------
    fixed_windowed&
    operator += (const argument_type& x) {
        push(x);
        return *this;
    }
    //-----------------------------------------------------
    void
    push(const argument_type& x) {
        if(buffer_.full()) {
            acc_ -= buffer_.front();
        }
        acc_ += x;
        buffer_.push_back(x);
    }


    //---------------------------------------------------------------
    const result_type&
    result() const noexcept {
        return acc_;
    }


private:
    Accumulator acc_;
    window_buffer<argument_type,windowSize> buffer_;
};




/*****************************************************************************
 *
 *
 *****************************************************************************/
template<class Accumulator>
inline decltype(auto)
result(const windowed<Accumulator>& a) {
    return a.result();
}

template<class Accumulator, std::size_t winSize>
inline decltype(auto)
result(const fixed_windowed<Accumulator,winSize>& a) {
    return a.result();
}


} //namespace stat
}  // namespace am


#endif
