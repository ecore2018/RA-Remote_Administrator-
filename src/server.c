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

int main(){
   
   int TCP, LIST;
   struct sockaddr_in cli;
   char buff[ MAXLINE ], cmd[ MAXLINE ], sendx[ MAXLINE ];
   FILE *fp;
   
   _print_header();
   
   if( ( LIST = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 )
      die();
      
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
      
      if( ( fp = popen( cmd, "r" ) ) < 0 )
         die();
      
      while( fgets( buff, sizeof( buff ), fp ) > 0 )
         strcat( sendx, buff );
         
      if( send( TCP, sendx , sizeof( sendx ), 0 ) < 0 )
         die();
      
      memset( sendx, 0x0, sizeof( sendx ) );
      memset( buff, 0x0, sizeof( buff ) );
      memset( cmd, 0x0, sizeof( cmd ) );
      fclose( fp );
      
      }
   
   close( LIST );
   close( TCP );
   
   return 0;      
}
