#include <fstream>
#include <cinder/Color.h>
#include "json_parser.h"

JsonParser::JsonParser(const std::string& path_to_file, const std::vector<std::string>& fields) {
  // open the Json file to read from
  std::ifstream file(path_to_file);

  // parse file and ensure if it contains all necessary fields
  try {
    json_object = json::parse(file);
    CheckValidJson(fields);
  } catch (const std::exception& e) {
    (void)e;
    throw std::invalid_argument("Invalid Json");
  }
}

void JsonParser::CheckValidJson(const std::vector<std::string>& fields) const {
  std::vector<std::string> json_keys = GetKeys();

  // invalid if there are any missing fields
  if (!Contains(json_keys, fields)) {
    throw std::invalid_argument("Invalid Json");
  }
}

bool JsonParser::Contains(const std::vector<std::string>& container,
                          const std::vector<std::string>& items) const {

  for (const std::string& item : items) {
    if (!std::any_of(container.begin(), container.end(),
                     [&item](const std::string& elem){return elem == item;})) {
      return false; // item not found in container
    }
  }

  return true;
}

std::vector<std::string> JsonParser::GetKeys() const {
  std::vector<std::string> keys;

  // iterate over key-value pairs of json object
  for (auto &elem: json_object.items()) {
    keys.push_back(elem.key());
  }
  return keys;
}

int JsonParser::GetWindowLength() const {
  return json_object["window_length"];
}

int JsonParser::GetWindowWidth() const {
  return json_object["window_width"];
}

int JsonParser::GetMarginSize() const {
  return json_object["margin_size"];
}

size_t JsonParser::GetInitialVelocityFactor() const {
  return json_object["initial_velocity_factor"];
}

std::vector<size_t> JsonParser::GetParticleCounts() const {
  std::vector<size_t> particle_counts;
  for (size_t count : json_object["particle_counts"]) {
    particle_counts.push_back(count);
  }
  return particle_counts;
}

std::vector<float> JsonParser::GetParticleRadii() const {
  std::vector<float> particle_radii;
  for (float radius : json_object["particle_radii"]) {
    particle_radii.push_back(radius);
  }
  return particle_radii;
}

std::vector<float> JsonParser::GetParticleMasses() const {
  std::vector<float> particle_masses;
  for (float mass : json_object["particle_masses"]) {
    particle_masses.push_back(mass);
  }
  return particle_masses;
}

std::vector<ci::Color> JsonParser::GetParticleColors() const {
  std::vector<ci::Color> particle_colors;

  // setting Color requires a pointer to a char
  for (const std::string color : json_object["particle_colors"]) {
    particle_colors.emplace_back(&(color[0]));
  }
  return particle_colors;
}

ci::Color JsonParser::GetBoundColor() const {
  // setting Color requires a pointer to a char
  std::string color = json_object["bound_color"];
  return {&(color[0])};
}

ci::Color JsonParser::GetBackgroundColor() const {
  // set background color with char pointer
  std::string color = json_object["background_color"];
  return {&(color[0])};
}

size_t JsonParser::GetBarCount() const {
  return json_object["bar_count"];
}




