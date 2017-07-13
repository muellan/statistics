#ifndef AMLIB_STATISTICS_VOID_ACCUMULATOR_H_
#define AMLIB_STATISTICS_VOID_ACCUMULATOR_H_



namespace am {
namespace stat {


/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<class T>
struct void_accumulator
{
    using value_type = T;
    struct result_type {};

    constexpr
    void_accumulator() = default;


    void_accumulator&
    operator = (const void_accumulator&) = default;

    void_accumulator&
    operator = (const T&) {return *this;}

    void
    clear() {}


    void_accumulator&
    operator += (const T&) {return *this; }

    void_accumulator&
    operator -= (const T&) {return *this; }


    void push(const T&) {}

    void pop() {}
    void pop(const T&) {}


    static constexpr result_type
    result() {
        return result_type();
    }

};



/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<class T>
auto result(const void_accumulator<T>& a) {
    return a.result();
}


}  // namespace stat
}  // namespace am


#endif
