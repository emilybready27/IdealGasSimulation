#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
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
    GasContainer(json j, ci::Rectf bounds);
    //GasContainer(ci::Rectf bounds);

/**
     * Displays the container walls and the current positions of the particles.
     */
    void Display() const;

    /**
     * Updates the positions and velocities of all particles (based on the rules
     * described in the assignment documentation).
     */
    void AdvanceOneFrame();

private:
    std::vector<Particle> particles_;
    ci::Rectf bounds_;
    size_t particle_count_;
    float particle_radius_;
    float particle_mass_;
    ci::Color particle_color_;
    ci::Color rectangle_color_;
    vec2 initial_position_;
    int initial_velocity_factor_;

};

}  // namespace idealgas
