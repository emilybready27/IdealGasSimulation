#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

using glm::vec2;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
    class GasContainer {
    public:
        /**
         * TODO: Add more parameters to this constructor, and add documentation.
         */
        GasContainer();

        GasContainer(ci::Rectf bounds);

        /**
         * Displays the container walls and the current positions of the particles.
         */
        void Display() const;

        /**
         * Updates the positions and velocities of all particles (based on the rules
         * described in the assignment documentation).
         */
        void AdvanceOneFrame();

        void AddParticle(const Particle &particle);



    private:
        std::vector<Particle> particles_;
        ci::Rectf bounds_;

        const ci::Color kDefaultColor = ci::Color("white");
        const ci::Rectf kDefaultBounds = ci::Rectf(vec2(100, 100), vec2(600, 400));

    };

}  // namespace idealgas
