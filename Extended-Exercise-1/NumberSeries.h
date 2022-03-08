//
// Created by ane on 18/02/2022.
//

#ifndef SESSION_5_NUMBERSERIES_H
#define SESSION_5_NUMBERSERIES_H


#include <vector>
#include <random>
#include <functional>
#include <iostream>

namespace series {

    class NumberSeries {
        std::vector<int> series{};
        int maximum{std::numeric_limits<int>::min()};
        int minimum{std::numeric_limits<int>::max()};

    public:
        int GetMaximum() {
            return maximum;
        }

        int GetMimimum() {
            return minimum;
        }

        void AddNumber(int);

        void RemoveNumbers(int);

        static NumberSeries MakeRandom(int);

        NumberSeries operator+(const NumberSeries&);

        NumberSeries& operator+=(const NumberSeries&);

        bool operator<(const NumberSeries&) const;

        friend std::ostream& operator<<(std::ostream&, const NumberSeries&);
    };

}


#endif //SESSION_5_NUMBERSERIES_H
