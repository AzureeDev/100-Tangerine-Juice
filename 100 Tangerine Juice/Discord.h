#pragma once
#include <string>
#include "Discord.h"

using std::string;

class Discord
{
private:
	static string state;
	static string details;
	static string largeImageKey;
	static string largeImageText;
	static string smallImageKey;
	static string smallImageText;

public:
	struct DiscordPresenceParams {
		string state = "";
		string details = "";
		string largeImageKey = "game_base";
		string largeImageText = "100% Tangerine Juice";
		string smallImageKey = "";
		string smallImageText = "";
	};

	static void init(string discordAppId);
	static void setRichPresence(DiscordPresenceParams params);
	static void setState(string newState);
	static void setDetails(string newDetails);
};

