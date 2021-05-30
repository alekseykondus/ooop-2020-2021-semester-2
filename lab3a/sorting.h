#pragma once

#include <vector>
#include <future>
#include <algorithm>
#include <random>
#include <QElapsedTimer>
#include <fstream>
#include <cmath>

typedef long long Type;

class Sorting
{
public:
    Sorting(size_t size);
    int NaiveQuickSort(std::vector<Type>::iterator begin, std::vector<Type>::iterator end);
    void MultiThreadedQuicksort(std::vector<Type>::iterator begin, std::vector<Type>::iterator end);
    void stdSort ();
    inline std::vector<Type>& GetVector() { return unsorted; }
    std::vector<Type> CreateVector(size_t size);
    static void CreateBenchmark();

    bool operator== (Sorting right) {
        return (unsorted==right.GetVector())?true:false;
    }
    bool operator!= (Sorting right) {
        return (unsorted!=right.GetVector())?true:false;
    }

private:
    std::vector<Type> unsorted;
    std::vector<Type>::iterator Partition(std::vector<Type>::iterator begin, std::vector<Type>::iterator end, std::vector<Type>::iterator pivot);
};

