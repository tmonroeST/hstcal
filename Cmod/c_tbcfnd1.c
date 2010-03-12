# include <ctype.h>
# include <stdlib.h>
# include <string.h>
# include <fitsio.h>
# include "ctables.h"

static void str_lower (char lc_name[], char name[]);

void c_tbcfnd1 (IRAFPointer tp, char *colname, IRAFPointer *cp) {

/* Find the column pointer for the column with the specified name.
arguments:
IRAFPointer tp          i: table descriptor
char *colname           i: column name
IRAFPointer *cp         o: column descriptor
*/

        char lc_colname[SZ_FITS_STR+1], lc_name[SZ_FITS_STR+1];
        TableDescr *tbl_descr;
        ColumnDescr *col_descr;
        int foundit = 0;
        int i;

        str_lower (lc_colname, colname);

        tbl_descr = (TableDescr *)tp;
        for (i = 0;  i < tbl_descr->ncols;  i++) {
            col_descr = (ColumnDescr *)tbl_descr->columns[i];
            str_lower (lc_name, col_descr->name);
            if (strcmp (lc_colname, lc_name) == 0) {
                foundit = 1;
                *cp = tbl_descr->columns[i];
                break;
            }
        }

        if (!foundit)
            *cp = NULL;
}

static void str_lower (char lc_name[], char name[]) {
/* Copy name to lc_name, converting to lower case. */

        int i;

        for (i = 0;  name[i] != '\0';  i++) {
            if (isupper (name[i]))
                lc_name[i] = tolower (name[i]);
            else
                lc_name[i] = name[i];
        }
        lc_name[i] = '\0';
}
