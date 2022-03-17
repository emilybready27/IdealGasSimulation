#include "gas_simulation_app.h"

using glm::vec2;

namespace idealgas {

IdealGasApp::IdealGasApp() {
  // collect and set configuration for app
  parser_ = JsonParser(kPathToJsonFile, kFields);
  container_ = GasContainer(parser_);

  // set background color with char pointer
  std::string color = parser_.json_object["background_color"];
  background_color_ = ci::Color(&(color[0]));

  // set size of display window
  window_length_ = parser_.json_object["window_length"];
  window_width_ = parser_.json_object["window_width"];
  margin_size_ = parser_.json_object["margin_size"];
  ci::app::setWindowSize(window_length_, window_width_);
}

void IdealGasApp::draw() {
  ci::Color background_color(background_color_);
  ci::gl::clear(background_color);
  container_.Display();
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();
}

}  // namespace idealgas
