
/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "SpheExpRedistributeGeometryDecorator.hpp"

////////////////////////////////////////////////////////////////////

int SpheExpRedistributeGeometryDecorator::dimension() const
{
    return geometry()->dimension();
}

////////////////////////////////////////////////////////////////////

double SpheExpRedistributeGeometryDecorator::weight(Position bfr) const
{
    double r = bfr.radius();
    return exp(-r/_rScaleLength);
}

////////////////////////////////////////////////////////////////////

double SpheExpRedistributeGeometryDecorator::maxWeight() const
{
    return 1;
}

////////////////////////////////////////////////////////////////////
