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
  std::complex<double> realderiv = (d.eval(r+h)-d.eval(r))/h;
  std::complex<double> i = std::complex<double>(0,1);
  double imagderiv = (d.eval(r + i*h)).imag()/h;
  //return realderiv.real();
  return imagderiv;
}
