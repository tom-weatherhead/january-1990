/* Assignment 2
 *
 * Modified   By               Reason
 * ========   ==               ======
 * 90/01/02   T. Weatherhead   Initial implementation
 * 90/01/05         ""         Modified
 * 90/02/09         ""         Style changes
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char        text[80];
int         presence[256];



extern void main( void )
{
    int     i;
    int     len;

    memset( presence, 0, 256 * sizeof( int ) );
    printf( "Text: " );
    fgets( text, 79, stdin );
    len = strlen( text );
    for( i = 0; i <= len; i++ ) {
        presence[ (int)text[ i ] ]++;
    }
    for( i = 0; i < 256; i++ ) {
        printf( "%3d: %-3d  ", i, presence[ i ] );
    }
    putchar( '\n' );
}
