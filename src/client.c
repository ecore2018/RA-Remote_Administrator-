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

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <util.h>

#define PORT 6667
#define IP "127.0.0.1"
#define MAXLINE 1000
#define STOP "stop_e"
#define REPLY 10000
#define RED \e[41m

int main(){

   int TCP, n_read, n_sent;
   char buffer[ MAXLINE ], reply[ REPLY ];
   struct sockaddr_in server;
   
   _print_header();
   
   if( ( TCP = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 )
      die();
   
   sock_init( &server, PORT, inet_addr( IP ) );
    
   if( connect( TCP, ( struct sockaddr * ) &server, sizeof( server ) ) < 0 )
      die();
   
   while( 1 ){
   
      printf( "-" );
      memset( buffer, 0x0, sizeof( buffer ) );
      fgets( buffer, sizeof( buffer ), stdin );
      buffer[ strlen( buffer ) - 1 ] = '\0';
      
      if( !strcmp( buffer, STOP ) ){
      
         printf( "Exiting...\n" );
         close( TCP );
         exit( EXIT_SUCCESS );
      
      }
      
      if( ( n_sent = send( TCP, buffer, sizeof( buffer ), 0 ) ) < 0 )
         die();
      
      printf( "String sent correctly\n" );
      
      if( ( n_read = recv( TCP, reply, sizeof( reply ), 0 ) ) < 0 )
         die();
      
      printf( "Correct execution\n" );
   
   }   
   
   close( TCP );
   return 0;

}
