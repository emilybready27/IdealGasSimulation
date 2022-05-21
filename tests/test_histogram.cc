#include <catch2/catch.hpp>
#include <histogram.h>
#include <gas_simulation_app.h>

using idealgas::Histogram;
using idealgas::IdealGasApp;

TEST_CASE("Test Histogram construction") {
  ci::Rectf bounds = ci::Rectf(vec2(100, 100), vec2(1200, 500));
  Histogram histogram = Histogram(15, bounds, ci::Color("purple"), ci::Color("green"));

  SECTION("Sets correct bar width") {
    REQUIRE(histogram.GetBarWidth() == (float) 1100 / 15);
  }

  SECTION("Sets correct bar_weight") {
    REQUIRE(histogram.GetBarWeight() == 5);
  }
}

TEST_CASE("Test Display") {
  int window_length = 2500;
  int window_width = 1500;
  int margin_size = 100;

  SECTION("Calculates correct location of first histogram") {
    ci::Rectf bounds = ci::Rectf(vec2(margin_size,
                                      margin_size),
                                 vec2((window_length / 2) - (margin_size / 2),
                                      window_width / 3));
    REQUIRE(bounds.getCenter() == vec2(650, 300));
  }

  SECTION("Calculates correct location of second histogram") {
    ci::Rectf bounds = ci::Rectf(vec2(margin_size,
                                      (window_width / 3) + (margin_size / 2)),
                                 vec2((window_length / 2) - (margin_size / 2),
                                      (2 * window_width / 3) - (margin_size / 2)));
    REQUIRE(bounds.getCenter() == vec2(650, 750));
  }

  SECTION("Calculates correct location of third histogram") {
    ci::Rectf bounds = ci::Rectf(vec2(margin_size,
                                      2 * window_width / 3),
                                 vec2((window_length / 2) - (margin_size / 2),
                                      window_width - margin_size));
    REQUIRE(bounds.getCenter() == vec2(650, 1200));
  }

  SECTION("Calculates correct initial height of first bar") {
    ci::Rectf bounds = ci::Rectf(vec2(100, 100), vec2(1200, 500));
    Histogram histogram = Histogram(15, bounds, ci::Color("purple"), ci::Color("green"));
    REQUIRE(vec2(bounds.x1 + (histogram.GetBarWidth() * 0),
                 bounds.y2 - (histogram.GetFrequencies()[0] * histogram.GetBarWeight())) == vec2(100,500));
  }

}