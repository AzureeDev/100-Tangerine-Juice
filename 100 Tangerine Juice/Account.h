#pragma once
#include <string>
#include <vector>

using std::string, std::vector, std::stoi;

class Account
{
private:
	string accountName = "";
	unsigned accountLevel = 0;
	unsigned accountExperience = 0;
	int accountStars = 0;
	string accountFavoriteUnit = "";

public:
	void init();
	bool accountCreated() const;
	string name() const;
	unsigned level() const;
	unsigned experience() const;
	int stars() const;
	string unit() const;
};

