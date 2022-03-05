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

  const int kWindowSize = 875;
  const int kMargin = 100;

 private:
    GasContainer container_;

    const ci::Color kDefaultColor = ci::Color("white");
    const vec2 kTopLeft = vec2(100,100);
    const vec2 kBottomRight = vec2(775,775);
    const ci::Rectf kDefaultBounds = ci::Rectf(kTopLeft, kBottomRight);
    const size_t kDefaultParticleCount = 50;
    const ci::vec2 kDefaultPosition = ci::vec2(10,10);
    const ci::vec2 kDefaultVelocity = ci::vec2(1,0);
    const float kDefaultRadius = 10.0;
};

}  // namespace idealgas
