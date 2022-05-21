#include <catch2/catch.hpp>
#include <gas_simulation_app.h>

TEST_CASE("Test IdealGasApp construction") {
  std::string path = R"(C:\Users\Mary\Desktop\Cinder\my-projects\ideal-gas-ebready2\resources\configuration.json)";
  std::vector<std::string> fields = {"window_length", "window_width", "margin_size", "initial_velocity_factor",
                                     "particle_counts", "particle_radii", "particle_masses", "particle_colors",
                                     "bound_color", "background_color", "bar_count"};
  JsonParser parser = JsonParser(path, fields);

  SECTION("Sets background color correctly") {
    REQUIRE(parser.GetBackgroundColor() == "black");
  }

  SECTION("Sets window length correctly") {
    REQUIRE(parser.GetWindowLength() == 2500);
  }

  SECTION("Sets window width correctly") {
    REQUIRE(parser.GetWindowWidth() == 1500);
  }

  SECTION("Sets margin size correctly") {
    REQUIRE(parser.GetMarginSize() == 100);
  }
}