#include "particle.h"

using glm::vec2;

namespace idealgas {

Particle::Particle(const glm::vec2& position, const glm::vec2& velocity, const float& radius) {
    position_ = position;
    velocity_ = velocity;
    radius_ = radius;
}

void Particle::SetPosition(const vec2& position) {
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

bool Particle::IsMovingTowards(vec2 const& other_position, vec2 const& other_velocity) {
    return glm::dot(velocity_ - other_velocity, position_ - other_position) < 0;
}

} // namespace idealgas