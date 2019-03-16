
#pragma once

#include "si/Action.hpp"
#include "si/Amount.hpp"
#include "si/Coefficient.hpp"
#include "si/ElectricCharge.hpp"
#include "si/Entropy.hpp"
#include "si/MolarEntropy.hpp"

#include "si/Operations.hpp"

namespace si {

    namespace consts {

        constexpr Entropy boltzmann()
        {
            using namespace si::literals;
            return 1.380649e-23_J_p_K;
        }

        constexpr Action planck ()
        {
            using namespace si::literals;
            return 6.62607015e-34_Js;
        }

        constexpr ElectricCharge e()
        {
            using namespace si::literals;
            return 1.602176634e-19_C;
        }

        namespace detail {
            using AvogadroDim = Dim<
                base::Mass<0>,
                base::Length<0>,
                base::Time<0>,
                base::Current<0>,
                base::Temperature<0>,
                base::Amount<-1>,
                base::LightIntensity<0>
            >;
            using per_mole_t = unit<AvogadroDim, factor_conv<std::ratio<1> > >;
        }

        constexpr auto avogadro()
        {
            return Value<detail::AvogadroDim>{ detail::per_mole_t { 6.02214076e23 } };
        }

        constexpr MolarEntropy R ()
        {
            return avogadro() * boltzmann();
        }
    }

}
