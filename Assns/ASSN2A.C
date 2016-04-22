/* Assignment 2a
 *
 * Modified   By               Reason
 * ========   ==               ======
 * 90/01/03   T. Weatherhead   Initial implementation
 * 90/01/05         ""         Modified
 * 90/02/09         ""         Style changes
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tomtypes.h"

bool        presence[256];
char        text[80];



extern void main( void )
{
    int     i;
    int     len;

    memset( presence, FALSE, 256 * sizeof( bool ) );
    putchar( '>' );
    fgets( text, 79, stdin );
    len = strlen( text );
    for( i = 0; i < len; i++ ) {
        presence[ (int)text[ i ] ] = TRUE;
    }
    for( i = 0; i < 256; i++ ) {
        if( presence[ i ] != FALSE ) {
            putchar( (char)i );
        }
    }
    putchar( '\n' );
}
