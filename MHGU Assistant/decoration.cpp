#include "decoration.h"

// Default constructor for Decoration, initializes values
Decoration::Decoration()
{
	this->m_name = "";
	this->m_rarity = 0;
	this->m_slotsRequired = 0;
	this->m_skill1.name = "";
	this->m_skill2.name = "";
	this->m_skill1.points = 0;
	this->m_skill2.points = 0;
}/*Decoration::Decoration();*/

// Sets the decoration name to the passed string
void Decoration::SetName(string a_name)
{
	this->m_name = a_name;
}/*void Decoration::SetName(string a_name);*/

// Sets the decorations rarity to the passed integer
void Decoration::SetRarity(int a_rarity)
{
	this->m_rarity = a_rarity;
}/*void Decoration::SetRarity(int a_rarity);*/

// Sets the decorations slots required to the passed integer
void Decoration::SetSlotsRequired(int a_slotsRequired)
{
	this->m_slotsRequired = a_slotsRequired;
}/*void Decoration::SetSlotsRequired(int a_slotsRequired);*/

// Sets the decorations skill 1 name to the passed string
void Decoration::SetSkill1(string a_skill1)
{
	this->m_skill1.name = a_skill1;
}/*void Decoration::SetSkill1(string a_skill1);*/

// Sets the decorations skill 1 points to the passed int
void Decoration::SetSkill1Points(int a_skill1Points)
{
	this->m_skill1.points = a_skill1Points;
}/*void Decoration::SetSkill1Points(int a_skill1Points);*/

// Sets the decorations skill 2 name to the passed string
void Decoration::SetSkill2(string a_skill2)
{
	this->m_skill2.name = a_skill2;
}/*void Decoration::SetSkill2(string a_skill2);*/

// Sets the decorations skill 2 points to the passed int
void Decoration::SetSkill2Points(int a_skill2Points)
{
	this->m_skill2.points = a_skill2Points;
}/*void Decoration::SetSkill2Points(int a_skill2Points);*/

// Returns the decorations name as a string m_name
string Decoration::GetName()
{
	return this->m_name;
}/*string Decoration::GetName();*/

// Returns the decorations rarity as an int m_rarity
int Decoration::GetRarity()
{
	return this->m_rarity;
}/*int Decoration::GetRarity();*/

// Returns the slots required to use the decoration as int m_slotsRequired
int Decoration::GetSlotsRequired()
{
	return this->m_slotsRequired;
}/*int Decoration::GetSlotsRequired();*/

// Returns the name of the first skill on this decoration as string m_skill1.name
string Decoration::GetSkill1()
{
	return this->m_skill1.name;
}/*string Decoration::GetSkill1();*/

// Returns the skill points of the first skill on this decoration as int m_skill1.points
int Decoration::GetSkill1Points()
{
	return this->m_skill1.points;
}/*int Decoration::GetSkill1Points();*/

// Returns the name of the second skill on this decoration as string m_skill2.name
string Decoration::GetSkill2()
{
	return this->m_skill2.name;
}/*string Decoration::GetSkill2();*/

// Returns the skill points of the second skill on this decoration as int m_skill1.points
int Decoration::GetSkill2Points()
{
	return this->m_skill2.points;
}/*int Decoration::GetSkill2Points();*/

// Function to determine whether this decoration is empty or not using the name
bool Decoration::IsEmpty()
{
	if (this->m_name == "")
	{
		return true;
	}
	else
	{
		return false;
	}
}/*bool Decoration::IsEmpty();*/