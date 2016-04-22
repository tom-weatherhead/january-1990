/* map.h
 *
 * Header file for Map package
 *
 * Modified   Reason
 * ========   ======
 * 90/03/07   Initial implementation
 * 90/03/29   citytype added
 */

typedef struct {
    char            ouch;
    char *          can_go;
    int             hits;
    int             givehits;
    int             prtime;
} pcdata;

typedef struct {
    char            under;
    int             x;
    int             y;
    pcdata *        data;
} piece;

typedef struct aaa {
    int             x;
    int             y;
    char            who_owns;
    pcdata *        prod;
    int             next_prod;
    struct aaa *    next;
} citytype;

const pcdata    Pieces[] = {
    { 'A', "+*X", 1, 1, 5 },
    { 'F', "+.O", 1, 1, 10 },
    { 'D', ".O",  3, 1, 20 },
    { 'S', ".O",  2, 3, 25 },
    { 'T', ".O",  3, 1, 30 },
    { 'R', ".O",  8, 1, 50 },
    { 'C', ".O",  8, 1, 60 },
    { 'B', ".O", 12, 1, 75 },
    NULL };

#define ESC         27
#define YOU_OWN     'X'
#define NEUTRAL     '*'
#define I_OWN       'O'
