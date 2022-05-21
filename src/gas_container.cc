#include "gas_container.h"
#include "gas_simulation_app.h"

namespace idealgas {

GasContainer::GasContainer(const JsonParser& parser) {
  // set bounds to right half of window
  int length = parser.GetWindowLength();
  int width = parser.GetWindowWidth();
  int margin = parser.GetMarginSize();
  bounds_ = ci::Rectf(vec2((length / 2) + (margin / 2), margin),
                      vec2(length - margin, width - margin));

  // particles start in lower-right corner of container
  initial_position_ = bounds_.getLowerRight();
  initial_velocity_factor_ = parser.GetInitialVelocityFactor();

  particle_counts_ = parser.GetParticleCounts();
  particle_radii_ = parser.GetParticleRadii();
  particle_masses_ = parser.GetParticleMasses();
  particle_colors_ = parser.GetParticleColors();
  bound_color_ = parser.GetBoundColor();

  // construct and store particles in a vector
  AddParticles();
}

void GasContainer::AddParticles() {
  size_t total_particle_count = std::accumulate(particle_counts_.begin(), particle_counts_.end(), 0);
  for (size_t i = 0; i < total_particle_count; i++) {
    // set particle state using configuration
    // set velocity magnitude to random number > 0 and <= initial_velocity_factor_
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

std::vector<size_t> GasContainer::GetParticleCounts() const {
  return particle_counts_;
}

std::vector<float> GasContainer::GetParticleRadii() const {
  return particle_radii_;
}

std::vector<float> GasContainer::GetParticleMasses() const {
  return particle_masses_;
}

std::vector<ci::Color> GasContainer::GetParticleColors() const {
  return particle_colors_;
}
ci::Color GasContainer::GetBoundColor() const {
  return bound_color_;
}

}  // namespace idealgas
