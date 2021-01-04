#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

int main()
{
    std::cout << std::hex << std::stoll("100110110010100100111101010001001101100101010110000101111111111",NULL,  2) << std::endl;

    std::stringstream ss;
    ss << std::hex << std::stoll("100110110010100100111101010001001101100101010110000101111111111", NULL, 2);
    std::cout << ss.str() << std::endl;

    return 0;
}
