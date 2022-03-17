#include <catch2/catch.hpp>
#include <gas_container.h>

using idealgas::GasContainer;

TEST_CASE("Test GasContainer construction") {
  std::string path = R"(C:\Users\Mary\Desktop\Cinder\my-projects\ideal-gas-ebready2\resources\configuration.json)";
  std::vector<std::string> fields = {"window_size", "margin_size", "initial_velocity_factor", "particle_count",
                                     "particle_radius", "particle_mass", "particle_color", "rectangle_color",
                                     "background_color"};

  JsonParser parser = JsonParser(path, fields);
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
    REQUIRE(container.GetBoundColor() == "purple");
  }
}
