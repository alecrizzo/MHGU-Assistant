#include "data.h"

Data::Data()
{
	head.clear();
	arms.clear();
	body.clear();
	waist.clear();
	legs.clear();

	head = loadArmor("head.txt");
	arms = loadArmor("arms.txt");
	body = loadArmor("body.txt");
	waist = loadArmor("waist.txt");
	legs = loadArmor("legs.txt");



	// !TEST
	/*
	for (int i = 0; i < legs.size(); i++)
	{
		cout << "============================================\n";
		legs.at(i).printArmor();
	}
	*/
}

vector<Armor> Data::loadArmor(string filename)
{
	// Determine armortype from filename
	string pieceType = "";
	if (filename == "head.txt")
	{
		pieceType = "head";
	}
	else if (filename == "body.txt")
	{
		pieceType = "body";
	}
	else if (filename == "arms.txt")
	{
		pieceType = "arms";
	}
	else if (filename == "waist.txt")
	{
		pieceType = "waist";
	}
	else if (filename == "legs.txt")
	{
		pieceType = "legs";
	}
	else 
	{
		pieceType = "error";
	}

	vector<Armor> armorVec;
	fstream file;
	file.open(filename);

	if (file.is_open())
	{
		string line = "";
		while (getline(file, line))
		{
			Armor armor;
			armor.setBodyPart(pieceType);
			string current = "";
			char last = ' ';
			int commaCount = 0;
			for (int i = 0; i < line.length(); i++)
			{
				// Format for the armor data is as follows
				// EquipmentName(String Value), Gender(None[0], Male[1] / Female[2]), hunterType(Both[0], Blademaster[1], Gunner[2]), 
				// rarity, DecorationSlots, Defense, MaximumDefense, FireDefense, WaterDefense, ThunderDefense, IceDefense, 
				// DragonDefense, Skills(until, , )
				// EX: Hunter's Helm,0,0,1,0,6,54,0,0,0,0,0,Ranger,3,Speed Setup,2,, 
				if (line[i] == ',')
				{
					commaCount++;
					switch (commaCount)
					{
					// Equipment Name
					case 1:	
						armor.setName(current);
						current = "";
						break;
					// Gender
					case 2:
						if (current == "0") { current = "none"; }
						else if (current == "1") { current = "male"; }
						else if (current == "2") { current = "female"; }
						else { current = "error"; }
						armor.setGender(current);
						current = "";
						break;
					// hunterType
					case 3:
						if (current == "0") { current = "both"; }
						else if (current == "1") { current = "blademaster"; }
						else if (current == "2") { current = "gunner"; }
						else { current = "error"; }
						armor.setHunterType(current);
						current = "";
						break;
					// rarity
					case 4:
						armor.setRarity(current);
						current = "";
						break;
					// decoSlots
					case 5:
						if (stoi(current) >= 0 && stoi(current) <= 3)
						{
							armor.setDecoSlots(stoi(current));
						}
						current = "";
						break;
					// baseDef
					case 6:
						if (stoi(current) >= 0)
						{
							armor.setBaseDef(stoi(current));
						}
						current = "";
						break;
					// maxDef
					case 7:
						if (stoi(current) >= 0)
						{
							armor.setMaxDef(stoi(current));
						}
						current = "";
						break;
					// fireDef
					case 8:
						armor.setFireDef(stoi(current));
						current = "";
						break;
					// waterDef
					case 9:
						armor.setWaterDef(stoi(current));
						current = "";
						break;
					// thunderDef
					case 10:
						armor.setThunderDef(stoi(current));
						current = "";
						break;
					// iceDef
					case 11:
						armor.setIceDef(stoi(current));
						current = "";
						break;
					// dragonDef
					case 12:
						armor.setDragonDef(stoi(current));
						current = "";
						break;
					// skill1 
					case 13:
						armor.setSkill1(current);
						current = "";
						break;
					// skill1Points
					case 14:
						armor.setSkill1Points(stoi(current));
						current = "";
						break;
					// skill2
					case 15:
						armor.setSkill2(current);
						current = "";
						break;
					// skill2Points
					case 16:
						armor.setSkill2Points(stoi(current));
						current = "";
						break;
					// skill3
					case 17:
						armor.setSkill3(current);
						current = "";
						break;
					// skill3Points
					case 18:
						armor.setSkill3Points(stoi(current));
						current = "";
						break;
					// skill4
					case 19:
						armor.setSkill4(current);
						current = "";
						break;
					// skill4Points
					case 20:
						armor.setSkill4Points(stoi(current));
						current = "";
						break;
					// skill5
					case 21:
						armor.setSkill5(current);
						current = "";
						break;
					// skill5Points
					case 22:
						armor.setSkill5Points(stoi(current));
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
					armorVec.push_back(armor);
					break;
				}
				last = line[i];
			}
		}
	}

	file.close();
	return armorVec;
}
