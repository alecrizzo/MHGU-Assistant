#pragma once
/********************************************************************************************/
/*

NAME
        data.h - imports the data from the text files and converts it to armor pieces
                 using armor.h

SYNOPSIS


DESCRIPTION
       This header has the functionality of reading the armors from the data sets and
       assigning meaning to the values, which is necessary for creating our armor sets.

RETURNS

AUTHOR
        Alec Rizzo

*/
/********************************************************************************************/

#include "armor.h"

class Data
{
private:
    vector<Armor> head;
    vector<Armor> arms;
    vector<Armor> body;
    vector<Armor> waist;
    vector<Armor> legs;

public:
    Data();
    vector<Armor> loadArmor(string filename);

};