#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"
#include "json_parser.h"

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

 private:
    GasContainer container_;
    JsonParser parser_;
    int window_size_;
    int margin_size_;
};

const std::string kPathToJsonFile =
        R"(C:\Users\Mary\Desktop\Cinder\my-projects\ideal-gas-ebready2\resources\configuration.json)";
const std::vector<std::string> kFields =
        {"window_size", "margin_size", "initial_velocity_factor", "particle_count", "particle_radius",
         "particle_mass", "particle_color", "rectangle_color"};

}  // namespace idealgas
