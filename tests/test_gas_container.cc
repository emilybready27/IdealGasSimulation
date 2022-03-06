#include <catch2/catch.hpp>

#include <gas_container.h>

using idealgas::GasContainer;

TEST_CASE("Placeholder testt") {
    GasContainer container;
    container.AdvanceOneFrame();
    REQUIRE(1 > 0);
}