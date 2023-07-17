
/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "AxPowerLawRedistributeGeometryDecorator.hpp"

////////////////////////////////////////////////////////////////////

int AxPowerLawRedistributeGeometryDecorator::dimension() const
{
    return geometry()->dimension();
}

////////////////////////////////////////////////////////////////////

double AxPowerLawRedistributeGeometryDecorator::weight(Position bfr) const
{
    double R = bfr.cylRadius();
    double z = abs(bfr.z());
    if (z < _z0 || abs(R) < _R0) return 0;
    return pow(R, -_pR) * pow(z, -_pz);
}

////////////////////////////////////////////////////////////////////

double AxPowerLawRedistributeGeometryDecorator::maxWeight() const
{
    return weight(Position(_R0, 0, _z0, Position::CoordinateSystem::CYLINDRICAL));
}

////////////////////////////////////////////////////////////////////
