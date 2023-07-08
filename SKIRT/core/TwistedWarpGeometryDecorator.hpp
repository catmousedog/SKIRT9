/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef TWISTEDWARPGEOMETRYDECORATOR_HPP
#define TWISTEDWARPGEOMETRYDECORATOR_HPP

#include "GenGeometry.hpp"

////////////////////////////////////////////////////////////////////

/** The TwistedWarpGeometryDecorator class is a geometry decorator that warps any geometry. 
    The warp only shifts the z-coordinate by \f[ h(R,\phi) = \frac{2H}{\pi} \sqrt{10\frac{R}{R_0}} 
    \sin\left(\sqrt{10\frac{R}{R_0}}\right) \cos\left(\phi\right). \f] Here \f$H\f$ is the max warp height and \f$R_0\f$ the max radius, outside of which the density is 0. Since this decorator only shifts the \f$z\f$-cooridnate the random point sampling and density evaluation comes down to just applying the warp to the points. */
class TwistedWarpGeometryDecorator : public GenGeometry
{
    ITEM_CONCRETE(TwistedWarpGeometryDecorator, GenGeometry, "a decorator that applies a twisted warp to any geometry")

        PROPERTY_ITEM(geometry, Geometry, "the general geometry to be warped")

        PROPERTY_DOUBLE(maxRadius, "the max radius of the warp")
        ATTRIBUTE_QUANTITY(maxRadius, "length")
        ATTRIBUTE_MIN_VALUE(maxRadius, "]0")

        PROPERTY_DOUBLE(maxWarpHeight, "the max height of the warp")
        ATTRIBUTE_QUANTITY(maxWarpHeight, "length")
        ATTRIBUTE_MIN_VALUE(maxWarpHeight, "[0")

    ITEM_END()

    //======================== Other Functions =======================

public:
    /** This function returns the density \f$\rho({\bf{r}})\f$ at the position \f${\bf{r}}\f$. It 
        applies the inverse warp back to the original density distribution and evaluates the density. 
        The density for \f$R\gt R_0\f$ is 0. */
    double density(Position bfr) const override;

    /** This function generates a random position from the geometry by
        drawing a random point from the three-dimensional probability density
        \f$p({\bf{r}})\,{\text{d}}{\bf{r}} = \rho({\bf{r}})\, {\text{d}}{\bf{r}}\f$. We apply the warp
        to the points generated from the original density distribution. */
    Position generatePosition() const override;

    /** This function returns the surface mass density along the X-axis, i.e.
        the integration of the mass density along the entire X-axis, \f[
        \Sigma_X = \int_{-\infty}^\infty \rho(x,0,0)\, {\text{d}}x.\f] This integral cannot be
        calculated analytically for the current decorator. */
    double SigmaX() const override;

    /** This function returns the surface mass density along the Y-axis, i.e.
        the integration of the mass density along the entire Y-axis, \f[
        \Sigma_Y = \int_{-\infty}^\infty \rho(0,y,0)\, {\text{d}}y.\f] This integral cannot be
        calculated analytically for the current decorator. */
    double SigmaY() const override;

    /** This function returns the surface mass density along the Z-axis, i.e.
        the integration of the mass density along the entire Z-axis, \f[
        \Sigma_Z = \int_{-\infty}^\infty \rho(0,0,z)\, {\text{d}}z.\f] For the present decorator, this integral
        is equal to the surface density of the unwarped model, as the warping only shifts the z-component. */
    double SigmaZ() const override;

private:
    /** This private function implements the formula for the height of the warped disc \f$h(R,\phi)\f$. */
    double warpHeight(double R, double phi) const;
};

////////////////////////////////////////////////////////////////////

#endif
