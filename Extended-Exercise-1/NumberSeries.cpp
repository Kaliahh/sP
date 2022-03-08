//
// Created by ane on 18/02/2022.
//

#include <chrono>
#include "NumberSeries.h"

namespace series {

    void NumberSeries::AddNumber(int num) {
        if (num < minimum) {
            minimum = num;
        }
        else if (num > maximum) {
            maximum = num;
        }

        series.push_back(num);
    }

    void NumberSeries::RemoveNumbers(int num) {
        auto it = std::remove_if(series.begin(), series.end(), [num](int x) -> bool {
            return x == num;
        });

        series.erase(it, std::end(series));
    }

    NumberSeries NumberSeries::MakeRandom(int length) {
        NumberSeries result{};

        std::random_device dev{};
        std::default_random_engine random_engine {dev()};
        std::uniform_int_distribution<> dist {0, 10000};
        auto rng = std::bind(dist, random_engine);

        for (int i = 0; i < length; i++) {
//        result.AddNumber(dist(random_engine));
            result.AddNumber(rng());
        }

        return result;
    }

    NumberSeries NumberSeries::operator+(const NumberSeries &other) {
        NumberSeries result{};

        int a = series.size();
        int b = other.series.size();

        int min_length = a < b ? a : b;

        int i = 0;
        for (; i < min_length; i++) {
            result.AddNumber(series[i] + other.series[i]);
        }

        for (; i < series.size(); i++) {
            result.AddNumber(series[i]);
        }

        for (; i < other.series.size(); i++) {
            result.AddNumber(other.series[i]);
        }

        return result;
    }

    NumberSeries &NumberSeries::operator+=(const NumberSeries &other) {
        int i = 0;
        for (; i < series.size() && i < other.series.size(); i++) {
            series[i] += other.series[i];
            if (series[i] > maximum) {
                maximum = series[i];
            }
            else if (series[i] < minimum) {
                minimum = series[i];
            }
        }

        for (; i < other.series.size(); i++) {
            AddNumber(other.series[i]);
        }

        return *this;
    }

    bool NumberSeries::operator<(const NumberSeries &other) const {
        int my_amplitude = maximum - minimum;
        int other_amplitude = other.maximum - other.minimum;

        return my_amplitude < other_amplitude;
    }

    std::ostream& operator<<(std::ostream& os, const NumberSeries& numberSeries) {
        if (numberSeries.series.empty()) {
            os << "(empty series)";
        }
        else {
            for (const auto& i : numberSeries.series) {
                os << i << " ";
            }
        }

        return os;
    }
}



