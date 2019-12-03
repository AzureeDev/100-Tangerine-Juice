#include "Discord.h"
#include <discord_rpc.h>

string Discord::details = "";
string Discord::state = "";
string Discord::largeImageKey = "";
string Discord::largeImageText = "";
string Discord::smallImageKey = "";
string Discord::smallImageText = "";

void Discord::init(string discordAppId)
{
	DiscordEventHandlers handlers;
	Discord_Initialize(discordAppId.c_str(), &handlers, 1, "");
}

void Discord::setRichPresence(DiscordPresenceParams params)
{
	DiscordRichPresence presence;
	memset(&presence, 0, sizeof(presence));

	// This is not an error. To me, state should be the title while details is below it, not the reverse.
	presence.state = params.details.c_str();
	presence.details = params.state.c_str();
	presence.largeImageKey = params.largeImageKey.c_str();
	presence.largeImageText = params.largeImageText.c_str();
	presence.smallImageKey = params.smallImageKey.c_str();
	presence.smallImageText = params.smallImageText.c_str();

	Discord::details = params.details;
	Discord::state = params.state;
	Discord::largeImageKey = params.largeImageKey;
	Discord::largeImageText = params.largeImageText;
	Discord::smallImageKey = params.smallImageKey;
	Discord::smallImageText = params.smallImageText;

	Discord_UpdatePresence(&presence);
}

void Discord::setState(string newState)
{
	DiscordRichPresence presence;
	memset(&presence, 0, sizeof(presence));

	Discord::state = newState;

	presence.details = newState.c_str();
	presence.state = Discord::details.c_str();
	presence.largeImageKey = Discord::largeImageKey.c_str();
	presence.largeImageText = Discord::largeImageText.c_str();
	presence.smallImageKey = Discord::smallImageKey.c_str();
	presence.smallImageText = Discord::smallImageText.c_str();

	Discord_UpdatePresence(&presence);
}

void Discord::setDetails(string newDetails)
{
	DiscordRichPresence presence;
	memset(&presence, 0, sizeof(presence));

	Discord::details = newDetails;

	presence.state = newDetails.c_str();
	presence.details = Discord::state.c_str();
	presence.largeImageKey = Discord::largeImageKey.c_str();
	presence.largeImageText = Discord::largeImageText.c_str();
	presence.smallImageKey = Discord::smallImageKey.c_str();
	presence.smallImageText = Discord::smallImageText.c_str();

	Discord_UpdatePresence(&presence);
}
