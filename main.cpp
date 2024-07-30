// Gun Parser feat by govnocode

#include <stdio.h>
#include <iostream>
#include <vector>
#include "RecipesParser.h"
#include "JsonWriter.h"



int main() 
{
	
	RecipesParser *parser = new RecipesParser("message.txt");

	parser->Parse();

	parser->GetRecipe();

	JsonWriter writer(parser->GetRecipe(true));
	writer.WriteToFile("recipes.json");

	return 0;

}