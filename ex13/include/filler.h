#ifndef _FILLER_H_
#define _FILLER_H_


typedef struct  map_s
{
  int           h;
  int           w;
  char          **array;
}               map_t;

typedef struct  elem_s
{
  int           h;
  int           w;
  char          **array;
}               elem_t;

typedef struct  pos_s
{
  int           x;
  int           y;
}               pos_t;

typedef struct  req_s
{
  char          symbol;
  map_t         map;
  elem_t        elem;
  int           enemn;
}               req_t;

typedef struct  stream_s
{
  char          *str;
  unsigned int  size;
  unsigned int  limit;
}               stream_t;

typedef struct  filler_s
{
  stream_t      *current_stream;
  int           status;
  int           find_enemy;
}               filler_t;

/*Functions for reading*/
req_t*          read_request(filler_t *filler);
void            read_input(filler_t* filler);

/*Functions for parsing*/
req_t*          parse_all(char *all);
int             find_size(char array_elem_size[32], char *buf, int pos);
pos_t           parse_size(char *answer);

/*Functions for game logic*/
void            start_game(filler_t *filler);
pos_t           play(req_t *core);
int check_free_space(map_t *map, elem_t *new_elem, pos_t p);
int check_connection(map_t *map, elem_t *new_elem, pos_t p, char symbol);

/*Functions for printing*/
void            print_pos(pos_t p);

/*Functions for printing logs*/
void            print_log(const char *filename, const char *mode, const char *format, ...);

/*Tools*/
int             set_nonblocking(int fd);
void            fatal();
void            create_filler(filler_t *filler);
void            destroy_filler(filler_t *filler);
req_t           *create_req();
void            destroy_req(req_t *req);
#endif // _FILLER_H_
