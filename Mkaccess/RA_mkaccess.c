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
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


    Modulo per la gestione dei dati binari per l'autenticazione su Remote_Administrator*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#include <RA_mkaccess.h>
#include <util.h>

#define MAXLINE 100

int main(){

   FILE *flPtr;
   DATA lib;
   char temp[ MAXLINE ]; 
   char *dir = strcat( getenv( "HOME" ), "/.RA_Logging" );
   
   _print_header();
   
   if( ( flPtr = fopen( dir, "wb+" ) ) == NULL ){
   
      perror( "Errore apertura file" );
      exit( EXIT_FAILURE );
   
   }
   
   printf( "Username: " );
   scanf( "%s", lib.username );
   printf( "Password: " );
   scanf( "%s", temp );
   
   _Md5( temp, &lib );
   
   if( fwrite( &lib, sizeof( lib ), 1, flPtr ) < 0 ){
   
      perror( "Errore scrittura binaria" );
      exit( EXIT_FAILURE );
   
   }
   
   printf( "Scrittura eseguita con successo\n" );
   
   return 0;

}
