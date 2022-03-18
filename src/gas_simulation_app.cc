#include "gas_simulation_app.h"

using glm::vec2;

namespace idealgas {

IdealGasApp::IdealGasApp() {
  // collect and set configuration for app
  parser_ = JsonParser(kPathToJsonFile, kFields);
  container_ = GasContainer(parser_);

  // set background color with char pointer
  std::string color = parser_.json_object["background_color"];
  background_color_ = ci::Color(&(color[0])); // fix?

  // set size of display window
  window_length_ = parser_.json_object["window_length"];
  window_width_ = parser_.json_object["window_width"];
  margin_size_ = parser_.json_object["margin_size"];
  ci::app::setWindowSize(window_length_, window_width_);

  // create histograms
  std::vector<ci::Rectf> histogram_bounds;
  histogram_bounds.emplace_back(vec2(margin_size_,
                                     margin_size_),
                                vec2((window_length_ / 2) - (margin_size_ / 2),
                                     window_width_ / 3));
  histogram_bounds.emplace_back(vec2(margin_size_,
                                     (window_width_ / 3) + (margin_size_ / 2)),
                                vec2((window_length_ / 2) - (margin_size_ / 2),
                                     (2 * window_width_ / 3) - (margin_size_ / 2)));
  histogram_bounds.emplace_back(vec2(margin_size_,
                                     2 * window_width_ / 3),
                                vec2((window_length_ / 2) - (margin_size_ / 2),
                                     window_width_ - margin_size_));

  int bar_count = parser_.json_object["bar_count"];
  for (size_t i = 0; i < kParticleTypes; i++) {
    histograms_.emplace_back(bar_count,
                             histogram_bounds[i],
                             container_.GetBoundColor(),
                             container_.GetParticleColors()[i]);
  }
}

void IdealGasApp::draw() {
  ci::Color background_color(background_color_);
  ci::gl::clear(background_color);
  container_.Display();

  for (size_t i = 0; i < kParticleTypes; i++) {
    histograms_[i].Display();
  }
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();

  for (size_t i = 0; i < kParticleTypes; i++) {
    ci::Color color = container_.GetParticleColors()[i];
    histograms_[i].AdvanceOneFrame(container_.GetParticles(), color);
  }
}

}  // namespace idealgas
