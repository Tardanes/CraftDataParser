#include "RecipesParser.h"
#include <filesystem>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <regex>

RecipesParser::RecipesParser()
{
	RecipesParser::filepath = "D:/parsing/gunz";
}

RecipesParser::RecipesParser(std::string filepath)
{
	RecipesParser::filepath = filepath;
}

void RecipesParser::SetFilePath(std::string filepath)
{
	RecipesParser::filepath = filepath;
}

std::string RecipesParser::GetFilePath()
{
	return RecipesParser::filepath;
}

std::string RecipesParser::Parse()
{
	std::ifstream reader(RecipesParser::filepath);

	if (!reader) {
		return "File don`t exist/corrupted.";
	}

	std::string raw = "";

	std::string temp_string;

	while (reader) 
	{
		temp_string = "";
		std::getline(reader, temp_string);

		std::regex pattern(R"(Recipes\.addRecipeFor\((.*)\);)");
		std::smatch matches;

		if (std::regex_search(temp_string, matches, pattern)) 
		{
			std::string raw_data = matches[1].str();

			std::regex pattern(R"(new\s*|ItemStack\s*|\[|\])");

			std::string cleaned_data = std::regex_replace(raw_data, pattern, "");

			//std::cout << cleaned_data << std::endl;

			///////////////////////////////////////

			Recipe parsed_data = RecipesParser::parseCleanedData(cleaned_data);

			this->Recipes.push_back(parsed_data);
		}

		// backup
		raw += temp_string + "\n";
	}

	return "Ok.";
}

std::string RecipesParser::GetRecipe()
{
	std::string result = "";
	result += "Size: " + RecipesParser::Recipes.size();
	result += "\n";

	if (!RecipesParser::Recipes.empty()) 
	{
		for (int i = 0; i < RecipesParser::Recipes.size(); i++) 
		{
			result += i + ".\tN: " + RecipesParser::Recipes[i].GetName() + ",\tC: " + RecipesParser::Recipes[i].GetCountry() + ",\tRA: ";
			result += RecipesParser::Recipes[i].GetResultAmount() + ",\t | RQR: [ ";
			for (int j = 0; j < RecipesParser::Recipes[i].GetRequirments().size(); j++, result+=", ")
			{
				result += "{ " + RecipesParser::Recipes[i].GetRequirments()[j].GetMaterialName() + " : ";
				result += RecipesParser::Recipes[i].GetRequirments()[j].GetMaterialCount() + " }";
			}
			result += " ];\n";
		}
	}

	return result;
}

std::string RecipesParser::GetRecipe(int index)
{
	// lenj
	return std::string();
}

std::string RecipesParser::GetRecipe(std::string parameters)
{
	// lenj
	return std::string();
}

std::vector<Recipe> RecipesParser::GetRecipe(bool _gen)
{
	return this->Recipes;
}

void RecipesParser::SetRecipe(std::vector<Recipe> newRecipesVector)
{
	RecipesParser::Recipes = newRecipesVector;
}