
/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef SPHEPOWERLAWREDISTRIBUTEGEOMETRYDECORATOR_HPP
#define SPHEPOWERLAWREDISTRIBUTEGEOMETRYDECORATOR_HPP

#include "SpheRedistributeGeometryDecorator.hpp"

////////////////////////////////////////////////////////////////////

/** The abstract SphePowerLawRedistributeGeometryDecorator class implements a decorator that 
    adjusts a spherical geometry by multiplying the density with a spherical power law weight
    function \f[ \rho'(r, \theta, \phi) = n \rho(r, \theta, \phi) r^{-p}. \f] There is also a
    spherical clipping region around the origin determined by a radius \f$r_0 \gt 0\f$ where
    the density is made zero to cut out the singularity. */
class SphePowerLawRedistributeGeometryDecorator : public SpheRedistributeGeometryDecorator
{
    ITEM_CONCRETE(SphePowerLawRedistributeGeometryDecorator, SpheRedistributeGeometryDecorator,
                  "a decorator that redistributes another geometry with a spherical power law")

        PROPERTY_DOUBLE(exponent, "the negative exponent of the weight function")
        ATTRIBUTE_MIN_VALUE(exponent, "]0")

        PROPERTY_DOUBLE(minRadius, "the radius of the clipping sphere")
        ATTRIBUTE_QUANTITY(minRadius, "length")
        ATTRIBUTE_MIN_VALUE(minRadius, "]0 pc")

    ITEM_END()

    //======================== Other Functions =======================
protected:
    /** The weight function is the power law: \f$r^{-p}\f$. */
    double weight(double r) const override;

    /** The max weight is used in the rejection method and is equal to \f$r_0^{-p}\f$ 
        with \f$r_0\gt 0\f$ the radius of the clipping. */
    double maxWeight() const override;
};

////////////////////////////////////////////////////////////////////

#endif
