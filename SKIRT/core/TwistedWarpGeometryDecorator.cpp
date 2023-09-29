/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "TwistedWarpGeometryDecorator.hpp"
#include "Random.hpp"

//////////////////////////////////////////////////////////////////////

double TwistedWarpGeometryDecorator::density(Position bfr) const
{
    double R, phi, z;
    bfr.cylindrical(R, phi, z);

    return _geometry->density(Position(R, phi, z - warpHeight(R, phi), Position::CoordinateSystem::CYLINDRICAL));
}

////////////////////////////////////////////////////////////////////

Position TwistedWarpGeometryDecorator::generatePosition() const
{
    Position bfr;
    double R, phi, z;
    bfr = _geometry->generatePosition();
    bfr.cylindrical(R, phi, z);

    return Position(R, phi, z + warpHeight(R, phi), Position::CoordinateSystem::CYLINDRICAL);
}

////////////////////////////////////////////////////////////////////

double TwistedWarpGeometryDecorator::SigmaX() const
{
    return _geometry->SigmaX();
}

////////////////////////////////////////////////////////////////////

double TwistedWarpGeometryDecorator::SigmaY() const
{
    return _geometry->SigmaY();
}

////////////////////////////////////////////////////////////////////

double TwistedWarpGeometryDecorator::SigmaZ() const
{
    return _geometry->SigmaZ();
}

////////////////////////////////////////////////////////////////////

double TwistedWarpGeometryDecorator::warpHeight(double R, double phi) const
{
    if (R > _maxRadius) return 0;
    double u = M_PI * sqrt(R / _maxRadius);
    return 0.549541133154 * _maxWarpHeight * u * sin(u) * cos(phi - u);
}

////////////////////////////////////////////////////////////////////