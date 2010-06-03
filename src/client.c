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
#define STOP "stop_execution"
#define REPLY 10000
#define RED \e[41m

int main(){

   int TCP, n_read;
   char buffer[ MAXLINE ], reply[ REPLY ];
   struct sockaddr_in server;
   
   _print_header();
   
   if( ( TCP = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 )
      die();
   
   sock_init( &server, PORT, inet_addr( IP ) );
    
   if( connect( TCP, ( struct sockaddr * ) &server, sizeof( server ) ) < 0 )
      die();
   
   while( 1 ){
   
      switch( fork() ){
      
         case -1:
            die();
            break;
         
         case 0:
            while( ( n_read = recv( TCP, reply, sizeof( reply ), 0 ) ) > 0 ){
            
               printf( "%s\n", reply );
               memset( reply, 0x0, strlen( reply ) );
               reply[ REPLY - 1 ] = '\0';
            
            }
            break;
         
         default:
            memset( buffer, 0x0, strlen( buffer ) );
            printf( "RED>" );
            fgets( buffer, sizeof( buffer ), stdin );
            buffer[ MAXLINE - 1 ] = '\0';
            send( TCP, buffer, sizeof( buffer ), 0 );
            break;
      
      }
   
   }
   
   close( TCP );
   return 0;

}
