/* Assignment 1a
 *
 * Inputs list of <= 10 words and prints it out backwards
 *
 * Modified   By               Reason
 * ========   ==               ======
 * 90/01/02   T. Weatherhead   Initial implementation
 * 90/01/05         ""         Modified
 * 90/02/09         ""         Style changes
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct aaa {
    struct aaa *    prev;
    char *          line;
} list;

char        templine[80];


extern void main( void )
{
    list *  listptr;
    list *  oldlptr;

    listptr = NULL;

    for( ; ; ) {
        printf( "> " );
        gets( templine );

        if( strlen( templine ) ) {
            oldlptr = listptr;
            listptr = (list *)malloc( sizeof( list ) );
            listptr->prev = oldlptr;
            listptr->line = (char *)malloc( strlen( templine ) + 1 );
            strcpy( listptr->line, templine );
        } else {
            break;
        }
    }

    while( listptr != NULL ) {
        printf( "%s\n", listptr->line );
        oldlptr = listptr;
        listptr = listptr->prev;
        free( oldlptr->line );
        free( oldlptr );
    }
}
