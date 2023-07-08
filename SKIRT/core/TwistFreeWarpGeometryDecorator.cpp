/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "TwistFreeWarpGeometryDecorator.hpp"
#include "Random.hpp"

//////////////////////////////////////////////////////////////////////

double TwistFreeWarpGeometryDecorator::density(Position bfr) const
{
    double R, phi, z;
    bfr.cylindrical(R, phi, z);

    if (R > _maxRadius) return 0;

    return _geometry->density(Position(R, phi, z - warpHeight(R, phi), Position::CoordinateSystem::CYLINDRICAL));
}

////////////////////////////////////////////////////////////////////

Position TwistFreeWarpGeometryDecorator::generatePosition() const
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

double TwistFreeWarpGeometryDecorator::SigmaX() const
{
    return _geometry->SigmaX();
}

////////////////////////////////////////////////////////////////////

double TwistFreeWarpGeometryDecorator::SigmaY() const
{
    return _geometry->SigmaY();
}

////////////////////////////////////////////////////////////////////

double TwistFreeWarpGeometryDecorator::SigmaZ() const
{
    return _geometry->SigmaZ();
}

////////////////////////////////////////////////////////////////////

double TwistFreeWarpGeometryDecorator::warpHeight(double R, double phi) const
{
    return _maxWarpHeight * pow(R / _maxRadius, _warpPower) * cos(phi);
}

////////////////////////////////////////////////////////////////////