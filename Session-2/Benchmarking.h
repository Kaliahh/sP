//
// Created by ane on 08/02/2022.
//

#ifndef SESSION_2_BENCHMARKING_H
#define SESSION_2_BENCHMARKING_H

#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;


class Benchmarking {
    private:
        vector<double> times;

        high_resolution_clock::time_point temporaryTimestamp;

    public:
        void Start() {
            temporaryTimestamp = high_resolution_clock::now();
        }

        void Lap() {
            auto first = temporaryTimestamp;
            auto now = high_resolution_clock::now();

            auto difference = duration<double, std::milli>(now - first).count();

            times.push_back(difference);
        }

        double GetAverage() {
            double sum = 0;
            for (double time : times) {
                sum += time;
            }
            return sum / times.size();
        }
};


#endif //SESSION_2_BENCHMARKING_H
