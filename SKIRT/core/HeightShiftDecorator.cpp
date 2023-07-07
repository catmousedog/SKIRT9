/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "HeightShiftDecorator.hpp"

//////////////////////////////////////////////////////////////////////

double HeightShiftDecorator::density(Position bfr) const
{
    double R, phi, z;
    bfr.cylindrical(R, phi, z);

    return _geometry->density(Position(R, phi, z - heightShift(R, phi), Position::CoordinateSystem::CYLINDRICAL));
}

////////////////////////////////////////////////////////////////////

Position HeightShiftDecorator::generatePosition() const
{
    Position bfr = _geometry->generatePosition();

    double R, phi, z;
    bfr.cylindrical(R, phi, z);

    return Position(R, phi, z + heightShift(R, phi), Position::CoordinateSystem::CYLINDRICAL);
}

////////////////////////////////////////////////////////////////////

double HeightShiftDecorator::SigmaZ() const
{
    return _geometry->SigmaZ();
}

////////////////////////////////////////////////////////////////////
