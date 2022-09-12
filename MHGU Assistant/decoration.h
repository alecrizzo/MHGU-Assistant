#pragma once
/********************************************************************************************/
/*

NAME
		decoration.h - obtains the necessary functions to setup the decorations from the file
						decorations.txt

DESCRIPTION

	   Has the functionality to read and setup the essential values for a decoration


AUTHOR

		Alec Rizzo

*/
/********************************************************************************************/

#include "treeskill.h"
using namespace std;

class Decoration
{
private:
	string m_name;			// name of the decoration
	int m_rarity;			// rarity of the decoration
	int m_slotsRequired;	// amount of decoration slots needed to equip
	treeSkill m_skill1;		// positive skill
	treeSkill m_skill2;		// negative skill

public:

	Decoration();

	void SetName(string a_name);
	void SetRarity(int a_rarity);
	void SetSlotsRequired(int a_slotsRequired);
	void SetSkill1(string a_skill1);
	void SetSkill1Points(int a_skill1Points);
	void SetSkill2(string a_skill2);
	void SetSkill2Points(int a_skill2Points);

	string GetName();
	int GetRarity();
	int GetSlotsRequired();
	string GetSkill1();
	int GetSkill1Points();
	string GetSkill2();
	int GetSkill2Points();

	bool IsEmpty();
};