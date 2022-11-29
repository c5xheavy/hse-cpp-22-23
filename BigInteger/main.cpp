#include <iostream>
#include "BigInteger.h"

int main() {
    std::cout << "Enter math expression (a + b)\n";
    BigInteger a, b;
    std::string c;
    std::cin >> a >> c >> b;
    if (c == "+") {
        std::cout << a + b << '\n';
    } else if (c == "-") {
        std::cout << a - b << '\n';
    } else {
        std::cerr << "Incorrect operation\n";
    }
    return 0;
}