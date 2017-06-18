#include "Twiddle.h"
#include <iostream>

using namespace std;

bool Twiddle::update() {
  if ( finished_ || pid_.getIteration() < num_iterations_ ) {
    return false;
  }

  double error = pid_.getTotalError();
  if (error < best_error_)
  {
    best_error_ = error;
    cout << "Twiddle improved best error: " << best_error_ << " ";
    cout << "P: " << pid_[0] << " I: " << pid_[1] << " D: " << pid_[2] << endl;
    for ( auto i = 0; i < 3; ++i )
      best_pid_[i] = pid_[i];

    dp_[index_] *= 1.1;
    previous_increased_ = true;
    index_ = update_index();
    pid_[index_] += dp_[index_];
  } else {
    if (previous_increased_)
    {
      pid_[index_] -= 2 * dp_[index_];
      previous_increased_ = false;
    } else {
      pid_[index_] += dp_[index_];
      dp_[index_] *= 0.9;
      index_ = update_index();
      pid_[index_] += dp_[index_];
      previous_increased_ = true;
    }
  }

  auto total_dp = dp_[0] + dp_[1] + dp_[2];
  if (total_dp < tolerance_ )
  {
    finished_ = true;
    for ( auto i = 0; i < 3; ++i )
      pid_[i] = best_pid_[i];
    cout << "Restored best pid: P: " << pid_[0] << " I: " << pid_[1] << " D: " << pid_[2] << endl;
    return false;
  }
  else {
    pid_.reset();
    return true;
  }
}


