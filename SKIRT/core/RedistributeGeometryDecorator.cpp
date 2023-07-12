
/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "RedistributeGeometryDecorator.hpp"
#include "FatalError.hpp"
#include "Random.hpp"

////////////////////////////////////////////////////////////////////

void RedistributeGeometryDecorator::setupSelfAfter()
{
    Geometry::setupSelfAfter();

    int Nsamples = 10000, Ninside = 0;
    double sum = 0.;
    for (int k = 0; k < Nsamples; k++)
    {
        Position bfr = geometry()->generatePosition();
        if (inside(bfr))
        {
            Ninside++;
            sum += weight(bfr);
        }
    }
    if (Ninside / (double)Nsamples < 0.1)
        throw FATALERROR("Redistribute decorator minRadius removes more than 90% of the original mass");
    _norm = Nsamples / sum;
    _c = maxWeight();
}

//////////////////////////////////////////////////////////////////////

double RedistributeGeometryDecorator::density(Position bfr) const
{
    if (inside(bfr))
        return _norm * _geometry->density(bfr) * weight(bfr);
    else
        return 0;
}

////////////////////////////////////////////////////////////////////

Position RedistributeGeometryDecorator::generatePosition() const
{
    // can also use rejection: w(x) * max(r(x)) but would need to know max(r)
    // this would allow for divergent w(x) such as ~ x^-p with p < 1

    while (true)
    {
        Position bfr = _geometry->generatePosition();
        if (inside(bfr))
        {
            double t = random()->uniform() * _c / weight(bfr);
            if (t <= 1) return bfr;
        }
    }
}

////////////////////////////////////////////////////////////////////

double RedistributeGeometryDecorator::SigmaX() const
{
    return _geometry->SigmaX();
}

////////////////////////////////////////////////////////////////////

double RedistributeGeometryDecorator::SigmaY() const
{
    return _geometry->SigmaY();
}

////////////////////////////////////////////////////////////////////

double RedistributeGeometryDecorator::SigmaZ() const
{
    return _geometry->SigmaZ();
}

////////////////////////////////////////////////////////////////////

bool RedistributeGeometryDecorator::inside(Position bfr) const
{
    return true;
}

////////////////////////////////////////////////////////////////////