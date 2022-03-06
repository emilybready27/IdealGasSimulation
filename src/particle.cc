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

void Particle::SetPositionX(const float& x) {
    position_.x = x;
}

void Particle::SetPositionY(const float& y) {
    position_.y = y;
}

ci::vec2 Particle::GetPosition() const {
    return position_;
}

float Particle::GetPositionX() const {
    return position_.x;
}

float Particle::GetPositionY() const {
    return position_.y;
}

void Particle::SetVelocity(const ci::vec2& velocity) {
    velocity_ = velocity;
}

void Particle::SetVelocityX(const float& x) {
    velocity_.x = x;
}

void Particle::SetVelocityY(const float& y) {
    velocity_.y = y;
}

ci::vec2 Particle::GetVelocity() const {
    return velocity_;
}

float Particle::GetVelocityX() const {
    return velocity_.x;
}

float Particle::GetVelocityY() const {
    return velocity_.y;
}

void Particle::SetRadius(const float& radius) {
    radius_ = radius;
}

float Particle::GetRadius() const {
    return radius_;
}

void Particle::HandleWallCollision(ci::Rectf const& bounds) {
    // if particle isn't between west and east bounds, move it to the nearest bound
    if (IsOutsideBounds(position_.x, bounds.x1, bounds.x2)) {
        position_.x = GetNearestBound(position_.x, bounds.x1, bounds.x2);

        // if particle will collide with west or east wall, negate velocity in x direction
        if (IsMovingTowards(vec2(bounds.x1, position_.y))
            || IsMovingTowards(vec2(bounds.x2, position_.y))) {
            velocity_.x *= -1;
        }
    }

    // if particle isn't between north and south bounds, move it to the nearest bound
    if (IsOutsideBounds(position_.y, bounds.y1, bounds.y2)) {
        position_.y = GetNearestBound(position_.y, bounds.y1, bounds.y2);

        // if particle will collide with north or south wall, negate velocity in y direction
        if (IsMovingTowards(vec2(position_.x, bounds.y1))
            || IsMovingTowards(vec2(position_.x, bounds.y2))) {
            velocity_.y *= -1;
        }
    }
}

void Particle::HandleParticleCollision(Particle& other) {
    if ((*this).Equals(other)) {
        return;
    }

    if (glm::distance(position_, other.position_) <= radius_ + other.radius_
        && IsMovingTowards(other.position_, other.velocity_)) {

        std::vector<vec2> v = {velocity_, other.velocity_};
        std::vector<vec2> x = {position_, other.position_};

        vec2 v_0 = glm::dot(v[0] - v[1], x[0] - x[1]) * (x[0] - x[1]) / pow(glm::length(x[0] - x[1]), 2);
        vec2 v_1 = glm::dot(v[1] - v[0], x[1] - x[0]) * (x[1] - x[0]) / pow(glm::length(x[1] - x[0]), 2);

        velocity_ -= v_0;
        other.velocity_ -= v_1;
    }
}

float Particle::GetNearestBound(const float value, const float min, const float max) const {
    return glm::clamp(value, min + radius_, max - radius_);
}

bool Particle::IsOutsideBounds(const float value, const float min, const float max) const {
    return value - radius_ <= min || value + radius_ >= max;
}

bool Particle::IsMovingTowards(vec2 const& other_position, vec2 const& other_velocity) const {
    return glm::dot(velocity_ - other_velocity, position_ - other_position) < 0;
}

bool Particle::IsMovingTowards(vec2 const& other_position) const {
    return IsMovingTowards(other_position, vec2(0,0));
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