#include <catch2/catch.hpp>
#include <gas_simulation_app.h>

TEST_CASE("Test JsonParser construction") {
  std::string path = R"(C:\Users\Mary\Desktop\Cinder\my-projects\ideal-gas-ebready2\resources\configuration.json)";
  std::vector<std::string> fields = {"window_length", "window_width", "margin_size", "initial_velocity_factor",
                                     "particle_counts", "particle_radii", "particle_masses", "particle_colors",
                                     "bound_color", "background_color", "bar_count"};


  SECTION("Valid file") {
    REQUIRE_NOTHROW(JsonParser(path, fields));
  }

  SECTION("File not found") {
    std::string path = R"(config.json)";
    REQUIRE_THROWS_AS(JsonParser(path, fields), std::invalid_argument);
  }

  SECTION("Empty file") {
    std::string path = R"(C:\Users\Mary\Desktop\Cinder\my-projects\ideal-gas-ebready2\resources\empty.json)";
    REQUIRE_THROWS_AS(JsonParser(path, fields), std::invalid_argument);
  }

  SECTION("Malformed file") {
    std::string path = R"(C:\Users\Mary\Desktop\Cinder\my-projects\ideal-gas-ebready2\resources\malformed.json)";
    REQUIRE_THROWS_AS(JsonParser(path, fields), std::invalid_argument);
  }

  SECTION("Missing field") {
    std::string path = R"(C:\Users\Mary\Desktop\Cinder\my-projects\ideal-gas-ebready2\resources\missing.json)";
    REQUIRE_THROWS_AS(JsonParser(path, fields), std::invalid_argument);
  }
}