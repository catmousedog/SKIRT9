/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "SerialParallel.hpp"

////////////////////////////////////////////////////////////////////

SerialParallel::SerialParallel(int /*threadCount*/)
{
}

////////////////////////////////////////////////////////////////////

void SerialParallel::call(size_t maxIndex, std::function<void(size_t,size_t)> target)
{
    // Invoke the target function in a single chunk
    if (maxIndex) target(0, maxIndex);
}

////////////////////////////////////////////////////////////////////
