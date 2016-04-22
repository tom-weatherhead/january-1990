/* dataconv.c
 * Data file converter
 *
 * Modified   By               Reason
 * ========   ==               ======
 * 90/01/08   T. Weatherhead   Initial implementation
 * 90/01/12         ""         Changed to leave spaces inside quoted strings
 *                             and to ask for input and output filenames
 * 90/02/09         ""         Changed to take command line arguments,
 *                             style changes
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>



extern void main( int argc, char * argv[] )
{
    FILE *      instrm;
    FILE *      outstrm;
    char *      dqptr;
    char *      end;
    char *      line;
    char        notq;
    char        q;
    char        quotemode;
    char *      sqptr;
    char *      start;
    int         lineno;

    if( argc != 3 ) {
        printf( "Usage : dataconv infile.ext outfile.ext\n" );
        exit( 0 );
    }
    instrm = fopen( argv[ 1 ], "r" );
    if( instrm == NULL ) {
        printf( "Unable to open input file '%s'\n", argv[ 1 ] );
    }
    outstrm = fopen( argv[ 2 ], "w" );
    if ( outstrm == NULL ) {
        printf( "Unable to open output file '%s'\n", argv[ 2 ] );
    }
    if( instrm == NULL  ||  outstrm == NULL ) {
        if( instrm != NULL ) {
            fclose( instrm );
        }
        if( outstrm != NULL ) {
            fclose( outstrm );
        }
        exit( 0 );
    }
    line = (char *)malloc( 100 );
    for( lineno = 0; fgets( line, 100, instrm ) != NULL; lineno++ ) {
        sqptr = strchr( line, '\'' );
        dqptr = strchr( line, '"' );
        if( sqptr == NULL  ||  ( dqptr != NULL  &&  sqptr >= dqptr ) ) {
            start = dqptr;
            q = '\'';
            notq = '"';
        } else {
            start = sqptr;
            q = '"';
            notq = '\'';
        }
        if( start != NULL ) {
            quotemode = 0;
            start++;
            end = strchr( start, notq );
            for( ; start < end; start++ ) {
                if( *start == q ) {
                    quotemode = ~quotemode;
                }
                if( *start != ' '  ||  quotemode ) {
                    fputc( *start, outstrm );
                }
            }
            fputc( '\n', outstrm );
        }
    }
    free( line );
    fclose( instrm );
    fclose( outstrm );
    printf( "%d lines of code processed.\n", lineno );
}
