
/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef SPHEREDISTRIBUTEGEOMETRYDECORATOR_HPP
#define SPHEREDISTRIBUTEGEOMETRYDECORATOR_HPP

#include "SpheGeometry.hpp"

////////////////////////////////////////////////////////////////////

/** The abstract SpheRedistributeGeometryDecorator class implements a decorator that adjusts another
    spherical geometry by multiplying the density with some abstract spherical weight function
    \f[ \rho'(r) = n \rho(r) w(r). \f] Each SpheRedistributeGeometryDecorator subclass must implement
    the virtual functions weight(double r) and maxWeight(). The decorator renormalizes the distribution
    by using the importance sampling method from the original distribution. The normalisation constant
    is chosen such that:
    \f[ \int n\rho({\bf{r}})w({\bf{r}})\; d{\bf{r}} = \int 4\pi r^2\,n\rho(r)w(r)\;dr=1. \f]
    The random radii are generated using the rejection method with the reference distribution the
    original density. The current implementation does not properly adjust the surface densities along
    the coordinate axes. */
class SpheRedistributeGeometryDecorator : public SpheGeometry
{
    ITEM_ABSTRACT(SpheRedistributeGeometryDecorator, SpheGeometry,
                  "a decorator that redistributes spherical geometry with a spherical weight function")
        ATTRIBUTE_TYPE_DISPLAYED_IF(RedistributeGeometryDecorator, "Level2")

        PROPERTY_ITEM(geometry, SpheGeometry, "the geometry for which the density will be redistributed")

    ITEM_END()

    //============= Construction - Setup - Destruction =============

protected:
    /** This function calculates the norm using the importance sampling method from the original
        distribution. It also calculates the factor \f$c\f$ for the rejection method, which is just
        the maxWeight(). */
    void setupSelfAfter() override;

    //======================== Other Functions =======================

public:
    /** This function returns the normalised density at a radius \f$r\f$. */
    double density(double r) const override;

    /** This function generates a random radius from the geometry using the rejection method. It draws
        a random radius from the probability density \f$\rho(r)\f$, this point is
        accepted if \f$t=\xi \frac{\max_{r}{w(r)}}{w(r)}\le 1.\f$ */
    double randomRadius() const override;

    /** This function returns the r-axis surface density, i.e. the integration of the density along
        the entire r-axis, \f[ \Sigma_r = \int_0^\infty \rho(r)\,{\text{d}}r. \f] For a 
        generic spherical geometry this decorator will not have an analytical solution for this integral. 
        We use  the r-axis surface density of the original distribution. */
    double Sigmar() const override;

protected:
    /** This pure virtual function, to be implemented by a subclass, gives the weight function's value
        at a given radius. This function does not need to be normalized. */
    virtual double weight(double r) const = 0;

    /** This pure virtual function, to be implemented by a subclass, gives the maximum value of the weight
        function. This value is used in the rejection method. */
    virtual double maxWeight() const = 0;

    //======================== Data Members ========================

private:
    // values initialized during setup
    double _norm{0.};
    double _maxWeight;
};

////////////////////////////////////////////////////////////////////

#endif
