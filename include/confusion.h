#ifndef AMLIB_STATISTICS_CONFUSION_H_
#define AMLIB_STATISTICS_CONFUSION_H_

#include <cstdint>


namespace am {
namespace stat {


/*****************************************************************************
 *
 * @brief
 *
 *****************************************************************************/
class confusion_statistics
{
public:
    using count_type = std::uint_least64_t;

    confusion_statistics() noexcept:
        tp_(0), fp_(0), tn_(0), fn_(0)
    {}

    void count_outcome_truth(bool outcome, bool truth) {
        if(outcome) {
            if(truth) count_true_pos(); else count_false_pos();
        } else {
            if(truth) count_true_neg(); else count_false_neg();
        }
    }

    void count_true_pos(count_type times = 1)  noexcept { tp_ += times; }
    void count_false_pos(count_type times = 1) noexcept { fp_ += times; }
    void count_true_neg(count_type times = 1)  noexcept { tn_ += times; }
    void count_false_neg(count_type times = 1) noexcept { fn_ += times; }

    count_type true_pos()  const noexcept { return tp_; }
    count_type false_pos() const noexcept { return fp_; }
    count_type true_neg()  const noexcept { return tn_; }
    count_type false_neg() const noexcept { return fn_; }

    count_type condition_pos() const noexcept { return true_pos() + false_neg(); }
    count_type condition_neg() const noexcept { return true_neg() + false_pos(); }
    count_type outcome_pos()   const noexcept { return true_pos() + false_pos(); }
    count_type outcome_neg()   const noexcept { return true_neg() + false_neg(); }

    count_type total() const noexcept {
        return condition_pos() + condition_neg();
    }

    double outcome_pos_rate() const noexcept {
        return outcome_pos() / double(total());
    }
    double outcome_neg_rate() const noexcept {
        return outcome_neg() / double(total());
    }

    double accuracy() const noexcept {
        return (true_pos() + true_neg()) / double(total());
    }

    //true positive rate, hit rate, recall
    double sensitivity() const noexcept {
        return true_pos() / double(condition_pos());
    }
    //true negative rate
    double specificity() const noexcept {
        return true_neg() / double(condition_neg());
    }

    //positive predictive value
    double precision() const noexcept {
        return true_pos() / double(outcome_pos());
    }

    double negative_prediction() const noexcept {
        return true_neg() / double(outcome_neg());
    }

    double negative_omission() const noexcept {
        return false_neg() / double(outcome_neg());
    }

    double false_positive_rate() const noexcept {
        return false_pos() / double(condition_neg());
    }

    double false_discovery_rate() const noexcept {
        return false_pos() / double(outcome_pos());
    }

    double miss_rate() const noexcept {
        return false_neg() / double(condition_pos());
    }


private:
    count_type tp_;
    count_type fp_;
    count_type tn_;
    count_type fn_;
};


} // namespace am
} // namespace stat


#endif
