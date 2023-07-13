
/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef REDISTRIBUTEPOWERLAWGEOMETRY_HPP
#define REDISTRIBUTEPOWERLAWGEOMETRY_HPP

#include "RedistributeGeometryDecorator.hpp"

////////////////////////////////////////////////////////////////////

/** The abstract SphericalPowerLawRedistributeGeometryDecorator class implements a decorator that 
    adjusts another geometry by multiplying the density with a power law weight function 
    \f[ \rho'(r, \theta, \phi) = n \rho(r, \theta, \phi) r^{-p}. \f] There is also a spherical
    clipping region around the origin determined by a radius \f$r_0 \gt 0\f$ where the density is made 
    zero to cut out the singularity. */
class SphericalPowerLawRedistributeGeometryDecorator : public RedistributeGeometryDecorator
{
    ITEM_CONCRETE(SphericalPowerLawRedistributeGeometryDecorator, RedistributeGeometryDecorator,
                  "a decorator that redistributes another geometry with a spherical power law")

        PROPERTY_DOUBLE(power, "the negative power of the weight function")
        ATTRIBUTE_MIN_VALUE(power, "]0")

        PROPERTY_DOUBLE(minRadius, "the radius of the clipping sphere")
        ATTRIBUTE_QUANTITY(minRadius, "length")
        ATTRIBUTE_MIN_VALUE(minRadius, "]0 pc")

    ITEM_END()

    //======================== Other Functions =======================
public:
    /** The dimension of this decorator is the dimension of the original geometry. */
    int dimension() const override;

protected:
    /** The weight function is the power law: \f$r^{-p}\f$. */
    double weight(Position bfr) const override;

    /** The max weight is used in the rejection method and is equal to \f$r_0^{-p}\f$ 
        with \f$r_0\gt 0\f$ the radius of the clipping. */
    double maxWeight() const override;

    /** Returns true if inside the clipped distribution. In this case that is for any 
        \f$r \ge r_0\f$ with \f$r_0 \gt 0\f$ the clipping sphere centered on the origin. */
    bool inside(Position bfr) const override;
};

////////////////////////////////////////////////////////////////////

#endif
