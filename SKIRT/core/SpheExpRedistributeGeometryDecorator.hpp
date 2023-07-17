
/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef SPHEEXPREDISTRIBUTEGEOMETRYDECORATOR_HPP
#define SPHEEXPREDISTRIBUTEGEOMETRYDECORATOR_HPP

#include "RedistributeGeometryDecorator.hpp"

////////////////////////////////////////////////////////////////////

/** The abstract SpheExpRedistributeGeometryDecorator class implements a decorator that adjusts
    another geometry by multiplying the density with a spherical exponential function \f[ \rho'(r,
    \theta, \phi) = n \rho(r, \theta, \phi) \exp{-\frac{r}{L_r}}. \f] */
class SpheExpRedistributeGeometryDecorator : public RedistributeGeometryDecorator
{
    ITEM_CONCRETE(SpheExpRedistributeGeometryDecorator, RedistributeGeometryDecorator,
                  "a decorator that redistributes another geometry with a spherical exponential")

        PROPERTY_DOUBLE(rScaleLength, "the scale length of the exponential weight function")
        ATTRIBUTE_QUANTITY(rScaleLength, "length")
        ATTRIBUTE_MIN_VALUE(rScaleLength, "]0")

    ITEM_END()

    //======================== Other Functions =======================
public:
    /** The dimension of the geometry after applying the decorator cannot change and is
        thus the dimension of the original geometry. */
    int dimension() const override;

protected:
    /** The weight function is the exponential: \f$\exp{-\frac{r}{L_r}}\f$. */
    double weight(Position bfr) const override;

    /** The max weight, used in the rejection method, is equal to 1. */
    double maxWeight() const override;
};

////////////////////////////////////////////////////////////////////

#endif
