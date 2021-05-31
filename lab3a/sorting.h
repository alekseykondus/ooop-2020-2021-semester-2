#pragma once

#include <vector>
#include <future>
#include <algorithm>
#include <random>
#include <QElapsedTimer>
#include <fstream>
#include <cmath>

typedef long long Type;

/// <summary>
/// Сlass that stores a vector of elements and can sort them
/// </summary>
class Sorting
{
public:
    Sorting(size_t size);

    /// <summary>
    /// Method that sorts with normal quicksort
    /// </summary>
    int NaiveQuickSort(std::vector<Type>::iterator begin, std::vector<Type>::iterator end);

    /// <summary>
    /// Sorting method with multithreaded quicksort
    /// </summary>
    void MultiThreadedQuicksort(std::vector<Type>::iterator begin, std::vector<Type>::iterator end);

    /// <summary>
    /// Sorting method with std::sort()
    /// </summary>
    void stdSort ();

    /// <summary>
    /// To get a vector containing the Sorting class
    /// </summary>
    /// <returns>
    ///  Returns a vector
    /// </returns>
    inline std::vector<Type>& GetVector() { return unsorted; }

    /// <summary>
    /// Creates a vector with random values ​​for a given number of elements
    /// </summary>
    /// <returns>
    ///  Returns the generated vector
    /// </returns>
    std::vector<Type> CreateVector(size_t size);

    /// <summary>
    /// Creates a vector with random values ​​for a given number of elements
    /// </summary>
    static void CreateBenchmark();

    /// <returns>
    ///  returns true if vectors are equal else returns false
    /// </returns>
    bool operator== (Sorting right) {
        return (unsorted==right.GetVector())?true:false;
    }
    /// <returns>
    ///  returns false if vectors are equal else returns true
    /// </returns>
    bool operator!= (Sorting right) {
        return (unsorted!=right.GetVector())?true:false;
    }

private:
    std::vector<Type> unsorted;
    std::vector<Type>::iterator Partition(std::vector<Type>::iterator begin, std::vector<Type>::iterator end, std::vector<Type>::iterator pivot);
};

