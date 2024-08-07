#include <iostream>
#include <cmath>

int main()
{
    int imin, n = 30;
    float error, y, x = 0.5f, h = 1.0f, emin = 1.0f;
    for(int i = 0; i < n; ++i)
    {
        h = 0.25f * h;
        y = (std::sin(x + h) - std::sin(x)) / h;
        error = std::abs(std::cos(x) - y);
        std::cout << "i = " << i << ", h = " << h << ", y = " << y << ", error = " << error << std::endl;
        if (error < emin)
        {
            emin = error;
            imin = i;
        }
    }
    std::cout << "imin = " << imin << ", emin = " << emin << std::endl;
    return 0;
}