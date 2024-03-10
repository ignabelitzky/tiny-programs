#include "../include/utils.hpp"

double cpu_time() {
    double value;
    value = (double) std::clock() / (double) CLOCKS_PER_SEC;
    return value;
}

void timestamp() {
    static char time_buffer[TIME_SIZE];
    const struct std::tm *tm_ptr;
    std::time_t now;

    now = std::time(NULL);
    tm_ptr = std::localtime(&now);

    std::strftime (time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr);
    
    std::cout << time_buffer << "\n";
}