#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"
#include "particle.h"

using glm::vec2;

namespace idealgas {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  void draw() override;
  void update() override;

  const int kWindowSize = 875;
  const int kMargin = 100;
  const std::string kPathToJsonFile =
          R"(C:\Users\Mary\Desktop\Cinder\my-projects\ideal-gas-ebready2\resources\configuration.json)";

 private:
    GasContainer container_;
    vec2 top_left_;
    vec2 bottom_right_;
    cinder::RectT<float> bounds_;
};

}  // namespace idealgas
