/* genmap.c
 *
 * Modified   Reason
 * ========   ======
 * 90/02/27   Initial implementation on PS2
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <malloc.h>
#include "tomtypes.h"
#include "map.h"

int         Xlim;
int         Ylim;



extern void main( int argc, char * argv[] )
{
    FILE *      strm;
    bool        cont;
    char **     currmap;
    char *      filename;
    char **     nextmap;
    char **     temp;
    int         bot;
    int         cities;
    int         i;
    int         lft;
    int         reps;
    int         rgt;
    int         sum;
    int         top;
    int         x;
    int         x2;
    int         y;
    int         y2;

    if( argc != 4 ) {
        printf( "Usage: genmap width height reps\n" );
        exit( 0 );
    }
    Xlim = atoi( argv[ 1 ] );
    Ylim = atoi( argv[ 2 ] );
    reps = atoi( argv[ 3 ] );
    if( Xlim <= 0  ||  Ylim <= 0  ||  Xlim * Ylim > 1000 ) {
        printf( "Illegal dimension(s)\n" );
        exit( 0 );
    }
    printf( "Press a key:\n" );
    getch();
    srand( (unsigned int)clock() );
    currmap = (char **)malloc( Ylim * sizeof( char * ) );
    nextmap = (char **)malloc( Ylim * sizeof( char * ) );
    if( currmap == NULL  ||  nextmap == NULL ) {
        printf( "malloc error on currmap / nextmap\n" );
        exit( 0 );
    }
    srand( (unsigned int)clock() );
    for( y = 0; y < Ylim; y++ ) {
        currmap[ y ] = (char *)malloc( Xlim + 1 );
        nextmap[y] = (char *)malloc( Xlim + 1 );
        if( currmap[ y ] == NULL  ||  nextmap[ y ] == NULL ) {
            printf( "malloc error on currmap[%d] / nextmap[%d]\n", y, y );
            exit( 0 );
        }
        currmap[ y ][ Xlim ] = '\0';
        nextmap[ y ][ Xlim ] = '\0';
        for( x = 0; x < Xlim; x++ ) {
            currmap[ y ][ x ] = ( rand() % 2 != 0 ) ? '+' : '.' ;
        }
    }
    prtmap( currmap );
    for( ; reps > 0; reps-- ) {
        cont = FALSE;
        for( y = 0; y < Ylim; y++ ) {
            memcpy( nextmap[ y ], currmap[ y ], Xlim );
            top = ( y ) ? y - 1 : 0 ;
            bot = ( y < Ylim - 1 ) ? y + 1 : y ;
            for( x = 0; x < Xlim; x++ ) {
                lft = ( x ) ? x - 1 : 0 ;
                rgt = ( x < Xlim - 1 ) ? x + 1 : x ;
                sum = ( currmap[ y ][ x ] == '+' ) ? 7 : 9 ;
                for( y2 = top; y2 <= bot; y2++ ) {
                    for( x2 = lft; x2 <= rgt; x2++ ) {
                        if( currmap[ y2 ][ x2 ] == '+' ) {
                            sum++;
                        } else {
                            sum--;
                        }
                    }
                }
                if( sum < 5  &&  currmap[ y ][ x ] == '+' ) {
                    nextmap[ y ][ x ] = '.';
                    cont = TRUE;
                } else if( sum > 11  &&  currmap[ y ][ x ] == '.' ) {
                    nextmap[ y ][ x ] = '+';
                    cont = TRUE;
                }
            }
        }
        if( cont == FALSE ) break;
        temp = currmap;
        currmap = nextmap;
        nextmap = temp;
        prtmap( currmap );
    }
    printf( "Save as: (q to quit) " );
    filename = (char *)malloc( 20 );
    for( ; ; ) {
        gets( filename );
        if( *filename == 'q' ) break;
        strm = fopen( filename, "w" );
        if( strm == NULL ) {
            printf( "Unable to open file\n" );
            continue;
        }
        fprintf( strm, "%d %d ", Xlim, Ylim );
        for( y = 0; y < Ylim; y++ ) {
            fprintf( strm, "%s", currmap[ y ] );
        }
        cities = Xlim * Ylim / 50;
        fprintf( strm, "%d ", cities );
        for( i = 0; i < cities; i++ ) {
            do {
                x = rand() % Xlim;
                y = rand() % Ylim;
            } while( currmap[ y ][ x ] != '+' );
            fprintf( strm, "%d %d %c %d %d ", x, y, ( i ) ? NEUTRAL : I_OWN,
              NULL, 0 );
        }
        fclose( strm );
        break;
    }
    free( filename );
    for( y = 0; y < Ylim; y++ ) {
        free( currmap[ y ] );
        free( nextmap[ y ] );
    }
    free( currmap );
    free( nextmap );
}



static void prtmap( char ** currmap )
{
    int     y;

    putchar( '\n' );
    for( y = 0; y < Ylim; y++ ) {
        printf( "%s\n", currmap[ y ] );
    }
}
