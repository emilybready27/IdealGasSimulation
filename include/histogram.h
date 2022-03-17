#pragma once

#include <cinder/Rect.h>
#include "cinder/gl/gl.h"

namespace idealgas {

class Histogram {
 public:
  Histogram(const ci::Rectf& bounds, const ci::Color& bound_color,
            const std::vector<ci::Color>& particle_colors);

    Histogram();

    void Display() const;

  void AdvanceOneFrame();

 private:
  ci::Rectf bounds_;
  ci::Color bound_color_;
  std::vector<ci::Color> graph_colors_;
};

} // namespace idealgas
