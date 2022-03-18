#pragma once

#include "particle.h"
#include <cinder/Rect.h>
#include "cinder/gl/gl.h"

namespace idealgas {

class Histogram {
 public:
  Histogram(size_t bar_count,
            const ci::Rectf& bounds,
            const ci::Color& bound_color,
            const ci::Color& particle_colors);

  void Display() const;

  void AdvanceOneFrame(const std::vector<Particle>& particles, const ci::Color& color);

 private:
  ci::Rectf bounds_;
  ci::Color bound_color_;
  ci::Color bar_color_;
  size_t bar_count_;
  float bar_width_;
  size_t bar_weight_;
  std::vector<size_t> frequencies_;
};

} // namespace idealgas
