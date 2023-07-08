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

    if (R > _maxRadius) return 0;

    return _geometry->density(Position(R, phi, z - warpHeight(R, phi), Position::CoordinateSystem::CYLINDRICAL));
}

////////////////////////////////////////////////////////////////////

Position TwistedWarpGeometryDecorator::generatePosition() const
{
    Position bfr;
    double R, phi, z;
    do
    {
        bfr = _geometry->generatePosition();
        bfr.cylindrical(R, phi, z);
    } while (R > _maxRadius);

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
    double r = sqrt(10 * R / _maxRadius);
    return 2 * _maxWarpHeight / M_PI * r * sin(r) * cos(phi - r);
}

////////////////////////////////////////////////////////////////////