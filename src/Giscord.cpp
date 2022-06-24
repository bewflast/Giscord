#include "GmodProcInfo.h"
#include "DRPC.h"

void	update_server_info(server* srv, GmodProcInfo game)
{
	srv->max_player = Utils::readMem<int>(game.GetProcessID(), game.GetDLLBase("engine.dll").addr + Utils::sigscan::offsets::max_players);
	
	if (srv->max_player)
	{
		srv->hostname = (srv->max_player == 1 ? "Single player" : Utils::readString( game.GetProcessID(), game.GetDLLBase("client.dll").addr + Utils::sigscan::offsets::host_name, 1));
		srv->current_players = (srv->max_player == 1 ? 0 : Utils::readMem<int>(game.GetProcessID(), game.GetDLLBase("client.dll").addr + Utils::sigscan::offsets::cur_players));
		srv->ip_port = (srv->max_player == 1 ? 0 : Utils::readString( game.GetProcessID(), game.GetDLLBase("engine.dll").addr + Utils::sigscan::offsets::ip_port, 2));
	}
	else
		srv->hostname = "Menu";
	
}

int main()
{
	std::set<const char*>	required_dlls{ "client.dll", "engine.dll" };
	GmodProcInfo			gmod(required_dlls);
	bool					state;
	server					srv;
	DRPC*					RPC;
	std::string				last_hostname;
	
	RPC = new DRPC("989609317185507418");

	srv.hostname = "Menu";
	last_hostname = srv.hostname;
	RPC->update(&srv, true);

	state = gmod.IsGameStarted();
	if (state)
		update_server_info(&srv, gmod);

	while(Sleep(1000), 1)
	{
		bool	now(gmod.IsGameStarted());
		bool	upd_time(false);

		if (now != state || last_hostname != srv.hostname)
		{
			state = now;
			last_hostname = srv.hostname;
			upd_time = true;
		}

		if (now)
			update_server_info(&srv, gmod);
		else
			srv.hostname = "Idle";
		
		RPC->update(&srv, upd_time);
	}
}
