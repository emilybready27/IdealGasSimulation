#include "gas_simulation_app.h"

using glm::vec2;

namespace idealgas {

IdealGasApp::IdealGasApp() {
  // collect and set configuration for app
  parser_ = JsonParser(kPathToJsonFile, kFields);
  container_ = GasContainer(parser_);

  // set size of display window
  window_size_ = parser_.json_object["window_size"];
  margin_size_ = parser_.json_object["margin_size"];
  ci::app::setWindowSize(window_size_, window_size_);
}

void IdealGasApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
  container_.Display();
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();
}

}  // namespace idealgas
