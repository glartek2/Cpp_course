// mySorting.h
#ifndef MYSORTING_H
#define MYSORTING_H


#include <algorithm>
#include <cstring>
#include "myList.h"

template<typename T>
void mySort(T& arr) {
    std::sort(std::begin(arr), std::end(arr));
}

template<size_t N>
void mySort(char (&arr)[N][20]) {
    std::vector<std::string> temp;
    for (size_t i = 0; i < N; ++i) {
        temp.push_back(arr[i]);
    }
    std::sort(temp.begin(), temp.end());
    for (size_t i = 0; i < N; ++i) {
        std::strcpy(arr[i], temp[i].c_str());
    }
}


template<size_t N>
void mySortIgnoreCase(char (&arr)[N][10], size_t length) {
    std::sort(std::begin(arr), std::end(arr), [length](const char* a, const char* b) {
        return std::strncmp(a, b, length) < 0;
    });
}


template<typename T>
void mySort(MyList<T>& list) {
    std::vector<T> temp;
    for (const auto& elem : list) {
        temp.push_back(elem);
    }
    std::sort(temp.begin(), temp.end());

    // Clear the list
    list.clear();

    // Push sorted elements back to the list
    for (const auto& elem : temp) {
        list.push_front(elem);
    }
}


#endif // MYSORTING_H
