#pragma once
/********************************************************************************************/
/*

NAME

		activeskill.h - used to store the value of an active skill name, the tree/point name and
						the amount of points required to activate the active skill

DESCRIPTION

	   This header has the functionality of setting up the values of an active skill

AUTHOR

		Alec Rizzo

*/
/********************************************************************************************/

#include "treeskill.h"

struct activeSkill
{
	string activeName = "";
	string treeName = "";
	int pointsRequired = 0;
};
