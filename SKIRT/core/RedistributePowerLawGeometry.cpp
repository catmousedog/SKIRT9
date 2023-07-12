
/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "RedistributePowerLawGeometry.hpp"

////////////////////////////////////////////////////////////////////

int SphericalPowerLawRedistributeGeometryDecorator::dimension() const
{
    return max(geometry()->dimension(), 2);
}

////////////////////////////////////////////////////////////////////

double SphericalPowerLawRedistributeGeometryDecorator::weight(Position bfr) const
{
    return pow(bfr.radius(), -_power);
}

////////////////////////////////////////////////////////////////////

double SphericalPowerLawRedistributeGeometryDecorator::maxWeight() const
{
    return weight(Position(_minRadius, 0, 0, Position::CoordinateSystem::SPHERICAL));
}

////////////////////////////////////////////////////////////////////

bool SphericalPowerLawRedistributeGeometryDecorator::inside(Position bfr) const
{
    return bfr.radius() >= _minRadius;
}

////////////////////////////////////////////////////////////////////