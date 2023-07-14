
/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "SpheRedistributeGeometryDecorator.hpp"

////////////////////////////////////////////////////////////////////

int SpheRedistributeGeometryDecorator::dimension() const
{
    return geometry()->dimension();
}

////////////////////////////////////////////////////////////////////

double SpheRedistributeGeometryDecorator::weight(Position bfr) const
{
    return weight(bfr.radius());
}

////////////////////////////////////////////////////////////////////

double SpheRedistributeGeometryDecorator::norm() const
{
    int Nsamples = 10000;
    double sum = 0.;
    for (int k = 0; k < Nsamples; k++)
    {
        double r = geometry()->generatePosition().radius();
        sum += weight(r) * r;
    }
    return Nsamples / (4 * M_PI * sum);
}

////////////////////////////////////////////////////////////////////