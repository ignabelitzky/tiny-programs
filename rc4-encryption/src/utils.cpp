#include "../include/utils.hpp"

void swap(std::vector<int>& S, int a, int b)
{
    int tmp = S[a];
    S[a] = S[b];
    S[b] = tmp;
}

void rc4(std::vector<int>& data, const std::string &key)
{
    std::vector<int> state(256);
    for(int i = 0; i < 256; ++i)
    {
        state[i] = i;
    }

    int j = 0;
    for(int i = 0; i < 256; ++i)
    {
        j = (j + state[i] + key[i % key.size()]) % 256;
        swap(state, i, j);
    }

    int i = 0;
    j = 0;
    for(unsigned int k = 0; k < data.size(); ++k)
    {
        i = (i + 1) % 256;
        j = (j + state[i]) % 256;
        swap(state, i, j);
        int t = (state[i] + state[j]) % 256;
        data[k] ^= state[t];
    }
}
