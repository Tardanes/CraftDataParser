#pragma once
#include <string>
#include <vector>
#include "Recipe.h"

class JsonWriter {
public:
    JsonWriter(const std::vector<Recipe>& recipes);
    void WriteToFile(const std::string& filename);

private:
    std::vector<Recipe> recipes;
    std::string ConvertToJson() const;
};
