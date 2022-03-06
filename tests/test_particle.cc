#include <catch2/catch.hpp>

#include <gas_simulation_app.h>
#include <particle.h>

using idealgas::IdealGasApp;
using idealgas::Particle;

static ci::Rectf bounds = ci::Rectf(vec2(100, 100), vec2(775, 775));
static Particle particle1 = Particle(vec2(775, 775), vec2(-1, -1), 10.0);

TEST_CASE("Handle outside of bound") {
    SECTION("Particle west of west wall") {
        particle1.SetPositionX(bounds.x1 - 1);
        particle1.HandleWallCollision(bounds);
        REQUIRE(particle1.GetPositionX() == bounds.x1 + particle1.GetRadius());
    }

    SECTION("Particle east of east wall") {
        particle1.SetPositionX(bounds.x2 + 1);
        particle1.HandleWallCollision(bounds);
        REQUIRE(particle1.GetPositionX() == bounds.x2 - particle1.GetRadius());
    }

    SECTION("Particle north of north wall") {
        particle1.SetPositionY(bounds.y1 - 1);
        particle1.HandleWallCollision(bounds);
        REQUIRE(particle1.GetPositionY() == bounds.y1 + particle1.GetRadius());
    }

    SECTION("Particle south of south wall") {
        particle1.SetPositionY(bounds.y2 + 1);
        particle1.HandleWallCollision(bounds);
        REQUIRE(particle1.GetPositionY() == bounds.y2 - particle1.GetRadius());
    }

    SECTION("Particle north of north wall and west of west wall") {
        particle1.SetPosition(vec2(bounds.x1 - 1, bounds.y1 - 1));
        particle1.HandleWallCollision(bounds);
        REQUIRE(particle1.GetPosition() == vec2(bounds.x1 + particle1.GetRadius(),
                                               bounds.y1 + particle1.GetRadius()));
    }

    SECTION("Particle south of south wall and east of east wall") {
        particle1.SetPosition(vec2(bounds.x2 + 1, bounds.y2 + 1));
        particle1.HandleWallCollision(bounds);
        REQUIRE(particle1.GetPosition() == vec2(bounds.x2 - particle1.GetRadius(),
                                               bounds.y2 - particle1.GetRadius()));
    }

}

TEST_CASE("Handle collision with bound") {
    SECTION("Particle collision with west wall") {
        particle1.SetPositionX(bounds.x1 - 1);
        particle1.SetVelocityX(-1);
        particle1.HandleWallCollision(bounds);
        REQUIRE(particle1.GetVelocityX() == 1);
    }

    SECTION("Particle collision with east wall") {
        particle1.SetPositionX(bounds.x2 + 1);
        particle1.SetVelocityX(1);
        particle1.HandleWallCollision(bounds);
        REQUIRE(particle1.GetVelocityX() == -1);
    }

    SECTION("Particle collision with north wall") {
        particle1.SetPositionY(bounds.y1 - 1);
        particle1.SetVelocityY(-1);
        particle1.HandleWallCollision(bounds);
        REQUIRE(particle1.GetVelocityY() == 1);
    }

    SECTION("Particle collision with south wall") {
        particle1.SetPositionY(bounds.y2 + 1);
        particle1.SetVelocityY(1);
        particle1.HandleWallCollision(bounds);
        REQUIRE(particle1.GetVelocityY() == -1);
    }

    SECTION("Particle collision with northwest corner") {
        particle1.SetPosition(vec2(bounds.x1 - 1, bounds.y1 - 1));
        particle1.SetVelocity(vec2(-1, -1));
        particle1.HandleWallCollision(bounds);
        REQUIRE(particle1.GetVelocity() == vec2(1, 1));
    }

    SECTION("Particle collision with southeast corner") {
        particle1.SetPosition(vec2(bounds.x2 + 1, bounds.y2 + 1));
        particle1.SetVelocity(vec2(1, 1));
        particle1.HandleWallCollision(bounds);
        REQUIRE(particle1.GetVelocity() == vec2(-1, -1));
    }
}

//TEST_CASE("Handle collision with other particle") {
//    SECTION("Particle in contact with other particle")
//
//    SECTION("Particle in contact with and moving towards other particle")
//
//    SECTION("Particle collision with itself")
//}