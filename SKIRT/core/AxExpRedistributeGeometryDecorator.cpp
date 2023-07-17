
/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "AxExpRedistributeGeometryDecorator.hpp"

////////////////////////////////////////////////////////////////////

int AxExpRedistributeGeometryDecorator::dimension() const
{
    return max(2, geometry()->dimension());
}

////////////////////////////////////////////////////////////////////

double AxExpRedistributeGeometryDecorator::weight(Position bfr) const
{
    double R = bfr.cylRadius();
    double z = abs(bfr.z());
    return exp(-R / _LR - z / _Lz);
}

////////////////////////////////////////////////////////////////////

double AxExpRedistributeGeometryDecorator::maxWeight() const
{
    return 1;
}

////////////////////////////////////////////////////////////////////
