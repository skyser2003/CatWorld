#include "DataManager.h"

#include <fstream>
using namespace std;

#include "json/json.h"

bool DataManager::LoadFile(const std::string& filename)
{
	ifstream input;
	string content;

	input.open(filename);

	if (input.is_open())
	{
		string temp;

		while (input)
		{
			temp.clear();
			getline(input, temp);
			content += '\n';
			content += temp;
		}
	}
	
	input.close();

	if (content.length() == 0)
	{
		return false;
	}

	Json::Reader reader;
	Json::Value root;
	reader.parse(content, root);

	return true;
}