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

#include <RA_mkaccess.h>
#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

void _print_header(){

   printf( "#####   #\n"    
           " #  #   ##\n"   
           " # #    # #\n" 
           " ###    ####\tRemote_Administrator\n"
          " #  ##  #   #\n"
         " ##  ## #   ##\n" );

}

void _Md5( const char *stringa, DATA *final ){

   MD5_CTX md5;
   int x, y;
   unsigned char buffer[ 1000 ];
   
   MD5_Init (&md5);
   MD5_Update (&md5, (const unsigned char *) stringa, strlen(stringa));
   MD5_Final ( buffer, &md5);
   
   for( x = 0, y = 0; x < 16; x++, y += 2 )
      sprintf(  &final->password[ y ] , "%02x", buffer[ x ] );

}

int datacmp( DATA *first, DATA *second ){

   if( ( strcmp( first->username, second->username ) == 0 ) && ( strcmp( first->password, second->password ) == 0 ) )
      return 0;
   else
      return -1;
      
}

void init_instruction( char *instruction ){

   strcat( instruction, " > temp" );

}

void _usage( const char *name){

   printf( "Usage: \"%s < username > < password >\"\n", name );
   exit( EXIT_FAILURE );

}
