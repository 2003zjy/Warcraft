#include "warrior.h"
#include "cstdio"
#include "cstring"
extern City *citys;
extern int K;

weapon::weapon(_WEAPON type, const warrior &w)
{
    if (type == sword)
    {
        id = 0;
        ATKtoOther = w.getATK() * 2 / 10;
        ATKtoSelf = 0;
        NumOfUse = -1;
    } else if (type == bomb)
    {
        id = 1;
        ATKtoOther = w.getATK() * 4 / 10;
        ATKtoSelf = w.getATK() * 2 / 10;
        NumOfUse = 1;
    } else if (type == arrow)
    {
        id = 2;
        ATKtoOther = w.getATK() * 3 / 10;
        ATKtoSelf = 0;
        NumOfUse = 2;
    }
}

bool weapon::operator<(const weapon &b) const
{
    if (NumOfUse == 0)
        return false;
    if (b.NumOfUse == 0)
        return true;
    if (id != b.id)
        return id < b.id;
    return NumOfUse > b.NumOfUse;
}

warrior::warrior(_WARRIOR ttype, int curid, _CAMP tcamp) : type(ttype), id(curid), visble(true), camp(tcamp)
{
    ATK = InitATK[type];
    Health = InitHealth[type];
    if (type == dragon || type == lion)
        weapons.push_back(weapon(_WEAPON(id % 3), *this));
    if (type == ninja)
    {
        weapons.push_back(weapon(_WEAPON(id % 3), *this));
        weapons.push_back(weapon(_WEAPON((id + 1) % 3), *this));
    }
    if (type == iceman)
        weapons.push_back(weapon(_WEAPON(id % 3), *this));
}

void warrior::march()
{
    if (type == iceman)
        Health -= Health / 10;
    if (Health <= 0)
    {
        visble = false;
        return;
    }
    if (camp == RED)
    {
        citys[pos].clear();
        pos++;
        citys[pos].add(camp, id);
    }
}

void warrior::report_march()
{
    char wartypename[10];
    switch (type) {
        case dragon:
            strcpy(wartypename, "dragon");
            break;
        case ninja:
            strcpy(wartypename, "ninja");
            break;
        case iceman:
            strcpy(wartypename, "iceman");
            break;
        case lion:
            strcpy(wartypename, "lion");
            break;
        case wolf:
            strcpy(wartypename, "wolf");
            break;
    }
    printf("%03d:10 %s %s %d marched to city %d with %d elements and force %d\n",CurHour, camp == RED ? "red" : "blue", wartypename, id);
}

Lion::Lion(_WARRIOR ttype, int curid, _CAMP tcamp) : warrior(ttype, curid, tcamp) {}

warrior *Command::create()
{
    curid++;
    _WARRIOR wartype = makelist[camp][CurHour % 5];
    warrior *pt;
    if (wartype == lion)
        pt = new Lion(wartype, curid, camp);
    else if (wartype == wolf)
        pt = new Wolf(wartype, curid, camp);
    else
        pt = new warrior(wartype, curid, camp);
    char wartypename[10];
    switch (wartype) {
        case dragon:
            strcpy(wartypename, "dragon");
            break;
        case ninja:
            strcpy(wartypename, "ninja");
            break;
        case iceman:
            strcpy(wartypename, "iceman");
            break;
        case lion:
            strcpy(wartypename, "lion");
            break;
        case wolf:
            strcpy(wartypename, "wolf");
            break;
    }
    printf("%03d:00 %s %s %d born\n", CurHour, camp == RED ? "red" : "blue", wartypename, curid);
    if (wartype == lion)
        printf("Its loyalty is %d\n", K);
    return pt;
}