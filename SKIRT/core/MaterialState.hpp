/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef MATERIALSTATE_HPP
#define MATERIALSTATE_HPP

#include "MediumState.hpp"

//////////////////////////////////////////////////////////////////////

/** An instance of the MaterialState class provides access to the medium state for a particular
    spatial cell and medium component, as determined during construction. This includes the common
    state variables for the cell as well as the specific state variables for the medium component.
    */
class MaterialState
{
    //============= Construction - Setup - Destruction =============

public:
    /** The constructor arguments specify the spatial cell and medium component to be represented.
        */
    MaterialState(MediumState& ms, int m, int h) : _ms{ms}, _m{m}, _h{h} {}

    /** TO DO */
    MaterialState(const MediumState& ms, int m, int h) : _ms{const_cast<MediumState&>(ms)}, _m{m}, _h{h} {}

    //============= Setting =============

public:
    /** This function sets the temperature \f$T\f$ of the medium component in the spatial cell. */
    void setTemperature(double value) { _ms.setTemperature(_m, _h, value); }

    //============= Querying =============

public:
    /** This function returns the volume \f$V\f$ of the spatial cell. */
    double volume() const { return _ms.volume(_m); }

    /** This function returns the aggregate bulk velocity \f${\boldsymbol{v}}\f$ of the medium in
        the spatial cell. */
    Vec bulkVelocity() const { return _ms.bulkVelocity(_m); }

    /** This function returns the magnetic field \f${\boldsymbol{B}}\f$ in the spatial cell. */
    Vec magneticField() const { return _ms.magneticField(_m); }

    /** This function returns the number density of the medium component in the spatial cell. */
    double numberDensity() const { return _ms.numberDensity(_m, _h); }

    /** This function returns the temperature \f$T\f$ of the medium component in the spatial
        cell. */
    double temperature() const { return _ms.temperature(_m, _h); }

    //======================== Data Members ========================

private:
    MediumState& _ms;
    int _m{-1};
    int _h{-1};
};

////////////////////////////////////////////////////////////////

#endif
