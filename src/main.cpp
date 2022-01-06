#include <iostream>

int main() {
    int x[100];
    std::cout << "Hello UB" << x[1000];
}
