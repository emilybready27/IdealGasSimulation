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
  ci::Rectf bounds = ci::Rectf(vec2(margin_size_,
                                    margin_size_),
                               vec2((window_length_ / 2) - (margin_size_ / 2),
                                    window_width_ / 3)); // TODO: magic number
  histograms_.emplace_back(bounds,
                         container_.GetBoundColor(),
                         container_.GetParticleColors()[0],
                         container_.GetParticleCount() / 3); // TODO: magic number

  bounds = ci::Rectf(vec2(margin_size_,
                          (window_width_ / 3) + (margin_size_ / 2)),
                     vec2((window_length_ / 2) - (margin_size_ / 2),
                          (2 * window_width_ / 3) - (margin_size_ / 2))); // TODO: magic number
  histograms_.emplace_back(bounds,
                           container_.GetBoundColor(),
                           container_.GetParticleColors()[1],
                           container_.GetParticleCount() / 3); // TODO: magic number

  bounds = ci::Rectf(vec2(margin_size_,
                          2 * window_width_ / 3),
                     vec2((window_length_ / 2) - (margin_size_ / 2),
                          window_width_ - margin_size_)); // TODO: magic number
  histograms_.emplace_back(bounds,
                           container_.GetBoundColor(),
                           container_.GetParticleColors()[2],
                           container_.GetParticleCount() / 3); // TODO: magic number
}

void IdealGasApp::draw() {
  ci::Color background_color(background_color_);
  ci::gl::clear(background_color);
  container_.Display();

  for (int i = 0; i < 3; i++) { // TODO: magic number
    histograms_[i].Display();
  }
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();

  for (int i = 0; i < 3; i++) { // TODO: magic number
    ci::Color color = container_.GetParticleColors()[i];
    histograms_[i].AdvanceOneFrame(container_.GetParticles(color));
  }
}

}  // namespace idealgas
