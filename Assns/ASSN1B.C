/* Assignment 1b
 *
 * Inputs list of words and prints it out backwards
 *
 * Modified   By               Reason
 * ========   ==               ======
 * 90/01/02   T. Weatherhead   Initial implementation
 * 90/01/03         ""         Modified
 * 90/02/09         ""         Style changes
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>


static void process( int n )
{
    char *  st;

    st = (char *)malloc( 80 );
    printf( "Word #%d: ", n );
    fgets( st, 80, stdin );

    if( strlen( st ) > 1 ) {
        process( n + 1 );
    }

    printf( "%s", st );
    free( st );
}


extern void main( void )
{
    process( 1 );
}
