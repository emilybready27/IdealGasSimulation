#include "gas_simulation_app.h"

namespace idealgas {

IdealGasApp::IdealGasApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
  container_ = GasContainer(kDefaultBounds);

  for (size_t i = 0; i < kDefaultParticleCount; i++) {
      Particle particle = Particle(
              kBottomRight,
              vec2(-(std::rand() % 10), -(std::rand() % 10)),
              kDefaultRadius);
      container_.AddParticle(particle);
  }
}

void IdealGasApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
  ci::gl::color(kDefaultColor);
  ci::gl::drawStrokedRect(kDefaultBounds);

  container_.Display();
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();
}

}  // namespace idealgas
