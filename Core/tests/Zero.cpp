
#include "ph/Physics.hpp"

#include "catch.hpp"



TEST_CASE("Zero", "[zero]")
{

    SECTION("comparison") {

        REQUIRE(ph::Volume{} == ph::zero);
        REQUIRE(ph::Volume::fromM3(1.0) > ph::zero);
        REQUIRE(ph::Volume::fromM3(-1.0) < ph::zero);

    }


}

