#include "armor.h"

// Default Constructor of Armor()
Armor::Armor()
{
    this->m_name = "";
    this->m_gender = "none";
    this->m_bodyPart = "";
    this->m_hunterType = "both";
    this->m_rarity = "0";
    this->m_decoSlots = 0;
    this->m_baseDef = 0;
    this->m_maxDef = 0;
    this->m_fireDef = 0;
    this->m_waterDef = 0;
    this->m_thunderDef = 0;
    this->m_iceDef = 0;
    this->m_dragonDef = 0;
    this->m_skill1.name = "";
    this->m_skill2.name = "";
    this->m_skill3.name = "";
    this->m_skill4.name = "";
    this->m_skill5.name = "";
    this->m_skill1.points = 0;
    this->m_skill2.points = 0;
    this->m_skill3.points = 0;
    this->m_skill4.points = 0;
    this->m_skill5.points = 0;
    this->m_numSkills = -1;     // Starts at -1 due to an issue with m_numSkills++
}/*Armor::Armor();*/

// Prints all the armor values 
/**/
/*
void Armor::PrintArmor() void Armor::PrintArmor()

NAME
        Armor::PrintArmor - prints the armor values to output

SYNOPSIS
    
        void Armor::PrintArmor()

DESCRIPTION

        Simple print function to output all the values of this armor piece

RETURNS
        
        void 

AUTHOR
        Alec Rizzo

*/
/**/
void Armor::PrintArmor()
{
    cout << "Name: " << this->m_name << endl;
    cout << "Gender: " << this->m_gender << endl;
    cout << "Body Part: " << this->m_bodyPart << endl;
    cout << "Hunter Type: " << this->m_hunterType << endl;
    cout << "Rarity: " << this->m_rarity << endl;
    cout << "Decoration Slots: " << this->m_decoSlots << endl;
    cout << "Base Defense: " << this->m_baseDef << endl;
    cout << "Max Defense: " << this->m_maxDef << endl;
    cout << "Fire Defense: " << this->m_fireDef << endl;
    cout << "Water Defense: " << this->m_waterDef << endl;
    cout << "Thunder Defense: " << this->m_thunderDef << endl;
    cout << "Ice Defense: " << this->m_iceDef << endl;
    cout << "Dragon Defense: " << this->m_dragonDef << endl;
    cout << "Skill1: " << this->m_skill1.name << " " << this->m_skill1.points << endl;
    cout << "Skill2: " << this->m_skill2.name << " " << this->m_skill2.points << endl;
    cout << "Skill3: " << this->m_skill3.name << " " << this->m_skill3.points << endl;
    cout << "Skill4: " << this->m_skill4.name << " " << this->m_skill4.points << endl;
    cout << "Skill5: " << this->m_skill5.name << " " << this->m_skill5.points << endl;
}/*void Armor::PrintArmor();*/

// Sets passed name as the new name of the armor
void Armor::SetName(string a_name)
{
    this->m_name = a_name;
}/*void Armor::SetName(string a_name);*/

// Sets passed gender as the new gender of the armor
void Armor::SetGender(string a_gender)
{
    this->m_gender = a_gender;
}/*void Armor::SetGender(string a_gender);*/

// Sets passed armor type as the new armor type
void Armor::SetBodyPart(string a_bodyPart)
{
    this->m_bodyPart = a_bodyPart;
}/*void Armor::SetBodyPart(string a_bodyPart);*/

// Sets passed hunter type as the new hunter type
void Armor::SetHunterType(string a_hunterType)
{
    this->m_hunterType = a_hunterType;
}/*void Armor::SetHunterType(string a_hunterType);*/

// Sets passed rarity as the new rarity of the armor
void Armor::SetRarity(string a_rarity)
{
    this->m_rarity = a_rarity;
}/*void Armor::SetRarity(string a_rarity);*/

// Sets passed deco slots int as the new value for decoSlots
void Armor::SetDecoSlots(int a_decoSlots)
{
    this->m_decoSlots = a_decoSlots;
}/*void Armor::SetDecoSlots(int a_decoSlots);*/

// Sets passed int as the new value of baseDef
void Armor::SetBaseDef(int a_baseDef)
{
    this->m_baseDef = a_baseDef;
}/*void Armor::SetBaseDef(int a_baseDef);*/

// Sets passed int as the new value of maxDef
void Armor::SetMaxDef(int a_maxDef)
{
    this->m_maxDef = a_maxDef;
}/*void Armor::SetMaxDef(int a_maxDef);*/

// Sets passed int as the new value of fireDef
void Armor::SetFireDef(int a_fireDef)
{
    this->m_fireDef = a_fireDef;
}/*void Armor::SetFireDef(int a_fireDef);*/

// Sets passed int as the new value of waterDef
void Armor::SetWaterDef(int a_waterDef)
{
    this->m_waterDef = a_waterDef;
}/*void Armor::SetWaterDef(int a_waterDef);*/

// Sets passed int as the new value of thunderDef
void Armor::SetThunderDef(int a_thunderDef)
{
    this->m_thunderDef = a_thunderDef;
}/*void Armor::SetThunderDef(int a_thunderDef);*/

// Sets passed int as the new value of iceDef
void Armor::SetIceDef(int a_iceDef)
{
    this->m_iceDef = a_iceDef;
}/*void Armor::SetIceDef(int a_iceDef);*/

// Sets passed int as the new value of dragonDef
void Armor::SetDragonDef(int a_dragonDef)
{
    this->m_dragonDef = a_dragonDef;
}/*void Armor::SetDragonDef(int a_dragonDef);*/

// Sets passed string as the new value of skill1 name and increases num skills
void Armor::SetSkill1(string a_skill1)
{
    this->m_skill1.name = a_skill1;
    this->m_numSkills++;
}/*void Armor::SetSkill1(string a_skill1);*/

// Sets passed string as the new value of skill2 name and increases num skills
void Armor::SetSkill2(string a_skill2)
{
    this->m_skill2.name = a_skill2;
    this->m_numSkills++;
}/*void Armor::SetSkill2(string a_skill2);*/

// Sets passed string as the new value of skill3 name and increases num skills
void Armor::SetSkill3(string a_skill3)
{
    this->m_skill3.name = a_skill3;
    this->m_numSkills++;
}/*void Armor::SetSkill3(string a_skill3);*/

// Sets passed string as the new value of skill4 name and increases num skills
void Armor::SetSkill4(string a_skill4)
{ 
    this->m_skill4.name = a_skill4; 
    this->m_numSkills++;
}/*void Armor::SetSkill4(string a_skill4);*/

// Sets passed string as the new value of skill5 and increases num skills
void Armor::SetSkill5(string a_skill5)
{
    this->m_skill5.name = a_skill5;
    this->m_numSkills++;
}/*void Armor::SetSkill5(string a_skill5);*/

// Sets passed int as the new value of skill1 points
void Armor::SetSkill1Points(int a_skill1Points)
{
    this->m_skill1.points = a_skill1Points;
}/*void Armor::SetSkill1Points(int a_skill1Points);*/

// Sets passed int as the new value of skill2 points
void Armor::SetSkill2Points(int a_skill2Points)
{
    this->m_skill2.points = a_skill2Points;
}/*void Armor::SetSkill2Points(int a_skill2Points);*/

// Sets passed int as the new value of skill3 points
void Armor::SetSkill3Points(int a_skill3Points)
{
    this->m_skill3.points = a_skill3Points;
}/*void Armor::SetSkill3Points(int a_skill3Points);*/

// Sets passed int as the new value of skill4 points
void Armor::SetSkill4Points(int a_skill4Points)
{
    this->m_skill4.points = a_skill4Points;
}/*void Armor::SetSkill4Points(int a_skill4Points);*/

// Sets passed int as the new value of skill5 points
void Armor::SetSkill5Points(int a_skill5Points)
{
    this->m_skill5.points = a_skill5Points;
}/*void Armor::SetSkill5Points(int a_skill5Points);*/

// Returns the string value of name 
string Armor::GetName() 
{
    return this->m_name;
}/*string Armor::GetName();*/

// Returns the string value of gender 
string Armor::GetGender()
{
    return this->m_gender;
}/*string Armor::GetGender();*/

// Returns the string value of bodyPart 
string Armor::GetBodyPart()
{
    return this->m_bodyPart;
}/*string Armor::GetBodyPart();*/

// Returns the string value of hunterType
string Armor::GetHunterType()
{
    return this->m_hunterType;
}/*string Armor::GetHunterType();*/

// Returns the string value of rarity 
string Armor::GetRarity()
{
    return this->m_rarity;
}/*string Armor::GetRarity();*/

// Returns the int value of decoSlots
int Armor::GetDecoSlots()
{
    return this->m_decoSlots;
}/*int Armor::GetDecoSlots();*/

// Returns the int value of baseDef
int Armor::GetBaseDef()
{
    return this->m_baseDef;
}/*int Armor::GetBaseDef();*/

// Returns the int value of maxDef
int Armor::GetMaxDef()
{
    return this->m_maxDef;
}/*int Armor::GetMaxDef();*/

// Returns the int value of fireDef
int Armor::GetFireDef()
{
    return this->m_fireDef;
}/*int Armor::GetFireDef();*/

// Returns the int value of waterDef
int Armor::GetWaterDef()
{
    return this->m_waterDef;
}/*int Armor::GetWaterDef();*/

// Returns the int value of thunderDef
int Armor::GetThunderDef()
{
    return this->m_thunderDef;
}/*int Armor::GetThunderDef();*/

// Returns the int value of iceDef
int Armor::GetIceDef()
{
    return this->m_iceDef;
}/*int Armor::GetIceDef();*/

// Returns the int value of dragonDef
int Armor::GetDragonDef()
{
    return this->m_dragonDef;
}/*int Armor::GetDragonDef();*/

// Returns the string value of skill1
string Armor::GetSkill1()
{
    return this->m_skill1.name;
}/*string Armor::GetSkill1();*/

// Returns the string value of skill2
string Armor::GetSkill2()
{
    return this->m_skill2.name;
}/*string Armor::GetSkill2();*/

// Returns the string value of skill13
string Armor::GetSkill3()
{
    return this->m_skill3.name;
}/*string Armor::GetSkill3();*/

// Returns the string value of skill4
string Armor::GetSkill4()
{
    return this->m_skill4.name;
}/*string Armor::GetSkill4();*/

// Returns the string value of skill5
string Armor::GetSkill5()
{
    return this->m_skill5.name;
}/*string Armor::GetSkill5();*/

// Returns the int value of skill1Points
int Armor::GetSkill1Points()
{
    return this->m_skill1.points;
}/*int Armor::GetSkill1Points();*/

// Returns the int value of skill2Points
int Armor::GetSkill2Points()
{
    return this->m_skill2.points;
}/*int Armor::GetSkill2Points();*/

// Returns the int value of skill3Points
int Armor::GetSkill3Points()
{
    return this->m_skill3.points;
}/*int Armor::GetSkill3Points();*/

// Returns the int value of skill4Points
int Armor::GetSkill4Points()
{
    return this->m_skill4.points;
}/*int Armor::GetSkill4Points();*/

// Returns the int value of skill5Points
int Armor::GetSkill5Points()
{
    return this->m_skill5.points;
}/*int Armor::GetSkill5Points();*/

// Returns the int value of numSkills
int Armor::GetNumSkills()
{
    return this->m_numSkills;
}/*int Armor::GetNumSkills();*/

// Sets the member vector m_decorations to the passed vector a_decorations
void Armor::SetDecorations(vector<Decoration> a_decorations)
{
    this->m_decorations = a_decorations;
}/*void Armor::SetDecorations(vector<Decoration> a_decorations);*/

// Returns the member vector of decorations, m_decorations
vector<Decoration> Armor::GetDecorations()
{
    return this->m_decorations;
}/*vector<Decoration> Armor::GetDecorations();*/

/**/
/*
Armor::GetRemainingDecoSlots() Armor::GetRemainingDecoSlots()

NAME
        
        Armor::GetRemainingDecoSlots - gets how many decoration slots 
                                       remain on this armor piece
SYNOPSIS

DESCRIPTION

        This function will return the amount of decoration slots remaining
        on this armor piece

RETURNS
        Returns integer for the amoung of slots remaining

AUTHOR
        Alec Rizzo

*/
/**/
int Armor::GetRemainingDecoSlots()
{
    int slotsUsed = 0;
    int slotsRemaining = 0;
    // Determine how many slots were used on this armor piece so far
    for (int i = 0; i < m_decorations.size(); i++)
    {
        slotsUsed += m_decorations.at(i).GetSlotsRequired();
    }
    // Based on the remaining slots see if we can add the passed decoration to the armor
    slotsRemaining =  m_decoSlots - slotsUsed;
    return slotsRemaining;
}/*int Armor::GetRemainingDecoSlots();*/

/**/
/*
void Armor::AddDecorationToArmor() void Armor::AddDecorationToArmor()

NAME
        
        Armor::AddDecorationToArmor - adds a decoration to the armor

SYNOPSIS

        void Armor::AddDecorationToArmor(Decoration a_decoration)

            a_decoration    -->     the decoration to add to the armor

DESCRIPTION
        
        This function will attempt to add the decoration to this armor piece
        after first determining if it can fit on our armor currently.

RETURNS
        
        Void

AUTHOR
        Alec Rizzo

*/
/**/
void Armor::AddDecorationToArmor(Decoration a_decoration)
{
    int slotsRemaining = GetRemainingDecoSlots();
    if (a_decoration.GetSlotsRequired() <= slotsRemaining)
    {
        m_decorations.push_back(a_decoration);
    }
}/*void Armor::AddDecorationToArmor(Decoration a_decoration);*/