/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "WarpedDiskGeometryDecorator.hpp"
#include "Random.hpp"

//////////////////////////////////////////////////////////////////////

double WarpedDiskGeometryDecorator::density(Position bfr) const
{
    double R, phi, z;
    bfr.cylindrical(R, phi, z);

    double h = 0.;
    if (R <= _maxRadius) h = warpHeight(R, phi);

    return _geometry->density(Position(R, phi, z - h, Position::CoordinateSystem::CYLINDRICAL));
}

////////////////////////////////////////////////////////////////////

Position WarpedDiskGeometryDecorator::generatePosition() const
{
    Position bfr = _geometry->generatePosition();

    double R, phi, z;
    bfr.cylindrical(R, phi, z);

    double h = 0.;
    if (R <= _maxRadius) h = warpHeight(R, phi);

    return Position(R, phi, z + h, Position::CoordinateSystem::CYLINDRICAL);
}

////////////////////////////////////////////////////////////////////

double WarpedDiskGeometryDecorator::SigmaX() const
{
    return _geometry->SigmaX();
}

////////////////////////////////////////////////////////////////////

double WarpedDiskGeometryDecorator::SigmaY() const
{
    return _geometry->SigmaY();
}

////////////////////////////////////////////////////////////////////

double WarpedDiskGeometryDecorator::SigmaZ() const
{
    return _geometry->SigmaZ();
}

////////////////////////////////////////////////////////////////////

double WarpedDiskGeometryDecorator::warpHeight(double R, double phi) const
{
    double r = sqrt(10 * R / _maxRadius);
    return 2 * _maxWarpHeight / M_PI * r * sin(r) * cos(phi - _phaseZeroPoint - r);
}

////////////////////////////////////////////////////////////////////