#include "gas_simulation_app.h"

namespace idealgas {

IdealGasApp::IdealGasApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);

  for (size_t i = 0; i < kDefaultParticleCount; i++) {
      Particle particle = Particle(kDefaultPosition, kDefaultVelocity, kDefaultRadius);
      container_.AddParticle(particle);
  }
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
