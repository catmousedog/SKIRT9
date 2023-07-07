/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "WarpedDiskGeometryDecorator.hpp"
#include "Random.hpp"

//////////////////////////////////////////////////////////////////////

double WarpedDiskGeometryDecorator::SigmaX() const
{
    return geometry()->SigmaX();
}

////////////////////////////////////////////////////////////////////

double WarpedDiskGeometryDecorator::SigmaY() const
{
    return geometry()->SigmaY();
}

////////////////////////////////////////////////////////////////////

double WarpedDiskGeometryDecorator::heightShift(double R, double phi) const
{
    // twisted
    double r = sqrt(10 * R / _maxRadius);
    return 2 * _maxWarpHeight / M_PI * r * sin(r) * cos(phi - _phaseZeroPoint - r);

    // twist-free
    // double r = r / _maxRadius;
}

////////////////////////////////////////////////////////////////////