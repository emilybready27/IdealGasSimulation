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
  size_t GetInitialVelocityFactor() const;
  std::vector<ci::Color> GetParticleColors() const;
  ci::Color GetBoundColor() const;

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
  size_t initial_velocity_factor_;

  /**
   * List of number of each type of particle.
   */
  std::vector<size_t> particle_counts_;

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
  ci::Color bound_color_;

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
