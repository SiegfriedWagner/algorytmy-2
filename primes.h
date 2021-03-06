//
// Created by mateu on 09.11.2021.
//

#ifndef ALGORYTMY_2_PRIMES_H
#define ALGORYTMY_2_PRIMES_H
#include <array>
// list of 32 prime number closest to 2^n, n : {1, 2, ... , 32 }
constexpr static std::array<uint32_t, 32> primes = {2, 3, 7, 17, 31, 61, 127, 257, 509, 1021, 2053, 4093, 8191,
                                               16381, 32771, 65537, 131071, 262147, 524287, 1048573, 2097143,
                                               4194301, 8388617, 16777213, 33554467, 67108859, 134217757,
                                               268435459, 536870909, 1073741827, 2147483647, 4294967291};
#endif //ALGORYTMY_2_PRIMES_H
