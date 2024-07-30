#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include <regex>
#include "Recipe.h"

class RecipesParser

{

public:

	RecipesParser();
	RecipesParser(std::string filepath);

	void SetFilePath(std::string filepath);
	std::string GetFilePath();

	std::string Parse();

    Recipe parseCleanedData(const std::string& cleanedData) {
        Recipe recipe;
        // какой-то пиздец
        std::regex countryRegex("\"([^\"]+)\"");
        std::regex resultNameRegex("\"[^\"]+\",\\s*\\(([^,\\s]+),\\s*(\\d+)\\)");
        std::regex resultNameNoAmountRegex("\"[^\"]+\",\\s*([^,\\s]+)");
        std::regex requirementsRegex("\\{([^}]+)\\}");
        std::regex requirementItemRegex("\\(([^,]+),\\s*(\\d*)\\)");

        std::smatch match;

        if (std::regex_search(cleanedData, match, countryRegex)) {
            recipe.SetCountry(match[1].str());
        }

        if (std::regex_search(cleanedData, match, resultNameRegex)) {
            recipe.SetName(match[1].str());
            recipe.SetResultAmount(std::stoi(match[2].str()));
        }
        else if (std::regex_search(cleanedData, match, resultNameNoAmountRegex)) {
            recipe.SetName(match[1].str());
            recipe.SetResultAmount(1);
        }

        if (std::regex_search(cleanedData, match, requirementsRegex)) {
            std::string requirementsStr = match[1].str();
            std::sregex_iterator iter(requirementsStr.begin(), requirementsStr.end(), requirementItemRegex);
            std::sregex_iterator end;

            std::vector<RecipeReq> requirements;
            while (iter != end) {
                std::smatch reqMatch = *iter;
                RecipeReq req;
                req.SetMaterialName(reqMatch[1].str());
                if (reqMatch[2].str().empty()) {
                    req.SetMaterialCount(1);
                }
                else {
                    req.SetMaterialCount(std::stoi(reqMatch[2].str()));
                }
                requirements.push_back(req);
                ++iter;
            }
            recipe.SetRequirments(requirements);
        }

        return recipe;
    }

	std::string GetRecipe();
	std::string GetRecipe(int index);
	std::string GetRecipe(std::string parameters);
    std::vector<Recipe> GetRecipe(bool _gen);
	void SetRecipe(std::vector<Recipe> newRecipesVector);

private:

	std::string filepath;

	std::vector<Recipe> Recipes;

};