#include "gas_container.h"

namespace idealgas {

GasContainer::GasContainer() {
    //bounds_ = kDefaultBounds;
}

GasContainer::GasContainer(ci::Rectf bounds) {
    bounds_ = bounds;
}

void GasContainer::Display() const {
    for (const Particle& particle : particles_) {
        ci::gl::color(ci::Color("orange"));
        ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetRadius());
    }
}

void GasContainer::AdvanceOneFrame() {
    for (Particle& particle : particles_) {
        particle.SetPosition(particle.GetPosition() + particle.GetVelocity());

        particle.CheckWallCollision(bounds_);
        // if particle is going to hit another particle, or if
        // particle is going to hit a wall, execute collision
    }
}

void GasContainer::AddParticle(Particle const& particle) {
    particles_.push_back(particle);
}


}  // namespace idealgas
