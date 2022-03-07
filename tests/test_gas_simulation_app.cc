#include <catch2/catch.hpp>
#include <gas_simulation_app.h>

TEST_CASE("Test IdealGasApp construction") {
    JsonParser parser = JsonParser(idealgas::kPathToJsonFile, idealgas::kFields);

    SECTION("Sets window size correctly") {
        REQUIRE(parser.json_object["window_size"] == 875);
    }

    SECTION("Sets margin size correctly") {
        REQUIRE(parser.json_object["margin_size"] == 100);
    }
}