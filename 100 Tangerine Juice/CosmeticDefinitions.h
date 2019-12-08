#pragma once
#include <string>
#include <vector>

using std::string, std::vector;

struct CosmeticData
{
	string id;
	string type = "hair"; // available: [hair][clothing]
	string unitId;
	unsigned cost = 0;
	unsigned levelUnlock = 1;
};

class CosmeticDefinitions
{
	static vector<CosmeticData> def;
public:
	static void createDefinitions();
	static CosmeticData getCosmeticData(const string cosmeticIdentifier);
	static vector<CosmeticData> getAllHairs();
};

