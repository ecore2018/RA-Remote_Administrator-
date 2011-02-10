#define RED "\e[0;31m"
#define WHITE "\e[0;37m"

void _print_header( void );
void sock_init( struct sockaddr_in *, long int, int );
void die( void );
/*It'll be useful*/
void _Md5( char *, char * );
int testroot( void );
