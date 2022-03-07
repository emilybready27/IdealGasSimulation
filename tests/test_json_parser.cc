#include <catch2/catch.hpp>
#include <gas_simulation_app.h>

TEST_CASE("Test JsonParser construction") {
    SECTION("Valid file") {
        REQUIRE_NOTHROW(JsonParser(idealgas::kPathToJsonFile, idealgas::kFields));
    }

    SECTION("File not found") {
        std::string path = R"(config.json)";
        REQUIRE_THROWS_AS(JsonParser(path, idealgas::kFields), std::invalid_argument);
    }

    SECTION("Empty file") {
        std::string path = R"(C:\Users\Mary\Desktop\Cinder\my-projects\ideal-gas-ebready2\resources\empty.json)";
        REQUIRE_THROWS_AS(JsonParser(path, idealgas::kFields), std::invalid_argument);
    }

    SECTION("Malformed file") {
        std::string path = R"(C:\Users\Mary\Desktop\Cinder\my-projects\ideal-gas-ebready2\resources\malformed.json)";
        REQUIRE_THROWS_AS(JsonParser(path, idealgas::kFields), std::invalid_argument);
    }

    SECTION("Missing field") {
        std::string path = R"(C:\Users\Mary\Desktop\Cinder\my-projects\ideal-gas-ebready2\resources\missing.json)";
        REQUIRE_THROWS_AS(JsonParser(path, idealgas::kFields), std::invalid_argument);
    }

}