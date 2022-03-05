#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace idealgas {

    class Particle {
    public:
        Particle(const ci::vec2& position, const ci::vec2& velocity, const float& radius);

        void SetPosition(const ci::vec2& position);
        ci::vec2 GetPosition() const;
        void SetVelocity(const ci::vec2& velocity);
        ci::vec2 GetVelocity() const;
        void SetRadius(const float& radius);
        float GetRadius() const;

    private:
        ci::vec2 position_;
        ci::vec2 velocity_;
        float radius_;
        // later add mass, color

    };

} // namespace idealgas
