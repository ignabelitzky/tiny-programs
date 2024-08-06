#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cout << "Give me the number of coefficients (n): ";
    std::cin >> n;
    float p, x, tmp;
    std::cout << "Give me the value of X: ";
    std::cin >> x;
    std::vector<float> array;
    for(int i = 0; i < n; ++i)
    {
        std::cout << "Coefficient " << i << ": ";
        std::cin >> tmp;
        array.push_back(tmp);
    }
    p = array.at(n - 1);
    for(int i = n - 2; i >= 0; --i)
    {
        p = array.at(i) + x * p;
    }
    std::cout << "Result: " << p << std::endl;
    return 0;
}
