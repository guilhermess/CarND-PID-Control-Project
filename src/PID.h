#ifndef PID_H
#define PID_H

#include <vector>

class Twiddle;

class PID {
public:

  /*
  * Constructor
  */
  PID(double Kp, double Ki, double Kd);

  /*
* Update the PID error variables given cross track error.
*/
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double getTotalError() const { return total_error_; }

  inline const double &operator[](std::size_t index) const
  {
    return pid_[index];
  }

  double getSteering() const;

protected:
  friend class Twiddle;

  inline double& operator[](std::size_t index)
  {
    return pid_[index];
  }

  inline void reset()
  {
    cte_ = 0;
    prev_cte_ = 0;
    integral_cte_ = 0;
    total_error_ = 0;
    iteration_ = 0;
  }

  inline unsigned int getIteration() const { return iteration_; }

private:
  double cte_;
  double prev_cte_;
  double integral_cte_;
  double total_error_;
  unsigned int iteration_;
  std::vector<double> pid_;




};

#endif /* PID_H */
