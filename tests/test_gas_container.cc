#include <catch2/catch.hpp>
#include <gas_container.h>

using idealgas::GasContainer;

TEST_CASE("Test GasContainer construction") {
  std::string path = R"(C:\Users\Mary\Desktop\Cinder\my-projects\ideal-gas-ebready2\resources\configuration.json)";
  std::vector<std::string> fields = {"window_length", "window_width", "margin_size", "initial_velocity_factor",
                                     "particle_counts", "particle_radii", "particle_masses", "particle_colors",
                                     "bound_color", "background_color", "bar_count"};

  JsonParser parser = JsonParser(path, fields);
  GasContainer container = GasContainer(parser);

  SECTION("Added correct number of particles") {
    REQUIRE(container.GetParticles().size() == 150);
  }

  SECTION("Set correct bounds") {
    REQUIRE(container.GetBounds().getCenter() == vec2(1850, 750));
  }

  SECTION("Set correct initial position") {
    REQUIRE(container.GetInitialPosition() == vec2(2400, 1400));
  }

  SECTION("Extracted initial velocity factor correctly") {
    REQUIRE(container.GetInitialVelocityFactor() == 5);
  }

  SECTION("Extracted particle counts correctly") {
    REQUIRE(container.GetParticleCounts() == std::vector<size_t>{50, 50, 50});
  }

  SECTION("Extracted particle radii correctly") {
    REQUIRE(container.GetParticleRadii() == std::vector<float>{10.0, 10.0, 25.0});
  }

  SECTION("Extracted particle masses correctly") {
    REQUIRE(container.GetParticleMasses() == std::vector<float>{1.0, 10.0, 40.0});
  }

  SECTION("Extracted particle colors correctly") {
    REQUIRE(container.GetParticleColors() == std::vector<ci::Color>{"green", "teal", "maroon"});
  }

  SECTION("Extracted bound color correctly") {
    REQUIRE(container.GetBoundColor() == "purple");
  }
}
