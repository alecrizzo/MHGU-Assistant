#include "armorset.h"

// Default constructor of ArmorSet()
ArmorSet::ArmorSet()
{
	this->m_skills.clear();
	this->m_weaponSlots = 0;
	this->m_charmSlots = 0;
}/*ArmorSet::ArmorSet();*/

/**/
/*
ArmorSet::CalculateActiveSkills() ArmorSet::CalculateActiveSkills()
NAME

		ArmorSet::CalculateActiveSkills - calculates which skills are active
										  on this armor set

SYNOPSIS

		void ArmorSet::CalculateActiveSkills(vector<activeSkill> a_activeSkills)

			a_activeSkills		-->  a vector of the active skills that exist in the game

DESCRIPTION

		This function goes through all the tree skill points (innate skill points)
		on the armor pieces and decorations to determine if they reached the activation threshold.
		If they activate the skill gets pushed onto the member vector of m_skills.

RETURNS

		Void

AUTHOR
		Alec Rizzo

*/
/**/
void ArmorSet::CalculateActiveSkills(vector<activeSkill> a_activeSkills)
{
	// Clear because this is likely to be called twice for a single armor set
	// we do not want to have duplicate skills in the m_skills vector
	this->m_skills.clear();

	vector<treeSkill> totalSkillPoints;
	vector<treeSkill> tempVec;

	// Compare the skills between the armor pieces and increase or decrease points accordingly
	totalSkillPoints = TreeSkillsOnArmor(this->m_head);
	tempVec = TreeSkillsOnArmor(this->m_arms);
	totalSkillPoints = CombineTreeSkillVectors(totalSkillPoints, tempVec);

	tempVec = TreeSkillsOnArmor(this->m_body);
	totalSkillPoints = CombineTreeSkillVectors(totalSkillPoints, tempVec);

	tempVec = TreeSkillsOnArmor(this->m_waist);
	totalSkillPoints = CombineTreeSkillVectors(totalSkillPoints, tempVec);

	tempVec = TreeSkillsOnArmor(this->m_legs);
	totalSkillPoints = CombineTreeSkillVectors(totalSkillPoints, tempVec);

	tempVec = TreeSkillsOnArmor(this->m_charm);
	totalSkillPoints = CombineTreeSkillVectors(totalSkillPoints, tempVec);

	// Compare the skills between the decorations for all the necessary equipment
	tempVec = TreeSkillsOnDecorations(this->m_weaponDecorations);
	totalSkillPoints = CombineTreeSkillVectors(totalSkillPoints, tempVec);

	tempVec = TreeSkillsOnDecorations(this->m_head.GetDecorations());
	totalSkillPoints = CombineTreeSkillVectors(totalSkillPoints, tempVec);

	tempVec = TreeSkillsOnDecorations(this->m_arms.GetDecorations());
	totalSkillPoints = CombineTreeSkillVectors(totalSkillPoints, tempVec);

	tempVec = TreeSkillsOnDecorations(this->m_body.GetDecorations());
	totalSkillPoints = CombineTreeSkillVectors(totalSkillPoints, tempVec);

	tempVec = TreeSkillsOnDecorations(this->m_waist.GetDecorations());
	totalSkillPoints = CombineTreeSkillVectors(totalSkillPoints, tempVec);

	tempVec = TreeSkillsOnDecorations(this->m_legs.GetDecorations());
	totalSkillPoints = CombineTreeSkillVectors(totalSkillPoints, tempVec);

	tempVec = TreeSkillsOnDecorations(this->m_charm.GetDecorations());
	totalSkillPoints = CombineTreeSkillVectors(totalSkillPoints, tempVec);


	// If the skills reach the skill activation threshold add the active skill to the m_skills vector
	for (int i = 0; i < totalSkillPoints.size(); i++)
	{
		for (int z = 0; z < a_activeSkills.size(); z++)
		{
			if(a_activeSkills.at(z).pointsRequired > 0)
			{
				// Activation case for positive skills
				if (totalSkillPoints.at(i).name == a_activeSkills.at(z).treeName &&
					totalSkillPoints.at(i).points >= a_activeSkills.at(z).pointsRequired)
				{
					this->m_skills.push_back(a_activeSkills.at(z));
				}
			}
			else if (a_activeSkills.at(z).pointsRequired < 0)
			{	
				// Activation case for negative skills
				if (totalSkillPoints.at(i).name == a_activeSkills.at(z).treeName &&
					totalSkillPoints.at(i).points <= a_activeSkills.at(z).pointsRequired)
				{
					this->m_skills.push_back(a_activeSkills.at(z));
				}
			}
		}
	}
}/*void ArmorSet::CalculateActiveSkills(vector<activeSkill> a_activeSkills);*/


/**/
/*
ArmorSet::CombineTreeSkillVectors() ArmorSet::CombineTreeSkillVectors()
NAME
		ArmorSet::CombineTreeSkillVectors - combine the treeskills between the 
											two passed vectors and return the results

SYNOPSIS

		vector<treeSkill> ArmorSet::CombineTreeSkillVectors(vector<treeSkill> a_baseVec, 
														vector<treeSkill> a_newVec)
			a_baseVec  --> the original vector to be combined to
			a_newVec   --> the new vector we will compare our base vectors values to


DESCRIPTION

		This function compares the tree skills between the two passed vectors and accumulates
		them into just 1 vector which is returned.

RETURNS

		Returns a vector of the combined tree skill vectors. if a_newVec is somehow empty 
		the a_baseVec is going to be returned anyways so all is good in the world.

AUTHOR
		Alec Rizzo

*/
/**/
vector<treeSkill> ArmorSet::CombineTreeSkillVectors(vector<treeSkill> a_baseVec, vector<treeSkill> a_newVec)
{
	for (int i = 0; i < a_newVec.size(); i++)
	{
		bool skillExists = false;
		for (int z = 0; z < a_baseVec.size(); z++)
		{
			// If the skill exists in both vectors increase points accordingly
			if (a_newVec.at(i).name == a_baseVec.at(z).name)
			{
				a_baseVec.at(z).points += a_newVec.at(i).points;
				skillExists = true;
			}
		}
		if (skillExists == false)
		{
			a_baseVec.push_back(a_newVec.at(i));
		}
	}

	return a_baseVec;
}/*vector<treeSkill> ArmorSet::CombineTreeSkillVectors(vector<treeSkill> a_baseVec, vector<treeSkill> a_newVec);*/


/**/
/*
ArmorSet::TreeSkillsOnArmor() ArmorSet::TreeSkillsOnArmor()
NAME
		ArmorSet::TreeSkillsOnArmor - Gets all the tree skills on an armor piece 
									  and returns them in a vector

SYNOPSIS

		vector<treeSkill> ArmorSet::TreeSkillsOnArmor(Armor a_armor)

			a_armor		-->		the armor we are checking the skills of


DESCRIPTION

		This function gets all the tree skills (innate skills) on an armor piece 
		and returns them as a vector of tree skills

RETURNS

		Returns a vector of the tree skills on the armor piece

AUTHOR
		Alec Rizzo

*/
/**/ 
vector<treeSkill> ArmorSet::TreeSkillsOnArmor(Armor a_armor)
{
	vector<treeSkill> tempVec;
	for (int i = 0; i < a_armor.GetNumSkills(); i++)
	{
		treeSkill tempSkill;
		switch (i)
		{
		case 0:
			tempSkill.name = a_armor.GetSkill1();
			tempSkill.points += a_armor.GetSkill1Points();
			tempVec.push_back(tempSkill);
			tempSkill.name = "";
			tempSkill.points = 0;
			break;
		case 1:
			tempSkill.name = a_armor.GetSkill2();
			tempSkill.points += a_armor.GetSkill2Points();
			tempVec.push_back(tempSkill);
			tempSkill.name = "";
			tempSkill.points = 0;
			break;
		case 2:
			tempSkill.name = a_armor.GetSkill3();
			tempSkill.points += a_armor.GetSkill3Points();
			tempVec.push_back(tempSkill);
			tempSkill.name = "";
			tempSkill.points = 0;
			break;
		case 3:
			tempSkill.name = a_armor.GetSkill4();
			tempSkill.points += a_armor.GetSkill4Points();
			tempVec.push_back(tempSkill);
			tempSkill.name = "";
			tempSkill.points = 0;
			break;
		case 4:
			tempSkill.name = a_armor.GetSkill5();
			tempSkill.points += a_armor.GetSkill5Points();
			tempVec.push_back(tempSkill);
			tempSkill.name = "";
			tempSkill.points = 0;
			break;
		default:
			break;
		}
	}
	return tempVec;
}/*vector<treeSkill> ArmorSet::TreeSkillsOnArmor(Armor a_armor);*/

/**/
/*
ArmorSet::TreeSkillsOnDecorations() ArmorSet::TreeSkillsOnDecorations()

NAME
		ArmorSet::TreeSkillsOnDecorations - gets all the tree skills in  
											the passed vector of decorations

SYNOPSIS
	
		vector<treeSkill> ArmorSet::TreeSkillsOnDecorations(vector<Decoration> a_decorations)

			a_decorations		-->		the decorations vector which we will be checking the
										tree skills of
										

DESCRIPTION

		Function to obtain the tree skills on the decorations of the passed vector

RETURNS

		Returns a vector of treeSkills which contain the accumulated skill points from the 
		passed vector of decorations

AUTHOR
		Alec Rizzo

*/
/**/
vector<treeSkill> ArmorSet::TreeSkillsOnDecorations(vector<Decoration> a_decorations)
{
	vector<treeSkill> tempVec;
	vector<Decoration> decoVec = a_decorations;
	if (decoVec.size() != 0)
	{
		for (int i = 0; i < decoVec.size(); i++)
		{
			if (tempVec.size() != 0)
			{
				bool skillExists = false;
				for (int z = 0; z < tempVec.size(); z++)
				{
					if (tempVec.at(z).name == decoVec.at(i).GetSkill1() && decoVec.at(i).GetSkill1() != "")
					{
						tempVec.at(z).points += decoVec.at(i).GetSkill1Points();
						skillExists = true;
					}
				}
				if (skillExists == false)
				{
					treeSkill tempSkill;
					tempSkill.name = decoVec.at(i).GetSkill1();
					tempSkill.points = decoVec.at(i).GetSkill1Points();
					tempVec.push_back(tempSkill);
				}
			}
			else
			{
				treeSkill tempSkill;
				tempSkill.name = decoVec.at(i).GetSkill1();
				tempSkill.points = decoVec.at(i).GetSkill1Points();
				tempVec.push_back(tempSkill);
			}
		}

		// Do the same loop over the values of tempvec again with skill2s of the decorations
		// incase there are any negative skill points that we need to add on
		// note: decorations second skills are only negative skills, if they even have one
		for (int i = 0; i < decoVec.size(); i++)
		{
			if (tempVec.size() != 0)
			{
				bool skillExists = false;
				for (int z = 0; z < tempVec.size(); z++)
				{
					if (tempVec.at(z).name == decoVec.at(i).GetSkill2() && decoVec.at(i).GetSkill2() != "")
					{
						tempVec.at(z).points += decoVec.at(i).GetSkill2Points();
						skillExists = true;
					}
				}
				if (skillExists == false)
				{
					treeSkill tempSkill;
					tempSkill.name = decoVec.at(i).GetSkill2();
					tempSkill.points = decoVec.at(i).GetSkill2Points();
					tempVec.push_back(tempSkill);
				}
			}
			else
			{
				treeSkill tempSkill;
				tempSkill.name = decoVec.at(i).GetSkill2();
				tempSkill.points = decoVec.at(i).GetSkill2Points();
				tempVec.push_back(tempSkill);
			}
		}
	}
	return tempVec;
}/*vector<treeSkill> ArmorSet::TreeSkillsOnDecorations(vector<Decoration> a_decorations);*/

// Returns the member m_weaponSlots
int ArmorSet::GetWeaponSlots()
{
	return this->m_weaponSlots;
}/*int ArmorSet::GetWeaponSlots();*/

// Returns the member m_charmSlots
int ArmorSet::GetCharmSlots()
{
	return this->m_charmSlots;
}/*int ArmorSet::GetCharmSlots();*/

// Returns the member m_head
Armor ArmorSet::GetHead()
{
	return this->m_head;
}/*Armor ArmorSet::GetHead();*/

// Returns the member m_body
Armor ArmorSet::GetBody()
{
	return this->m_body;
}/*Armor ArmorSet::GetBody();*/

// Returns the member m_arms
Armor ArmorSet::GetArms()
{
	return this->m_arms;
}/*Armor ArmorSet::GetArms();*/

// Returns the member m_waist
Armor ArmorSet::GetWaist()
{
	return this->m_waist;
}/*Armor ArmorSet::GetWaist();*/

// Returns the member m_legs
Armor ArmorSet::GetLegs()
{
	return this->m_legs;
}/*Armor ArmorSet::GetLegs();*/

// Returns the member m_charm
Armor ArmorSet::GetCharm()
{
	return this->m_charm;
}/*Armor ArmorSet::GetCharm();*/

// Returns the member m_skills which is our vector of active skills on the set
vector<activeSkill> ArmorSet::GetActiveSkills()
{
	return this->m_skills;
}/*vector<activeSkill> ArmorSet::GetActiveSkills();*/

// Sets the member m_weaponSlots to the passed argument of a_weaponSlots
void ArmorSet::SetWeaponSlots(int a_weaponSlots)
{
	this->m_weaponSlots = a_weaponSlots;
}/*void ArmorSet::SetWeaponSlots(int a_weaponSlots);*/

// Sets the member m_charmSlots to the passed argument of a_charmSlots
void ArmorSet::SetCharmSlots(int a_charmSlots)
{
	this->m_charmSlots = a_charmSlots;
}/*void ArmorSet::SetCharmSlots(int a_charmSlots);*/

// Sets the member m_head to the passed argument of a_head
void ArmorSet::SetHead(Armor a_head)
{
	this->m_head = a_head;
}/*void ArmorSet::SetHead(Armor a_head);*/

// Sets the member m_body to the passed argument of a_body
void ArmorSet::SetBody(Armor a_body)
{
	this->m_body = a_body;
}/*void ArmorSet::SetBody(Armor a_body)*/

// Sets the member m_arms to the passed argument of a_arms
void ArmorSet::SetArms(Armor a_arms)
{
	this->m_arms = a_arms;
}/*void ArmorSet::SetArms(Armor a_arms);*/

// Sets the member m_waist to the passed argument of a_waist
void ArmorSet::SetWaist(Armor a_waist)
{
	this->m_waist = a_waist;
}/*void ArmorSet::SetWaist(Armor a_waist);*/

// Sets the member m_legs to the passed argument of a_legs
void ArmorSet::SetLegs(Armor a_legs)
{
	this->m_legs = a_legs;
}/*void ArmorSet::SetLegs(Armor a_legs);*/

// Sets the member m_charm to the passed argument of a_charm and sets the charm slots
void ArmorSet::SetCharm(Armor a_charm)
{
	this->m_charm = a_charm;
	SetCharmSlots(a_charm.GetDecoSlots());
}/*void ArmorSet::SetCharm(Armor a_charm);*/

/**/
/*
ArmorSet::IsSkillActive() ArmorSet::IsSkillActive()

NAME
		ArmorSet::IsSkillActive	- determines if a skill is active in the set

SYNOPSIS

		bool ArmorSet::IsSkillActive(activeSkill a_activeSkill)

			a_activeSkill		-->		the skill we are checking for activation

DESCRIPTION

		This function checks if the passed active skill is activated in this armor
		set already.

RETURNS
		Returns true if the active skill exists in the armor already

AUTHOR
		Alec Rizzo

*/
/**/
bool ArmorSet::IsSkillActive(activeSkill a_activeSkill)
{
	for (int i = 0; i < m_skills.size(); i++)
	{
		if (m_skills.at(i).activeName == a_activeSkill.activeName)
		{
			return true;
		}
	}
	return false;
}/*bool ArmorSet::IsSkillActive(activeSkill a_activeSkill);*/

/**/
/*

NAME

		ArmorSet::PointsNeededToActivate - determines the points needed to 
										   activate the passed active skill

SYNOPSIS

		int ArmorSet::PointsNeededToActivate(activeSkill a_desiredSkill)
		
			a_desiredSkil		-->		the skill we are determining the points
										needed to activate

DESCRIPTION

		This function goes through the tree skills on all our armor pieces and determines 
		how many points are needed to activate the passed active skill (the desired skill)

RETURNS
		
		Returns an integer amount of points needed to activate the passed skill

AUTHOR
		Alec Rizzo

*/
/**/
int ArmorSet::PointsNeededToActivate(activeSkill a_desiredSkill)
{
	int currentPoints = 0;

	vector<treeSkill> headSkills = TreeSkillsOnArmor(m_head);
	vector<treeSkill> bodySkills = TreeSkillsOnArmor(m_body);
	vector<treeSkill> armsSkills = TreeSkillsOnArmor(m_arms);
	vector<treeSkill> waistSkills = TreeSkillsOnArmor(m_waist);
	vector<treeSkill> legsSkills = TreeSkillsOnArmor(m_legs);
	vector<treeSkill> charmSkills = TreeSkillsOnArmor(m_charm);

	for (int i = 0; i < headSkills.size(); i++)
	{
		if (headSkills.at(i).name == a_desiredSkill.treeName)
		{
			currentPoints += headSkills.at(i).points;
		}
	}
	for (int i = 0; i < bodySkills.size(); i++)
	{
		if (bodySkills.at(i).name == a_desiredSkill.treeName)
		{
			currentPoints += bodySkills.at(i).points;
		}
	}
	for (int i = 0; i < armsSkills.size(); i++)
	{
		if (armsSkills.at(i).name == a_desiredSkill.treeName)
		{
			currentPoints += armsSkills.at(i).points;
		}
	}
	for (int i = 0; i < waistSkills.size(); i++)
	{
		if (waistSkills.at(i).name == a_desiredSkill.treeName)
		{
			currentPoints += waistSkills.at(i).points;
		}
	}
	for (int i = 0; i < legsSkills.size(); i++)
	{
		if (legsSkills.at(i).name == a_desiredSkill.treeName)
		{
			currentPoints += legsSkills.at(i).points;
		}
	}
	for (int i = 0; i < charmSkills.size(); i++)
	{
		if (charmSkills.at(i).name == a_desiredSkill.treeName)
		{
			currentPoints += charmSkills.at(i).points;
		}
	}

	return a_desiredSkill.pointsRequired - currentPoints;
}/*int ArmorSet::PointsNeededToActivate(activeSkill a_desiredSkill);*/

/**/
/*
ArmorSet::ClearSet() ArmorSet::ClearSet()
NAME
		
		ArmorSet::ClearSet - clears this armor set

SYNOPSIS

		void ArmorSet::ClearSet()

DESCRIPTION
		
		Resets all the values of this armor set

RETURNS
		
		Void

AUTHOR
		Alec Rizzo

*/
/**/
void ArmorSet::ClearSet()
{
	Armor temp;
	m_weaponSlots = 0;
	m_charmSlots = 0;
	m_head = temp;
	m_body = temp;
	m_arms = temp;
	m_waist = temp;
	m_legs = temp;
	m_charm = temp;
	m_skills.clear();
	m_weaponDecorations.clear();
}/*void ArmorSet::ClearSet();*/

// Simple bool function which determines if armor piece m_head is empty
bool ArmorSet::IsHeadEmpty()
{
	if (m_head.GetName() == "")
	{
		return true;
	}
	else
	{
		return false;
	}
}/*bool ArmorSet::IsHeadEmpty()*/

// Simple bool function which determines if armor piece m_body is empty
bool ArmorSet::IsBodyEmpty()
{
	if (m_body.GetName() == "")
	{
		return true;
	}
	else
	{
		return false;
	}
}/*bool ArmorSet::IsBodyEmpty();*/

// Simple bool function which determines if armor piece m_arms is empty
bool ArmorSet::IsArmsEmpty()
{
	if (m_arms.GetName() == "")
	{
		return true;
	}
	else
	{
		return false;
	}
}/*bool ArmorSet::IsArmsEmpty();*/

// Simple bool function which determines if armor piece m_waist is empty
bool ArmorSet::IsWaistEmpty()
{
	if (m_waist.GetName() == "")
	{
		return true;
	}
	else
	{
		return false;
	}
}/*bool ArmorSet::IsWaistEmpty();*/

// Simple bool function which determines if armor piece m_legs is empty
bool ArmorSet::IsLegsEmpty()
{
	if (m_legs.GetName() == "")
	{
		return true;
	}
	else
	{
		return false;
	}
}/*bool ArmorSet::IsLegsEmpty();*/

// Simple bool function which determines if armor piece m_charm is empty
bool ArmorSet::IsCharmEmpty()
{
	if (m_charm.GetSkill1() == "")
	{
		return true;
	}
	else
	{
		return false;
	}
}/*bool ArmorSet::IsCharmEmpty();*/

/**/
/*
ArmorSet::CanSlotDecos() ArmorSet::CanSlotDecos()
NAME
		ArmorSet::CanSlotDecos - checks if we can add decorations to the 
								 armor set

SYNOPSIS

		bool ArmorSet::CanSlotDecos()

DESCRIPTION

		This function determines whether decorations can be slotted onto 
		this armor set still by checking if the remaining deco slots are 
		availible for our weapon, head, body, arms, waist, legs, and charm.

RETURNS

		Returns a boolean value of true or false on whether any decoration can be slotted

AUTHOR
		Alec Rizzo

*/
/**/
bool ArmorSet::CanSlotDecos()
{
	// first check if weapon slots can be filled with a decoration
	if (GetRemainingWeaponDecoSlots() > 0)
	{
		return true;
	}

	// next check if armor pieces can be slotted with a decoration
	if (m_head.GetRemainingDecoSlots() > 0)
	{
		return true;
	}
	if (m_body.GetRemainingDecoSlots() > 0)
	{
		return true;
	}
	if (m_arms.GetRemainingDecoSlots() > 0)
	{
		return true;
	}
	if (m_waist.GetRemainingDecoSlots() > 0)
	{
		return true;
	}
	if (m_legs.GetRemainingDecoSlots() > 0)
	{
		return true;
	}

	// then check if charm can be slotted with a decoration
	if (m_charm.GetRemainingDecoSlots() > 0)
	{
		return true;
	}

	// if none of the equipment has decoration slots and returns true above
	// then we'd return false as there would be no availible decoration slots
	return false;
}/*bool ArmorSet::CanSlotDecos();*/

/**/
/*
ArmorSet::LargestAvailibleDecoSlot() ArmorSet::LargestAvailibleDecoSlot()

NAME
		ArmorSet::LargestAvailibleDecoSlot - gets the largest availible empty
											 decoration slot's size as an integer

SYNOPSIS

		int ArmorSet::LargestAvailibleDecoSlot()

DESCRIPTION

		This function checks through all availible decoration slots to determine
		what the largest availible decoration slot is

RETURNS

		Returns an integer representing what the largest availible decoration slot is

AUTHOR
		Alec Rizzo

*/
/**/
// Returns the largest availible (empty) decoration slot in the armor set as an int
int ArmorSet::LargestAvailibleDecoSlot()
{
	int largestDecoSlot = 0;

	if (GetRemainingWeaponDecoSlots() > largestDecoSlot)
	{
		largestDecoSlot = GetRemainingWeaponDecoSlots();
	}
	if (m_head.GetRemainingDecoSlots() > largestDecoSlot)
	{
		largestDecoSlot = m_head.GetRemainingDecoSlots();
	}
	if (m_body.GetRemainingDecoSlots() > largestDecoSlot)
	{
		largestDecoSlot = m_body.GetRemainingDecoSlots();
	}
	if (m_arms.GetRemainingDecoSlots() > largestDecoSlot)
	{
		largestDecoSlot = m_arms.GetRemainingDecoSlots();
	}
	if (m_waist.GetRemainingDecoSlots() > largestDecoSlot)
	{
		largestDecoSlot = m_waist.GetRemainingDecoSlots();
	}
	if (m_legs.GetRemainingDecoSlots() > largestDecoSlot)
	{
		largestDecoSlot = m_legs.GetRemainingDecoSlots();
	}
	if (m_charm.GetRemainingDecoSlots() > largestDecoSlot)
	{
		largestDecoSlot = m_charm.GetRemainingDecoSlots();
	}

	return largestDecoSlot;
}/*int ArmorSet::LargestAvailibleDecoSlot();*/

// Gets how many decoration slots remain on this armor piece
/**/
/*
ArmorSet::GetRemainingWeaponDecoSlots() ArmorSet::GetRemainingWeaponDecoSlots()

NAME
		ArmorSet::GetRemainingWeaponDecoSlots - returns the amount of decoration
												slots left on the weapon
		
SYNOPSIS

		int ArmorSet::GetRemainingWeaponDecoSlots()

DESCRIPTION
		
		This function determines how many slots are used on the weapon so far and
		returns the remaining slots.

RETURNS
		
		Returns an integer of the remaining decoration slots on the weapon

AUTHOR
		Alec Rizzo

*/
/**/
int ArmorSet::GetRemainingWeaponDecoSlots()
{
	int slotsUsed = 0;
	int slotsRemaining = 0;
	// Determine how many slots were used on this armor piece so far
	for (int i = 0; i < m_weaponDecorations.size(); i++)
	{
		slotsUsed += m_weaponDecorations.at(i).GetSlotsRequired();
	}
	// Based on the remaining slots see if we can add the passed decoration to the armor
	slotsRemaining = m_weaponSlots - slotsUsed;
	return slotsRemaining;
}/*int ArmorSet::GetRemainingWeaponDecoSlots();*/

/**/
/*
ArmorSet::AddDecorationToWeapon() ArmorSet::AddDecorationToWeapon()

NAME
		ArmorSet::AddDecorationToWeapon - adds a decoration to the weapon if there 
										  is space 

SYNOPSIS

		void ArmorSet::AddDecorationToWeapon(Decoration a_decoration)

		a_decoration		-->		the decoration which will be added to the weapon

DESCRIPTION

		This function adds a decoration to the weapon for this set (adds a decoration to our
		vector of weapon decorations) if there is space for it. 

RETURNS

		Void

AUTHOR
		Alec Rizzo

*/
/**/
void ArmorSet::AddDecorationToWeapon(Decoration a_decoration)
{
	int slotsRemaining = GetRemainingWeaponDecoSlots();
	if (a_decoration.GetSlotsRequired() <= slotsRemaining)
	{
		m_weaponDecorations.push_back(a_decoration);
	}
}/*void ArmorSet::AddDecorationToWeapon(Decoration a_decoration);*/

/**/
/*
ArmorSet::AddDecorationToSet()  ArmorSet::AddDecorationToSet()

NAME

		ArmorSet::AddDecorationToSet - adds a decoration to our set in
									   the most appropriate spot

SYNOPSIS

		void ArmorSet::AddDecorationToSet(Decoration a_decoration)

			a_decoration	-->		the decoration to be added to the set

DESCRIPTION
	
		This function adds a decoration to our set in the most fitting spot

RETURNS

		Void

AUTHOR
		Alec Rizzo

*/
/**/
void ArmorSet::AddDecorationToSet(Decoration a_decoration)
{
	// Find the best possible fit for the given decoration
	int decoSize = a_decoration.GetSlotsRequired();
	
	// try to find a spot for the deco that is of exact size
	if (GetRemainingWeaponDecoSlots() == decoSize)
	{
		AddDecorationToWeapon(a_decoration);
		return;
	}
	if (m_head.GetRemainingDecoSlots() == decoSize)
	{
		m_head.AddDecorationToArmor(a_decoration);
		return;
	}
	if (m_body.GetRemainingDecoSlots() == decoSize)
	{
		m_body.AddDecorationToArmor(a_decoration);
		return;
	}
	if (m_arms.GetRemainingDecoSlots() == decoSize)
	{
		m_arms.AddDecorationToArmor(a_decoration);
		return;
	}
	if (m_waist.GetRemainingDecoSlots() == decoSize)
	{
		m_waist.AddDecorationToArmor(a_decoration);
		return;
	}
	if (m_legs.GetRemainingDecoSlots() == decoSize)
	{
		m_legs.AddDecorationToArmor(a_decoration);
		return;
	}
	if (m_charm.GetRemainingDecoSlots() == decoSize)
	{
		m_charm.AddDecorationToArmor(a_decoration);
		return;
	}
	
	// otherwise try to find the next size up
	if (GetRemainingWeaponDecoSlots() == decoSize + 1)
	{
		AddDecorationToWeapon(a_decoration);
		return;
	}
	if (m_head.GetRemainingDecoSlots() == decoSize + 1)
	{
		m_head.AddDecorationToArmor(a_decoration);
		return;
	}
	if (m_body.GetRemainingDecoSlots() == decoSize + 1)
	{
		m_body.AddDecorationToArmor(a_decoration);
		return;
	}
	if (m_arms.GetRemainingDecoSlots() == decoSize + 1)
	{
		m_arms.AddDecorationToArmor(a_decoration);
		return;
	}
	if (m_waist.GetRemainingDecoSlots() == decoSize + 1)
	{
		m_waist.AddDecorationToArmor(a_decoration);
		return;
	}
	if (m_legs.GetRemainingDecoSlots() == decoSize + 1)
	{
		m_legs.AddDecorationToArmor(a_decoration);
		return;
	}
	if (m_charm.GetRemainingDecoSlots() == decoSize + 1)
	{
		m_charm.AddDecorationToArmor(a_decoration);
		return;
	}

	// last resort put it on a 3 slot
	if (GetRemainingWeaponDecoSlots() >= decoSize)
	{
		AddDecorationToWeapon(a_decoration);
		return;
	}
	if (m_head.GetRemainingDecoSlots() >= decoSize)
	{
		m_head.AddDecorationToArmor(a_decoration);
		return;
	}
	if (m_body.GetRemainingDecoSlots() >= decoSize)
	{
		m_body.AddDecorationToArmor(a_decoration);
		return;
	}
	if (m_arms.GetRemainingDecoSlots() >= decoSize)
	{
		m_arms.AddDecorationToArmor(a_decoration);
		return;
	}
	if (m_waist.GetRemainingDecoSlots() >= decoSize)
	{
		m_waist.AddDecorationToArmor(a_decoration);
		return;
	}
	if (m_legs.GetRemainingDecoSlots() >= decoSize)
	{
		m_legs.AddDecorationToArmor(a_decoration);
		return;
	}
	if (m_charm.GetRemainingDecoSlots() >= decoSize)
	{
		m_charm.AddDecorationToArmor(a_decoration);
		return;
	}

}/*void ArmorSet::AddDecorationToSet(Decoration a_decoration);*/

/**/
/*
ArmorSet::MeetsRequiredSkills() ArmorSet::MeetsRequiredSkills()
NAME

		ArmorSet::MeetsRequiredSkills - determines if the armorset meets the
										desired skills

SYNOPSIS

		bool ArmorSet::MeetsRequiredSkills(vector<activeSkill> a_desiredSkills)
		
			a_desiredSkills		-->		a vector of the active skills the user wants

DESCRIPTION

		This function checks if the passed skills are met by our armor set by calling
		the function IsSkillActive() for all activeSkills in the vector.

RETURNS

		Returns true if for all the desired skills, the skills are active in our set

AUTHOR
		Alec Rizzo

*/
/**/
bool ArmorSet::MeetsRequiredSkills(vector<activeSkill> a_desiredSkills)
{
	// If one of the skills is inactive, return false, if we haven't returned false
	// all the skills are active so we return true
	for (int i = 0; i < a_desiredSkills.size(); i++)
	{
		if (this->IsSkillActive(a_desiredSkills.at(i)) == false)
		{
			return false;
		}
	}

	return true;
}/*bool ArmorSet::MeetsRequiredSkills(vector<activeSkill> a_desiredSkills);*/

// Adds all the armor pieces max defense value
int ArmorSet::GetTotalMaximumDefense()
{
	return m_head.GetMaxDef() + m_body.GetMaxDef() + m_arms.GetMaxDef() + m_waist.GetMaxDef() + m_legs.GetMaxDef();
}/*int ArmorSet::GetTotalMaximumDefense();*/

// Adds all the armor pieces fire defense value
int ArmorSet::GetTotalFireDefense()
{
	return m_head.GetFireDef() + m_body.GetFireDef() + m_arms.GetFireDef() + m_waist.GetFireDef() + m_legs.GetFireDef();
}/*int ArmorSet::GetTotalFireDefense();*/

// Adds all the armor pieces water defense value
int ArmorSet::GetTotalWaterDefense()
{
	return m_head.GetWaterDef() + m_body.GetWaterDef() + m_arms.GetWaterDef() + m_waist.GetWaterDef() + m_legs.GetWaterDef();
}/*int ArmorSet::GetTotalWaterDefense();*/

// Adds all the armor pieces thunder defense value
int ArmorSet::GetTotalThunderDefense()
{
	return m_head.GetThunderDef() + m_body.GetThunderDef() + m_arms.GetThunderDef() + m_waist.GetThunderDef() + m_legs.GetThunderDef();
}/*int ArmorSet::GetTotalThunderDefense();*/

// Adds all the armor pieces ice defense value
int ArmorSet::GetTotalIceDefense()
{
	return m_head.GetIceDef() + m_body.GetIceDef() + m_arms.GetIceDef() + m_waist.GetIceDef() + m_legs.GetIceDef();
}/*int ArmorSet::GetTotalIceDefense();*/

// Adds all the armor pieces dragon defense value
int ArmorSet::GetTotalDragonDefense()
{
	return m_head.GetDragonDef() + m_body.GetDragonDef() + m_arms.GetDragonDef() + m_waist.GetDragonDef() + m_legs.GetDragonDef();
}/*int ArmorSet::GetTotalDragonDefense();*/

/**/
/*
ArmorSet::PrintArmorSet() ArmorSet::PrintArmorSet()

NAME
		ArmorSet::PrintArmorSet - prints the relevant information
								  about the set to the user

SYNOPSIS

		void ArmorSet::PrintArmorSet()

DESCRIPTION

		This function prints the names of the armor in this set, the
		charms skill points, the sets added defense values, and the decorations
		that are required to activate the skills (if there are any).

RETURNS

		Void

AUTHOR
		Alec Rizzo

*/
/**/
void ArmorSet::PrintArmorSet()
{
	cout << "=====================================================================\n";

	// Output armor piece names and the charms skills
	cout << "Head: " << m_head.GetName() << endl;
	cout << "Body: " << m_body.GetName() << endl;
	cout << "Arms: " << m_arms.GetName() << endl;
	cout << "Waist: " << m_waist.GetName() << endl;
	cout << "Legs: " << m_legs.GetName() << endl;
	cout << "Charm: ";
	if (m_charm.GetSkill1() != "")
	{
		cout << m_charm.GetSkill1() << " " << m_charm.GetSkill1Points() << endl;
	}
	if (m_charm.GetSkill2() != "")
	{
		cout << m_charm.GetSkill2() << " " << m_charm.GetSkill2Points() << endl;

	}

	cout << endl;
	cout << "---------------------------------------------------------------------\n";
	// Ouput armors defensive values
	cout << "\tDefense: " << GetTotalMaximumDefense() << endl;
	cout << "\tFire Defense: " << GetTotalFireDefense() << endl;
	cout << "\tWater Defense: " << GetTotalWaterDefense() << endl;
	cout << "\tThunder Defense: " << GetTotalThunderDefense() << endl;
	cout << "\tIce Defense: " << GetTotalIceDefense() << endl;
	cout << "\tDragon Defense: " << GetTotalDragonDefense() << endl;

	// Output the activated skills
	cout << "---------------------------------------------------------------------\n";
	cout << "Active Skills: \n";
	for (int i = 0; i < m_skills.size(); i++)
	{
		cout << "\t" << m_skills.at(i).activeName << endl;
	}

	// Output the decorations equipped
	cout << "---------------------------------------------------------------------\n";
	cout << "Decorations: \n";
	for (int i = 0; i < m_weaponDecorations.size(); i++)
	{
		cout << "\t" << m_weaponDecorations.at(i).GetName() << endl;
	}
	vector<Decoration> tempDecoVec = m_head.GetDecorations();
	for (int i = 0; i < tempDecoVec.size(); i++)
	{
		cout << "\t" << tempDecoVec.at(i).GetName() << endl;
	}
	tempDecoVec = m_body.GetDecorations();
	for (int i = 0; i < tempDecoVec.size(); i++)
	{
		cout << "\t" << tempDecoVec.at(i).GetName() << endl;
	}
	tempDecoVec = m_arms.GetDecorations();
	for (int i = 0; i < tempDecoVec.size(); i++)
	{
		cout << "\t" << tempDecoVec.at(i).GetName() << endl;
	}
	tempDecoVec = m_waist.GetDecorations();
	for (int i = 0; i < tempDecoVec.size(); i++)
	{
		cout << "\t" << tempDecoVec.at(i).GetName() << endl;
	}
	tempDecoVec = m_legs.GetDecorations();
	for (int i = 0; i < tempDecoVec.size(); i++)
	{
		cout << "\t" << tempDecoVec.at(i).GetName() << endl;
	}
	tempDecoVec = m_charm.GetDecorations();
	for (int i = 0; i < tempDecoVec.size(); i++)
	{
		cout << "\t" << tempDecoVec.at(i).GetName() << endl;
	}
}/*void ArmorSet::PrintArmorSet();*/