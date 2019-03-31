
#pragma once

#include "si/Config.hpp"

#ifdef HAVE_ACTION_HPP
#include "si/Action.hpp"
#endif
#ifdef HAVE_COEFFICIENT_HPP
#include "si/Coefficient.hpp"
#endif
#ifdef HAVE_ELECTRICCHARGE_HPP
#include "si/ElectricCharge.hpp"
#endif
#ifdef HAVE_ENTROPY_HPP
#include "si/Entropy.hpp"
#endif
#ifdef HAVE_MOLARENTROPY_HPP
#include "si/MolarEntropy.hpp"
#endif

namespace si {

    namespace consts {

        constexpr double pi = 3.14159265358979323846;

#ifdef HAVE_ENTROPY_HPP
        constexpr Entropy boltzmann()
        {
            using namespace si::literals;
            return 1.380649e-23_J_p_K;
        }
#endif

#ifdef HAVE_ACTION_HPP
        constexpr Action planck ()
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

#ifdef HAVE_AMOUNT_HPP
        namespace detail {
            using PerMole = Dim<
                base::Mass<0>,
                base::Length<0>,
                base::Time<0>,
                base::Current<0>,
                base::Temperature<0>,
                base::Amount<-1>,
                base::LightIntensity<0>
            >;
            using per_mole_t = unit<PerMole, factor_conv<std::ratio<1> > >;
        }

        constexpr auto avogadro()
        {
            return Value<detail::PerMole>{ detail::per_mole_t { 6.02214076e23 } };
        }

# ifdef HAVE_ENTROPY_HPP
        constexpr MolarEntropy gas ()
        {
            return avogadro() * boltzmann();
        }
    }
# endif
#endif
}
