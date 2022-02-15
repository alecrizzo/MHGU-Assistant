#pragma once
/********************************************************************************************/
/*

NAME
        armor.h - obtains the necessary functions to create an armorpiece from
                  data assigned through the setter funcitons

SYNOPSIS


DESCRIPTION
       This header has the functionality of reading making individual armor pieces

RETURNS

AUTHOR
        Alec Rizzo

*/
/********************************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Armor
{
private:
    string name;        // name of the armor piece
    string gender;      // armor gender: none, male or female
    string bodyPart;   // armor type: head, arms, body, legs, waist
    string hunterType;  // hunter type: both, blademaster, gunner
    string rarity;      // number of the armors rarity, (string due to deviant armor being marked X)
    int decoSlots;      // how many decoration slots the equipment has
    int baseDef;        // armors initial defense value
    int maxDef;         // armors maximum defense value
    int fireDef;        // armors fire defense value
    int waterDef;       // armors water defense value
    int thunderDef;     // armors thunder defense value
    int iceDef;         // armors ice defense value
    int dragonDef;      // armors dragon defense value
    string skill1;      // armor skills and the associated points
    string skill2;
    string skill3;
    string skill4;
    string skill5;
    int skill1Points;
    int skill2Points;
    int skill3Points;
    int skill4Points;
    int skill5Points;

public:
    Armor();
    void printArmor();
    void setName(string newName);
    void setGender(string newGender);
    void setBodyPart(string newbodyPart);
    void setHunterType(string newHunterType);
    void setRarity(string newRarity);
    void setDecoSlots(int newDecoSlots);
    void setBaseDef(int newBaseDef);
    void setMaxDef(int newMaxDef);
    void setFireDef(int newFireDef);
    void setWaterDef(int newWaterDef);
    void setIceDef(int newIceDef);
    void setThunderDef(int newThunderDef);
    void setDragonDef(int newDragonDef);
    void setSkill1(string newSkill1);
    void setSkill2(string newSkill2);
    void setSkill3(string newSkill3);
    void setSkill4(string newSkill4);
    void setSkill5(string newSkill5);
    void setSkill1Points(int newSkill1Points);
    void setSkill2Points(int newSkill2Points);
    void setSkill3Points(int newSkill3Points);
    void setSkill4Points(int newSkill4Points);
    void setSkill5Points(int newSkill5Points);

    string getName();
    string getGender();
    string getBodyPart();
    string getHunterType();
    string getRarity();
    int getDecoSlots();
    int getBaseDef();
    int getMaxDef();
    int getFireDef();
    int getWaterDef();
    int getThunderDef();
    int getIceDef();
    int getDragonDef();
    string getSkill1();
    string getSkill2();
    string getSkill3();
    string getSkill4();
    string getSkill5();
    int getSkill1Points();
    int getSkill2Points();
    int getSkill3Points();
    int getSkill4Points();
    int getSkill5Points();
};

