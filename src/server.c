/*< [RA-Remote_Administrator-] -A programm created to control the own remote system->
    Copyright (C) <2010>  <D4RKN355-H4CK>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <util.h>

#define BACKLOG 3
#define MAXLINE 1000
#define PORT 6667
#define REPLY 10000

int main(){
   
   int TCP, LIST;
   struct sockaddr_in cli;
   char file[ MAXLINE ], cmd[ MAXLINE ], new_cmd[ 1200 ], reply[ REPLY ];
   FILE *fp;
   
   _print_header();
   
   if( ( LIST = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 )
      die();
   
   snprintf( file, sizeof( file ), "%s/.cmd", getenv( "HOME" ) );
   sock_init( &cli, INADDR_ANY , PORT );
   
   if( ( bind( LIST, ( struct sockaddr * ) &cli, sizeof( cli ) ) ) < 0 )
      die();
   
   if( ( listen( LIST, BACKLOG ) ) < 0 )
      die();
   
   if( ( TCP = accept( LIST, ( struct sockaddr * ) NULL, NULL ) ) < 0 )
      die();
   
   while( 1 ){
   
      if( ( recv( TCP, cmd, sizeof( cmd ), 0 ) ) < 0 )
         die();
      
      memset( new_cmd, 0x0, sizeof( new_cmd ) );
      snprintf( new_cmd, sizeof( new_cmd ), "%s > %s", cmd, file );
      system( new_cmd );
      system( cmd );
      
      if( ( fp = fopen( file, "r" ) ) == NULL )
         die();
      
      memset( reply, 0x0, sizeof( reply ) );   
      fgets( reply, sizeof( reply ), fp );
      reply[ strlen( reply ) ] = '\0';
      
      if( send( TCP, reply, sizeof( reply ), 0 ) < 0 )
         die();
      
      fclose( fp );
      unlink( file );
      
      }
   
   close( LIST );
   close( TCP );
   
   return 0;      
}
