#include "particle.h"

using glm::vec2;

namespace idealgas {

Particle::Particle(const vec2& position, const vec2& velocity, float radius,
                 float mass, const ci::Color& color) {
  position_ = position;
  velocity_ = velocity;
  radius_ = radius;
  mass_ = mass;
  color_ = color;
}

void Particle::HandleWallCollision(const ci::Rectf& bounds) {
  // if particle isn't between west and east bounds, move it to the nearest bound
  if (IsOutsideBounds(position_.x, bounds.x1, bounds.x2)) {
    position_.x = GetNearestBound(position_.x, bounds.x1, bounds.x2);

    // if particle will collide with west or east wall, negate velocity in x direction
    if (IsMovingTowards(vec2(bounds.x1, position_.y),vec2(0,0))
        || IsMovingTowards(vec2(bounds.x2, position_.y),vec2(0,0))) {
      velocity_.x *= -1;
    }
  }

  // if particle isn't between north and south bounds, move it to the nearest bound
  if (IsOutsideBounds(position_.y, bounds.y1, bounds.y2)) {
    position_.y = GetNearestBound(position_.y, bounds.y1, bounds.y2);

    // if particle will collide with north or south wall, negate velocity in y direction
    if (IsMovingTowards(vec2(position_.x, bounds.y1),vec2(0,0))
        || IsMovingTowards(vec2(position_.x, bounds.y2),vec2(0,0))) {
      velocity_.y *= -1;
    }
  }
}

void Particle::HandleParticleCollision(Particle* other) {
  if ((*this).Equals(*other)) { // collision with itself
    return;
  }

  // collision if two particles are touching and moving towards each other
  // update both of their positions and velocities according to formula given
  if (glm::distance(position_, other->position_) <= radius_ + other->radius_
      && IsMovingTowards(other->position_, other->velocity_)) {

    std::vector<vec2> v = {velocity_, other->velocity_};
    std::vector<vec2> x = {position_, other->position_};
    std::vector<float> m = {mass_, other->mass_};

    vec2 v_0 = glm::dot(v[0] - v[1], x[0] - x[1]) * (x[0] - x[1]) / pow(glm::length(x[0] - x[1]), 2);
    vec2 v_1 = glm::dot(v[1] - v[0], x[1] - x[0]) * (x[1] - x[0]) / pow(glm::length(x[1] - x[0]), 2);

    velocity_ -= v_0 * (2 * m[1] / (m[0] + m[1]));
    other->velocity_ -= v_1 * (2 * m[0] / (m[0] + m[1]));

    position_ += velocity_;
    other->position_ += other->velocity_;
  }
}

float Particle::GetNearestBound(float value, float min, float max) const {
  return glm::clamp(value, min + radius_, max - radius_);
}

bool Particle::IsOutsideBounds(float value, float min, float max) const {
  return value - radius_ <= min || value + radius_ >= max;
}

bool Particle::IsMovingTowards(const Particle& other_particle) const {
  return IsMovingTowards(other_particle.position_, other_particle.velocity_);
}

bool Particle::IsMovingTowards(vec2 const& other_position, vec2 const& other_velocity) const {
  return glm::dot(velocity_ - other_velocity, position_ - other_position) < 0;
}

bool Particle::Equals(const Particle& other) const {
  if (this == &other) {
    return true;
  }
  return position_ == other.position_
         && velocity_ == other.velocity_
         && fabs(radius_ - other.radius_) <= std::numeric_limits<float>::epsilon()
         && fabs(mass_ - other.mass_) <= std::numeric_limits<float>::epsilon()
         && color_ == other.color_;
}

void Particle::SetPosition(const vec2& position) {
  position_ = position;
}

void Particle::SetPositionX(float x) {
  position_.x = x;
}

void Particle::SetPositionY(float y) {
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

void Particle::SetVelocityX(float x) {
  velocity_.x = x;
}

void Particle::SetVelocityY(float y) {
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

float Particle::GetRadius() const {
  return radius_;
}

ci::Color Particle::GetColor() const {
  return color_;
}

} // namespace idealgas