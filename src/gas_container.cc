#include "gas_container.h"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

namespace idealgas {

GasContainer::GasContainer(json json_object, ci::Rectf bounds) {
    particle_count_ = json_object["particle_count"];
    particle_radius_ = json_object["particle_radius"];
    particle_mass_ = json_object["particle_mass"];
    std::string color = json_object["particle_color"];
    particle_color_ = ci::Color(&(color[0]));
    color = json_object["rectangle_color"];
    rectangle_color_ = ci::Color(&(color[0]));

    bounds_ = bounds;
    initial_position_ = bounds_.getLowerRight();
    initial_velocity_factor_ = json_object["initial_velocity_factor"];

    for (size_t i = 0; i < particle_count_; i++) {
        Particle particle = Particle(
                initial_position_,
                vec2((std::rand() % initial_velocity_factor_) + 1,
                            (std::rand() % initial_velocity_factor_) + 1),
                particle_radius_,
                particle_mass_,
                particle_color_);
        particles_.push_back(particle);
    }
}

void GasContainer::Display() const {
    ci::gl::color(rectangle_color_);
    ci::gl::drawStrokedRect(bounds_);

    for (const Particle& particle : particles_) {
        ci::gl::color(particle.GetColor());
        ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetRadius());
    }
}

void GasContainer::AdvanceOneFrame() {
    for (Particle& particle : particles_) {
        particle.SetPosition(particle.GetPosition() + particle.GetVelocity());

        particle.HandleWallCollision(bounds_);

        for (Particle& other_particle : particles_) {
            particle.HandleParticleCollision(other_particle);
        }
    }
}

}  // namespace idealgas
