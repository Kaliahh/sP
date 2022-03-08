//
// Created by ane on 18/02/2022.
//

#ifndef SESSION_5_NUMBERSERIESWRAPPER_H
#define SESSION_5_NUMBERSERIESWRAPPER_H


#include <memory>
#include "NumberSeries.h"

namespace series {
    class NumberSeriesWrapper {
        std::unique_ptr<NumberSeries> ptr{};
    public:

        explicit NumberSeriesWrapper(const NumberSeries& series) {
            ptr = std::make_unique<NumberSeries>(series);
        }

        NumberSeriesWrapper() = default;

        ~NumberSeriesWrapper() noexcept = default;

        NumberSeriesWrapper(const NumberSeriesWrapper& other) = delete;

        NumberSeriesWrapper& operator=(const NumberSeriesWrapper& other) = delete;

        NumberSeriesWrapper(NumberSeriesWrapper&& other) noexcept {
            *this = std::move(other);
        }

        NumberSeriesWrapper& operator=(NumberSeriesWrapper&& other) noexcept {
            if (this == &other) {
                return *this;
            }

//        std::swap(ptr, other.ptr);
            ptr = std::move(other.ptr);

            return *this;
        }

        int GetMaximum();

        int GetMinimum();

        static NumberSeriesWrapper MakeRandom(int);

        NumberSeriesWrapper operator+(const NumberSeriesWrapper&);

        NumberSeriesWrapper& operator+=(const NumberSeriesWrapper&);

        bool operator<(const NumberSeriesWrapper& other) const {
            return *ptr < *other.ptr;
        }
    };
}




#endif //SESSION_5_NUMBERSERIESWRAPPER_H
