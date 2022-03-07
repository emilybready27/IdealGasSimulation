#include "gas_simulation_app.h"

using glm::vec2;

namespace idealgas {

IdealGasApp::IdealGasApp() {
    ci::app::setWindowSize(kWindowSize, kWindowSize);
    top_left_ = vec2(kMargin, kMargin);
    bottom_right_ = vec2(kWindowSize - kMargin, kWindowSize - kMargin);
    bounds_ = ci::Rectf(top_left_, bottom_right_);

    std::ifstream file(kPathToJsonFile);
    json json_object = json::parse(file);
    file.close();

    container_ = GasContainer(json_object, bounds_);
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
