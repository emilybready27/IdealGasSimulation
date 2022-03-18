#include "gas_container.h"
#include "gas_simulation_app.h"

namespace idealgas {

GasContainer::GasContainer(const JsonParser& parser) {
  ExtractData(parser);
  AddParticles();
}

void GasContainer::ExtractData(const JsonParser& parser) {
  // set bounds to right half of window
  int length = parser.json_object["window_length"];
  int width = parser.json_object["window_width"];
  int margin = parser.json_object["margin_size"];
  vec2 top_left = vec2((length / 2) + (margin / 2),
                       margin);
  vec2 bottom_right = vec2(length - margin,
                           width - margin);
  bounds_ = ci::Rectf(top_left, bottom_right);

  // particles start in lower-right corner of container
  initial_position_ = bounds_.getLowerRight();
  initial_velocity_factor_ = parser.json_object["initial_velocity_factor"];

  for (const size_t count : parser.json_object["particle_counts"]) {
    particle_counts_.push_back(count);
  }
  for (const float radius : parser.json_object["particle_radii"]) {
    particle_radii_.push_back(radius);
  }
  for (const float mass : parser.json_object["particle_masses"]) {
    particle_masses_.push_back(mass);
  }

  // setting Color requires a pointer to a char
  for (const std::string color : parser.json_object["particle_colors"]) {
    particle_colors_.emplace_back(&(color[0]));
  }
  std::string color = parser.json_object["bound_color"];
  bound_color_ = ci::Color(&(color[0]));
}

void GasContainer::AddParticles() {
  size_t total_particle_count = std::accumulate(particle_counts_.begin(), particle_counts_.end(), 0);
  for (size_t i = 0; i < total_particle_count; i++) {
    // set particle state using configuration
    // set velocity magnitude to random number > 0 and < initial_velocity_factor_
    Particle particle = Particle(
                initial_position_,
                vec2((std::rand() % initial_velocity_factor_) + 1,
                        (std::rand() % initial_velocity_factor_) + 1),
                 particle_radii_[i % IdealGasApp::kParticleTypes],
                 particle_masses_[i % IdealGasApp::kParticleTypes],
                 particle_colors_[i % IdealGasApp::kParticleTypes]);

    particles_.push_back(particle);
  }
}

void GasContainer::Display() const {
  // display rectangle
  ci::gl::color(bound_color_);
  ci::gl::drawStrokedRect(bounds_);

  // display circular particles
  for (const Particle& particle : particles_) {
    ci::gl::color(particle.GetColor());
    ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetRadius());
  }
}

void GasContainer::AdvanceOneFrame() {
  for (size_t i = 0; i < particles_.size(); i++) {
    Particle& particle = particles_[i];

    // new position = old position + velocity
    particle.SetPosition(particle.GetPosition() + particle.GetVelocity());

    // resets velocity and position of particle after wall collision (if any)
    particle.HandleWallCollision(bounds_);

    for (size_t j = i + 1; j < particles_.size(); j++) {
      Particle& other_particle = particles_[j];

      // resets velocity and position of both particles after collision (if any)
      particle.HandleParticleCollision(&other_particle);
    }
  }
}

std::vector<Particle> GasContainer::GetParticles() const {
  return particles_;
}

ci::Rectf GasContainer::GetBounds() const {
  return bounds_;
}

vec2 GasContainer::GetInitialPosition() const {
  return initial_position_;
}

size_t GasContainer::GetInitialVelocityFactor() const {
  return initial_velocity_factor_;
}

std::vector<ci::Color> GasContainer::GetParticleColors() const {
  return particle_colors_;
}
ci::Color GasContainer::GetBoundColor() const {
  return bound_color_;
}

}  // namespace idealgas
