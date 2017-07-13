AM statistics
==========

Header-only library of statistics utilities for C++14.

- [Interfaces](#interfaces)
- [Requirements](#requirements)




## Quick Overview


### Histograms

#### [uniform\_histogram](#uniform-histogram)
List of counters where the index of each counter is determined by mapping an input value to a range of bins of the same size.

#### [nonuniform\_histogram](#non-uniform-histogram)
List of counters where the index of each counter is determined by mapping an input value to a range of bins of non-uniform size (specified by their lower bounds).

#### [partial\_sum\_counter](#partial-sum-counter)
List of counters with efficient partial sum (prefix sum) queries.


### Accumulators
An accumulator provides running statistical analyses of a (growing) sample of values.

 - ```moments_accumulator```
     - ```mean_accumulator```      (running mean)
     - ```variance_accumulator```  (includes running mean)
     - ```skewness_accumulator```  (includes running mean & variance)
     - ```kurtosis_accumulator```  (includes running mean, variance & skewness)
 - ```comparative_accumulator```
     - ```min_accumulator```
     -``` max_accumulator```
 - ```reversible_comparative_accumulator``` (supports undo/pop operation)
     - ```reversible_min_accumulator```
     - ```reversible_max_accumulator```
 - ```min_max_moments_accumulator```
 - ```reversible_min_max_moments_accumulator```

#### Accumulator Decorators
 - ```windowed<Accumulator>```  restricts statistics on the n latest samples
 - ```reversible<Accumulator>``` augments an accumulator with an undo history  
 - ```combined<Accumulators...>``` combines several accumulators into one
 
#### Accumulator Adapters
 - ```histogram_accumulator``` augments a histogram with an accumulator interface 
 



## Interfaces

Note that the descriptions provided here are informal and simplified for better readability.

### Accumulator Interface

All accumulators have the following members:
```cpp
using 
//reset accumulator
accumulator::clear();
accumulator::operator = (const argument_type&);

//add sample to statistics
accumulator::push(const argument_type&);
accumulator::operator += (const argument_type&);
```

Reversible accumulators also have:
```cpp
//remove value from statistics
accumulator::pop(const argument_type&);
accumulator::operator -= (const argument_type&);
```


### Uniform Histogram
List of counters where the index of each counter is determined by mapping an input value to a range of bins of the same size.

```cpp
template<
    class Argument,                               //counted values type
    class Bins = std::vector<std::uint_least32_t> //counters
>
class uniform_histogram {
public:
    using argument_type = Argument;
    using count_type = typename Bins::value_type;
    using value_type = count_type;

    uniform_histogram() = default;
    uniform_histogram(argument_type binWidth);
    uniform_histogram(argument_type min, argument_type max, argument_type binWidth);

    uniform_histogram(const uniform_histogram&) = default;
    uniform_histogram(uniform_histogram&&)      = default;
    uniform_histogram& operator = (const uniform_histogram&) = default;
    uniform_histogram& operator = (uniform_histogram&&)      = default;

    //clear all counters
    void clear();

    //expand bin range; values that would shrink the range are ignored
    void expand(argument_type newMin, argument_type newMax);

    //expand bin range so that 'x' will be included in the new range
    void expand_include(const argument_type& x);

    //get bin range & width
    const argument_type& min() const noexcept;
    const argument_type& max() const noexcept;
    const argument_type& bin_width() const noexcept;

    //insert value => increase counter of bin into which 'x' belongs
    void insert(const argument_type& x); 
    
    template<class InputIterator>
    void insert(InputIterator begin, InputIterator end);

    //get bin count by value
    count_type operator () (const argument_type&) const noexcept; 

    //returns true, if 'x' falls into histogram range
    bool range_includes(const argument_type& x) const noexcept;

    //find bin by value
    iterator find(const argument_type&) const noexcept;

    //sum of all bin counters
    count_type total() const;

    //vector-like access to counters by index
    const count_type& operator [] (size_type idx) const noexcept;
    count_type& operator [] (size_type idx) noexcept;

    //number of counters 
    size_type size() const noexcept;
    bool empty() const noexcept;

    iterator begin() noexcept;
    const_iterator begin() const noexcept 
    const_iterator cbegin() const noexcept 

    iterator end() noexcept 
    const_iterator end() const noexcept 
    const_iterator cend() const noexcept 
};
```


### Non-uniform Histogram
List of counters where the index of each counter is determined by mapping an input value to a range of bins of non-uniform size (specified by their lower bounds).

```cpp
template<
    class Argument,
    class Count = std::uint_least32_t
>
class nonuniform_histogram {
public:
    using argument_type = Argument;
    using count_type = Count;
    using value_type = count_type;
    using bins_type = std::vector<std::pair<argument_type,count_type>>;

    nonuniform_histogram(bins_type bins);
    nonuniform_histogram() = default;

    //initialize with a list of lower bounds for all bins
    template<class T>
    nonuniform_histogram(std::initializer_list<T> binMins);

    //initialize with a list of lower bounds for all bins
    template<class InputIterator>
    nonuniform_histogram(InputIterator binMinFirst, InputIterator binMinLast);

    //give a list 
    nonuniform_histogram(bins_type bins);

    nonuniform_histogram(const nonuniform_histogram&) = default;
    nonuniform_histogram(nonuniform_histogram&&)      = default;
    nonuniform_histogram& operator = (const nonuniform_histogram&) = default;
    nonuniform_histogram& operator = (nonuniform_histogram&&)      = default;

    //clear all counters
    void clear();

    //insert value => increase counter of bin into which 'x' belongs
    void insert(const argument_type& x); 
    
    template<class InputIterator>
    void insert(InputIterator begin, InputIterator end);

    //get bin count by value
    count_type operator () (const argument_type&) const noexcept; 

    //returns true, if 'x' falls into histogram range
    bool range_includes(const argument_type& x) const noexcept;

    //find bin by value
    iterator find(const argument_type&) const noexcept;

    //sum of all bin counters
    count_type total() const;

    //vector-like access to counters by index
    const count_type& operator [] (size_type idx) const noexcept;
    count_type& operator [] (size_type idx) noexcept;

    //number of counters 
    size_type size() const noexcept;
    bool empty() const noexcept;

    iterator begin() noexcept;
    const_iterator begin() const noexcept 
    const_iterator cbegin() const noexcept 

    iterator end() noexcept 
    const_iterator end() const noexcept 
    const_iterator cend() const noexcept 

};
```

### Counter With Efficient Prefix Sum Queries

A.k.a Fenwick tree.
List of integral counters with efficient prefix sums queries.

```cpp
template<class IntegralT = std::int_least64_t>
class partial_sum_counter {
public:
    using argument_type = IntegralT;
    using size_type = argument_type;

    partial_sum_accumulator() = default;
    partial_sum_accumulator(size_type size);

    void reserve(size_type);
    void resize(size_type);

    //increase on of the counters
    void increase(size_type index, argument_type increment = 1);

    size_type size() const noexcept;

    //returns the frequency of one element
    argument_type operator [] (size_type idx) const;

    /returns the total of elements in index range [0,idx]
    argument_type total(size_type index) const noexcept;

    //returns the total of elements in index range [a,b]
    argument_type total(size_type a, size_type b) const noexcept;

private:
    //store_[i] = total of elements in index range [i&(i+1), i]
    std::vector<IntegralT> store_;
};
```


## Requirements
  - requires C++14 conforming compiler
  - tested with g++ 5.3.1

