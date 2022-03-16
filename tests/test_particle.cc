#include <catch2/catch.hpp>
#include <particle.h>

using idealgas::Particle;

TEST_CASE("Handle outside of bound") {
  ci::Rectf bounds = ci::Rectf(vec2(100, 100), vec2(775, 775));
  Particle particle = Particle(vec2(775, 775), vec2(-1, -1), 10.0, 4.0, "green");

  SECTION("Particle west of west wall") {
    particle.SetPositionX(bounds.x1 - 1);
    particle.HandleWallCollision(bounds);
    REQUIRE(particle.GetPositionX() == bounds.x1 + particle.GetRadius());
  }

  SECTION("Particle east of east wall") {
    particle.SetPositionX(bounds.x2 + 1);
    particle.HandleWallCollision(bounds);
    REQUIRE(particle.GetPositionX() == bounds.x2 - particle.GetRadius());
  }

  SECTION("Particle north of north wall") {
    particle.SetPositionY(bounds.y1 - 1);
    particle.HandleWallCollision(bounds);
    REQUIRE(particle.GetPositionY() == bounds.y1 + particle.GetRadius());
  }

  SECTION("Particle south of south wall") {
    particle.SetPositionY(bounds.y2 + 1);
    particle.HandleWallCollision(bounds);
    REQUIRE(particle.GetPositionY() == bounds.y2 - particle.GetRadius());
  }

  SECTION("Particle north of north wall and west of west wall") {
    particle.SetPosition(vec2(bounds.x1 - 1, bounds.y1 - 1));
    particle.HandleWallCollision(bounds);
    REQUIRE(particle.GetPosition() == vec2(bounds.x1 + particle.GetRadius(),
                                           bounds.y1 + particle.GetRadius()));
  }

  SECTION("Particle south of south wall and east of east wall") {
    particle.SetPosition(vec2(bounds.x2 + 1, bounds.y2 + 1));
    particle.HandleWallCollision(bounds);
    REQUIRE(particle.GetPosition() == vec2(bounds.x2 - particle.GetRadius(),
                                           bounds.y2 - particle.GetRadius()));
  }
}

TEST_CASE("Handle collision with bound") {
  ci::Rectf bounds = ci::Rectf(vec2(100, 100), vec2(775, 775));
  Particle particle = Particle(vec2(775, 775), vec2(-1, -1), 10.0, 4.0, "green");

  SECTION("Particle collision with west wall") {
    particle.SetPositionX(bounds.x1 - 1);
    particle.SetVelocityX(-1);
    particle.HandleWallCollision(bounds);
    REQUIRE(particle.GetVelocityX() == 1);
  }

  SECTION("Particle collision with east wall") {
    particle.SetPositionX(bounds.x2 + 1);
    particle.SetVelocityX(1);
    particle.HandleWallCollision(bounds);
    REQUIRE(particle.GetVelocityX() == -1);
  }

  SECTION("Particle collision with north wall") {
    particle.SetPositionY(bounds.y1 - 1);
    particle.SetVelocityY(-1);
    particle.HandleWallCollision(bounds);
    REQUIRE(particle.GetVelocityY() == 1);
  }

  SECTION("Particle collision with south wall") {
    particle.SetPositionY(bounds.y2 + 1);
    particle.SetVelocityY(1);
    particle.HandleWallCollision(bounds);
    REQUIRE(particle.GetVelocityY() == -1);
  }

  SECTION("Particle collision with northwest corner") {
    particle.SetPosition(vec2(bounds.x1 - 1, bounds.y1 - 1));
    particle.SetVelocity(vec2(-1, -1));
    particle.HandleWallCollision(bounds);
    REQUIRE(particle.GetVelocity() == vec2(1, 1));
  }

  SECTION("Particle collision with southeast corner") {
    particle.SetPosition(vec2(bounds.x2 + 1, bounds.y2 + 1));
    particle.SetVelocity(vec2(1, 1));
    particle.HandleWallCollision(bounds);
    REQUIRE(particle.GetVelocity() == vec2(-1, -1));
  }
}

TEST_CASE("Handle collision with other particle") {
  ci::Rectf bounds = ci::Rectf(vec2(100, 100), vec2(775, 775));
  Particle particle1 = Particle(vec2(775, 775), vec2(-1, -1), 10.0, 4.0, "green");
  Particle particle2 = Particle(vec2(775, 775), vec2(-1, -1), 10.0, 4.0, "green");

  SECTION("Particle collision with another particle") {
    particle2.SetPosition(bounds.getCenter());
    particle2.SetVelocity(vec2(1, 1));
    particle1.SetPosition(particle2.GetPosition() - vec2(1,1));
    particle1.HandleParticleCollision(&particle2);
    REQUIRE(!particle1.IsMovingTowards(particle2));
  }
}