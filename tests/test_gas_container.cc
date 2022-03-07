#include <catch2/catch.hpp>
#include <gas_simulation_app.h>
#include <gas_container.h>

using idealgas::GasContainer;

TEST_CASE("Test GasContainer construction") {
    JsonParser parser = JsonParser(idealgas::kPathToJsonFile, idealgas::kFields);
    GasContainer container = GasContainer(parser);

    SECTION("Added correct number of particles") {
        REQUIRE(container.GetParticles().size() == 50);
    }

    SECTION("Set correct bounds") {
        REQUIRE(container.GetBounds().getCenter() == ci::Rectf(vec2(100, 100), vec2(775, 775)).getCenter());
    }

    SECTION("Set correct initial position") {
        REQUIRE(container.GetInitialPosition() == vec2(775, 775));
    }

    SECTION("Extracted initial velocity factor correctly") {
        REQUIRE(container.GetInitialVelocityFactor() == 5);
    }

    SECTION("Extracted particle count correctly") {
        REQUIRE(container.GetParticleCount() == 50);
    }

    SECTION("Extracted particle radius correctly") {
        REQUIRE(container.GetParticleRadius() == 10.0);
    }

    SECTION("Extracted particle mass correctly") {
        REQUIRE(container.GetParticleMass() == 4.0);
    }

    SECTION("Extracted particle color correctly") {
        REQUIRE(container.GetParticleColor() == "green");
    }

    SECTION("Extracted rectangle color correctly") {
        REQUIRE(container.GetRectangleColor() == "purple");
    }
}
