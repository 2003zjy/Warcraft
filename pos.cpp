#include "pos.h"
#include "cstdio"

extern int CurHour;

void Command::report_bio()
{
    printf("%03d:50 %d elements in %s headquarter\n", CurHour, bioelement, (camp == RED ? "red" : "blue"));
}
