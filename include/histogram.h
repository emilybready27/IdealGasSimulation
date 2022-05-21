#pragma once

#include "particle.h"
#include <cinder/Rect.h>
#include "cinder/gl/gl.h"

namespace idealgas {

class Histogram {
 public:
  /**
   * Constructs a Histogram to represent the number of particles at a range of speeds.
   * @param bar_count size_t
   * @param bounds ci::Rectf
   * @param bound_color ci::Color
   * @param particle_colors ci::Color
   */
  Histogram(size_t bar_count,
            const ci::Rectf& bounds,
            const ci::Color& bound_color,
            const ci::Color& particle_colors);

  /**
   * Displays the Histogram bars along with x- and y-axis labels.
   */
  void Display() const;

  /**
   * Updates the frequencies of speeds of the particles of the given color, using
   * information about the range of speeds from all the particles.
   * @param particles std::vector<Particle>
   * @param color ci::Color
   */
  void AdvanceOneFrame(const std::vector<Particle>& particles, const ci::Color& color);

  /**
   * Getters for Histogram state.
   */
  ci::Rectf GetBounds() const;
  ci::Color GetBoundColor() const;
  ci::Color GetBarColor() const;
  size_t GetBarCount() const;
  float GetBarWidth() const;
  size_t GetBarWeight() const;
  std::vector<size_t> GetFrequencies() const;


 private:
  /**
   * Outline for the graph.
   */
  ci::Rectf bounds_;

  /**
   * Color for the outline for the graph.
   */
  ci::Color bound_color_;

  /**
   * Color for the bars of the graph, corresponding to the
   * color of the particle they represent.
   */
  ci::Color bar_color_;

  /**
   * Number of bars used in the graph.
   */
  size_t bar_count_;

  /**
   * X-directional value of the graph bars.
   */
  float bar_width_;

  /**
   * Positive factor used to magnify the graph bars.
   */
  size_t bar_weight_;

  /**
   * Y-directional values of the graph bars.
   */
  std::vector<size_t> frequencies_;
};

} // namespace idealgas
