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

void Particle::CheckWallCollision(ci::Rectf const& bounds) {
    // if particle isn't between east and west bounds, move it to the nearest bound
    if (position_.x - radius_ <= bounds.x1 || position_.x + radius_ >= bounds.x2) {
        position_.x = glm::clamp(position_.x, bounds.x1 + radius_, bounds.x2 - radius_);

        // if particle will collide with east or west wall, negate velocity in x direction
        if (IsMovingTowards(vec2(bounds.x1, position_.y), vec2(0,0))
            || IsMovingTowards(vec2(bounds.x2, position_.y), vec2(0,0))) {
            velocity_.x *= -1;
        }
    }

    // if particle isn't between north and south bounds, move it to the nearest bound
    if (position_.y - radius_ <= bounds.y1 || position_.y + radius_ >= bounds.y2) {
        position_.y = glm::clamp(position_.y, bounds.y1 + radius_, bounds.y2 - radius_);

        // if particle will collide with north or south wall, negate velocity in y direction
        if (IsMovingTowards(vec2(position_.x, bounds.y1), vec2(0,0))
            || IsMovingTowards(vec2(position_.x, bounds.y2), vec2(0,0))) {
            velocity_.y *= -1;
        }
    }
}

void Particle::CheckParticleCollision(Particle& other) {
    if ((*this).Equals(other)) {
        return;
    }

    if (glm::distance(position_, other.position_) <= radius_ + other.radius_
        && IsMovingTowards(other.position_, other.velocity_)) {

        vec2 velocity_new = glm::dot(velocity_ - other.velocity_, position_ - other.position_)
                * (position_ - other.position_)
                / (float) pow(glm::length(position_ - other.position_),2.0);
        vec2 other_velocity_new = glm::dot(other.velocity_ - velocity_, other.position_ - position_)
                * (other.position_ - position_)
                / (float) pow(glm::length(other.position_ - position_), 2.0);

        velocity_ -= velocity_new;
        other.velocity_ -= other_velocity_new;
    }
}

bool Particle::IsMovingTowards(vec2 const& other_position, vec2 const& other_velocity) {
    return glm::dot(velocity_ - other_velocity, position_ - other_position) < 0;
}

bool Particle::Equals(const Particle& other) const {
    if (this == &other) {
        return true;
    }
    return position_ == other.position_
        && velocity_ == other.velocity_
        && fabs(radius_ - other.radius_) <= std::numeric_limits<float>::epsilon();
}

} // namespace idealgas