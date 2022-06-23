#include "DRPC.h"


void DRPC::init()
{
	this->handler = new DiscordEventHandlers();
	this->presence = new DiscordRichPresence();
	Discord_Initialize(this->cid, this->handler, NULL, NULL);
	this->presence->largeImageKey = "https://files.facepunch.com/lewis/1b1811b1/gmod-hero.png";
	Discord_UpdatePresence(this->presence);
}

void DRPC::update(server* info, bool update_time)
{
	std::string	hname = info->hostname;

	this->presence->details = info->hostname;
	
	if (hname != "Menu" && hname != "Single player" && hname != "Idle")
	{
		std::string		plys;
		plys = info->current_players ? std::to_string(info->current_players) + "/" + std::to_string(info->max_player) : "Joining...";
		this->presence->state = plys.c_str();
	}
	else
		this->presence->state = NULL;

	if (update_time)
		this->presence->startTimestamp = std::time(nullptr);
	Discord_UpdatePresence(this->presence);
}

DRPC::DRPC(const char* cID)
{
	this->cid = cID;
	this->init();
}