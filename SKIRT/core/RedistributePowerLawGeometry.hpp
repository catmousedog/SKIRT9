
/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef REDISTRIBUTEPOWERLAWGEOMETRY_HPP
#define REDISTRIBUTEPOWERLAWGEOMETRY_HPP

#include "RedistributeGeometryDecorator.hpp"

////////////////////////////////////////////////////////////////////

/** The abstract SphericalPowerLawRedistributeGeometryDecorator class implements a decorator that adjusts another geometry
    by setting the density equal to zero inside or outside a region defined in a subclass. Each
    ClipGeometryDecorator subclass must implement the virtual functions dimension() and inside().
    The decorator increases the density in the remaining region with a constant factor to ensure
    that the total mass remains equal to one. The current implementation does not properly adjust
    the surface densities along the coordinate axes for the mass taken away by the cavity. */
class SphericalPowerLawRedistributeGeometryDecorator : public RedistributeGeometryDecorator
{

    ITEM_CONCRETE(SphericalPowerLawRedistributeGeometryDecorator, RedistributeGeometryDecorator,
                  "a decorator that clips another geometry")

        // ATTRIBUTE_TYPE_INSERT(SphericalPowerLawRedistributeGeometryDecorator, "Dimension2")

        PROPERTY_DOUBLE(power, "the negative power of the weight function")
        ATTRIBUTE_MIN_VALUE(power, "]0")

        PROPERTY_DOUBLE(minRadius, "")
        ATTRIBUTE_QUANTITY(minRadius, "length")
        ATTRIBUTE_MIN_VALUE(minRadius, "]0 pc")

    ITEM_END()

    //======================== Other Functions =======================
public:
    /** */
    int dimension() const override;

protected:
    /** This pure virtual function, to be implemented by a subclass, returns true if the specified
        position is inside the boundary defined by the subclass, i.e. the point is in the region
        that would be carved away when creating a cavity, or in the region that would be retained
        when cropping. */
    double weight(Position bfr) const override;

    /** */
    double maxWeight() const override;

    /** */
    bool inside(Position bfr) const override;
};

////////////////////////////////////////////////////////////////////

#endif
