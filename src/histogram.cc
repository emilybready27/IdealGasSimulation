#include "histogram.h"
#include <algorithm>

namespace idealgas {

Histogram::Histogram(const cinder::Rectf &bounds, const cinder::Color &bound_color,
                               const ci::Color& particle_color, const int particle_count) {
  bounds_ = bounds;
  bound_color_ = bound_color;
  bar_color_ = particle_color;
//  bar_count_ = particle_count;
  bar_count_ = 10; // TODO: add to JSON configuration
  bar_width_ = bounds_.getWidth() / (float) bar_count_;
  frequencies_ = std::vector<int>(bar_count_);
}

Histogram::Histogram() {
}

void Histogram::Display() const {
  ci::gl::color(bound_color_);
  ci::gl::drawStrokedRect(bounds_);

  // display particle speeds as bars
  for (int i = 0; i < bar_count_; i++) { // only display green particles atm
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
  ci::gl::scale( 2, 2 );
  ci::gl::drawStringCentered("Speed",
                             vec2(0, 0),
                             ci::Color("white")); // TODO: add Json configuration
  ci::gl::popModelMatrix();

  // display y-label
  ci::gl::pushModelMatrix();
  ci::gl::translate(bounds_.x1, bounds_.getCenter().y); // move to center of y-axis
  ci::gl::rotate((float) M_PI / 2);
  ci::gl::scale( 2, 2 );
  ci::gl::drawStringCentered("Frequency",
                             vec2(0, 0),
                             ci::Color("white"));
  ci::gl::popModelMatrix();

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

