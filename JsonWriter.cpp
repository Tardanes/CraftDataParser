#include "JsonWriter.h"
#include <fstream>
#include <sstream>

JsonWriter::JsonWriter(const std::vector<Recipe>& recipes) : recipes(recipes) {}

std::string JsonWriter::ConvertToJson() const {
    std::ostringstream oss;
    oss << "{\n";

    for (size_t i = 0; i < recipes.size(); ++i) {
        const auto& recipe = recipes[i];
        oss << "  \"" << recipe.GetName() << "\": {\n";
        oss << "    \"resultAmount\": " << recipe.GetResultAmount() << ",\n";
        oss << "    \"country\": \"" << recipe.GetCountry() << "\",\n";
        oss << "    \"requirements\": {\n";

        const auto& requirements = recipe.GetRequirments();
        for (size_t j = 0; j < requirements.size(); ++j) {
            const auto& req = requirements[j];
            oss << "      \"" << req.GetMaterialName() << "\": " << req.GetMaterialCount();
            if (j < requirements.size() - 1) {
                oss << ",";
            }
            oss << "\n";
        }

        oss << "    }\n";
        oss << "  }";
        if (i < recipes.size() - 1) {
            oss << ",";
        }
        oss << "\n";
    }

    oss << "}\n";
    return oss.str();
}

void JsonWriter::WriteToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        std::string json = ConvertToJson();
        file << json;
        file.close();
    }
    else {
        throw std::runtime_error("Unable to open file");
    }
}
