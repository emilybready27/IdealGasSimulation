#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace idealgas {

/**
 * The data members and behaviors of a gas particle.
 */
class Particle {
public:
    Particle(const vec2& position, const vec2& velocity, const float radius,
             const float mass, const ci::Color& color);

    Particle(const vec2& position, const vec2& velocity, const float radius);

    void SetPosition(const vec2& position);
    void SetPositionX(const float &x);
    void SetPositionY(const float &y);
    vec2 GetPosition() const;
    float GetPositionX() const;
    float GetPositionY() const;
    void SetVelocity(const vec2& velocity);
    void SetVelocityX(const float x);
    void SetVelocityY(const float y);
    vec2 GetVelocity() const;
    float GetVelocityX() const;
    float GetVelocityY() const;
    void SetRadius(const float radius);
    float GetRadius() const;
    void SetMass(const float mass);
    float GetMass() const;
    void SetColor(const ci::Color& color);
    ci::Color GetColor() const;

    void HandleWallCollision(const cinder::Rectf &bounds);
    void HandleParticleCollision(Particle &other);
    bool IsMovingTowards(const Particle &other_particle) const;
    bool IsMovingTowards(const vec2 &other_position, const vec2 &other_velocity) const;
    bool Equals(const Particle& other) const;

private:
    vec2 position_;
    vec2 velocity_;
    float radius_;
    float mass_;
    ci::Color color_;

    float GetNearestBound(const float value, const float min, const float max) const;
    bool IsOutsideBounds(const float value, const float min, const float max) const;


};

} // namespace idealgas
