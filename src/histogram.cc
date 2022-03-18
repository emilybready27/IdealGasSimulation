#include "histogram.h"
#include <algorithm>

namespace idealgas {

Histogram::Histogram(const int bar_count,
                     const cinder::Rectf &bounds,
                     const cinder::Color &bound_color,
                     const ci::Color& particle_color) {
  bar_count_ = bar_count;
  bounds_ = bounds;
  bound_color_ = bound_color;
  bar_color_ = particle_color;
  bar_width_ = bounds_.getWidth() / (float) bar_count_;
  frequencies_ = std::vector<int>(bar_count_);
}

Histogram::Histogram() {
}

void Histogram::Display() const {
  ci::gl::color(bound_color_);
  ci::gl::drawStrokedRect(bounds_);

  // display particle speeds as bars
  for (int i = 0; i < bar_count_; i++) {
    ci::gl::color(bar_color_);
    vec2 top_left = vec2(bounds_.x1 + (bar_width_ * (float) i),
                              bounds_.y2 - (float) (frequencies_[i] * 10)); // TODO: magic number
    vec2 bottom_right = vec2(bounds_.x1 + (bar_width_ * (float) (i + 1)),
                                  bounds_.y2);
    ci::gl::drawSolidRect(ci::Rectf(top_left, bottom_right));
  }

  // display x-label
  ci::gl::pushModelMatrix();
  ci::gl::translate(bounds_.getCenter().x, bounds_.y2); // move to center of x-axis
  ci::gl::scale( 3, 3);
  ci::gl::drawStringCentered("Speed",
                             vec2(0, 0),
                             bound_color_);
  ci::gl::popModelMatrix();

  // display y-label
  ci::gl::pushModelMatrix();
  ci::gl::translate(bounds_.x1, bounds_.getCenter().y); // move to center of y-axis
  ci::gl::rotate((float) M_PI / 2);
  ci::gl::scale( 3, 3);
  ci::gl::drawStringCentered("Frequency",
                             vec2(0, 0),
                             bound_color_);
  ci::gl::popModelMatrix();

}

void Histogram::AdvanceOneFrame(const std::vector<Particle>& particles,
                                const ci::Color& color) {

  std::vector<float> speeds; // speeds of all particles, of all colors
  std::vector<float> color_speeds; // speeds of particles of given color
  for (const Particle& particle : particles) {
    float speed = glm::length(particle.GetVelocity());
    speeds.push_back(speed);
    if (particle.GetColor() == color) {
      color_speeds.push_back(speed);
    }
  }

  float delta = *std::max_element(speeds.begin(), speeds.end()) / (float) bar_count_;

  frequencies_ = std::vector<int>(bar_count_); // reset the frequencies
  for (size_t i = 0; i < color_speeds.size(); i++) {
    for (int j = 0; j < bar_count_; j++) {
      if (color_speeds[i] <= delta + (delta * (float) j)) {
        frequencies_[j]++;
        break;
      }
    }
  }
}

} // namespace idealgas

