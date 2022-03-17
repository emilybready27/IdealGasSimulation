#pragma once

#include "particle.h"
#include <cinder/Rect.h>
#include "cinder/gl/gl.h"

namespace idealgas {

class Histogram {
 public:
  Histogram(const cinder::Rectf &bounds,
            const cinder::Color &bound_color,
            const ci::Color &particle_colors,
            const int particle_count);

  Histogram();

  void Display() const;

  void AdvanceOneFrame(const std::vector<Particle>& particles,
                       const ci::Color& color);

 private:
  ci::Rectf bounds_;
  ci::Color bound_color_;
  ci::Color bar_color_;
  int bar_count_;
  float bar_width_;
  std::vector<int> frequencies_;

  std::vector<Particle> GetColoredParticles(const std::vector<Particle> &particles,
                                            const cinder::Color &color);

};

} // namespace idealgas
