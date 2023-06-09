#ifndef _WARRIOR_H
#define _WARRIOR_H

#include "algorithm"
#include "pos.h"
#include "vector"

class weapon
{
private:
    int ATKtoOther;
    int ATKtoSelf;
    int NumOfUse;
    int id;

public:
    weapon(_WEAPON);
    bool operator<(const weapon &b) const;
    const int getID() { return id; }
    const int getNum() { return NumOfUse; }
    const int getATK2o(const warrior &a);
    const int getATK2s(const warrior &a);
    void use() { --NumOfUse; }
};

class warrior
{
private:
    int id;
    std::vector<weapon> weapons;
    bool visble;
    _WARRIOR type;
    int ATK;
    int Health;
    _CAMP camp;
    int pos;
    int curweaponID;
    void useweapon(warrior &b);
    void beAtk(int);

public:
    warrior(_WARRIOR ttype, int curid, _CAMP tcamp);
    int getATK() const { return ATK; }
    virtual ~warrior(){};
    void march();
    void fight(warrior &b);
    const bool &vis() const { return visble; }
    _CAMP getcamp() { return camp; }
    const int getid() const { return id; }
    const int getpos() const { return pos; }
    void report_march();
    const _WARRIOR &gettype() const { return type; }
    weapon &firstweapon() { return weapons[0]; }
    const int weaponNum() const { return weapons.size(); }
    void report_weapon();
    void addWeapon(const weapon &w) { weapons.push_back(w); }
    void sortWeapon();
    weapon belooted();
    bool emptyWeapon();
    bool sumAtk();
    void died();
};

class Lion : public warrior
{
private:
    bool WillRun;
    int loyalty;

public:
    Lion(_WARRIOR ttype, int curid, _CAMP tcamp, int loy);
    bool isrun();
    void check();
};

class Wolf : public warrior
{
public:
    Wolf(_WARRIOR ttype, int curid, _CAMP tcamp) : warrior(ttype, curid, tcamp){};
    void loot(warrior *b);
};

#endif