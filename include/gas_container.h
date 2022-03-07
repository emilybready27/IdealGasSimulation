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
     *
     */
    GasContainer() = default;
    GasContainer(const JsonParser& parser);

    /**
     * Displays the container walls and the current positions of the particles.
     */
    void Display() const;

    /**
     * Updates the positions and velocities of all particles (based on the rules
     * described in the assignment documentation).
     */
    void AdvanceOneFrame();

    std::vector<Particle> GetParticles() const;
    ci::Rectf GetBounds() const;
    vec2 GetInitialPosition() const;
    int GetInitialVelocityFactor() const;
    int GetParticleCount() const;
    float GetParticleRadius() const;
    float GetParticleMass() const;
    ci::Color GetParticleColor() const;
    ci::Color GetRectangleColor() const;


private:
    std::vector<Particle> particles_;
    ci::Rectf bounds_;
    vec2 initial_position_;
    int initial_velocity_factor_;
    int particle_count_;
    float particle_radius_;
    float particle_mass_;
    ci::Color particle_color_;
    ci::Color rectangle_color_;

    void ExtractData(const JsonParser& parser);
    void AddParticles();
};

}  // namespace idealgas
