#include "gas_container.h"

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
  particle_count_ = parser.json_object["particle_count"];

  for (const float radius : parser.json_object["particle_radii"]) {
    particle_radii_.push_back(radius);
  }
  for (const float mass : parser.json_object["particle_masses"]) {
    particle_masses_.push_back(mass);
  }

  // setting Color requires a pointer to a char
  for (const std::string color : parser.json_object["particle_colors"]) {
    particle_colors_.push_back(ci::Color(&(color[0])));
  }
  std::string color = parser.json_object["bound_color"];
  bound_color_ = ci::Color(&(color[0]));
}

void GasContainer::AddParticles() {
  for (int i = 0; i < particle_count_; i++) {

    // set particle state using configuration
    // set velocity magnitude to random number > 0 and < initial_velocity_factor_
    Particle particle = Particle(
                initial_position_,
                vec2((std::rand() % initial_velocity_factor_) + 1,
                        (std::rand() % initial_velocity_factor_) + 1),
                 particle_radii_[i % 3],
                 particle_masses_[i % 3],
                 particle_colors_[i % 3]); // TODO: magic number!

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
  for (Particle& particle : particles_) {
    // new position = old position + velocity
    particle.SetPosition(particle.GetPosition() + particle.GetVelocity());

    // resets velocity and position of particle after wall collision (if any)
    particle.HandleWallCollision(bounds_);

    for (Particle& other_particle : particles_) {
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

int GasContainer::GetInitialVelocityFactor() const {
  return initial_velocity_factor_;
}

int GasContainer::GetParticleCount() const {
  return particle_count_;
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
