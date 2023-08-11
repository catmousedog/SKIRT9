
/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef AXEXPREDISTRIBUTEGEOMETRYDECORATOR_HPP
#define AXEXPREDISTRIBUTEGEOMETRYDECORATOR_HPP

#include "RedistributeGeometryDecorator.hpp"

////////////////////////////////////////////////////////////////////

/** The abstract AxExpRedistributeGeometryDecorator class implements a decorator that adjusts
    another geometry by multiplying the density with an axial exponential weight function \f[
    \rho'(r, \phi, z) = n \rho(R, \phi, z) \exp{\left(-\frac{R}{L_R}-\frac{z}{L_z}\right)}. \f] */
class AxExpRedistributeGeometryDecorator : public RedistributeGeometryDecorator
{
    ITEM_CONCRETE(AxExpRedistributeGeometryDecorator, RedistributeGeometryDecorator,
                  "a decorator that redistributes another geometry with an axial exponential")
        ATTRIBUTE_TYPE_INSERT(AxExpRedistributeGeometryDecorator, "Dimension2")

        PROPERTY_DOUBLE(RScaleLength, "the scale length in the radial direction")
        ATTRIBUTE_QUANTITY(RScaleLength, "length")
        ATTRIBUTE_MIN_VALUE(RScaleLength, "[0")

        PROPERTY_DOUBLE(zScaleLength, "the scale length in the vertical direction")
        ATTRIBUTE_QUANTITY(zScaleLength, "length")
        ATTRIBUTE_MIN_VALUE(zScaleLength, "[0")

    ITEM_END()

    //======================== Other Functions =======================
public:
    /** The dimension of the geometry after applying the decorator can only change
        spherical geometries into axially symmetric, otherwise it doesn't change the
        dimension. */
    int dimension() const override;

protected:
    /** The weight function is the exponential:
        \f$\exp{\left(-\frac{R}{L_R}-\frac{z}{L_z}\right)}\f$. */
    double weight(Position bfr) const override;

    /** The max weight, used in the rejection method, is equal to \f$1\f$. */
    double maxWeight() const override;

    //======================== Data Members ========================

private:
    // aliases to discoverable data members for ease of notation and backwards compatibility
    const double& _LR{_RScaleLength};
    const double& _Lz{_zScaleLength};
};

////////////////////////////////////////////////////////////////////

#endif
