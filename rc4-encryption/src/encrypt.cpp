#include <iostream>
#include <fstream>
#include "../include/utils.hpp"

int main()
{
    std::string filename;
    std::cout << "Give me the filename of the plaintext: ";
    std::cin >> filename;
    std::ifstream file(filename, std::ios::binary);
    if(!file.is_open())
    {
        std::cerr << "Error: file not found" << std::endl;
        return 1;
    }

    // Read the file
    std::vector<int> data;
    int c;
    while((c = file.get()) != EOF)
    {
        data.push_back(c);
    }
    
    std::string key;
    std::cout << "Give me the key: ";
    std::cin >> key;
    
    // Encrypt the data using RC4
    rc4(data, key);

    // Write the encrypted data
    std::ofstream output("encrypted_output.txt", std::ios::binary);
    for(unsigned int k = 0; k < data.size(); ++k)
    {
        output.put(static_cast<char>(data[k]));
    }

    // Close the files
    file.close();
    output.close();

    // Exit
    return 0;
}
