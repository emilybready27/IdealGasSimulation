#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"
#include "json_parser.h"
#include "histogram.h"

using glm::vec2;

namespace idealgas {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class IdealGasApp : public ci::app::App {
 public:
  /**
   * Constructs IdealGasApp with a JsonParser to gather configuration details
   * and a GasContainer to store the state of the app.
   */
  IdealGasApp();

  /**
   * Draws the movement of Particles in the GasContainer through continuous calls.
   */
  void draw() override;

  /**
   * Updates the state of the GasContainer through continuous calls.
   */
  void update() override;

  /**
   * The number of different types of particles the simulation can have.
   */
  static const size_t kParticleTypes = 3;

  /**
   * The path to the Json file storing preset configuration details.
   */
  const std::string kPathToJsonFile =
          R"(C:\Users\Mary\Desktop\Cinder\my-projects\ideal-gas-ebready2\resources\configuration.json)";

  /**
   * The list of configuration fields needed to initialize the IdealGasApp.
   */
  const std::vector<std::string> kFields =
          {"window_length", "window_width", "margin_size", "initial_velocity_factor", "particle_counts",
           "particle_radii", "particle_masses", "particle_colors", "bound_color", "background_color", "bar_count"};

 private:
  /**
   * Container storing the state of the app.
   */
  GasContainer container_;

  /**
   * Parser used to gather configuration details upon initialization.
   */
  JsonParser parser_;

  /**
   * List of histograms, one for each particle type.
   */
  std::vector<Histogram> histograms_;

  /**
   * The color of the background of the display screen.
   */
  ci::Color background_color_;

  /**
   * The length of the display window for the app.
   */
  int window_length_;

  /**
   * The width of the display window for the app.
   */
  int window_width_;

  /**
   * The width of the space between the GasContainer and display window edges.
   */
  int margin_size_;

  /**
   * Constructs the vector of Histograms used to display particle speeds.
   */
  void AddHistograms();
};

}  // namespace idealgas
