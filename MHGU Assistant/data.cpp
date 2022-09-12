#include "data.h"

// Default constructor of Data()
Data::Data()
{
	m_head.clear();
	m_arms.clear();
	m_body.clear();
	m_waist.clear();
	m_legs.clear();
	m_possibleSkills.clear();
	m_decorations.clear();

	m_head = LoadArmor("head.txt");
	m_arms = LoadArmor("arms.txt");
	m_body = LoadArmor("body.txt");
	m_waist = LoadArmor("waist.txt");
	m_legs = LoadArmor("legs.txt");

	m_possibleSkills = LoadSkills("skills.txt");
	m_decorations = LoadDecorations("decorations.txt");
}/*Data::Data();*/

/**/
/*
string Data::DetermineBodyPart() string Data::DetermineBodyPart()

NAME

		Data::DetermineBodyPart() - determines the body part based on the filename

SYNOPSIS

		string Data::DetermineBodyPart(string a_filename)

			a_filname		-->		the name of the file which should give our
									body part type for the equipment


DESCRIPTION

		This function simply determines the armor pieces body type value based on the name
		of the file that is going to be opened, since the files containing the armor data 
		are all named after the body part that they are equipped on.

RETURNS

		Returns a string of the pieceType which is the body part it is to be equipped to

AUTHOR
		Alec Rizzo

*/
/**/
string Data::DetermineBodyPart(string a_filename)
{
	string pieceType = "";
	if (a_filename == "head.txt")
	{
		pieceType = "head";
	}
	else if (a_filename == "body.txt")
	{
		pieceType = "body";
	}
	else if (a_filename == "arms.txt")
	{
		pieceType = "arms";
	}
	else if (a_filename == "waist.txt")
	{
		pieceType = "waist";
	}
	else if (a_filename == "legs.txt")
	{
		pieceType = "legs";
	}
	else
	{
		pieceType = "error";
	}
	return pieceType;
}/* string Data::DetermineBodyPart(string a_filename); */

// Returns member m_head
vector<Armor> Data::GetHead()
{
	return this->m_head;
}/*vector<Armor> Data::GetHead();*/

// Returns member m_arms
vector<Armor> Data::GetArms()
{
	return this->m_arms;
}/*vector<Armor> Data::GetArms();*/

// Returns member m_body
vector<Armor> Data::GetBody()
{
	return this->m_body;
}/*vector<Armor> Data::GetBody();*/

// Returns member m_waist
vector<Armor> Data::GetWaist()
{
	return this->m_waist;
}/*vector<Armor> Data::GetWaist();*/

// Returns member m_legs
vector<Armor> Data::GetLegs()
{
	return this->m_legs;
}/*vector<Armor> Data::GetLegs();*/

// Returns member m_decorations
vector<Decoration> Data::GetDecorations()
{
	return this->m_decorations;
}/*vector<Decoration> Data::GetDecorations();*/

// Returns member m_possible skills
vector<activeSkill> Data::GetPossibleSkills()
{
	return this->m_possibleSkills;
}/*vector<activeSkill> Data::GetPossibleSkills();*/

/**/
/*
vector<Armor> Data::LoadArmor() vector<Armor> Data::LoadArmor() 

NAME

		Data::LoadArmor - loads the armor pieces from a file into a vector.

SYNOPSIS

		vector<Armor> Data::LoadArmor(string a_filename)

			a_filname		-->		the name of the file to be opened


DESCRIPTION

		This function loads the values of the armor pieces into a vector by
		going through the text file for the passed string which will denote the
		body part of the armor using the function DetermineBodyPart(). Then line by line
		the data will be analyzed and allocated according to the order in which they
		are split via commas.

		Format for the armor data per line is as follows
			 name, gender, hunterType, rarity, decoSlots, baseDef, maxDef, fireDef, 
							waterDef, thunderDef, iceDef, dragonDef, Skills(until, , )

			EX: Hunter's Helm,0,0,1,0,6,54,0,0,0,0,0,Ranger,3,Speed Setup,2,,

RETURNS

		Returns a vector of Armor's which will contain all the loaded armor 
		values of the passed filename

AUTHOR
		Alec Rizzo

*/
/**/
vector<Armor> Data::LoadArmor(string a_filename)
{
	// Determine armor type from filename (head, body, arms, legs, waist)
	string pieceType = DetermineBodyPart(a_filename);

	vector<Armor> armorVec;
	fstream file;
	file.open(a_filename);

	if (file.is_open())
	{
		string line = "";
		while (getline(file, line))
		{
			Armor armor;
			armor.SetBodyPart(pieceType);
			string current = "";
			char last = ' ';
			int commaCount = 0;
			for (int i = 0; i < line.length(); i++)
			{
				// Format for the armor data is as follows
				// EquipmentName(String Value), Gender(None[0], Male[1] / Female[2]), hunterType(Both[0], Blademaster[1], Gunner[2]), 
				// rarity, DecorationSlots, Defense, MaximumDefense, FireDefense, WaterDefense, ThunderDefense, IceDefense, DragonDefense, Skills(until, , )
				// EX: Hunter's Helm,0,0,1,0,6,54,0,0,0,0,0,Ranger,3,Speed Setup,2,, 
				if (line[i] == ',')
				{
					commaCount++;
					switch (commaCount)
					{
					// Equipment Name
					case 1:	
						armor.SetName(current);
						current = "";
						break;
					// Hunter Gender
					case 2:
						if (current == "0") { current = "none"; }
						else if (current == "1") { current = "male"; }
						else if (current == "2") { current = "female"; }
						else { current = "error"; }
						armor.SetGender(current);
						current = "";
						break;
					// Hunter Type
					case 3:
						if (current == "0") { current = "both"; }
						else if (current == "1") { current = "blademaster"; }
						else if (current == "2") { current = "gunner"; }
						else { current = "error"; }
						armor.SetHunterType(current);
						current = "";
						break;
					// Rarity
					case 4:
						armor.SetRarity(current);
						current = "";
						break;
					// Decoration Slots
					case 5:
						if (stoi(current) >= 0 && stoi(current) <= 3)
						{
							armor.SetDecoSlots(stoi(current));
						}
						current = "";
						break;
					// Base Defense
					case 6:
						if (stoi(current) >= 0)
						{
							armor.SetBaseDef(stoi(current));
						}
						current = "";
						break;
					// Maximum Defense
					case 7:
						if (stoi(current) >= 0)
						{
							armor.SetMaxDef(stoi(current));
						}
						current = "";
						break;
					// Fire Defense
					case 8:
						armor.SetFireDef(stoi(current));
						current = "";
						break;
					// Water Defense
					case 9:
						armor.SetWaterDef(stoi(current));
						current = "";
						break;
					// Thunder Defense
					case 10:
						armor.SetThunderDef(stoi(current));
						current = "";
						break;
					// Ice Defense
					case 11:
						armor.SetIceDef(stoi(current));
						current = "";
						break;
					// Dragon Defense
					case 12:
						armor.SetDragonDef(stoi(current));
						current = "";
						break;
					// Skill 1 String/Name 
					case 13:
						armor.SetSkill1(current);
						current = "";
						break;
					// Skill 1 Points
					case 14:
						armor.SetSkill1Points(stoi(current));
						current = "";
						break;
					// Skill 2 String/Name
					case 15:
						armor.SetSkill2(current);
						current = "";
						break;
					// Skill 2 Points
					case 16:
						armor.SetSkill2Points(stoi(current));
						current = "";
						break;
					// Skill 3 String/Name
					case 17:
						armor.SetSkill3(current);
						current = "";
						break;
					// Skill 3 Points
					case 18:
						armor.SetSkill3Points(stoi(current));
						current = "";
						break;
					// Skill 4 String/Name
					case 19:
						armor.SetSkill4(current);
						current = "";
						break;
					// Skill 4 Points
					case 20:
						armor.SetSkill4Points(stoi(current));
						current = "";
						break;
					// Skill 5 String/Name
					case 21:
						armor.SetSkill5(current);
						current = "";
						break;
					// Skill 5 Points
					case 22:
						armor.SetSkill5Points(stoi(current));
						current = "";
						break;
					default:
						// if we somehow get a default we don't want to assign any values
						// to the armor, the armor constructor will take care of any potential
						// garbage values
						break;
					}
				}
				else
				{
					current = current + line[i];
				}
				if (last == ',' && line[i] == ',')
				{
					armorVec.push_back(armor);
					break;
				}
				last = line[i];
			}
		}
	}
	file.close();
	return armorVec;
}/* vector<Armor> Data::LoadArmor(string a_filename); */


/**/
/*
vector<activeSkill> Data::LoadSkills() vector<activeSkill> Data::LoadSkills()

NAME

		Data::LoadSkills - loads the activatable skills from a file into a vector

SYNOPSIS

		vector<activeSkill> Data::LoadSkills(string a_filename)

			a_filname		-->		the name of the file to be opened


DESCRIPTION

		This function loads the values of the possible activatable skills from 
		a text file into a vector of activeSkill

RETURNS

		Returns a vector of activeSkill which will contain every activatable skill
		in the game from our text file

AUTHOR
		Alec Rizzo

*/
/**/
vector<activeSkill> Data::LoadSkills(string a_filename)
{
	vector<activeSkill> skillVec;
	fstream file;
	file.open(a_filename);

	if (file.is_open())
	{
		string line = "";
		while (getline(file, line))
		{
			activeSkill skill;
			string current = "";
			char last = ' ';
			int commaCount = 0;
			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] == ',')
				{
					commaCount++;
					switch (commaCount)
					{
					// Active Skill Name
					case 1:
						skill.activeName = current;
						current = "";
						break;
					// Tree Skill Name (skill point name)
					case 2:
						skill.treeName = current;
						current = "";
						break;
					// Skill Points
					case 3:
						skill.pointsRequired = stoi(current);
						current = "";
						break;
					default:
						break;
					}
				}
				else
				{
					current = current + line[i];
				}
				if (last == ',' && line[i] == ',')
				{
					skillVec.push_back(skill);
					break;
				}
				last = line[i];
			}
		}
	}
	return skillVec;
}/* vector<activeSkill> Data::LoadSkills(string a_filename); */


/**/
/*
vector<Decoration> Data::LoadDecorations() vector<Decoration> Data::LoadDecorations()

NAME

		Data::LoadDecorations - loads the list of decorations from a file into a vector
								of decoration objects

SYNOPSIS

		vector<Decoration> Data::LoadDecorations(string a_filename)

			a_filname		-->		the name of the file to be opened


DESCRIPTION

		This function loads the values of the decorations into the vector of
		decoration objects

RETURNS

		Returns a vector of Decoration which will contain every decoration
		in the game from our text file

AUTHOR
		Alec Rizzo

*/
/**/
vector<Decoration> Data::LoadDecorations(string a_filename)
{
	vector<Decoration> decoVec;
	fstream file;
	file.open(a_filename);

	if (file.is_open())
	{
		string line = "";
		while (getline(file, line))
		{
			Decoration deco;
			string current = "";
			char last = ' ';
			int commaCount = 0;
			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] == ',')
				{
					commaCount++;
					switch (commaCount)
					{
					// Format for the Decorations is as follows
					// DecorationName(String Value), Rarity, SlotsRequiredToUse, Skills(until, , )
					// EX: Paralysis Jwl 1,4,1,Paralysis,1,Poison,-1,,
					// Decoration name
					case 1: 
						deco.SetName(current);
						current = "";
						break;
					// Rarity
					case 2:
						deco.SetRarity(stoi(current));
						current = "";
						break;
					// Slots required to use
					case 3:
						deco.SetSlotsRequired(stoi(current));
						current = "";
						break;
					// Skill1 name
					case 4:
						deco.SetSkill1(current);
						current = "";
						break;
					// Sklll1 points
					case 5:
						deco.SetSkill1Points(stoi(current));
						current = "";
						break;
					// Skill2 name
					case 6:
						deco.SetSkill2(current);
						current = "";
						break;
					// Skill2 points
					case 7:
						deco.SetSkill2Points(stoi(current));
						current = "";
						break;
					default:
						break;
					}
				}
				else
				{
					current = current + line[i];
				}
				if (last == ',' && line[i] == ',')
				{
					decoVec.push_back(deco);
					break;
				}
				last = line[i];
			}
		}
	}
	return decoVec;
}/* vector<Decoration> Data::LoadDecorations(string a_filename); */

/**/
/*
bool Data::ActiveSkillExists() bool Data::ActiveSkillExists()

NAME

			Data::ActiveSkillExists - determines whether the passed string is
										an active skill name in the member vector of 
										possible skills 

SYNOPSIS

			bool Data::ActiveSkillExists(string a_activeSkillName)

			a_activeSkillName		-->		the name of the skill to be checked


DESCRIPTION

		This function determines whether the passed string is an active skill name 
		in the member vector of possible skills 

RETURNS

		Returns a bool value, true if the skill exists, false if not

AUTHOR
		Alec Rizzo

*/
/**/
bool Data::ActiveSkillExists(string a_activeSkillName)
{
	for (int i = 0; i < this->m_possibleSkills.size(); i++)
	{
		if (m_possibleSkills.at(i).activeName == a_activeSkillName)
		{
			return true;
		}
	}
	return false;
}/*bool Data::ActiveSkillExists(string a_activeSkillName);*/

/**/
/*
bool Data::TreeSkillExists() bool Data::TreeSkillExists()

NAME

			Data::TreeSkillExists - determines whether the passed string is
									a tree skill name in the member vector of 
									possible skills 

SYNOPSIS
			
			bool Data::TreeSkillExists(string a_treeSkillName)

				a_treeSkillName		-->  string of the tree name to compare

DESCRIPTION

			determines whether the passed string is	an tree skill name in the 
			member vector of possible skills 

RETURNS
		
			Returns a bool value, true if the tree skill exists, false if not

AUTHOR
		Alec Rizzo

*/
/**/
bool Data::TreeSkillExists(string a_treeSkillName)
{
	for (int i = 0; i < this->m_possibleSkills.size(); i++)
	{
		if (m_possibleSkills.at(i).treeName == a_treeSkillName)
		{
			return true;
		}
	}
	return false;
}/*bool Data::TreeSkillExists(string a_treeSkillName);*/