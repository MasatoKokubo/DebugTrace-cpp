/// Example4.cpp 
/// (C) 2017 Masato Kokubo
#include "stdafx.h"
#include <complex>
#include "Example.hpp"
#include "DebugTrace.hpp"

/// ClassA::func4
void ClassA::func4() const noexcept {
    DEBUG_TRACE // for Debugging

    // std::complex<float>
    std::complex<float> fcomplex1(1.234F, 3.456F);
    DEBUG_PRINT(fcomplex1) // for Debugging

    // std::complex<double>
    const std::complex<double> dcomplex1(1.23456, 3.45678);
    DEBUG_PRINT(dcomplex1) // for Debugging

    // std::complex<long double>
    std::complex<long double> ldcomplex1(1.2345678L, 3.4567890L);
    DEBUG_PRINT(ldcomplex1) // for Debugging
}
