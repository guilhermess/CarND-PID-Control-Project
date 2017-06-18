#include "PID.h"
#include <cmath>
#include <iostream>


using namespace std;


PID::PID(double Kp, double Ki, double Kd) : cte_{0},
                                         prev_cte_{0},
                                         integral_cte_{0},
                                         total_error_{0},
                                         iteration_{0},
                                         pid_(3)
{
  pid_[0] = Kp;
  pid_[1] = Ki;
  pid_[2] = Kd;
}


void PID::UpdateError(double cte) {
  total_error_ += ((cte*cte) - total_error_) / ++iteration_;
  prev_cte_ = cte_;
  cte_ = cte;
  integral_cte_ += cte;
  if ( fabs(cte) > max_cte_ )
    max_cte_ = fabs(cte);
}


double PID::getSteering() const
{
  double steering = (-pid_[0] * cte_) + (-pid_[1] * integral_cte_) + (-pid_[2] * (cte_ - prev_cte_));
  steering = std::max(-1.0, steering);
  steering = std::min(1.0, steering);
  return steering;
}