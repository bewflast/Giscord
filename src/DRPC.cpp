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
	if (hname != "Главное меню" && hname != "Одиночная игра" && hname != "Спит")
	{
		std::string		plys;
		plys = info->current_players ? std::to_string(info->current_players) + "/" + std::to_string(info->max_player) : "Заходит...";
		this->presence->state = plys.c_str();
		this->presence->buttons[0].label = "Присоединиться!";
		this->presence->buttons[0].url = ((std::string)"steam://connect/" + (std::string)info->ip_port).c_str();
	}
	else
	{
		this->presence->buttons[0].label = NULL;
		this->presence->buttons[0].url = NULL;	
		this->presence->state = "";
	}
	if (update_time)
		this->presence->startTimestamp = std::time(nullptr);
	Discord_UpdatePresence(this->presence);
}

DRPC::DRPC(const char* cID)
{
	this->cid = cID;
	this->init();
}