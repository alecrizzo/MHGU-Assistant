#pragma once
/********************************************************************************************/
/*

NAME
        treeskill.h - struct treeskill which has a string value for the name and int for 
                      its points

DESCRIPTION
       
       Struct treeskill which is used when reading armor pieces innate skill points
       as the names are different to the active skills.

AUTHOR

        Alec Rizzo

*/
/********************************************************************************************/

#include <iostream>
#include <string> 
#include <map>
using namespace std;

struct treeSkill 
{
	string name = "";		// Name of skill in tree / skill point name
	int points = 0;			// Amount of points on skill
};

