#ifndef DRPC_H
#define DRPC_H

# include <discord_register.h>
# include <discord_rpc.h>
# include <iostream>
# include <ctime>
# include "utils.h"

class DRPC
{
	private:
		DiscordEventHandlers *handler;
		DiscordRichPresence *presence;
		const char* cid;

	public:
		DRPC(const char* cID);
		void init();
		void update(server* info, bool update_time);

};

#endif 