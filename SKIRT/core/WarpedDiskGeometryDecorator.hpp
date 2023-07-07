/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef WARPEDDISKGEOMETRYDECORATOR_HPP
#define WARPEDDISKGEOMETRYDECORATOR_HPP

#include "GenGeometry.hpp"

////////////////////////////////////////////////////////////////////

/** The WarpedDiskGeometryDecorator class is a geometry decorator that warps any geometry. 
    The warp only shifts the z-coordinate by \f[ h(R,\phi) = \frac{2H}{\pi} \sqrt{10\frac{R}{R_0}} 
    \sin\left(\sqrt{10\frac{R}{R_0}}\right) \cos\left(\phi-\phi_0\right). \f] Here \f$H\f$ is the max warp height,
    \f$R_0\f$ the max warp radius and \f$\phi_0\f$ the phase zero-point. Since this decorator only shifts the 
    \f$z\f$-cooridnate the random point sampling and density evaluation comes down to just applying the warp 
    to the points. */
class WarpedDiskGeometryDecorator : public GenGeometry
{
    ITEM_CONCRETE(WarpedDiskGeometryDecorator, GenGeometry, "A decorator that warps any disc-like geometry.")

        PROPERTY_ITEM(geometry, Geometry, "the general geometry to be warped")

        PROPERTY_DOUBLE(maxRadius, "the max radius of the warp")
        ATTRIBUTE_QUANTITY(maxRadius, "length")
        ATTRIBUTE_MIN_VALUE(maxRadius, "]0")

        PROPERTY_DOUBLE(maxWarpHeight, "the max height of the warp")
        ATTRIBUTE_QUANTITY(maxWarpHeight, "length")
        ATTRIBUTE_MIN_VALUE(maxWarpHeight, "[0")

        PROPERTY_DOUBLE(phaseZeroPoint, "the phase zero-point")
        ATTRIBUTE_QUANTITY(phaseZeroPoint, "posangle")
        ATTRIBUTE_MIN_VALUE(phaseZeroPoint, "[0 deg")
        ATTRIBUTE_MAX_VALUE(phaseZeroPoint, "360 deg]")
        ATTRIBUTE_DEFAULT_VALUE(phaseZeroPoint, "0 deg")
        ATTRIBUTE_DISPLAYED_IF(phaseZeroPoint, "Level2")

    ITEM_END()

    //======================== Other Functions =======================

public:
    /** This function returns the density \f$\rho({\bf{r}})\f$ at the position \f${\bf{r}}\f$. It 
        applies the inverse warp back to the original density distribution and evaluates the density. */
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
