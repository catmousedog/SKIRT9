
/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "SphePowerLawRedistributeGeometryDecorator.hpp"

////////////////////////////////////////////////////////////////////

int SphePowerLawRedistributeGeometryDecorator::dimension() const
{
    return geometry()->dimension();
}

////////////////////////////////////////////////////////////////////

double SphePowerLawRedistributeGeometryDecorator::weight(Position bfr) const
{
    double r = bfr.radius();
    if (r < _minRadius) return 0;
    return pow(r, -_exponent);
}

////////////////////////////////////////////////////////////////////

double SphePowerLawRedistributeGeometryDecorator::maxWeight() const
{
    return weight(Position(_minRadius, 0, 0, Position::CoordinateSystem::SPHERICAL));
}

////////////////////////////////////////////////////////////////////
