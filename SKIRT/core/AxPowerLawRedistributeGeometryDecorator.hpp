
/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef AXPOWERLAWREDISTRIBUTEGEOMETRYDECORATOR_HPP
#define AXPOWERLAWREDISTRIBUTEGEOMETRYDECORATOR_HPP

#include "RedistributeGeometryDecorator.hpp"

////////////////////////////////////////////////////////////////////

/** The abstract AxPowerLawRedistributeGeometryDecorator class implements a decorator that 
    adjusts another geometry by multiplying the density with an axial power law weight function 
    \f[ \rho'(r, \phi, z) = n \rho(R, \phi, z) R^{-p_R}z^{-p_z}. \f] There are also two clipping
    clipping regions, one around the z-axis determined by a radius \f$R_0\f$ and one above
    and below the xy-plane with a height \f$z_0\f$, where the density is made zero to cut
    out the singularity. If an exponent is made zero, then the clipping region for that exponent
    can also be made zero. */
class AxPowerLawRedistributeGeometryDecorator : public RedistributeGeometryDecorator
{
    ITEM_CONCRETE(AxPowerLawRedistributeGeometryDecorator, RedistributeGeometryDecorator,
                  "a decorator that redistributes another geometry with an axial power law")

        PROPERTY_DOUBLE(RExponent, "the negative power of the radial part of the weight function")
        ATTRIBUTE_MIN_VALUE(RExponent, "[0")

        PROPERTY_DOUBLE(zExponent, "the negative power of the z-part of the weight function")
        ATTRIBUTE_MIN_VALUE(zExponent, "[0")

        PROPERTY_DOUBLE(minR, "the radius of the clipping cylinder around the z-axis")
        ATTRIBUTE_QUANTITY(minR, "length")
        ATTRIBUTE_MIN_VALUE(minR, "[0 pc")
        ATTRIBUTE_RELEVANT_IF(minR, "RExponent")

        PROPERTY_DOUBLE(minZ, "half the height of the clipping region around the xy-plane")
        ATTRIBUTE_QUANTITY(minZ, "length")
        ATTRIBUTE_MIN_VALUE(minZ, "[0 pc")
        ATTRIBUTE_RELEVANT_IF(minZ, "zExponent")

    ITEM_END()

    //======================== Other Functions =======================
public:
    /** The dimension of the geometry after applying the decorator cannot change and is
        thus the dimension of the original geometry. */
    int dimension() const override;

protected:
    /** The weight function is the power law: \f$r^{-p}\f$. */
    double weight(Position bfr) const override;

    /** The max weight is used in the rejection method and is equal to \f$r_0^{-p}\f$ 
        with \f$r_0\gt 0\f$ the radius of the clipping. */
    double maxWeight() const override;

    //======================== Data Members ========================

private:
    // aliases to discoverable data members for ease of notation and backwards compatibility
    const double& _R0{_minR};
    const double& _z0{_minZ};
    const double& _pR{_RExponent};
    const double& _pz{_zExponent};
};

////////////////////////////////////////////////////////////////////

#endif
