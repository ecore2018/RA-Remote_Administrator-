#define RED "\e[0;31m"
#define WHITE "\e[0;37m"

void _print_header( void );
void _usage( const char *);
void sock_init( struct sockaddr_in *, long int, int );
void die( void );
