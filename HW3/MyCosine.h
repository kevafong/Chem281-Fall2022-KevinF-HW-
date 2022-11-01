#if !defined MYCOSINE__H
#define MYCOSINE_H
#include <hw3.1.h>

class MyCosine : public Derivable
{
  std::complex<double> eval(const std::complex<double> coord);
};

#endif
