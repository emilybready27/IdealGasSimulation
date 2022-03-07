#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

/**
 * An external class that handles the Json parsing into a Json object
 * and ensures it is valid.
 */
class JsonParser {
 public:
  JsonParser() = default;
  JsonParser(const std::string& path_to_file, const std::vector<std::string>& fields);
  json json_object;

 private:
  void CheckValidJson(const std::vector<std::string>& fields) const;
  bool Contains(const std::vector<std::string> &container, const std::vector<std::string> &items) const;
  std::vector<std::string> GetFields() const;

};
