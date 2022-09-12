#pragma once
/********************************************************************************************/
/*

NAME
       data.h - imports the data from the text files and converts it to armor pieces
                 using armor.h

DESCRIPTION

       This header has the functionality of reading the armors from the data sets and
       assigning meaning to the values, which is necessary for creating our armor sets.
       (data sets should be in the local directory of the program/executable)

AUTHOR

        Alec Rizzo

*/
/********************************************************************************************/

#include "activeskill.h"
#include "armor.h"
#include "decoration.h"

class Data
{
private:
    vector<Armor> m_head;
    vector<Armor> m_arms;
    vector<Armor> m_body;
    vector<Armor> m_waist;
    vector<Armor> m_legs;
    vector<Decoration> m_decorations;
    vector<activeSkill> m_possibleSkills;

public:
    Data();
    string DetermineBodyPart(string a_filename);
    vector<Armor> LoadArmor(string a_filename);
    vector<activeSkill> LoadSkills(string a_filename);
    vector<Decoration> LoadDecorations(string a_filename);

    vector<Armor> GetHead();
    vector<Armor> GetArms();
    vector<Armor> GetBody();
    vector<Armor> GetWaist();
    vector<Armor> GetLegs();
    vector<Decoration> GetDecorations();
    vector<activeSkill> GetPossibleSkills();
    bool ActiveSkillExists(string a_activeSkillName);
    bool TreeSkillExists(string a_treeSkillName);
};