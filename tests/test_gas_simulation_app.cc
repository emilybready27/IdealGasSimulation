#include <catch2/catch.hpp>
#include <gas_simulation_app.h>

TEST_CASE("Test IdealGasApp construction") {
  std::string path = R"(C:\Users\Mary\Desktop\Cinder\my-projects\ideal-gas-ebready2\resources\configuration.json)";
  std::vector<std::string> fields = {"window_size", "margin_size", "initial_velocity_factor", "particle_count",
                                     "particle_radius", "particle_mass", "particle_color", "rectangle_color"};
  JsonParser parser = JsonParser(path, fields);

  SECTION("Sets window size correctly") {
    REQUIRE(parser.json_object["window_size"] == 875);
  }

  SECTION("Sets margin size correctly") {
    REQUIRE(parser.json_object["margin_size"] == 100);
  }
}