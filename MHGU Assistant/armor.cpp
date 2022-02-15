#include "armor.h"

Armor::Armor()
{
    this->name = "";
    this->gender = "none";
    this->bodyPart = "";
    this->hunterType = "both";
    this->rarity = "0";
    this->decoSlots = 0;
    this->baseDef = 0;
    this->maxDef = 0;
    this->fireDef = 0;
    this->waterDef = 0;
    this->thunderDef = 0;
    this->iceDef = 0;
    this->dragonDef = 0;
    this->skill1 = "";
    this->skill2 = "";
    this->skill3 = "";
    this->skill4 = "";
    this->skill5 = "";
    this->skill1Points = 0;
    this->skill2Points = 0;
    this->skill3Points = 0;
    this->skill4Points = 0;
    this->skill5Points = 0;
}

// Prints all the armor values 
void Armor::printArmor()
{
    cout << "Name: " << this->name << endl;
    cout << "Gender: " << this->gender << endl;
    cout << "Body Part: " << this->bodyPart << endl;
    cout << "Hunter Type: " << this->hunterType << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Decoration Slots: " << this->decoSlots << endl;
    cout << "Base Defense: " << this->baseDef << endl; 
    cout << "Max Defense: " << this->maxDef << endl;
    cout << "Fire Defense: " << this->fireDef << endl; 
    cout << "Water Defense: " << this->waterDef << endl;
    cout << "Thunder Defense: " << this->thunderDef << endl;
    cout << "Ice Defense: " << this->iceDef << endl;
    cout << "Dragon Defense: " << this->dragonDef << endl;
    cout << "Skill1: " << this->skill1 << " " << this->skill1Points << endl;
    cout << "Skill2: " << this->skill2 << " " << this->skill2Points << endl;
    cout << "Skill3: " << this->skill3 << " " << this->skill3Points << endl;
    cout << "Skill4: " << this->skill4 << " " << this->skill4Points << endl;
    cout << "Skill5: " << this->skill5 << " " << this->skill5Points << endl;

}

// Sets passed name as the new name of the armor
void Armor::setName(string newName)
{
    this->name = newName;
}

// Sets passed gender as the new gender of the armor
void Armor::setGender(string newGender)
{
    this->gender = newGender;
}

// Sets passed armor type as the new armor type
void Armor::setBodyPart(string newbodyPart)
{
    this->bodyPart = newbodyPart;
}

// Sets passed hunter type as the new hunter type
void Armor::setHunterType(string newHunterType)
{
    this->hunterType = newHunterType;
}

// Sets passed rarity as the new rarity of the armor
void Armor::setRarity(string newRarity) 
{
    this->rarity = newRarity;
}

// Sets passed deco slots int as the new value for decoSlots
void Armor::setDecoSlots(int newDecoSlots) 
{
    this->decoSlots = newDecoSlots;
}

// Sets passed int as the new value of baseDef
void Armor::setBaseDef(int newBaseDef) 
{
    this->baseDef = newBaseDef;
}

// Sets passed int as the new value of maxDef
void Armor::setMaxDef(int newMaxDef) 
{
    this->maxDef = newMaxDef;
}

// Sets passed int as the new value of fireDef
void Armor::setFireDef(int newFireDef) 
{
    this->fireDef = newFireDef;
}

// Sets passed int as the new value of waterDef
void Armor::setWaterDef(int newWaterDef) 
{
    this->waterDef = newWaterDef;
}

// Sets passed int as the new value of thunderDef
void Armor::setThunderDef(int newThunderDef)
{
    this->thunderDef = newThunderDef;
}

// Sets passed int as the new value of iceDef
void Armor::setIceDef(int newIceDef) 
{
    this->iceDef = newIceDef;
}

// Sets passed int as the new value of dragonDef
void Armor::setDragonDef(int newDragonDef) 
{
    this->dragonDef = newDragonDef;
}

// Sets passed string as the new value of skill1
void Armor::setSkill1(string newSkill1) 
{
    this->skill1 = newSkill1;
}

// Sets passed string as the new value of skill2
void Armor::setSkill2(string newSkill2) 
{
    this->skill2 = newSkill2;
}

// Sets passed string as the new value of skill3
void Armor::setSkill3(string newSkill3)
{
    this->skill3 = newSkill3;
}

// Sets passed string as the new value of skill4
void Armor::setSkill4(string newSkill4) 
{ 
    this->skill4 = newSkill4; 
}

// Sets passed string as the new value of skill5
void Armor::setSkill5(string newSkill5) 
{
    this->skill5 = newSkill5;
}

// Sets passed int as the new value of skill1Points
void Armor::setSkill1Points(int newSkill1Points) 
{
    this->skill1Points = newSkill1Points;
}

// Sets passed int as the new value of skill2Points
void Armor::setSkill2Points(int newSkill2Points) 
{
    this->skill2Points = newSkill2Points;
}

// Sets passed int as the new value of skill3Points
void Armor::setSkill3Points(int newSkill3Points)
{
    this->skill3Points = newSkill3Points;
}

// Sets passed int as the new value of skill4Points
void Armor::setSkill4Points(int newSkill4Points)
{
    this->skill4Points = newSkill4Points;
}

// Sets passed int as the new value of skill5Points
void Armor::setSkill5Points(int newSkill5Points)
{
    this->skill5Points = newSkill5Points;
}

// Returns the string value of name 
string Armor::getName() 
{
    return this->name;
}

// Returns the string value of gender 
string Armor::getGender() 
{
    return this->gender;
}

// Returns the string value of bodyPart 
string Armor::getBodyPart() 
{
    return this->bodyPart;
}

// Returns the string value of hunterType
string Armor::getHunterType()
{
    return this->hunterType;
}

// Returns the string value of rarity 
string Armor::getRarity() 
{
    return this->rarity;
}

// Returns the int value of decoSlots
int Armor::getDecoSlots() 
{
    return this->decoSlots;
}

// Returns the int value of baseDef
int Armor::getBaseDef() 
{
    return this->baseDef;
}

// Returns the int value of maxDef
int Armor::getMaxDef() 
{
    return this->maxDef;
}

// Returns the int value of fireDef
int Armor::getFireDef() 
{
    return this->fireDef;
}

// Returns the int value of waterDef
int Armor::getWaterDef() 
{
    return this->waterDef;
}

// Returns the int value of thunderDef
int Armor::getThunderDef() 
{
    return this->thunderDef;
}

// Returns the int value of iceDef
int Armor::getIceDef() 
{
    return this->iceDef;
}

// Returns the int value of dragonDef
int Armor::getDragonDef()
{
    return this->dragonDef;
}

// Returns the string value of skill1
string Armor::getSkill1() 
{
    return this->skill1;
}

// Returns the string value of skill2
string Armor::getSkill2() 
{
    return this->skill2;
}

// Returns the string value of skill13
string Armor::getSkill3()
{
    return this->skill3;
}

// Returns the string value of skill4
string Armor::getSkill4() 
{
    return this->skill4;
}

// Returns the string value of skill5
string Armor::getSkill5() 
{
    return this->skill5;
}

// Returns the int value of skill1Points
int Armor::getSkill1Points() 
{
    return this->skill1Points;
}

// Returns the int value of skill2Points
int Armor::getSkill2Points() 
{
    return this->skill2Points;
}

// Returns the int value of skill3Points
int Armor::getSkill3Points() 
{
    return this->skill3Points;
}

// Returns the int value of skill4Points
int Armor::getSkill4Points() 
{
    return this->skill4Points;
}

// Returns the int value of skill5Points
int Armor::getSkill5Points() 
{
    return this->skill5Points;
}