#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JsonParser {
 public:
  JsonParser() = default;
  JsonParser(const std::string& path_to_file, const std::vector<std::string>& fields);
  json json_object;

 private:
  void CheckValidJson(const std::vector<std::string>& fields) const;
  std::vector<std::string> GetFields() const;
  bool Contains(const std::vector<std::string> &container, const std::vector<std::string> &items) const;

};