#include <vector>
#include <iostream>


int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::vector<int> vec2 = {0, 0, 0, 0, 0};
    vec = vec2;
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    return 0;
}