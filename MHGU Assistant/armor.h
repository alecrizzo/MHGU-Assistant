#pragma once
/********************************************************************************************/
/*

NAME
        armor.h - obtains the necessary functions to create an armorpiece from
                  data assigned through the setter funcitons

DESCRIPTION

       This header has the functionality of making individual armor pieces


AUTHOR

        Alec Rizzo

*/
/********************************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "treeskill.h"
#include "decoration.h"
using namespace std;

class Armor
{
private:
    string m_name;        // name of the armor piece
    string m_gender;      // armor gender: none, male or female
    string m_bodyPart;    // armor type: head, arms, body, legs, waist
    string m_hunterType;  // hunter type: both, blademaster, gunner
    string m_rarity;      // number of the armors rarity, (string due to deviant armor being marked X)
    int m_decoSlots;      // how many decoration slots the equipment has
    int m_baseDef;        // armors initial defense value
    int m_maxDef;         // armors maximum defense value
    int m_fireDef;        // armors fire defense value
    int m_waterDef;       // armors water defense value
    int m_thunderDef;     // armors thunder defense value
    int m_iceDef;         // armors ice defense value
    int m_dragonDef;      // armors dragon defense value
    treeSkill m_skill1;   // armor skills and the associated points as they appear
    treeSkill m_skill2;       // on the skill tree (not active skills)
    treeSkill m_skill3;
    treeSkill m_skill4;
    treeSkill m_skill5;
    vector<Decoration> m_decorations;    // decorations to be equipped based on m_decoSlots

    int m_numSkills;

public:
    Armor();
    void PrintArmor();

    void AddDecorationToArmor(Decoration a_decoration);

    void SetName(string a_name);
    void SetGender(string a_gender);
    void SetBodyPart(string a_bodyPart);
    void SetHunterType(string a_hunterType);
    void SetRarity(string a_rarity);
    void SetDecoSlots(int a_decoSlots);
    void SetBaseDef(int a_baseDef);
    void SetMaxDef(int a_maxDef);
    void SetFireDef(int a_fireDef);
    void SetWaterDef(int a_waterDef);
    void SetIceDef(int a_iceDef);
    void SetThunderDef(int a_thunderDef);
    void SetDragonDef(int a_dragonDef);
    void SetSkill1(string a_skill1);
    void SetSkill2(string a_skill2);
    void SetSkill3(string a_skill3);
    void SetSkill4(string a_skill4);
    void SetSkill5(string a_skill5);
    void SetSkill1Points(int a_skill1Points);
    void SetSkill2Points(int a_skill2Points);
    void SetSkill3Points(int a_skill3Points);
    void SetSkill4Points(int a_skill4Points);
    void SetSkill5Points(int a_skill5Points);
    void SetDecorations(vector<Decoration> a_decorations);

    string GetName();
    string GetGender();
    string GetBodyPart();
    string GetHunterType();
    string GetRarity();
    int GetDecoSlots();
    int GetBaseDef();
    int GetMaxDef();
    int GetFireDef();
    int GetWaterDef();
    int GetThunderDef();
    int GetIceDef();
    int GetDragonDef();
    string GetSkill1();
    string GetSkill2();
    string GetSkill3();
    string GetSkill4();
    string GetSkill5();
    int GetSkill1Points();
    int GetSkill2Points();
    int GetSkill3Points();
    int GetSkill4Points();
    int GetSkill5Points();
    int GetNumSkills();
    vector<Decoration> GetDecorations();
    int GetRemainingDecoSlots();
};

