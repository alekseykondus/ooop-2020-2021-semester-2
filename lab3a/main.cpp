#include <iostream>
#include "sorting.h"

#define DOCTEST_CONFIG_IMPLEMENT
#ifdef DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"


TEST_CASE("verification of operators") {
    for (size_t size = 100000; size < 2100000; size += 100000) {
        Sorting arr(size);
        Sorting arr_copy = arr;
        CHECK((arr_copy == arr));

        Sorting arr2(size);
        Sorting arr3(size+1);
        CHECK((arr3 != arr2));
    }
}

TEST_CASE("checking std::reverse") {
    for (size_t size = 100000; size < 2100000; size += 100000) {
        Sorting sorted_arr(size);
        sorted_arr.stdSort();
        Sorting reverse_arr = sorted_arr;
        CHECK((reverse_arr == sorted_arr));

        std::reverse(reverse_arr.GetVector().begin(), reverse_arr.GetVector().end());
        CHECK((reverse_arr != sorted_arr));

        std::reverse(reverse_arr.GetVector().begin(), reverse_arr.GetVector().end());
        CHECK((reverse_arr == sorted_arr));
    }
}
TEST_CASE("checking for reverse array") {

    size_t size = 2100000;
    Sorting random_arr(size);
    Sorting sorted_arr = random_arr;
    sorted_arr.stdSort();
    Sorting reverse_arr = random_arr;
    std::reverse(reverse_arr.GetVector().begin(), reverse_arr.GetVector().end());

    SUBCASE ("NaiveQuickSort") {
        reverse_arr.NaiveQuickSort(reverse_arr.GetVector().begin(), reverse_arr.GetVector().end());
    }
    SUBCASE ("MultiThreadedQuicksort") {
        reverse_arr.MultiThreadedQuicksort(reverse_arr.GetVector().begin(), reverse_arr.GetVector().end());
    }
    SUBCASE ("std::sort()") {
        reverse_arr.stdSort();
    }
    CHECK((reverse_arr == sorted_arr));
}

TEST_CASE("checking if sorting is correct") {
    for (size_t size = 100000; size < 210000; size += 100000) {

        Sorting random_arr(size);
        Sorting random_arr_copy = random_arr;
        CHECK((random_arr_copy == random_arr));

        Sorting sorted_arr = random_arr;
        CHECK((sorted_arr == random_arr));

        sorted_arr.stdSort();

        random_arr_copy.NaiveQuickSort(random_arr_copy.GetVector().begin(), random_arr_copy.GetVector().end());
        CHECK((random_arr_copy == sorted_arr));

        random_arr_copy = random_arr;
        CHECK((random_arr_copy == random_arr));
        random_arr_copy.MultiThreadedQuicksort(random_arr_copy.GetVector().begin(), random_arr_copy.GetVector().end());
        CHECK((random_arr_copy == sorted_arr));

        random_arr_copy = random_arr;
        CHECK((random_arr_copy == random_arr));
        random_arr_copy.stdSort();
        CHECK((random_arr_copy == sorted_arr));
  }
}
#endif


/// <summary>
/// Multithreaded Quicksort
/// </summary>
int main() {

#ifdef DOCTEST_CONFIG_IMPLEMENT
    doctest::Context context;
    int res = context.run();
#endif

//  Sorting::CreateBenchmark();
}
