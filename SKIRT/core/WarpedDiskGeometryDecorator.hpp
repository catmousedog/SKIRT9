/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef WARPEDDISKGEOMETRYDECORATOR_HPP
#define WARPEDDISKGEOMETRYDECORATOR_HPP

#include "GenGeometry.hpp"
#include "HeightShiftDecorator.hpp"

////////////////////////////////////////////////////////////////////

/** The WarpedDiskGeometryDecorator class is a geometry decorator that warps any geometry. 
    The warp only shifts the z-coordinate by \f[ h(R,\phi) = \frac{2H}{\pi} \sqrt{10\frac{R}{R_0}} 
    \sin\left(\sqrt{10\frac{R}{R_0}}\right) \cos\left(\phi-\phi_0\right). \f] Here \f$H\f$ is the max warp height,
    \f$R_0\f$ the max warp radius and \f$\phi_0\f$ the phase zero-point. Since this decorator only shifts the 
    \f$z\f$-cooridnate the random point sampling and density evaluation comes down to just applying the warp 
    to the points. */
class WarpedDiskGeometryDecorator : public HeightShiftDecorator
{
    ITEM_CONCRETE(WarpedDiskGeometryDecorator, HeightShiftDecorator, "a decorator that warps any disc-like geometry")

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

private:
    /** This private function implements the formula for the height of the warped disc \f$h(R,\phi)\f$. */
    double heightShift(double R, double phi) const override;
};

////////////////////////////////////////////////////////////////////

#endif
