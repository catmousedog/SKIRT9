
/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef SPHEREDISTRIBUTEGEOMETRYDECORATOR_HPP
#define SPHEREDISTRIBUTEGEOMETRYDECORATOR_HPP

#include "RedistributeGeometryDecorator.hpp"
#include "SpheGeometry.hpp"

////////////////////////////////////////////////////////////////////

/** The abstract SpheRedistributeGeometryDecorator class implements a decorator that
    adjusts another spherical geometry by multiplying the density with a spherical
    weight function \f[ \rho'(r) = n \rho(r) w(r). \f] */
class SpheRedistributeGeometryDecorator : public RedistributeGeometryDecorator
{
    ITEM_ABSTRACT(SpheRedistributeGeometryDecorator, RedistributeGeometryDecorator,
                  "a decorator that redistributes another geometry with a spherical weight function")

        // PROPERTY_ITEM(geometry, SpheGeometry, "the geometry for which the density will be redistributed")

    ITEM_END()

    //======================== Other Functions =======================
public:
    /** The dimension of the resulating geometry is always 1. */
    int dimension() const override;

protected:
    /** This pure virtual function, to be implemented by a subclass, gives the weight function's value
        at a given radius. This function does not need to be normalized. */
    virtual double weight(double r) const = 0;

    /** This function gives the value of the abstract weight function at a radius r. */
    double weight(Position bfr) const override;

    /** This function numerically calculates the norm of the spherical distribution
        \f$n\rho({\bf{r}})w({\bf{r}})\f$. */
    double norm() const override;
};

////////////////////////////////////////////////////////////////////

#endif
