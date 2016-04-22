/* filepath.c
 *
 * This program finds the path of a given file in or below the current dir
 *
 * Modified   By               Reason
 * ========   ==               ======
 * 90/02/09   T. Weatherhead   Initial implementation
 * 90/03/28         ""         Style changes, optimization
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys\types.h>
#include <direct.h>
#include <malloc.h>



static void search( char * path, char * filename )
{
    DIR *       dirp;
    DIR *       direntp;
    char *      endptr;

    endptr = path + strlen( path );
    if( endptr > path  &&  *( endptr - 1 ) != '\\' ) {
        strcpy( endptr, "\\" );
        endptr++;
    }
    strcpy( endptr, "*.*" );
    dirp = opendir( path );
    if( dirp != NULL ) {
        for( ; ; ) {
            direntp = readdir( dirp );
            if( direntp == NULL ) break;
            if( *(direntp->d_name) != '.' ) {
                *endptr = '\0';
                strcat( path, direntp->d_name );
                if( !strcmp( filename, direntp->d_name ) ) {
                    printf( "Found at %s\n", path );
                }
                search( path, filename );
            }
        }
        closedir( dirp );
    }
}



extern void main( int argc, char * argv[] )
{
    char *  path;

    if( argc != 2 ) {
        printf( "Usage : filepath filename.ext\n" );
    } else {
        path = (char *)malloc( 256 );
        *path = '\0';
        strupr( argv[1] );
        search( path, argv[1] );
        free( path );
    }
}
