#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include "RecipeReq.h"

class Recipe {
public:
    std::string GetName() const { return name; }
    void SetName(const std::string& newName) { name = newName; }

    int GetResultAmount() const { return resultAmount; }
    void SetResultAmount(int newResult) { resultAmount = newResult; }

    std::string GetCountry() const { return country; }
    void SetCountry(const std::string& newCountry) { country = newCountry; }

    std::vector<RecipeReq> GetRequirments() const { return requirments; }
    void SetRequirments(const std::vector<RecipeReq>& newRequirments) { requirments = newRequirments; }

private:
    std::string name;
    int resultAmount = 1;
    std::string country;
    std::vector<RecipeReq> requirments;
};