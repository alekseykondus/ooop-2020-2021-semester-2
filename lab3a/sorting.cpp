#include "sorting.h"

Sorting::Sorting(size_t size) {
    unsorted = CreateVector(size);
}

std::vector<Type> Sorting::CreateVector(size_t size) {
    std::random_device rd;
    std::mt19937 mersenne(rd());

    std::vector<Type> unsorted;
    for (size_t i = 0; i < size; i++) {
        unsorted.push_back(mersenne());
    }
    return unsorted;
}

int Sorting::NaiveQuickSort(std::vector<Type>::iterator begin, std::vector<Type>::iterator end) {
    auto const size = end - begin;
     if (size <= 1) return 0;

     auto pivot = begin + size / 2;
     auto const pivot_v = *pivot;

     std::swap(*pivot, *(end - 1));
     auto p = std::partition(begin, end, [&](const Type& a) { return a < pivot_v; });
     std::swap(*p, *(end - 1));

     NaiveQuickSort(begin, p);
     NaiveQuickSort(p + 1, end);
     return 0;
}

void Sorting::MultiThreadedQuicksort(std::vector<Type>::iterator begin, std::vector<Type>::iterator end) {
    if (end - begin > 1) {
        auto pivot = begin;
        auto p = Partition(begin, end, pivot);
        if (end - begin > 5000) {
            std::future<void> f1 = std::async(std::launch::async, [&]() {MultiThreadedQuicksort(begin, p); });
            MultiThreadedQuicksort(p + 1, end);
        }
        else {
            NaiveQuickSort(begin, p);
            NaiveQuickSort(p + 1, end);
        }
    }
}

std::vector<Type>::iterator Sorting::Partition(std::vector<Type>::iterator begin, std::vector<Type>::iterator end, std::vector<Type>::iterator pivot) {
       std::vector<Type>::iterator left = begin, right = end;
       while (true) {
           while (*(++left) < *begin) {
               if (left == end - 1) break;
           }
           while (*begin < *(--right)) {
               if (right == begin) break;
           }
           if (left >= right) break;
           std::swap(*left, *right);
       }
       std::swap(*begin, *right);
       return right;
   }


void Sorting::stdSort () {
        std::sort(unsorted.begin(), unsorted.end());
}

void Sorting::CreateBenchmark() {
        srand(time(0));
        QElapsedTimer time;

        std::ofstream fout("Benchmark.txt");

        fout << "Number of logical processors: " << std::thread::hardware_concurrency() << std::endl << std::endl;
        fout << "Vector Size       " << "One stream         " << "Multi threaded        " << "std::sort()" << std::endl;
        fout << "___________       " << "__________         " << "______________        " << "___________" << std::endl;

        for (size_t size = 100000; size < 21000000; size += 100000) {

            int numberOfDigits = (size==0? 1: int (log10 (size) + 1));

            Sorting sort(size);
            Sorting sort_2 = sort;
            Sorting sort_3 = sort;
            fout << size << "            ";
            if(numberOfDigits < 8)
                for (int k = 0; k < 8-numberOfDigits; k++)
                    fout << " ";

            time.start();
            sort.NaiveQuickSort(sort.GetVector().begin(), sort.GetVector().end());
            fout << (float)time.nsecsElapsed()/1000000 << "               ";

            time.start();
            sort_2.MultiThreadedQuicksort(sort_2.GetVector().begin(), sort_2.GetVector().end());
            fout << (float)time.nsecsElapsed()/1000000 << "              ";


            time.start();
            sort_3.stdSort();
            fout << (float)time.nsecsElapsed()/1000000 << std::endl;
        }
        fout.close();
}
