#pragma once
#include <stdio.h>
#include <string>
#include <vector>

class RecipeReq {
public:
    std::string GetMaterialName() const { return materialName; }
    void SetMaterialName(const std::string& newName) { materialName = newName; }

    int GetMaterialCount() const { return materialCount; }
    void SetMaterialCount(int newCount) { materialCount = newCount; }

private:
    std::string materialName;
    int materialCount = 1; 
};
