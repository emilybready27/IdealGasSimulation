#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

/**
 * A class that handles parsing the Json file into a valid Json object
 * using the C++ Json library: https://github.com/nlohmann/json.git.
 */
class JsonParser {
 public:
  /**
   * Constructs the parser by reading the file at the path,
   * parsing it according to the specification of the library,
   * and ensuring that all the necessary fields are present as keys.
   * @param path_to_file std::string
   * @param fields std::vector<std::string>
   */
  JsonParser(const std::string& path_to_file, const std::vector<std::string>& fields);

  /**
   * Default constructor.
   */
  JsonParser() = default;

  /**
   * Getters for Json fields.
   */
  int GetWindowLength() const;
  int GetWindowWidth() const;
  int GetMarginSize() const;
  size_t GetInitialVelocityFactor() const;
  std::vector<size_t> GetParticleCounts() const;
  std::vector<float> GetParticleRadii() const;
  std::vector<float> GetParticleMasses() const;
  std::vector<ci::Color> GetParticleColors() const;
  ci::Color GetBoundColor() const;
  ci::Color GetBackgroundColor() const;
  size_t GetBarCount() const;

 private:
  /**
   * Json object storing the key-value pairs.
   */
  json json_object;

  /**
   * Throws invalid_argument exception if any of the given fields
   * are not present in the json_object as keys.
   * @param fields std::vector<std::string>
   */
  void CheckValidJson(const std::vector<std::string>& fields) const;

  /**
   * Determines if the container contains all of the given items.
   * @param container std::vector<std::string>
   * @param items std::vector<std::string>
   * @return bool
   */
  bool Contains(const std::vector<std::string> &container, const std::vector<std::string> &items) const;

  /**
   * Gets a list of all the keys in the json_object.
   * @return std::vector<std::string>
   */
  std::vector<std::string> GetKeys() const;
};
