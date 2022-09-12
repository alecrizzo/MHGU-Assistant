#pragma once

/********************************************************************************************/
/*

NAME
		search.h - obtains the necessary functions to search for armorsets and get user input

DESCRIPTION

	   Has the functionality to get user input, narrow down armor options, and construct 
	   useable armor sets 

AUTHOR
		Alec Rizzo

*/
/********************************************************************************************/

#include "armorset.h"
#include "data.h"

class Search
{
private:
	int m_weaponSlots;
	int m_charmSlots;
	string m_gender;
	string m_hunterType;
	string m_sortMethod;
	Armor m_charm;

public:
	Search();
	vector<Armor> RemoveGenderArmors(vector<Armor> a_armors);
	vector<Armor> RemoveHunterType(vector<Armor> a_armors);
	vector<Armor> RemoveSkilllessArmors(vector<Armor> a_armors, vector<activeSkill> a_desiredSkills);
	vector<Decoration> RemoveSkilllessDecorations(vector<Decoration> a_decorations, vector<activeSkill> a_desiredSkills);
	vector<ArmorSet> ConstructSets(vector<Decoration> a_decorations, vector<Armor> a_head, vector<Armor> a_arms, 
		vector<Armor> a_body, vector<Armor> a_waist, vector<Armor> a_legs, Armor a_charm, vector<activeSkill> a_desiredSkills,
		vector<activeSkill> a_activeSkills);
	vector<Armor> SortUsefulArmor(vector<Armor> a_armor, vector<activeSkill> a_desiredSkills);
	int NumUsefulPoints(Armor a_armor, vector<activeSkill> a_desiredSkills);
	activeSkill TargetSkill(ArmorSet a_armorSet, vector<activeSkill> a_desiredSkills);
	Armor FindArmorWithSkill(vector<Armor> a_armors, activeSkill a_desiredSkill);
	Decoration FindDecoWithSkill(int a_largestSlotsRemaining, vector<Decoration> a_decorations, activeSkill a_desiredSkill);

	void SearchLoop(Data a_data);

	int InputMainMenu();
	int InputNumSkillsDesired();
	int InputWeaponSlots();
	string InputHunterGender();
	string InputHunterType();
	string InputSortMethod();
	Armor InputCharm(Data a_data);

	vector<ArmorSet> SortSetsBy(vector<ArmorSet> a_sets, string a_sortMethod);

	// Functions to calculate effective raw damage
	float InputRaw();
	float InputAffinity();
    float InputSharpness();
    float InputCriticalBoost();
    float CalculateEFR();
};