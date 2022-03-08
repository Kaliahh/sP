//
// Created by ane on 18/02/2022.
//

#include "NumberSeriesWrapper.h"

namespace series {
    int NumberSeriesWrapper::GetMaximum() {
        return ptr->GetMaximum();
    }

    int NumberSeriesWrapper::GetMinimum() {
        return ptr->GetMimimum();
    }

    NumberSeriesWrapper NumberSeriesWrapper::MakeRandom(int length) {
        return NumberSeriesWrapper(NumberSeries::MakeRandom(length));
    }

    NumberSeriesWrapper NumberSeriesWrapper::operator+(const NumberSeriesWrapper& other) {
        return NumberSeriesWrapper(*ptr + *other.ptr);
    }

    NumberSeriesWrapper &NumberSeriesWrapper::operator+=(const NumberSeriesWrapper& other) {
        *ptr += *other.ptr;
        return *this;
    }
}




