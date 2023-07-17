
/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "SpheRedistributeGeometryDecorator.hpp"
#include "Random.hpp"

////////////////////////////////////////////////////////////////////

void SpheRedistributeGeometryDecorator::setupSelfAfter()
{
    SpheGeometry::setupSelfAfter();

    int Nsamples = 10000;
    double sum = 0.;
    for (int k = 0; k < Nsamples; k++)
    {
        double r = _geometry->randomRadius();
        sum += weight(r);
    }
    _norm = Nsamples / sum;
    _maxWeight = maxWeight();
}

////////////////////////////////////////////////////////////////////

double SpheRedistributeGeometryDecorator::density(double r) const
{
    return _norm * _geometry->density(r) * weight(r);
}

////////////////////////////////////////////////////////////////////

double SpheRedistributeGeometryDecorator::randomRadius() const
{
    while (true)
    {
        double r = _geometry->randomRadius();
        double t = random()->uniform() * _maxWeight / weight(r);
        if (t <= 1) return r;
    }
}

////////////////////////////////////////////////////////////////////

double SpheRedistributeGeometryDecorator::Sigmar() const
{
    return _geometry->Sigmar();
}

////////////////////////////////////////////////////////////////////
