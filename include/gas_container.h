#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"
#include "json_parser.h"

using glm::vec2;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * Constructs a GasContainer by initializing state with configuration details
   * given by JsonParser parameter.
   * @param parser
   */
  GasContainer(const JsonParser& parser);

  /**
   * Default constructor.
   */
  GasContainer() = default;

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  /**
   * Getters for GasContainer state.
   */
  std::vector<Particle> GetParticles() const;
  ci::Rectf GetBounds() const;
  vec2 GetInitialPosition() const;
  int GetInitialVelocityFactor() const;
  int GetParticleCount() const;
  std::vector<float> GetParticleRadius() const;
  std::vector<float> GetParticleMass() const;
  std::vector<ci::Color> GetParticleColor() const;
  ci::Color GetRectangleColor() const;

 private:
  /**
   * List of the Particles stored by the container.
   */
  std::vector<Particle> particles_;

  /**
   * Rectangle comprising the bounds for the container.
   */
  ci::Rectf bounds_;

  /**
   * Starting position for the particles at time 0.
   */
  vec2 initial_position_;

  /**
   * Factor used to randomize starting velocities.
   */
  int initial_velocity_factor_;

  /**
   * Default number of particles in the container.
   */
  int particle_count_;

  /**
   * List of radii for particles.
   */
  std::vector<float> particle_radii_;

  /**
   * List of masses for particles.
   */
  std::vector<float> particle_masses_;

  /**
   * List of colors for particles.
   */
  std::vector<ci::Color> particle_colors_;

  /**
   * Default color of the rectangular bounds.
   */
  ci::Color rectangle_color_;

  /**
   * Stores the configurations of the GasContainer from the Json data.
   * @param parser
   */
  void ExtractData(const JsonParser& parser);

  /**
   * Adds particles to the container after constructing them
   */
  void AddParticles();

};

}  // namespace idealgas
