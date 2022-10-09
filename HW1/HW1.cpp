#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

template <typename T>
std::ostream & operator << (std::ostream & os, const std::vector<T> & vec)  {
    for(auto elem : vec)    {
        os<<elem<< "\t";
    }
    return os;
}

float Euler(float n)  {
    return pow(1+(1/n), n);
}

float Euler2(float n)  { 
    float x = 1/n;
    float y = 1+x;
    float z = y-1;
    if (z=0)    {
        return exp((x/x));
    }
    else   {
        return exp(log(y)/(y-1));
    }
}

float Q2 (int n)  {
    float x=100;
    for (int i=0; i<n; i++)   {
        x=sqrt(x);
    }
    for (int i=0; i<n; i++)   {
        x=x*x;
    }
    return x;
}

double z1 (double x) {
    return (exp(x)-1)/x;
}

double y (double x) {
    return exp(x);
}

double z2 (double y) {
    if (y==1)  {
        return 1;
    }
    else {
        return (y-1)/(log(y));
    }
}

void exponent_(double* n) {
    union   {
        double d;
        unsigned long u;
    } 
    var = { .d=*n };
    short basepower = var.u>>52;
    basepower = basepower&0x7ff;
    basepower-=1023;
    printf("unbiased exponent in b2: %d\n", basepower);
    short exponent = round(log10(2)*basepower);
    printf("exponent in b10: %d\n", exponent);
}

int main() {
    std::cout<< "Q1: \n";
    std::vector<float> n1 ={10,10e2,10e3,10e4,10e5,10e6,10e7,10e8};
    std::vector<float> n1_1(n1.size());
    std::vector<float> n1_2(n1.size());
    std::cout<< "n's: \n \t"<< n1 <<std::endl;
    std::transform(n1.cbegin(), n1.cend(), n1_1.begin(), Euler);
    std::cout<< "Approxations of e: \n \t"<< n1_1 <<std::endl;
    std::cout<< "The limit appromixation of e approaches the real value, but begins breaking down beyond 10^5, where the error from representing even small numbers, and the machine cannot distinguish 1+ULP from 1, then the error is exponentially magnified" << std::endl;
    std::transform(n1.cbegin(), n1.cend(), n1_2.begin(), Euler2);
    std::cout<< " New Approxations of e: \n \t" << n1_2 <<std::endl <<std::endl;
    //----------------------------------------------
    std::cout<< "Q2: \n";
    std::vector<float> n2 ={2,5,10,20,30,40};
    std::cout<< "n-times: \n \t"<< n2 <<std::endl;
    std::transform(n2.cbegin(), n2.cend(), n2.begin(), Q2);
    std::cout<< "Should be 100: \n \t"<< n2 <<std::endl;
    std::cout<< "Between 10 and 20 transformations, the the value is further truncated and the error is exponentially magnified" <<std::endl<<std::endl;
    //----------------------------------------------
    std::cout<< "Q3: \n";
    std::vector<double> n3;
    for (int i=5 ; i<16 ; i++)   {
        n3.push_back(pow(10,-i));
    }

    std::cout<< "Initial x's: \n \t"<< n3 <<std::endl;
    std::vector<double> n3_x(n3.size());
    std::transform(n3.cbegin(), n3.cend(), n3_x.begin(), z1);
    std::cout<<"z's: \n \t"<< n3_x <<std::endl;
    std::cout<< "For this z-equation, z is undefined as x approaches 0, we need to introduce another function when the machine would input a 0 by floating by representation into the denominator" <<std::endl;

    std::vector<double> n3_y(n3.size());
    std::transform(n3.cbegin(), n3.cend(), n3_y.begin(), y);
    std::transform(n3_y.cbegin(), n3_y.cend(), n3_y.begin(), z2);
    std::cout<<"z's by y: \n \t"<< n3_y <<std::endl <<std::endl;
    //----------------------------------------------
    std::cout<< "Q4: \n";
    std::cout<<"for 256, "<<std::endl;
    double f=256;
    exponent_(&f);

    std::cout<<"for 99999, "<<std::endl;
    f=99999;
    exponent_(&f);

}