#if !defined MYPOTENTIAL__H
#define MYPOTENTIAL_H
#include <hw3.1.h>

class MyPotential : public Derivable
{
  std::complex<double> eval(const std::complex<double> coord);
};

#endif
