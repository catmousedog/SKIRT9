/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef HEIGHTSHIFTDECORATOR_HPP
#define HEIGHTSHIFTDECORATOR_HPP

#include "GenGeometry.hpp"

////////////////////////////////////////////////////////////////////

/** The HeightShiftDecorator class is an abstract geometry decorator that shifts an axisymmetric geometry. 
    The warp only shifts the z-coordinate by some abstract \f[ h(R,\phi). \f] Since this decorator only shifts the 
    \f$z\f$-cooridnate, the random point sampling and density evaluation comes down to just applying the shift 
    to the positions. */
class HeightShiftDecorator : public GenGeometry
{
    ITEM_ABSTRACT(HeightShiftDecorator, GenGeometry, "an abstract decorator that shifts any axisymmetric geometry")
        PROPERTY_ITEM(geometry, Geometry, "the general geometry to be shifted")
    ITEM_END()

    //======================== Other Functions =======================

public:
    /** This function returns the density \f$\rho({\bf{r}})\f$ at the position \f${\bf{r}}\f$. It 
        applies the inverse shift back to the original density distribution and evaluates the density. */
    double density(Position bfr) const override;

    /** This function generates a random position from the geometry by
        drawing a random point from the three-dimensional probability density
        \f$p({\bf{r}})\,{\text{d}}{\bf{r}} = \rho({\bf{r}})\, {\text{d}}{\bf{r}}\f$. We then apply the shift
        to the points generated from the original density distribution. */
    Position generatePosition() const override;

    /** This function returns the surface mass density along the Z-axis, i.e.
        the integration of the mass density along the entire Z-axis, \f[
        \Sigma_Z = \int_{-\infty}^\infty \rho(0,0,z)\, {\text{d}}z.\f] For the present decorator, this integral
        is equal to the surface density of the unwarped model, as the warping only shifts the z-component. */
    double SigmaZ() const override;

protected:
    /** This private function implements the formula for the height of the shifted disc \f$h(R,\phi)\f$. */
    virtual double heightShift(double R, double phi) const = 0;
};

////////////////////////////////////////////////////////////////////

#endif
