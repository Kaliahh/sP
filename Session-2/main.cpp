#include <iostream>
#include <bitset>
#include <limits>
#include <vector>
#include <chrono>
#include "Benchmarking.h"

using namespace std;
using namespace std::chrono;


vector<int> vec(10000000);

int main() {
    Benchmarking bench;

    bench.Start();

    for (auto& item : vec) {
//        item = item + 1;
        bench.Lap();
    }

    cout << bench.GetAverage() << endl;


    return 0;
}


