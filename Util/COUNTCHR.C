/* countchr.c - Counts frequencies of characters in a file
 *
 * Modified   By               Reason
 * ========   ==               ======
 * 90/01/02   T. Weatherhead   Initial implementation
 * 90/01/26         ""         argv, argc used
 * 90/02/09         ""         Style changes
 * 90/02/16         ""         fgets algorithm changed to fgetc
 * 90/03/28         ""         style changes, optimization
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int         chrnum[256];
int         presence[256];



extern void main( int argc, char * argv[] )
{
    FILE *  strm;
    int     inch;
    int     i;
    int     j;
    int     temp;

    memset( presence, 0, 256 * sizeof( int ) );
    for( i = 0; i < 256; i++ ) {
        chrnum[i] = i;
    }
    if( argc != 2 ) {
        printf( "Usage : countchr filename.ext\n" );
        strm = NULL;
    } else {
        strm = fopen( argv[1], "r" );
        if( strm == NULL ) {
            printf( "File '%s' not found.\n", argv[1] );
        }
    }
    if( strm != NULL) {
        for( ; ; ) {
            inch = fgetc( strm );
            if( inch == EOF ) break;
            presence[inch]++;
        }
        fclose( strm );
        for( i = 1; i <= 20; i++ ) {
            for( j = 254; j >= i; j-- ) {
                if ( presence[j] < presence[j + 1] ) {
                    temp = presence[j];
                    presence[j] = presence[j + 1];
                    presence[j + 1] = temp;
                    temp = chrnum[j];
                    chrnum[j] = chrnum[j + 1];
                    chrnum[j + 1] = temp;
                }
            }
            printf( "%2d: %1c (char #%3d): %5d times\n", i, (char)chrnum[i],
                chrnum[i], presence[i] );
        }
    }
}
