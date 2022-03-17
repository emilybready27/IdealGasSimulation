#include "histogram.h"
#include <algorithm>

namespace idealgas {

Histogram::Histogram(const cinder::Rectf &bounds, const cinder::Color &bound_color,
                               const ci::Color& particle_color, const int particle_count) {
  bounds_ = bounds;
  bound_color_ = bound_color;
  bar_color_ = particle_color;
//  bar_count_ = particle_count;
  bar_count_ = 5; // TODO: add to JSON configuration
  bar_width_ = bounds_.getWidth() / (float) bar_count_;
  frequencies_ = std::vector<int>(bar_count_);
}

Histogram::Histogram() {
}

void Histogram::Display() const {
  ci::gl::color(bound_color_);
  ci::gl::drawStrokedRect(bounds_);

  for (int i = 0; i < bar_count_; i++) { // only display green particles atm
    ci::gl::color(bar_color_);
    vec2 top_left = vec2(bounds_.x1 + (bar_width_ * i),
                              bounds_.y2 - (frequencies_[i]));
    vec2 bottom_right = vec2(bounds_.x1 + (bar_width_ * (i + 1)),
                                  bounds_.y2);
    ci::gl::drawSolidRect(ci::Rectf(top_left, bottom_right));
  }
}

void Histogram::AdvanceOneFrame(const std::vector<Particle>& particles,
                                const ci::Color& color) {
  std::vector<Particle> colored_particles = GetColoredParticles(particles, color);

  std::vector<float> speeds;
  for (const Particle& colored_particle : colored_particles) {
    speeds.push_back(glm::length(colored_particle.GetVelocity()));
  }

  std::sort(speeds.begin(), speeds.end());
  float delta = speeds.at(speeds.size() - 1) / (float) bar_count_;

  frequencies_ = std::vector<int>(bar_count_); // reset the frequencies
  for (size_t i = 0; i < speeds.size(); i++) {
    for (int j = 0; j < bar_count_; j++) {
      if (speeds[i] <= delta + (delta * (float) j)) {
        frequencies_[j]++;
        break;
      }
    }
  }
}

std::vector<Particle> Histogram::GetColoredParticles(const std::vector<Particle>& particles,
                                                     const ci::Color& color) {
  std::vector<Particle> colored_particles;
  for (const Particle& particle : particles) {
    if (particle.GetColor() == color) {
      colored_particles.push_back(particle);
    }
  }
  return colored_particles;
}

} // namespace idealgas

