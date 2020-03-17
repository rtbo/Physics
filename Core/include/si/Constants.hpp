
#pragma once

#include "si/Config.hpp"

#ifdef HAVE_FREQUENCY_HPP
#    include "si/Frequency.hpp"
#endif
#ifdef HAVE_VELOCITY_HPP
#    include "si/Velocity.hpp"
#endif
#ifdef HAVE_ACTION_HPP
#    include "si/Action.hpp"
#endif
#ifdef HAVE_ELECTRICCHARGE_HPP
#    include "si/ElectricCharge.hpp"
#endif
#ifdef HAVE_ENTROPY_HPP
#    include "si/Entropy.hpp"
#endif
#ifdef HAVE_LUMINUOUSEFFICACY_HPP
#    include "si/LuminuousEfficacy.hpp"
#endif
#ifdef HAVE_MOLARENTROPY_HPP
#    include "si/MolarEntropy.hpp"
#endif

namespace si {

/*! \module provides definition for the seven constants that define the
 * SI and a few other derived units
 */
namespace consts {

#ifdef HAVE_FREQUENCY_HPP
    constexpr Frequency cesium_hyperfine_transition()
    {
        using namespace si::literals;
        return 9192631770_Hz;
    }
#endif

#ifdef HAVE_VELOCITY_HPP
    constexpr Velocity light_speed()
    {
        using namespace si::literals;
        return 299792458_m_p_s;
    }
#endif

#ifdef HAVE_ACTION_HPP
    constexpr Action planck()
    {
        using namespace si::literals;
        return 6.62607015e-34_Js;
    }
#endif

#ifdef HAVE_ELECTRICCHARGE_HPP
    constexpr ElectricCharge elementary_charge()
    {
        using namespace si::literals;
        return 1.602176634e-19_C;
    }
#endif

#ifdef HAVE_ENTROPY_HPP
    constexpr Entropy boltzmann()
    {
        using namespace si::literals;
        return 1.380649e-23_J_p_K;
    }
#endif

#ifdef HAVE_AMOUNT_HPP
    namespace detail {
        using PerMole = Dim<base::Mass<0>, base::Length<0>, base::Time<0>,
                            base::Current<0>, base::Temperature<0>,
                            base::Amount<-1>, base::LuminuousIntensity<0>>;
        using per_mole_t = unit<PerMole, factor_conv<std::ratio<1>>>;
    } // namespace detail

    constexpr auto avogadro()
    {
        return Value<detail::PerMole>{ detail::per_mole_t{ 6.02214076e23 } };
    }
#endif

#ifdef HAVE_LUMINUOUSEFFICACY_HPP
    constexpr LuminuousEfficacy luminuous_efficacy()
    {
        using namespace si::literals;
        return 683_lm_p_W;
    }
#endif
    // other derived constants

#ifdef HAVE_ENTROPY_HPP
    constexpr MolarEntropy gas() { return avogadro() * boltzmann(); }
#endif

} // namespace consts
} // namespace si
