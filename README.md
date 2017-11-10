AM statistics
==========

Header-only collection of statistics utilities for C++14.

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


#### Accumulator Interface

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

#### Accumulator Decorators
 - ```windowed<Accumulator>```  restricts statistics on the n latest samples
 - ```reversible<Accumulator>``` augments an accumulator with an undo history  
 - ```combined<Accumulators...>``` combines several accumulators into one
 
#### Accumulator Adapters
 - ```histogram_accumulator``` augments a histogram with an accumulator interface 
 



## Requirements
  - requires C++14 conforming compiler
  - tested with g++ 5.3.1

