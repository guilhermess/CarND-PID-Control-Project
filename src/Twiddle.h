#ifndef TWIDDLE_H
#define TWIDDLE_H

#include "PID.h"
#include <vector>
#include <limits>
#include <iostream>

using std::vector;
using std::size_t;

class Twiddle {
public:
  Twiddle(PID &pid,
          unsigned int num_iterations,
          double tolerance,
          const vector<double> &dp) : pid_{pid},
                                      num_iterations_{num_iterations},
                                      tolerance_{tolerance},
                                      dp_(dp), best_error_{std::numeric_limits<double>::max()},
                                      index_{0}, previous_increased_{true}, finished_{false}, best_pid_(3)
  {
    for ( auto i = 0; i < 3; ++i) {
      if ( i == 0 )
        pid_[i] = dp_[i];
      else
        pid_[i] = 0;
    }
  }

  bool update();


private:
  PID &pid_;
  unsigned int num_iterations_;
  double tolerance_;
  vector<double> dp_;

  double best_error_;
  size_t index_;
  bool previous_increased_;
  bool finished_;

  vector<double> best_pid_;

  inline size_t update_index()
  {
    ++index_;
    if ( index_ == 3 ) index_ = 0;
    return index_;
  }

};

#endif

