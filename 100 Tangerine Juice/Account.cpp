#include "Account.h"
#include "Globals.h"

void Account::init()
{
	auto playerData = Globals::engine->getPlayerData();

	this->accountName = playerData->get("account.playerName");
	this->accountLevel = stoi(playerData->get("account.playerLevel"));
	this->accountExperience = stoi(playerData->get("account.playerExperience"));
	this->accountStars = stoi(playerData->get("account.playerStars"));
	this->accountFavoriteUnit = playerData->get("account.playerUnit");
}

bool Account::accountCreated() const
{
	return this->accountName != "";
}

string Account::name() const
{
	return this->accountName;
}

unsigned Account::level() const
{
	return this->accountLevel;
}

unsigned Account::experience() const
{
	return this->accountExperience;
}

int Account::stars() const
{
	return this->accountStars;
}

string Account::unit() const
{
	return this->accountFavoriteUnit;
}
