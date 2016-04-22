/* Craps
 *
 * Modified   By               Reason
 * ========   ==               ======
 * 90/01/03   T. Weatherhead   Initial implementation
 * 90/01/05         ""         Modified
 * 90/02/09         ""         Style changes
 * 90/04/06         ""         Optimized
 */

#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include "tomtypes.h"

char *    Dots[ 6 ][ 3 ] = { { "   ", " . ", "   " },
                             { ".  ", "   ", "  ." },
                             { ".  ", " . ", "  ." },
                             { ". .", "   ", ". ." },
                             { ". .", " . ", ". ." },
                             { ". .", ". .", ". ." } };



extern void main( void )
{
    bool    cont;
    bool    cont2;
    int     bet;
    int     dice;
    int     games;
    int     point;
    int     roll( void );
    int     wallet;
    int     wins;

    cont = TRUE;
    wins = 0;
    games = 0;
    wallet = 1000;
    printf( "Welcome to the craps table.\n\n" );
    do {
        for( ; ; ) {
            printf( "\nPlace your bet ( $1 - $%d ): $", wallet );
            scanf( "%d", &bet );
            if( bet > 0  &&  bet <= wallet ) break;
            printf( "\nInvalid amount." );
        }
        printf( "Press any key twice to roll for point:\n" );
        point = roll();
        if( point == 7  ||  point == 11 ) {
            printf( "Winner!\n" );
            wins++;
            wallet += bet;
        } else {
            printf( "\n%d is your point.\n", point );
            cont2 = TRUE;
            do {
                printf( "Press any key twice to roll:\n" );
                dice = roll();
                if( dice == point ) {
                    printf( "Winner!\n" );
                    wins++;
                    wallet += bet;
                    cont2 = FALSE;
                } else if( dice == 7 ) {
                    printf( "Sorry. You lose.\n" );
                    wallet -= bet;
                    cont2 = FALSE;
                } else {
                    printf( "Roll again.\n" );
                }
            } while( cont2 );
        }
        games++;
        printf( "%d wins in %d games\nPercentage: %f\nMoney in wallet: $%d\n",
            wins, games, (double)wins * 100.0 / (double)games, wallet );
        if( wallet <= 0 ) {
            printf( "You're broke!\n" );
            cont = FALSE;
        } else {
            printf( "\nPlay again? ( y / n ): " );
            if( (char)getch() == 'n' ) {
                cont = FALSE;
            }
        }
    } while( cont );
}



static int roll( void )
{
    int     dies[ 2 ];
    int     i;
    int     result;
    int     total;

    total = 0;
    for( i = 0; i < 2; i++ ) {
        getch();
        srand( (unsigned int)clock() );
        result = rand() % 6 + 1;
        dies[ i ] = result - 1;
        total += result;
    }
    for( i = 0; i < 3; i++ ) {
        printf( "%s  %s\n", Dots[ dies[ 0 ] ][ i ], Dots[ dies[ 1 ] ][ i ] );
    }
    putchar( '\n' );
    return total;
}
