#ifndef AMLIB_WINDOW_BUFFER_H_
#define AMLIB_WINDOW_BUFFER_H_


#include <array>


namespace am {


/*************************************************************************//***
 *
 * @brief container that keeps a fixed number of values in a rolling fashion
 *    - values can only be inserted at one side
 *    - only the first value and the last value in the window can be accessed
 *
 *****************************************************************************/
template<class T, std::size_t windowSize>
class window_buffer
{
    using mem_t   = std::array<T,windowSize>;
    using iter_t = typename mem_t::iter_t;
    using citer_t = typename mem_t::citer_t;

public:
    //---------------------------------------------------------------
    using value_type = T;
    using size_type  = std::size_t;


    //---------------------------------------------------------------
    window_buffer() :
        mem_(), beg_(mem_.begin()), end_(mem_.begin())
    {}

    //-----------------------------------------------------
    window_buffer(std::initializer_list<value_type> il) :
        mem_(), beg_(mem_.begin()), end_(mem_.begin())
    {
        for(const auto& x : il) {
            push_back(x);
        }
    }


    //---------------------------------------------------------------
    size_type
    size() const noexcept {
        return distance(mem_.begin(), end_);
    }
    //-----------------------------------------------------
    static size_type
    max_size() noexcept {
        return windowSize;
    }
    //-----------------------------------------------------
    bool
    empty() const noexcept {
        return (mem_.begin() == end_);
    }
    //-----------------------------------------------------
    bool
    full() const noexcept {
        return (mem_.end() == end_);
    }


    //---------------------------------------------------------------
    const value_type&
    front() const noexcept {
        return *beg_;
    }
    //-----------------------------------------------------
    const value_type&
    back() const noexcept {
        using std::prev;
        return *prev(end_);
    }


    //---------------------------------------------------------------
    void
    clear() {
        beg_ = mem_.begin();
        end_ = mem_.end();
    }


    //---------------------------------------------------------------
    void
    push_back(const value_type& v)
    {
        using std::swap;

        if(!full()) {
            *end_ = v;
            ++end_;
        } else {
            *beg_ = std::move(mem_.back());
            ++beg_;
            if(beg_ == prev(mem_.end())) beg_ = mem_.begin();
            mem_.back() = v;
        }
    }

    //-----------------------------------------------------
    void
    push_back(value_type&& v)
    {
        using std::swap;

        if(!full()) {
            *end_ = std::move(v);
            ++end_;
        } else {
            *beg_ = std::move(mem_.back());
            ++beg_;
            if(beg_ == prev(mem_.end())) beg_ = mem_.begin();
            mem_.back() = std::move(v);
        }
    }

    //-----------------------------------------------------
    template<class... Args>
    void
    emplace_back(Args&&... args) {
        push_back(value_type{std::forward<Args>(args)...});
    }


private:
    mem_t mem_;
    iter_t beg_;
    iter_t end_;
};


}  // namespace am


#endif
