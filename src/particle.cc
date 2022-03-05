#include "particle.h"

namespace idealgas {

Particle::Particle(const ci::vec2& position, const ci::vec2& velocity, const float& radius) {
    position_ = position;
    velocity_ = velocity;
    radius_ = radius;
}

void Particle::SetPosition(const ci::vec2& position) {
    position_ = position;
}

ci::vec2 Particle::GetPosition() const {
    return position_;
}

void Particle::SetVelocity(const ci::vec2& velocity) {
    velocity_ = velocity;
}

ci::vec2 Particle::GetVelocity() const {
    return velocity_;
}

void Particle::SetRadius(const float& radius) {
    radius_ = radius;
}

float Particle::GetRadius() const {
    return radius_;
}

} // namespace idealgas