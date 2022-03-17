#include "histogram.h"

idealgas::Histogram::Histogram(const cinder::Rectf& bounds, const cinder::Color& bound_color,
                               const std::vector<ci::Color>& particle_colors) {
  bounds_ = bounds;
  bound_color_ = bound_color;
  graph_colors_ = particle_colors;

}

void idealgas::Histogram::Display() const {
  ci::gl::color(bound_color_);
  ci::gl::drawStrokedRect(bounds_);
}

void idealgas::Histogram::AdvanceOneFrame() {

}

idealgas::Histogram::Histogram() {

}


