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

#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <util.h>

void _print_header(){

   printf( "%s#####   #\n"    
           " #  #   ##\n"   
           " # #    # #\n" 
           " ###    ####\tRemote_Administrator\n"
          " #  ##  #   #\n"
         " ##  ## #   ##\n\n%s", RED, WHITE );

}

void _usage( const char *name){

   printf( "Usage: \"%s <IP_TO_CONNECT>\"\n", name );
   exit( EXIT_FAILURE );

}

void die(){

   perror( "Client error" );
   exit( EXIT_FAILURE );

}

void sock_init( struct sockaddr_in *server, long int ip, int port ){

   server->sin_family = AF_INET;
   server->sin_port = htons( port );
   server->sin_addr.s_addr = ip;

}
