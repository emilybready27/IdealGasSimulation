#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace idealgas {

class Particle {
public:
    Particle(const vec2& position, const vec2& velocity, const float& radius);

    void SetPosition(const vec2& position);
    vec2 GetPosition() const;
    void SetVelocity(const vec2& velocity);
    vec2 GetVelocity() const;
    void SetRadius(const float& radius);
    float GetRadius() const;

    void CheckWallCollision(const cinder::Rectf &bounds);
    void CheckParticleCollision(Particle &other_particle);

    bool Equals(const Particle& other) const;

private:
    vec2 position_;
    vec2 velocity_;
    float radius_;
    // later add mass, color

    bool IsMovingTowards(const vec2 &other_position, const vec2 &other_velocity);

};

} // namespace idealgas
