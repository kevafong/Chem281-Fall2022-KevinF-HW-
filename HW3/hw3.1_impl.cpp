#include <hw3.1.h>
#include <MyPotential.h>
#include <MyCosine.h>

std::complex<double> MyPotential::eval(const std::complex<double> r)
{
  return (1./(pow(r,2)))-(1./(pow(r,6)));
}

std::complex<double> MyCosine::eval(const std::complex<double> r)
{
  return std::cos(r);
}


/********************************/
#include <stdio.h>
#include <float.h>
#include <hw3.1.h>

double firstDerivative(Derivable& d, const double r)
{
  double h = 10e-8;
  std::complex<double> complexderiv = (d.eval(r+h)-d.eval(r))/h;
  return complexderiv.real();
}
