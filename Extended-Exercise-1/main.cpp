#include <iostream>
#include <vector>
#include <chrono>
#include "NumberSeries.h"
#include "NumberSeriesWrapper.h"
#include <numeric>

#define NUM_SERIES 100000
#define NUM_ELEMENTS 100

using namespace std;
using namespace series;

vector<NumberSeries> numberSeries(NUM_SERIES);
vector<NumberSeriesWrapper> numberSeriesWrappers(NUM_SERIES);

void testProgram() {

    cout << "Series: " << endl;

    auto first = std::chrono::high_resolution_clock::now();
    for (auto& series : numberSeries) {
        series = NumberSeries::MakeRandom(NUM_ELEMENTS);
    }
    auto last = std::chrono::high_resolution_clock::now();

    cout << "Building: " << chrono::duration<double, milli>(last - first).count() << endl;

    first = std::chrono::high_resolution_clock::now();
    std::sort(numberSeries.begin(), numberSeries.end());
    last = std::chrono::high_resolution_clock::now();

    cout << "Time: " << chrono::duration<double, milli>(last - first).count() << endl;
//    auto sum = std::accumulate(numberSeries.begin(), numberSeries.end(), NumberSeries());
//    cout << sum.GetMaximum() << endl;

    cout << endl;

    cout << "Wrappers: " << endl;

    first = std::chrono::high_resolution_clock::now();
    for (auto& series : numberSeriesWrappers) {
        series = NumberSeriesWrapper{NumberSeriesWrapper::MakeRandom(NUM_ELEMENTS)};
    }
    last = std::chrono::high_resolution_clock::now();

    cout << "Building: " << chrono::duration<double, milli>(last - first).count() << endl;

    first = std::chrono::high_resolution_clock::now();
    std::sort(numberSeriesWrappers.begin(), numberSeriesWrappers.end());
    last = std::chrono::high_resolution_clock::now();


    cout << "Time: " << chrono::duration<double, milli>(last - first).count() << endl;
}

int main() {
    testProgram();

    return 0;
}
