#pragma once
#include <stdexcept>
#include <cmath>
inline int char2idx(char ch)
{
    if (ch >= 'a' && ch <= 'z')
        return ch - 'a';
    else if (ch >= 'A' && ch <= 'Z')
        return ch - 'A';
    else
    {
        if(ch == '-') return 26;
        if(ch == '\'') return 27;
        else throw std::invalid_argument("An invalid character occurred. Please check your input.");
    }
}

inline double unnormalized_poisson(int k)
{
    int factorial = 1;
    for(int i = 2; i <= k; i++)
        factorial *= k;
    return std::exp(k) / factorial;
}

inline bool cmp(const std::pair<std::shared_ptr<Word>, int> &A,
               const std::pair<std::shared_ptr<Word>, int> &B)
{
    return A.first->cnt * unnormalized_poisson(A.second) >
           B.first->cnt * unnormalized_poisson(B.second);
}