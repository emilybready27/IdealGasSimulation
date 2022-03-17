#include "histogram.h"
#include <algorithm>

idealgas::Histogram::Histogram(const cinder::Rectf &bounds, const cinder::Color &bound_color,
                               const ci::Color& particle_color, const int particle_count) {
  bounds_ = bounds;
  bound_color_ = bound_color;
  bar_color_ = particle_color;
  bar_count_ = particle_count;
  bar_width_ = bounds_.getWidth() / (float) bar_count_;
  frequencies_ = std::vector<int>(bar_count_);
}

idealgas::Histogram::Histogram() {
}

void idealgas::Histogram::Display() const {
  ci::gl::color(bound_color_);
  ci::gl::drawStrokedRect(bounds_);

  for (int i = 0; i < bar_count_; i++) { // only display green particles atm
    ci::gl::color(bar_color_);
    vec2 top_left = vec2(bounds_.x1 + (bar_width_ * i),
                              bounds_.y2 - frequencies_[i]);
    vec2 bottom_right = vec2(bounds_.x1 + (bar_width_ * (i + 1)),
                                  bounds_.y2);
    ci::gl::drawSolidRect(ci::Rectf(top_left, bottom_right));
  }
}

void idealgas::Histogram::AdvanceOneFrame(const std::vector<Particle>& particles) {
//  std::vector<int> speeds;
//  for (const Particle& particle : particles) {
//    speeds.push_back(glm::length(particle.GetVelocity()));
//  }
//
//  std::sort(speeds.begin(), speeds.end());

  for (int i = 0; i < bar_count_; i++) {
    frequencies_[i]++;
  }
}


