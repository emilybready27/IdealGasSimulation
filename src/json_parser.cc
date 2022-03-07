#include <fstream>
#include "json_parser.h"

JsonParser::JsonParser(const std::string& path_to_file, const std::vector<std::string>& fields) {
    std::ifstream file(path_to_file);
    try {
        json_object = json::parse(file);
        CheckValidJson(fields);
    } catch (const std::exception& e) {
        (void)e;
        throw std::exception("Invalid Json");
    }
}

void JsonParser::CheckValidJson(const std::vector<std::string>& fields) const {
    std::vector<std::string> json_fields = GetFields();
    if (!Contains(json_fields, fields)) {
        throw std::exception("Invalid Json");
    }
}

bool JsonParser::Contains(const std::vector<std::string>& container,
                     const std::vector<std::string>& items) const {
    for (const std::string& item : items) {
        if (!std::any_of(container.begin(), container.end(),
                         [&item](const std::string& elem){return elem == item;})) {
            return false;
        }
    }
    return true;
}

std::vector<std::string> JsonParser::GetFields() const {
    std::vector<std::string> fields;
    for (auto &elem: json_object.items()) {
        fields.push_back(elem.key());
    }
    return fields;
}