#include "gas_container.h"

namespace idealgas {

using glm::vec2;

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


}

void GasContainer::AddParticle(Particle const& particle) {
    particles_.push_back(particle);
}


}  // namespace idealgas
