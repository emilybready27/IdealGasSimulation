#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"
#include "particle.h"

namespace idealgas {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  void draw() override;
  void update() override;

  // TODO: Delete this comment. Feel free to play around with these variables
  // provided that you can see the entire UI on your screen.
  const int kWindowSize = 875;
  const int kMargin = 100;

 private:
    GasContainer container_ = GasContainer(kDefaultBounds);
    const size_t kDefaultParticleCount = 50;
    const ci::Rectf kDefaultBounds = ci::Rectf(vec2(100, 100), vec2(600, 400));
    const ci::vec2 kDefaultPosition = ci::vec2(0,0);
    const ci::vec2 kDefaultVelocity = ci::vec2(0,0);
    const float kDefaultRadius = 1.0;
};

}  // namespace idealgas
