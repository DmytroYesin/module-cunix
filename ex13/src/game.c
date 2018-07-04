#include <sys/time.h>
#include <stddef.h>
#include "filler.h"
#include "my_string.h"

void timeout_reset(struct timeval *timer)
{
	timer->tv_sec = 1;
	timer->tv_usec = 0;
}

void start_game(filler_t *filler)
{
  req_t      *req;
	pos_t      pos;
	fd_set     rfds, wfds;
	struct     timeval timeout;

	set_nonblocking(0);
  req = create_req();
	while(1)
  {
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);
		switch(filler->status)
    {
			case 0: FD_SET(0, &rfds); break;
			case 1: FD_SET(1, &wfds); break;
		}
		timeout_reset(&timeout);
		select(2, &rfds, &wfds, NULL, &timeout);
		if(FD_ISSET(0, &rfds))
    {
			req = read_request(filler);
			if(req)
      {
				pos = play(req);
				filler->status = 1;
			}
		}
		if(FD_ISSET(1, &wfds))
    {
			print_pos(pos);
			filler->status = 0;
			string_destroy(filler->current_stream);
			filler->current_stream = NULL;
			destroy_req(req);
			req = NULL;
		}
	}
}

