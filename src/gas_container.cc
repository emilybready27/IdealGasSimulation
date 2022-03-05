#include "gas_container.h"

namespace idealgas {

    using glm::vec2;

    GasContainer::GasContainer() {
        bounds_ = kDefaultBounds;
    }

    GasContainer::GasContainer(ci::Rectf bounds) {
        bounds_ = bounds;
    }

    void GasContainer::Display() const {
        ci::gl::color(kDefaultColor);
        ci::gl::drawStrokedRect(kDefaultBounds);
    }

    void GasContainer::AdvanceOneFrame() {

    }

    void GasContainer::AddParticle(Particle const& particle) {
        particles_.push_back(particle);
    }


}  // namespace idealgas
