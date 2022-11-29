#include <iostream>
#include <vector>

#include "TVector3.h"
#include "TMat4.h"
#include "TQuanternion.h"
#include <cmath>

int main(int argc, char *argv[]) {
    SG::TQuanternion<double> test = SG::TQuanternion<double>::GetRotationQuanternion((3./2. * M_PI), SG::TVector3<double>(1., 0., 0.));
    std::cout << test.Rotate(SG::TVector3<double>(-1., -1., -1.)) << std::endl;

    SG::TQuanternion<double> quanternion_1 = SG::TQuanternion<double>(1, 2, 3, 4);
    SG::TQuanternion<double> quanternion_2 = SG::TQuanternion<double>(5, 4, 3, 2);

    std::cout << "Quanternion 1: " << quanternion_1 << std::endl;
    std::cout << "Quanternion 2: " << quanternion_2 << std::endl;

    std::cout << "Addition: " << quanternion_1 + quanternion_2 << std::endl;
    std::cout << "Subtraction: " << quanternion_1 - quanternion_2 << std::endl;

    std::cout << "Multiplication: " << quanternion_1 * quanternion_2 << std::endl;
    std::cout << "Division: " << quanternion_1 / quanternion_2 << std::endl;
    return 0;
}
