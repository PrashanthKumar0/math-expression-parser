#include <iostream>
#include <string>
#include "mep.hpp"

int main() 
{
    std::string exprStr{"22 * -3 + ( 8   - 4 * ( 5 - 1)) / 2"};
    double res{mep::eval(exprStr)};
    std::cout << "RES : " << res << std::endl;
}
