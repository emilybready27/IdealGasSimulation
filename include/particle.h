#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace idealgas {

/**
 * The data members and behaviors of a gas particle.
 */
class Particle {
 public:
  /**
   * Constructs a Particle from the given states.
   * @param position vec2
   * @param velocity vec2
   * @param radius float
   * @param mass float
   * @param color ci::Color
   */
  Particle(const vec2& position, const vec2& velocity, const float radius,
           const float mass, const ci::Color& color);

  /**
   * Detects collision of Particle with the container bounds based on its
   * position and velocity and updates both states accordingly.
   * @param bounds ci::Rectf
   */
  void HandleWallCollision(const ci::Rectf &bounds);

  /**
   * Detects collision of Particle with another given Particle based on their
   * positions and velocities and updates both states of both particles accordingly.
   * @param other
   */
  void HandleParticleCollision(Particle &other);

  /**
   * Determines if the Particle is moving towards the other given Particle.
   * @param other_particle Particle
   * @return bool
   */
  bool IsMovingTowards(const Particle &other_particle) const;

  /**
   * Determines if the Particle is moving towards another Particle given
   * the other's position and velocity.
   * @param other_particle Particle
   * @return bool
   */
  bool IsMovingTowards(const vec2 &other_position, const vec2 &other_velocity) const;

  /**
   * Determines if two Particles have the same internal state.
   * @param other Particle
   * @return bool
   */
  bool Equals(const Particle& other) const;

  /**
   * Getters and setters for Particle position.
   */
  void SetPosition(const vec2& position);
  void SetPositionX(const float &x);
  void SetPositionY(const float &y);
  vec2 GetPosition() const;
  float GetPositionX() const;
  float GetPositionY() const;

  /**
   * Getters and setters for Particle velocity.
   */
  void SetVelocity(const vec2& velocity);
  void SetVelocityX(const float x);
  void SetVelocityY(const float y);
  vec2 GetVelocity() const;
  float GetVelocityX() const;
  float GetVelocityY() const;

  /**
   * Getters for other Particle state.
   */
  float GetRadius() const;
  ci::Color GetColor() const;

 private:
  /**
   * Location of particle in container as an x, y coordinate-pair.
   */
  vec2 position_;

  /**
   * Speed of particle in container as an x, y coordinate-pair.
   */
  vec2 velocity_;

  /**
   * Radius of the given particle.
   */
  float radius_;

  /**
   * Mass of the given particle (for next week).
   */
  float mass_;

  /**
   * Color of the given particle.
   */
  ci::Color color_;

  /**
   * If given value is outside of bounds of [min, max],
   * returns the bound the value is closes to.
   * @param value float
   * @param min float
   * @param max float
   * @return float
   */
  float GetNearestBound(const float value, const float min, const float max) const;

  /**
   * Determines if the given value is outside of bounds of [min, max].
   * @param value float
   * @param min float
   * @param max float
   * @return bool
   */
  bool IsOutsideBounds(const float value, const float min, const float max) const;

};

} // namespace idealgas
