#include <fstream>
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
