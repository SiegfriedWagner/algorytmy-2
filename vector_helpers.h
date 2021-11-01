//
// Created by mateu on 01.11.2021.
//

#ifndef ALGORYTMY_2_VECTOR_HELPERS_H
#define ALGORYTMY_2_VECTOR_HELPERS_H
#include <vector>
#include <iostream>
#include <iomanip>

template <typename T>
void printVectorOfVectors(const std::vector<std::vector<T>> &arr) {
    for (const std::vector<T> &vec: arr) {
        for (T val: vec)
            std::cout << std::setw(4) << val << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
#endif //ALGORYTMY_2_VECTOR_HELPERS_H
