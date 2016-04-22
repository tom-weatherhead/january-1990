/* Assignment 3+
 *
 * Modified   By               Reason
 * ========   ==               ======
 * 90/01/03   T. Weatherhead   Initial implementation
 * 90/01/04         ""         Modified
 * 90/02/09         ""         Style change
 */

#include <stdlib.h>
#include <sys\types.h>
#include <direct.h>
#include <string.h>
#include <process.h>
#include <conio.h>
#include <stdio.h>

char        wslpath[80];
char        wslname[40];
char        line[80];
char        wifname[40];
char        wifpath[80];



extern void main( void )
{
    DIR *   dirpobj;
    DIR *   dpobj;
    DIR *   dirpwsl;
    DIR *   dpwsl;
    DIR *   wifdirp;
    DIR *   wifdirentp;
    char *  period;
    char *  startptr;
    FILE *  strm;

    dirpobj = opendir( "*.OBJ" );
    if( dirpobj == NULL ) {
        exit( 0 );
    }
    for( ; ; ) {
        dpobj = readdir( dirpobj );
        if( dpobj == NULL ) break;
        strcpy( wslname, dpobj->d_name );
        period = strchr( wslname, '.' );
        if( period == NULL  ||  period == wslname ) break;
        /* Got an OBJ file */
        *( period + 1 ) = '\0';
        strcat( wslname, "WSL" );
        _searchenv( wslname, "WSL", wslpath );
        dirpwsl = opendir( wslpath );
        if( dirpwsl == NULL ) continue;
        dpwsl = readdir( dirpwsl );
        if( dpwsl == NULL ) {
            closedir( dirpwsl );
            continue;
        }
        /* Matching source file pointed to by dpwsl */
        if( dpwsl->d_date > dpobj->d_date  ||  ( dpwsl->d_date == dpobj->d_date
          &&  dpwsl->d_time > dpobj->d_time ) ) {
            /* Source file is younger */
            printf( "%s is younger than its OBJ file\n", wslname );
        } else {
            /* Part 3b): read WSL file, search for %include */
            strm = fopen( wslpath, "r" );
            if( strm == NULL ) {
                closedir( dirpwsl );
                continue;
            }
            while( fgets( line, 80, strm ) != NULL ) {
                if( strstr( line, "%include" ) != NULL ) {
                    startptr = strchr( line, '<' );
                    if( startptr == NULL ) continue;
                    startptr++;
                    *strchr( startptr, '>' ) = '\0';
                    strcpy( wifname, startptr );
                    strcat( wifname, ".WIF" );
                    /* Search for WIF file named by wifname */
                    _searchenv( wifname, "WIF", wifpath );
                    wifdirp = opendir( wifpath );
                    if( wifdirp == NULL ) continue;
                    wifdirentp = readdir( wifdirp );
                    if( wifdirentp == NULL ) {
                        closedir( wifdirp );
                        continue;
                    }
                    /* WIF file pointed to by wifdirentp */
                    if( wifdirentp->d_date > dpobj->d_date
                      ||  ( wifdirentp->d_date == dpobj->d_date
                      &&  wifdirentp->d_time > dpobj->d_time ) ) {
                        printf( "OBJ file for %s is older than WIF file %s\n",
                          wslname, wifname );
                    }
                    closedir( wifdirp );
                }
            }
            fclose(strm);
        }
        closedir(dirpwsl);
    }
    closedir(dirpobj);
}
