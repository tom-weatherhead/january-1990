/* usemap.c
 *
 * Modified   Reason
 * ========   ======
 * 90/02/27   Initial implementation on PS2
 * 90/03/29   City information added
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <malloc.h>
#include "map.h"

char **         realmap;
char **         usermap;
citytype *      City;
int             ncities;
int             Xlim;
int             Ylim;



extern void main( int argc, char * argv[] )
{
    FILE *      strm;
    char *      buf;
    char        inch;
    citytype *  cityptr;
    int         i;
    int         x;
    int         y;
    piece *     pc;

    if( argc != 2 ) {
        printf( "Usage: usemap mapname\n" );
        exit( 0 );
    }
    printf( "Press a key:\n" );
    getch();
    srand( (unsigned int)clock() );
    /* Read in map */
    strm = fopen( argv[ 1 ], "r" );
    if( strm == NULL ) {
        printf( "Unable to open file\n" );
        exit( 0 );
    }
    fscanf( strm, "%d %d ", &Xlim, &Ylim );
    if( Xlim <= 0  ||  Ylim <= 0  ||  Xlim * Ylim > 1000 ) {
        printf( "Illegal dimensions: Xlim = %d, Ylim = %d\n", Xlim, Ylim );
        exit( 0 );
    }
    realmap = (char **)malloc( Ylim * sizeof( char * ) );
    usermap = (char **)malloc( Ylim * sizeof( char * ) );
    if( realmap == NULL  ||  usermap == NULL ) {
        printf( "malloc error on realmap/usermap\n" );
        exit( 0 );
    }
    buf = (char *)malloc( Xlim + 1 );
    for( y = 0; y < Ylim; y++ ) {
        realmap[ y ] = (char *)malloc( Xlim + 1 );
        usermap[ y ] = (char *)malloc( Xlim + 1 );
        if( realmap[ y ] == NULL  ||  usermap[ y ] == NULL ) {
            printf( "malloc error on realmap/usermap [%d]\n", y );
            fclose( strm );
            exit( 0 );
        }
        fgets( buf, Xlim + 1, strm );
        strcpy( realmap[ y ], buf );
        memset( usermap[ y ], ' ', Xlim );
        usermap[ y ][ Xlim ] = '\0';
    }
    free( buf );
    /* Read in city data */
    fscanf( strm, "%d ", &ncities );
    City = (citytype *)malloc( ncities * sizeof( citytype ) );
    for( i = 0; i < ncities; i++ ) {
        cityptr = &City[ i ];
        fscanf( strm, "%d %d %c %d %d ", &cityptr->x, &cityptr->y,
            &cityptr->who_owns, &cityptr->prod, &cityptr->next_prod );
        realmap[ cityptr->y ][ cityptr->x ] = cityptr->who_owns;
    }
    fclose( strm );
    /* Place piece */
    pc = (piece *)malloc( sizeof( piece ) );
    pc->data = Pieces;
    do {
        x = rand() % Xlim;
        y = rand() % Ylim;
    } while( realmap[ y ][ x ] != '+' );
    printf( "%c at %02d%02d\n\n", pc->data->ouch, x, y );
    pc->x = x;
    pc->y = y;
    pc->under = '+';
    /* Move piece around */
    for( ; ; ) {
        realmap[ pc->y ][ pc->x ] = pc->data->ouch;
        prtlocal( pc->x, pc->y );
        prtmap( usermap );
        x = pc->x;
        y = pc->y;
        do {
            printf( "%02d%02d: ", pc->x, pc->y );
            inch = (char)getch();
            if( inch == ESC ) break;
            if( pc->y  &&  ( inch == 'q'  ||  inch == 'w'  ||
              inch == 'e' ) ) {
                pc->y--;
            } else if( pc->y < Ylim - 1  &&  ( inch == 'z'  ||  inch == 'x'
              ||  inch == 'c' ) ) {
                pc->y++;
            }
            if( pc->x  &&  ( inch == 'q'  ||  inch == 'a'  ||
                inch == 'z' ) ) {
                pc->x--;
            } else if( pc->x < Xlim - 1  &&  ( inch == 'e'  ||  inch == 'd'
                ||  inch == 'c' ) ) {
                pc->x++;
            }
            if( realmap[ pc->y ][ pc->x ] == '.' ) {
                pc->x = x;
                pc->y = y;
            }
        } while( x == pc->x  &&  y == pc->y );
        if( inch == ESC ) break;
        realmap[ y ][ x ] = pc->under;
        pc->under = realmap[ pc->y ][ pc->x ];
    }
    /* Save map */
    printf( "Save? (y/n): " );
    if( (char)getch() == 'y' ) {
        strm = fopen( argv[ 1 ], "w" );
        for( y = 0; y < Ylim; y++ ) {
            fprintf( strm, "%s\n", realmap[ y ] );
        }
        for( i = 0; i < ncities; i++ ) {
            cityptr = &City[ i ];
            fprintf( strm, "%d%d%c%d%d", cityptr->x, cityptr->y,
              cityptr->who_owns, cityptr->prod, cityptr->next_prod );
        }
        fclose( strm );
    }
    /* Free data structures */
    for( y = 0; y < Ylim; y++ ) {
        free( realmap[ y ] );
        free( usermap[ y ] );
    }
    free( realmap );
    free( usermap );
    free( pc );
    free( City );
}



static void prtmap( char ** map )
{
    int     x;
    int     y;

    printf( "\n  " );
    for( x = 0; x < Xlim; x += 10 ) {
        printf( "%d         ", x / 10 );
    }
    printf( "\n  " );
    for( x = 0; x < Xlim; x++ ) {
        putchar( x % 10 + '0' );
    }
    putchar( '\n' );
    for( y = 0; y < Ylim; y++ ) {
        printf( "%2d%s\n", y, map[ y ] );
    }
}



static void prtlocal( int x, int y )
{
    int     bot;
    int     len;
    int     lft;
    int     top;
    int     y2;

    top = ( y ) ? y - 1 : 0 ;
    bot = ( y < Ylim - 1 ) ? y + 1 : y ;
    lft = ( x ) ? x - 1 : 0 ;
    len = ( x  &&  x < Xlim - 1 ) ? 3 : 2 ;
    for( y2 = top; y2 <= bot; y2++ ) {
        strncpy( usermap[ y2 ] + lft, realmap[ y2 ] + lft, len );
    }
}
