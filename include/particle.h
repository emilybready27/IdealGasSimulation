#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace idealgas {

class Particle {
public:
    Particle(const vec2& position, const vec2& velocity, const float& radius);

    void SetPosition(const vec2& position);
    void SetPositionX(const float &x);
    void SetPositionY(const float &y);
    vec2 GetPosition() const;
    float GetPositionX() const;
    float GetPositionY() const;
    void SetVelocity(const vec2& velocity);
    void SetVelocityX(const float &x);
    void SetVelocityY(const float &y);
    vec2 GetVelocity() const;
    float GetVelocityX() const;
    float GetVelocityY() const;
    void SetRadius(const float& radius);
    float GetRadius() const;

    void HandleWallCollision(const cinder::Rectf &bounds);
    void HandleParticleCollision(Particle &other);

    bool Equals(const Particle& other) const;

private:
    vec2 position_;
    vec2 velocity_;
    float radius_;
    // later add mass, color

    bool IsMovingTowards(const vec2 &other_position, const vec2 &other_velocity) const;
    bool IsMovingTowards(const vec2 &other_position) const;
    float GetNearestBound(const float value, const float min, const float max) const;
    bool IsOutsideBounds(const float value, const float min, const float max) const;
};

} // namespace idealgas
