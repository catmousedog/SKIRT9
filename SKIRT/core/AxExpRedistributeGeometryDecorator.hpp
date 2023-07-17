
/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef AXEXPREDISTRIBUTEGEOMETRYDECORATOR_HPP
#define AXEXPREDISTRIBUTEGEOMETRYDECORATOR_HPP

#include "RedistributeGeometryDecorator.hpp"

////////////////////////////////////////////////////////////////////

/** The abstract AxExpRedistributeGeometryDecorator class implements a decorator that 
    adjusts another geometry by multiplying the density with an axial exponential weight function 
    \f[ \rho'(r, \phi, z) = n \rho(R, \phi, z) \exp{(-R\, L_R)}\exp{(-z\, L_z)}. \f] */
class AxExpRedistributeGeometryDecorator : public RedistributeGeometryDecorator
{
    ITEM_CONCRETE(AxExpRedistributeGeometryDecorator, RedistributeGeometryDecorator,
                  "a decorator that redistributes another geometry with an axial power law")
        ATTRIBUTE_TYPE_INSERT(AxExpRedistributeGeometryDecorator, "Dimension2")

        PROPERTY_DOUBLE(RScaleLength, "the negative power of the radial part of the weight function")
        ATTRIBUTE_QUANTITY(RScaleLength, "length")
        ATTRIBUTE_MIN_VALUE(RScaleLength, "[0")

        PROPERTY_DOUBLE(zScaleLength, "the negative power of the vertical part of the weight function")
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
    /** The weight function is the power law: \f$\exp{-L_R\, R}\exp{-L_z\, z}\f$. */
    double weight(Position bfr) const override;

    /** The max weight is used in the rejection method and is equal to \f$1$. */
    double maxWeight() const override;

    //======================== Data Members ========================

private:
    // aliases to discoverable data members for ease of notation and backwards compatibility
    const double& _LR{_RScaleLength};
    const double& _Lz{_zScaleLength};
};

////////////////////////////////////////////////////////////////////

#endif
