/* Assignment 1c
 *
 * Inputs list of words and prints it out backwards and forwards
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
#include <malloc.h>

typedef struct ll {
  char *        text;
  struct ll *   fwd;
  struct ll *   bak;
} list;



static list * process( void )
{
    char *      templine;
    int         len;
    list *      cur;
    list *      prev;

    templine = (char *)malloc( 40 );
    prev = NULL;
    for( ; ; ) {
        putchar( '>' );
        fgets( templine, 40, stdin );
        len = strlen( templine );
        if( len < 2 ) {
            cur = NULL;
        } else {
            cur = (list *)malloc( sizeof( list ) );
            cur->bak = prev;
            cur->text = (char *)malloc( len + 1 );
            strcpy( cur->text, templine );
        }
        if( prev != NULL ) {
            prev->fwd = cur;
        }
        if( cur != NULL ) {
            prev = cur;
        } else break;
    }
    free( templine );
    return prev;
}



extern void main( void )
{
    list *      cur;
    list *      process( void );

    cur = process();
    if( cur == NULL ) {
        exit( 0 );
    }
    printf( "\nBackwards...\n" );
    for( ; ; cur = cur->bak ) {
        fputs( cur->text, stdout );
        if( cur->bak == NULL ) break;
    }
    printf( "\nForwards...\n" );
    for( ; cur != NULL; cur = cur->fwd ) {
        fputs( cur->text, stdout );
    }
}
