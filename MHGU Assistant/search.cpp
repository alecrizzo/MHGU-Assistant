#include "search.h"

/**/
/*
Search::Search() Search::Search()

NAME

        Search::Search - constructor for search which sets all our default values

SYNOPSIS

        Search::Search()

DESCRIPTION

        This is the default constructor for search which sets all our search values,
        creates a data object, gets user gender, and starts the search loop.

RETURNS

AUTHOR

        Alec Rizzo

*/
/**/
Search::Search()
{
    m_weaponSlots = 0;
    m_charmSlots = 0;
    m_gender = "male";
    m_hunterType = "blademaster";
    m_sortMethod = "defense";
    m_charm.SetBodyPart("charm");

    Data allData;

    // Input gender only once as it is unchangable in the game
    m_gender = InputHunterGender();

    // Program loops here until exit
    while (true) { SearchLoop(allData);}
}/*Search::Search()*/

/**/
/*
Search::SearchLoop() Search::SearchLoop()

NAME
        Search::SearchLoop - function to determine an action after the 
                             user first makes a menu selection

SYNOPSIS

        void Search::SearchLoop(Data a_data)

            a_data      -->     the data class object contaning all the loaded data

DESCRIPTION
    
        This function is designed to be used in a loop to let user select an option
        at the menu and then initiate the correct logic for the selected option.

RETURNS

        

AUTHOR

        Alec Rizzo

*/
/**/
void Search::SearchLoop(Data a_data)
{
    // Menu
    int menuSelection = InputMainMenu();
    if (menuSelection == 7)
    {
        // Menu Selection 7 exits program
        exit(0);
    }
    else if (menuSelection == 0)
    {
        // Display all activatable skill names
        for (int i = 0; i < a_data.GetPossibleSkills().size(); i++)
        {
            if (a_data.GetPossibleSkills().at(i).activeName != "")
            {
                cout << a_data.GetPossibleSkills().at(i).activeName << endl;
            }
        }
    }
    else if (menuSelection == 1)
    {
        // Conduct armor search
        int numSkills = InputNumSkillsDesired();

        vector<activeSkill> activeSkills = a_data.GetPossibleSkills();
        vector<activeSkill> desiredSkills;

        for (int i = 0; i < numSkills; i++)
        {
            string temp = "null";
            while (a_data.ActiveSkillExists(temp) == false && temp != "")
            {
                cout << "Enter the activated skill name of your desired skill: ";
                getline(cin, temp);
            }
            for (int i = 0; i < activeSkills.size(); i++)
            {
                if (temp == activeSkills.at(i).activeName)
                {
                    desiredSkills.push_back(activeSkills.at(i));
                }
            }
        }

        vector<Armor> head = a_data.GetHead();
        vector<Armor> arms = a_data.GetArms();
        vector<Armor> body = a_data.GetBody();
        vector<Armor> waist = a_data.GetWaist();
        vector<Armor> legs = a_data.GetLegs();
        vector<Decoration> decorations = a_data.GetDecorations();
        
        // If the user input their own charm during a loop it would be m_charm
        // otherwise m_charm is empty
        Armor charm = m_charm;

        // Reduce the possible search options by removing gendered armors and armors of
        // the wrong hunter type
        head = RemoveGenderArmors(head);
        arms = RemoveGenderArmors(arms);
        body = RemoveGenderArmors(body);
        waist = RemoveGenderArmors(waist);
        legs = RemoveGenderArmors(legs);

        head = RemoveHunterType(head);
        arms = RemoveHunterType(arms);
        body = RemoveHunterType(body);
        waist = RemoveHunterType(waist);
        legs = RemoveHunterType(legs);

        // Search for armor pieces based on desired skills from our data
        decorations = RemoveSkilllessDecorations(decorations, desiredSkills);
        head = RemoveSkilllessArmors(head, desiredSkills);
        arms = RemoveSkilllessArmors(arms, desiredSkills);
        body = RemoveSkilllessArmors(body, desiredSkills);
        waist = RemoveSkilllessArmors(waist, desiredSkills);
        legs = RemoveSkilllessArmors(legs, desiredSkills);

        // Construct possible armorsets with the armor pieces remaining after the options are narrowed
        vector<ArmorSet> results = ConstructSets(decorations, head, arms, body, waist, legs, charm, desiredSkills, activeSkills);
        
        results = SortSetsBy(results, m_sortMethod);

        if (results.size() == 0)
        {
            cout << "= No Results from Search =\n";
        }
        else 
        {
            for (int i = 0; i < results.size(); i++)
            {
                results.at(i).PrintArmorSet();
            }
        }
    }
    else if (menuSelection == 2)
    {
        // Change weapon slots
        m_weaponSlots = InputWeaponSlots();
    }
    else if (menuSelection == 3)
    {
        // Create and overwrite charm
        m_charm = InputCharm(a_data);
    }
    else if (menuSelection == 4)
    {
        // Change Hunter Type
        m_hunterType = InputHunterType();
    }
    else if (menuSelection == 5)
    {
        // Raw damage calculator
        float EFR = CalculateEFR();
        cout << "Your Weapons Effective Raw Damage is: " << EFR << endl;
    }
    else if (menuSelection == 6)
    {
        // Change defense sort method 
        m_sortMethod = InputSortMethod();
    }
    else 
    {
        cout << "ERROR: menuSelection illegal value\n";
    }
}/*void Search::SearchLoop(Data a_data);*/

/**/
/*
Search::InputMainMenu() Search::InputMainMenu()

NAME

        Search::InputMainMenu - gets user input for menu options

SYNOPSIS

        int Search::InputMainMenu()

DESCRIPTION
        
        This function outputs the menu options to the user and gets an
        appropriate response

RETURNS

        Returns an integer corresponding to the string version of that input.
        (input was done like this to reduce invalid inputs and infinite loops)

AUTHOR

        Alec Rizzo

*/
/**/
int Search::InputMainMenu()
{
    string input = "";
    while (!(input == "0" || input == "1" || input == "2" || input == "3" || input == "4" || input == "5" || input == "6" || input == "7"))
    {
        cout << "Please input a number to select an option below\n";
        cout << "|| (0) View Skills || (1) Armor Search || (2) Change Weapon Slots || (3) Create Charm || (4) Change Hunter Type || (5) Raw Damage Calculator || (6) Change Sort Method || (7) Exit: ";
        getline(cin, input);
    }

    if (input == "0") return 0;
    if (input == "1") return 1;
    if (input == "2") return 2;
    if (input == "3") return 3;
    if (input == "4") return 4;
    if (input == "5") return 5;
    if (input == "6") return 6;
    if (input == "7") return 7;

    return 7;
}/*int Search::InputMainMenu();*/

/**/
/*
Search::InputCharm() Search::InputCharm()

NAME

        Search::InputCharm - lets the user input their own charm

SYNOPSIS

        Armor Search::InputCharm(Data a_data)

            a_data      -->     data object containing all data set info

DESCRIPTION

        This function gets users input on their charm specifications

RETURNS

        Returns the new charm created by the user as an Armor

AUTHOR

        Alec Rizzo

*/
/**/
Armor Search::InputCharm(Data a_data)
{
    Armor newCharm;
    newCharm.SetBodyPart("charm");

    string input = "";
    while (!(input == "0" || input == "1" || input == "2" || input == "3"))
    {
        cout << "Please enter a number (0 - 3) for how many decoration slots are on your charm: ";
        getline(cin, input);
    }
    if (input == "0") newCharm.SetDecoSlots(0);
    if (input == "1") newCharm.SetDecoSlots(1);
    if (input == "2") newCharm.SetDecoSlots(2);
    if (input == "3") newCharm.SetDecoSlots(3);
    
    input = "";
    while (!(input == "1" || input == "2" ))
    {
        cout << "Do you have (1) or (2) skills on your charm?: ";
        getline(cin, input);
    }
    if (input == "1" || input == "2")
    {
        // Enter treeSkill1
        string temp = "null";
        while (a_data.TreeSkillExists(temp) == false && temp != "")
        {
            cout << "Enter the name of your charm skill: ";
            getline(cin, temp);
        }
        newCharm.SetSkill1(temp);

        int skillPoints = -100;
        while (!(skillPoints <= 10 && skillPoints >= -10))
        {
            cout << "Enter the points (from -10 -> 10) for " << temp << ": ";
            cin >> skillPoints;
            cin.ignore();
        }
        newCharm.SetSkill1Points(skillPoints);
    }
    if (input == "2")
    {
        // Enter treeSkill2
        string temp = "null";
        while (a_data.TreeSkillExists(temp) == false && temp != "")
        {
            cout << "Enter the name of your charm skill: ";
            getline(cin, temp);
        }
        newCharm.SetSkill2(temp);

        int skillPoints = -100;
        while (!(skillPoints <= 10 && skillPoints >= -10))
        {
            cout << "Enter the points (from -10 -> 10) for " << temp << ": ";
            cin >> skillPoints;
            cin.ignore();
        }
        newCharm.SetSkill2Points(skillPoints);
    }

    return newCharm;
}/*Armor Search::InputCharm(Data a_data);*/

/**/
/*
Search::InputHunterType() Search::InputHunterType()

NAME

        Search::InputHunterType - get user input on their hunter type

SYNOPSIS

        string Search::InputHunterType()

DESCRIPTION

        This function gets the users input on their hunter type and then returns
        the corresponding string for the hunter type.

RETURNS

        Returns the string corresponding to whether the user is a blademaster
        or a gunner.

AUTHOR

        Alec Rizzo

*/
/**/
string Search::InputHunterType()
{
    string input = "";
    while (!(input == "1" || input == "2" ))
    {
        cout << "Please enter a number to select the hunter type\n";
        cout << "|| (1) Blademaster || (2) Gunner: ";
        getline(cin, input);
    }

    if (input == "1") return "blademaster";
    if (input == "2") return "gunner";

    return "blademaster";
}/*string Search::InputHunterType();*/

/**/
/*
Search::InputSortMethod() Search::InputSortMethod()

NAME

        Search::InputSortMethod - gets users input on their desired armor
                                  sort method

SYNOPSIS

        string Search::InputSortMethod()

DESCRIPTION

        This function lets the user select from the output options on which
        defensive stat they want the armor to be sorted by.

RETURNS

        Returns a string for the users desired sort method.

AUTHOR

        Alec Rizzo

*/
/**/
string Search::InputSortMethod()
{
    string input = "";
    while (!(input == "1" || input == "2" || input == "3" || input == "4" || input == "5" || input == "6"))
    {
        cout << "Please enter a number to select the sort method\n";
        cout << "|| (1) Defense || (2) Fire || (3) Water || (4) Thunder || (5) Ice || (6) Dragon: ";
        getline(cin, input);
    }

    if (input == "1") return "defense";
    if (input == "2") return "fire";
    if (input == "3") return "water";
    if (input == "4") return "thunder";
    if (input == "5") return "ice";
    if (input == "6") return "dragon";

    return "defense";
}/*string Search::InputSortMethod();*/

/**/
/*
Search::InputWeaponSlots()  Search::InputWeaponSlots()

NAME

         Search::InputWeaponSlots - gets users input on how many decoration
                                    slots they have on their weapon.

SYNOPSIS

        int Search::InputWeaponSlots()
        
DESCRIPTION
    
        This function gets users input on how many decoration slots are on their 
        weapon.

RETURNS

        Returns the integer corresponding to the amount of slots the user input (0-3).

AUTHOR

        Alec Rizzo

*/
/**/
int Search::InputWeaponSlots()
{
    string input = "";
    while (!(input == "0" || input == "1" || input == "2" || input == "3" ))
    {
        cout << "Please enter a number (0 - 3) for how many decoration slots are on your weapon: ";
        getline(cin, input);
    }

    if (input == "0") return 0;
    if (input == "1") return 1;
    if (input == "2") return 2;
    if (input == "3") return 3;

    return 0;
}/*int Search::InputWeaponSlots();*/

/**/
/*
Search::InputNumSkillsDesired() Search::InputNumSkillsDesired()

NAME

        Search::InputNumSkillsDesired - gets users input for how many skills 
                                        they'd like to search for

SYNOPSIS

        int Search::InputNumSkillsDesired()

DESCRIPTION

        This function gets the amount of active skills the user would like to search 
        for on their set

RETURNS

        Returns an integer (1 - 5) corresponding to the users selection.

AUTHOR

        Alec Rizzo

*/
/**/
int Search::InputNumSkillsDesired()
{
    string input = "";
    while (!(input == "1" || input == "2"|| input == "3" || input == "4" || input == "5"))
    {
        cout << "Please enter a number (1 - 5) for how many skill you would like to search for: ";
        getline(cin, input);
    }

    if (input == "1") return 1;
    if (input == "2") return 2;
    if (input == "3") return 3;
    if (input == "4") return 4;
    if (input == "5") return 5;

    return 0;
}/*int Search::InputNumSkillsDesired();*/

/**/
/*
Search::InputHunterGender() Search::InputHunterGender()

NAME

        Search::InputHunterGender - gets users input on their hunters gender
                                

SYNOPSIS

        string Search::InputHunterGender()

DESCRIPTION

        This function gets users input on whether their hunter is male or female
        and returns the result as a string.

RETURNS

        Returns a string denoting the hunters gender of "male" or "female"

AUTHOR

        Alec Rizzo

*/
/**/
string Search::InputHunterGender()
{
    string input = "";
    while (!(input == "1" || input == "2" ))
    {
        cout << "Please enter a number for your Hunters gender\n";
        cout << "|| (1) Male || (2) Female: ";
        getline(cin, input);
    }

    if (input == "1") return "male";
    if (input == "2") return "female";

    return "male";
}/*string Search::InputHunterGender();*/

/**/
/*
Search::RemoveSkilllessDecorations() Search::RemoveSkilllessDecorations()

NAME

        Search::RemoveSkilllessDecorations - removes the decorations without the desired skills

SYNOPSIS

        vector<Decoration> Search::RemoveSkilllessDecorations(vector<Decoration> a_decorations, 
                                                            vector<activeSkill> a_desiredSkills)

            a_decorations       -->     the vector of decorations we are removing skills from
            a_desiredSkills     -->     the vector of desired active skills we are comparing 
                                        to the decorations

DESCRIPTION

            This function takes the desired skills the user wants and removes all of the
            decorations that do not have corresponding skill points.

RETURNS
        
        Returns a vector holding only decorations that may be useful to acquire our desired skills

AUTHOR

        Alec Rizzo

*/
/**/
vector<Decoration> Search::RemoveSkilllessDecorations(vector<Decoration> a_decorations, vector<activeSkill> a_desiredSkills)
{
    vector<Decoration> usefulDecorations;
    for (int i = 0; i < a_decorations.size(); i++)
    {
        for (int z = 0; z < a_desiredSkills.size(); z++)
        {
            if (a_decorations.at(i).GetSkill1() == a_desiredSkills.at(z).treeName)
            {
                usefulDecorations.push_back(a_decorations.at(i));
            }
        }
    }
    return usefulDecorations;
}/*vector<Decoration> Search::RemoveSkilllessDecorations(vector<Decoration> a_decorations, vector<activeSkill> a_desiredSkills);*/

/**/
/*
Search::RemoveSkilllessArmors() Search::RemoveSkilllessArmors()

NAME

        Search::RemoveSkilllessArmors - removes the armors that don't have the desired skills

SYNOPSIS

        vector<Armor> Search::RemoveSkilllessArmors(vector<Armor> a_armors,
                                                            vector<activeSkill> a_desiredSkills)

            a_armors            -->     the vector of armors we are removing skills from
            a_desiredSkills     -->     the vector of desired active skills we are comparing
                                        to the armors

DESCRIPTION

            This function takes the desired skills the user wants and removes all of the
            armors that do not have corresponding skill points.

RETURNS

        Returns a vector holding only armors that may be useful to acquire our desired skills

AUTHOR

        Alec Rizzo

*/
/**/
vector<Armor> Search::RemoveSkilllessArmors(vector<Armor> a_armors, vector<activeSkill> a_desiredSkills)
{
    vector<Armor> tempVec;

    for (int i = 0; i < a_armors.size(); i++)
    {
        for (int z = 0; z < a_desiredSkills.size(); z++)
        {
            // If armor is determined to have a skill we could want, break to avoid adding it twice
            if (a_armors.at(i).GetSkill1() == a_desiredSkills.at(z).treeName)
            {
                tempVec.push_back(a_armors.at(i));
                break;
            }
            if (a_armors.at(i).GetSkill2() == a_desiredSkills.at(z).treeName)
            {
                tempVec.push_back(a_armors.at(i));
                break;
            }
            if (a_armors.at(i).GetSkill3() == a_desiredSkills.at(z).treeName)
            {
                tempVec.push_back(a_armors.at(i));
                break;
            }
            if (a_armors.at(i).GetSkill4() == a_desiredSkills.at(z).treeName)
            {
                tempVec.push_back(a_armors.at(i));
                break;
            }
            if (a_armors.at(i).GetSkill5() == a_desiredSkills.at(z).treeName)
            {
                tempVec.push_back(a_armors.at(i));
                break;
            }
        }
    }

    return tempVec;
}/*vector<Armor> Search::RemoveSkilllessArmors(vector<Armor> a_armors, vector<activeSkill> a_desiredSkills);*/

/**/
/*
Search::RemoveGenderArmors() Search::RemoveGenderArmors()

NAME
        
        Search::RemoveGenderArmors - removes armors from vector if they are the opposite 
                                     gender then returns the updated vector

SYNOPSIS

        vector<Armor> Search::RemoveGenderArmors(vector<Armor> a_armors)

            a_armors    -->    vector of armors we will be removing armor pieces from

DESCRIPTION

        This function is meant to remove the armors of the opposite gender from the 
        passed vector of armors and return the rest of the passed armors.
        (you cannot change gender in the game and thus the user wont want armors of the opposite gender)

RETURNS

        Returns a vector of armor pieces which are all usable to the user based on their 
        gender.

AUTHOR
        Alec Rizzo

*/
/**/
vector<Armor> Search::RemoveGenderArmors(vector<Armor> a_armors)
{
    vector<Armor> tempVec;

    if (m_gender == "male")
    {
        for (int i = 0; i < a_armors.size(); i++)
        {
            if (a_armors.at(i).GetGender() == "male" || a_armors.at(i).GetGender() == "none")
            {
                tempVec.push_back(a_armors.at(i));
            }
        }
    }
    else if (m_gender == "female")
    {
        for (int i = 0; i < a_armors.size(); i++)
        {
            if (a_armors.at(i).GetGender() == "female" || a_armors.at(i).GetGender() == "none")
            {
                tempVec.push_back(a_armors.at(i));
            }
        }
    }

    return tempVec;
}/*vector<Armor> Search::RemoveGenderArmors(vector<Armor> a_armors);*/

/**/
/*
Search::RemoveHunterType() Search::RemoveHunterType()
NAME

        Search::RemoveHunterType - removes armors from vector if they are the wrong 
                                   hunter type then returns updated vector

SYNOPSIS

        vector<Armor> Search::RemoveHunterType(vector<Armor> a_armors)

            a_armors    -->     a vector of armors we will be removing values from

DESCRIPTION

        This function is designed to remove all armors of the wrong hunter type

RETURNS

        Returns a vector of armors containing armors which are useable to the 
        user (only their hunter type or both).

AUTHOR
        Alec Rizzo

*/
/**/
vector<Armor> Search::RemoveHunterType(vector<Armor> a_armors)
{
    vector<Armor> tempVec;

    if (m_hunterType == "blademaster")
    {
        for (int i = 0; i < a_armors.size(); i++)
        {
            if (a_armors.at(i).GetHunterType() == "blademaster" || a_armors.at(i).GetHunterType() == "both")
            {
                tempVec.push_back(a_armors.at(i));
            }
        }
    }
    else if (m_hunterType == "gunner")
    {
        for (int i = 0; i < a_armors.size(); i++)
        {
            if (a_armors.at(i).GetHunterType() == "gunner" || a_armors.at(i).GetHunterType() == "both")
            {
                tempVec.push_back(a_armors.at(i));
            }
        }
    }

    return tempVec;
}/*vector<Armor> Search::RemoveHunterType(vector<Armor> a_armors);*/

/**/
/*
Search::TargetSkill() Search::TargetSkill()

NAME

        Search::TargetSkill - Determines which skill to target first when making a set 
                              based on the lowest skill point activation requirement/threshold

SYNOPSIS

        activeSkill Search::TargetSkill(ArmorSet a_armorSet, vector<activeSkill> a_desiredSkills)

            a_armorSet          -->     the armor set which we are targeting skills on
            a_desiredSkills     -->     the desired skills we want to target in the search

DESCRIPTION

        This function targets the best skill to aim for first based on the closest
        skill to activation ensuring that the user is granted a set that has the skills
        they wanted in their set.

RETURNS

        Returns the activeSkill on which skill should be targeted next in constructing the set.

AUTHOR
        Alec Rizzo

*/
/**/
activeSkill Search::TargetSkill(ArmorSet a_armorSet, vector<activeSkill> a_desiredSkills)
{
    vector<int> intVec;
    activeSkill finalSkill;
    int leastPointsRequired = 100;
    for (int i = 0; i < a_desiredSkills.size(); i++)
    {
        if (a_armorSet.PointsNeededToActivate(a_desiredSkills.at(i)) < leastPointsRequired)
        {
            finalSkill = a_desiredSkills.at(i);
            leastPointsRequired = a_armorSet.PointsNeededToActivate(a_desiredSkills.at(i));
        }
    }
    return finalSkill;
}/*activeSkill Search::TargetSkill(ArmorSet a_armorSet, vector<activeSkill> a_desiredSkills);*/

/**/
/*
Search::ConstructSets() Search::ConstructSets()

NAME
        
        Search::ConstructSets - constructs armor sets

SYNOPSIS

        vector<ArmorSet> Search::ConstructSets(vector<Decoration> a_decorations, 
                                        vector<Armor> a_head, vector<Armor> a_arms,
                                        vector<Armor> a_body, vector<Armor> a_waist, 
                                        vector<Armor> a_legs, Armor a_charm, 
                                        vector<activeSkill> a_desiredSkills, 
                                        vector<activeSkill> a_activeSkills)

            a_decorations      -->      vector of decorations which have skills the user wants

            a_head             -->      vector of head armor pieces which have skills the user wants
                                        and should have the wrong gender/hunter type removed

            a_arms             -->      vector of arms aromr pieces which have skills the user wants
                                        and should have the wrong gender/hunter type removed

            a_body             -->      vector of body armor pieces which have skills the user wants
                                        and should have the wrong gender/hunter type removed

            a_waist            -->      vector of waist armor pieces which have skills the user wants
                                        and should have the wrong gender/hunter type removed

            a_legs             -->      vector of legs armor pieces which have skills the user wants
                                        and should have the wrong gender/hunter type removed

            a_charm            -->      an individual charm armor piece that the user inputs the skill 
                                        points and decoration slots for (by default will be left empty)

            a_desiredSkills    -->      the vector or desired skills the user input for their search

            a_activeSkills     -->      the full vector of active skills as loaded in from our txt file

DESCRIPTION

        This function is designed to take in the vectors of all our necessary data after the 
        results have been filtered due to user search prefrences (gender, hunter type, skills)
        to construct functional armorsets based on the desired skills the user wants.

RETURNS

        Returns a vector of armorsets which have met all the desired skills that the user wants.

AUTHOR
        Alec Rizzo

*/
/**/
vector<ArmorSet> Search::ConstructSets(vector<Decoration> a_decorations, vector<Armor> a_head, vector<Armor> a_arms,
    vector<Armor> a_body, vector<Armor> a_waist, vector<Armor> a_legs, Armor a_charm, vector<activeSkill> a_desiredSkills, 
    vector<activeSkill> a_activeSkills)
{
    vector<ArmorSet> completeSets;
    vector<ArmorSet> potentialSets;

    a_head = SortUsefulArmor(a_head, a_desiredSkills);
    a_arms = SortUsefulArmor(a_arms, a_desiredSkills);
    a_body = SortUsefulArmor(a_body, a_desiredSkills);
    a_waist = SortUsefulArmor(a_waist, a_desiredSkills);
    a_legs = SortUsefulArmor(a_legs, a_desiredSkills);

    ArmorSet tempSet;
    tempSet.SetCharm(a_charm);
    tempSet.SetWeaponSlots(m_weaponSlots);

    // Try to make a set with 1 of every head out of our useful heads
    // head is the seed for the set as it will have the most options and some head
    // pieces even have a full skill or two on them like the "hayabusa feather"
    for (int i = 0; i < a_head.size(); i++)
    {
        tempSet.SetHead(a_head.at(i));
        vector<activeSkill> remainingSkills = a_desiredSkills;
        bool exitCondition = false;
        while (exitCondition != true)
        {
            // Check if any skills are active
            tempSet.CalculateActiveSkills(a_activeSkills);
            // Get our next target skill
            activeSkill nextSkill = TargetSkill(tempSet, remainingSkills);
            // Check if the nextSkill is empty, if so exit condition is true
            if (nextSkill.activeName == "")
            {
                exitCondition = true;
                break;
            }
            // Target skill already active, remove from desired skills and find next target skill
            if (tempSet.IsSkillActive(nextSkill) == true)
            {
                for (int z = 0; z < remainingSkills.size(); z++)
                {
                    if (nextSkill.activeName == remainingSkills.at(z).activeName)
                    {
                        remainingSkills.erase(remainingSkills.begin() + z);
                        nextSkill = TargetSkill(tempSet, remainingSkills);
                        break;
                    }
                }
            }
            else
            {
                // Find an empty part in the set to find an armor piece for 
                if (tempSet.IsHeadEmpty() == true)
                {
                    Armor newHead = FindArmorWithSkill(a_head, nextSkill);
                    tempSet.SetHead(newHead);
                }
                else if (tempSet.IsArmsEmpty() == true)
                {
                    Armor newArms = FindArmorWithSkill(a_arms, nextSkill);
                    tempSet.SetArms(newArms);
                }
                else if (tempSet.IsBodyEmpty() == true)
                {
                    Armor newBody = FindArmorWithSkill(a_body, nextSkill);
                    tempSet.SetBody(newBody);
                }
                else if (tempSet.IsWaistEmpty() == true)
                {
                    Armor newWaist = FindArmorWithSkill(a_waist, nextSkill);
                    tempSet.SetWaist(newWaist);
                }
                else if (tempSet.IsLegsEmpty() == true)
                {
                    Armor newLegs = FindArmorWithSkill(a_legs, nextSkill);
                    tempSet.SetLegs(newLegs);
                }
                else if (tempSet.CanSlotDecos() == true)  // Case for slotting in decorations on our set
                {
                    Decoration newDeco = FindDecoWithSkill(tempSet.LargestAvailibleDecoSlot(), a_decorations, nextSkill);
                    if (newDeco.GetName() == "")
                    {
                        // Continue rather than break here as the next iteration could end up changing the 
                        // targetskill thus leading to finding a smaller decoration to fit into the set
                        continue;
                    }
                    else
                    {
                        tempSet.AddDecorationToSet(newDeco);
                    }
                }
                else
                {
                    exitCondition = true;
                    break;
                }
            }

        }
        // Calculate the active skills one final time before pushing to the potential sets vector
        tempSet.CalculateActiveSkills(a_activeSkills);
        potentialSets.push_back(tempSet);
    }

    for (int i = 0; i < potentialSets.size(); i++)
    {
        // Compare active skills on potential sets to our desired skills
        // If all are met push to complete sets
        if (potentialSets.at(i).MeetsRequiredSkills(a_desiredSkills) == true)
        {
            completeSets.push_back(potentialSets.at(i));
        }
    }
    return completeSets;
}/*vector<ArmorSet> Search::ConstructSets(vector<Decoration> a_decorations, vector<Armor> a_head, vector<Armor> a_arms,
    vector<Armor> a_body, vector<Armor> a_waist, vector<Armor> a_legs, Armor a_charm, vector<activeSkill> a_desiredSkills, 
    vector<activeSkill> a_activeSkills)*/



// Sorts vector by how many skill points the armors have from the desired skills
/**/
/*
Search::SortUsefulArmor() Search::SortUsefulArmor()

NAME
        Search::SortUsefulArmor - sorts the passed armor set by how useful they may be

SYNOPSIS

        vector<Armor> Search::SortUsefulArmor(vector<Armor> a_armors, vector<activeSkill> a_desiredSkills)

            a_armors            -->     the vector of passed armors we will sort
            a_desiredSkills     -->     the vector of active skills which the user desires, 
                                        which we will sort by

DESCRIPTION

         This function is designed to take the passed vector of armor pieces and sort them by
         their potential usefulness towards getting the desired skills using another function
         called NumUsefulPoints() which applies an integer value to each armor piece in the vector
         based on its potential usefulness in the current search. It's kind of like a weighing feature
         to determine the efficacy of all the armor pieces. The sorted armors are then returned.

RETURNS
    
        Returns a vector of the armors that were passed sorted according to the desired skills passed

AUTHOR
        Alec Rizzo

*/
/**/
vector<Armor> Search::SortUsefulArmor(vector<Armor> a_armors, vector<activeSkill> a_desiredSkills)
{
    vector<Armor> tempVec;

    for (int i = 0; i < a_armors.size(); i++)
    {
        if (tempVec.size() != 0)
        {
            int currentNumPoints = NumUsefulPoints(a_armors.at(i), a_desiredSkills);
            int highestNumPoints = NumUsefulPoints(tempVec.at(0), a_desiredSkills);
            // replace the begining element if the current armor has more useful points
            if (currentNumPoints >= highestNumPoints)
            {
                tempVec.insert(tempVec.begin(), a_armors.at(i));
            }
            else
            {
                // find where to put the current armor piece in the tempVec by comparing its points to
                // the other armors in the vector
                for (int z = 1; z < tempVec.size(); z++)
                {
                    // note: start at 1 because tempVec 0 is the most useful piece which is already taken care of above
                    if (currentNumPoints >= NumUsefulPoints(tempVec.at(z), a_desiredSkills))
                    {
                        tempVec.insert(tempVec.begin() + z, a_armors.at(i));
                        break;
                    }
                    else if (z + 1 == tempVec.size())
                    {
                        // if it is greater than or equal to nothing in tempVec pushback the armor
                        tempVec.push_back(a_armors.at(i));
                    }
                }
            }
        }
        else
        {
            tempVec.push_back(a_armors.at(i));
        }
    }

    return tempVec;
}/*vector<Armor> Search::SortUsefulArmor(vector<Armor> a_armors, vector<activeSkill> a_desiredSkills);*/

// 
/**/
/*
Search::NumUsefulPoints() Search::NumUsefulPoints()

NAME
        
        Search::NumUsefulPoints - determines the amount of useful points an individual 
                                  armor piece has

SYNOPSIS

        int Search::NumUsefulPoints(Armor a_armor, vector<activeSkill> a_desiredSkills)

            a_armor             -->     the armor piece which we are discerning the usefulness of
            a_desiredSkills     -->     the vector of desired skills that the user wants

DESCRIPTION

        This function applies an integer value to an armor piece based on its potential usefulness
        in the current search. It's kind of like a weighing feature to determine the efficacy of an armor
        piece.

RETURNS

        Returns an integer value which can be used to determine the armors usefulness in comparison
        to other armors that are sent through this function.

AUTHOR
        Alec Rizzo

*/
/**/
int Search::NumUsefulPoints(Armor a_armor, vector<activeSkill> a_desiredSkills)
{
    int usefulPoints = 0;
    for (int i = 0; i < a_desiredSkills.size(); i++)
    {
        if (a_armor.GetSkill1() == a_desiredSkills.at(i).treeName)
        {
            usefulPoints += a_armor.GetSkill1Points();
        }
        else if (a_armor.GetSkill2() == a_desiredSkills.at(i).treeName)
        {
            usefulPoints += a_armor.GetSkill2Points();
        }
        else if (a_armor.GetSkill3() == a_desiredSkills.at(i).treeName)
        {
            usefulPoints += a_armor.GetSkill3Points();
        }
        else if (a_armor.GetSkill4() == a_desiredSkills.at(i).treeName)
        {
            usefulPoints += a_armor.GetSkill4Points();
        }
        else if (a_armor.GetSkill5() == a_desiredSkills.at(i).treeName)
        {
            usefulPoints += a_armor.GetSkill5Points();
        }
    }

    // Note: the decoration slots and skill points aren't an exact 1-1 correlation,
    //       this is just to gauge how useful an armor piece could potentially be

    // Many 3 slot decorations actually give 4 skill points but 1 slot and 2 slot decorations 
    // often give exactly 1 or 2 skill points
    if (a_armor.GetDecoSlots() == 1)
    {
        usefulPoints += 1;
    }
    else if (a_armor.GetDecoSlots() == 2)
    {
        usefulPoints += 2;
    }
    else if (a_armor.GetDecoSlots() == 3)
    {
        usefulPoints += 4;
    }

    return usefulPoints;
}/*int Search::NumUsefulPoints(Armor a_armor, vector<activeSkill> a_desiredSkills);*/

/**/
/*
Search::FindArmorWithSkill() Search::FindArmorWithSkill()

NAME

        Search::FindArmorWithSkill - finds an armor piece with the passed skill

SYNOPSIS

        Armor Search::FindArmorWithSkill(vector<Armor> a_armors, activeSkill a_desiredSkill)

            a_armors        -->     vector of armors we will check for the desired skill
            a_desiredSkill  -->     the desired skill we will look for in the armors

DESCRIPTION

        This function has the ability to loop through the passed vector of armors and
        return once it finds an armor piece with a skill. Designed to be used after the
        armors have already been sorted by their usefulness. 

RETURNS

        Returns when an armor piece with the desired skill is found. If it finds no armor with the 
        skill desired it will return the blank armor object skillArmor.

AUTHOR
        Alec Rizzo

*/
/**/
Armor Search::FindArmorWithSkill(vector<Armor> a_armors, activeSkill a_desiredSkill)
{
    Armor skillArmor;
    for (int i = 0; i < a_armors.size(); i++)
    {
        if (a_armors.at(i).GetSkill1() == a_desiredSkill.treeName)
        {
            return a_armors.at(i);
        }
        if (a_armors.at(i).GetSkill2() == a_desiredSkill.treeName)
        {
            return a_armors.at(i);
        }
        if (a_armors.at(i).GetSkill3() == a_desiredSkill.treeName)
        {
            return a_armors.at(i);
        }
        if (a_armors.at(i).GetSkill4() == a_desiredSkill.treeName)
        {
            return a_armors.at(i);
        }
        if (a_armors.at(i).GetSkill5() == a_desiredSkill.treeName)
        {
            return a_armors.at(i);
        }
    }
    return skillArmor;
}/*Armor Search::FindArmorWithSkill(vector<Armor> a_armors, activeSkill a_desiredSkill);*/

/**/
/*
Search::FindDecoWithSkill() Search::FindDecoWithSkill()

NAME
        Search::FindDecoWithSkill - finds a decoration with the desired skill
                                    that fits in the amount of slots remaining

SYNOPSIS

        Decoration Search::FindDecoWithSkill(int a_largestSlotsRemaining, vector<Decoration> a_decorations, 
                                                                                activeSkill a_desiredSkill)

            a_largestSlotsRemaining     -->     integer denoting the largest slot remaining for this
                                                decoration to be slotted into
            a_decorations               -->     the vector of useable decorations for the current search
                                                based on the users desired skills
            a_desiredSkill              -->     the desired skill we are searching for in the decorations
DESCRIPTION

        This function finds a decoration from the set of passed decorations which satisfies the conditions
        of being able to fit in the passed integer of largest slot remaining as well as having the desired 
        skill as its skill.

RETURNS

        Returns a decoration best suited to the amount of slots remaining which has the desired skill

AUTHOR
        Alec Rizzo

*/
/**/
Decoration Search::FindDecoWithSkill(int a_largestSlotsRemaining, vector<Decoration> a_decorations, activeSkill a_desiredSkill)
{
    Decoration skillDeco;
    for (int i = 0; i < a_decorations.size(); i++)
    {
        // We only check for skill 1 as skill 2 are only negative skill points on decorations
        if (a_decorations.at(i).GetSkill1() == a_desiredSkill.treeName 
            && a_decorations.at(i).GetSlotsRequired() <= a_largestSlotsRemaining)
        {
            skillDeco = a_decorations.at(i);
        }
    }
    return skillDeco;
}/*Decoration Search::FindDecoWithSkill(int a_largestSlotsRemaining, vector<Decoration> a_decorations, activeSkill a_desiredSkill);*/

/**/
/*
Search::InputRaw() Search::InputRaw() 

NAME

        Search::InputRaw - gets users input for the raw damage of their weapon
        

SYNOPSIS

        float Search::InputRaw()

DESCRIPTION

        This function gets users input for the raw damage on their weapon for use with
        the effective raw damage calculation.
    
RETURNS

        Returns a float value for the raw damage number input

AUTHOR
        Alec Rizzo

*/
/**/
float Search::InputRaw()
{
    float raw = 0.0;
    cout << "Please input the Raw Damage of your weapon: ";
    
    while (!((cin >> raw) && raw > 0))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please input a valid number: ";

    }
    return raw;
}/*float Search::InputRaw();*/


/**/
/*
Search::InputAffinity() Search::InputAffinity()

NAME
        Search::InputAffinity - lets the user input the affinity of their weapon
                                for effective raw damage calculation

SYNOPSIS

        float Search::InputAffinity()

DESCRIPTION

        This function outputs the prompt to the user asking for their weapon affinity as a
        whole number and then gets their input. To calculate total effective raw damage we need
        the affinity to be a decimal so we multiply by .01 and return an appropriate affinity percent.

RETURNS

        Returns a decimal less than 1 denoting the affinity of the users weapon

AUTHOR
        Alec Rizzo

*/
/**/
float Search::InputAffinity()
{
    float affinityPercent = 0;
    cout << "Please input the affinity of your weapon (as a whole number): ";
    cin >> affinityPercent;
    while (affinityPercent > 100 || affinityPercent < -100)
    {
        cout << "Please enter a valid number: ";
        cin >> affinityPercent;
        cin.clear();
    }
    cin.clear();
    return affinityPercent * .01;
}/*float Search::InputAffinity();*/

/**/
/*
Search::InputSharpness() Search::InputSharpness()

NAME
        Search::InputSharpness() - lets the user input the sharpness of their weapon
                                   for effective raw damage calculation

SYNOPSIS

        float Search::InputSharpness()

DESCRIPTION

        This function outputs the prompt to the user asking for their weapon sharpness as a
        string and then gets their input. The sharpness is essentially a modifier/multiplier 
        for how much damage a weapon can do.

RETURNS

        Returns a float value for the appropriate sharpness color's modifier number in Monster Hunter Generations 
        Ultimate.

AUTHOR
        Alec Rizzo

*/
/**/
float Search::InputSharpness()
{
    float sharpness = 0.0;
    string color = "";
    cout << "Please enter your weapons sharpness(red, orange, yellow, green, blue, white, purple): ";
    cin >> color;
    while (!(color == "red" || color == "orange" || color == "yellow" || color == "green" || color == "blue" || color == "white" || color == "purple"))
    {
        cout << "Please enter only red, orange, yellow, green, blue, white, or purple for your sharpness grade: ";
        getline(cin, color);
    }
    
    if (color == "red")
    {
        sharpness = 0.50;
    }
    else if (color == "orange")
    {
        sharpness = 0.75;
    }
    else if (color == "yellow")
    {
        sharpness = 1.00;
    }
    else if (color == "green")
    {
        sharpness = 1.05;
    }
    else if (color == "blue")
    {
        sharpness = 1.20;
    }
    else if (color == "white")
    {
        sharpness = 1.32;
    }
    else if (color == "purple")
    {
        sharpness = 1.39;
    }
    else
    {
        sharpness = 0.0;
    }

    return sharpness;
}/*float Search::InputSharpness();*/

/**/
/*
Search::InputCriticalBoost() Search::InputCriticalBoost()

NAME
        
        Search::InputCriticalBoost - gets whether or not the user has critical boost

SYNOPSIS

        float Search::InputCriticalBoost()

DESCRIPTION

        This function determines whether a user has critical boost for aiding in calculation
        of their effective raw damage. Critical boost is one of the most important skills in 
        Monster Hunter Generations Ultimate when it comes to increasing the amount of damage
        a player can do so this needs to be accounted for in the formula. Landing a critical hit
        in the game without critical boost makes you do 1.25x the damage whereas with critical boost
        you get 1.40x the damage. 

RETURNS

        Returns a float value for the proper modifier for critical boost.

AUTHOR
        Alec Rizzo

*/
/**/
float Search::InputCriticalBoost()
{
    int cb = -1;
    cout << "Please enter (1) if you have critical boost, enter (0) if you do not: ";
    cin >> cb;
    while (cb != 1 && cb != 0)
    {
        cout << "Please enter only (1) or (0) : ";
        cin >> cb;
        cin.clear();
    }
    cin.clear();

    if (cb == 1)
    {
        return .40;
    }
    else { return .25; }
}/*float Search::InputCriticalBoost();*/

/**/
/*
Search::CalculateEFR() Search::CalculateEFR()

NAME
        Search::CalculateEFR - gets relevant info from the user to calculate their
                               effective raw damage for a weapon they have in the game

SYNOPSIS

DESCRIPTION

        This function calculates the total effective raw damage by getting the users weapon
        base damage (raw damage), weapon sharpness, weapon affinity, and whether they have the
        skill critical boost equipped. Depending on these variables we can determine how useful/strong
        a weapon/armor set is.

        (NOTE: Weapons from Monster Hunter Generations Ultimate are not a data set loaded into 
        this program, I could not bring myself to make another data set after how tedious the others were. 
        This is just an external a fun external tool to help aid the user on how strong their armor sets 
        are compared to one another)

RETURNS

        Returns the calculated float value for a users effective raw damage.

AUTHOR
        Alec Rizzo

*/
/**/
float Search::CalculateEFR()
{
    float raw = InputRaw();
    float sharpness = InputSharpness();
    float affinity = InputAffinity();
    float critboost = InputCriticalBoost();

    return (raw * sharpness * (1 + (affinity * critboost)));
}/*float Search::CalculateEFR();*/

/**/
/*
Search::SortSetsBy() Search::SortSetsBy()

NAME
        Search::SortSetsBy - sorts the armor sets by the preffered sort method
    
SYNOPSIS

        vector<ArmorSet> Search::SortSetsBy(vector<ArmorSet> a_sets, string a_sortMethod)

            a_sets          -->     the armor sets we are going to sort
            a_sortMethod    -->     the string denoting by which value we will sort the set

DESCRIPTION

        This function sorts the armor sets by the passed sort method (which is defaulted to defense).
        We will loop through the armor sets and get the total values of the specified defense for each armor
        set to find which are the largest and sort them accordingly.The user can input a sort method through 
        the correct actions in SearchLoop() prior to a search.
        
        NOTE: This function could probably be downsized by making another function to handle the looping
        of the if statements as they are rather repetitive. With calls to different GetToTalDefense() functions 
        being the only real difference in the loops.

RETURNS

        Returns a vector of armor sets after sorting by the appropriate passed sort method.
        if no sort was preformed just return the original armor sets vector of a_sets 

AUTHOR
        Alec Rizzo

*/
/**/
vector<ArmorSet> Search::SortSetsBy(vector<ArmorSet> a_sets, string a_sortMethod)
{
	if (a_sortMethod == "defense")
	{
        vector<ArmorSet> tempSetVec;
		// Sort by max def
		for (int i = 0; i < a_sets.size(); i++)
		{
			if (tempSetVec.size() != 0)
			{
				int currentDef = a_sets.at(i).GetTotalMaximumDefense();
				int highestDef = tempSetVec.at(0).GetTotalMaximumDefense();
				// Replace the first element if the current armor is higher defense
				if (currentDef >= highestDef)
				{
					tempSetVec.insert(tempSetVec.begin(), a_sets.at(i));
				}
				else
				{
					// Find where to put the set in temp vec by comparing to other sets in temp vec
					for (int z = 1; z < tempSetVec.size(); z++)
					{
						if (currentDef >= tempSetVec.at(z).GetTotalMaximumDefense())
						{
							tempSetVec.insert(tempSetVec.begin() + z, a_sets.at(i));
                            break;
						}
						else if (z + 1 == tempSetVec.size())
						{
							// if is the lowest in the vector, push back the set
							tempSetVec.push_back(a_sets.at(i));
						}
					}
				}
			}
			else
			{
				tempSetVec.push_back(a_sets.at(i));
			}
		}
		return tempSetVec;
    }
    if (a_sortMethod == "fire")
    {
        vector<ArmorSet> tempSetVec;
        // Sort by fire def
        for (int i = 0; i < a_sets.size(); i++)
        {
            if (tempSetVec.size() != 0)
            {
                int currentFire = a_sets.at(i).GetTotalFireDefense();
                int highestFire = tempSetVec.at(0).GetTotalFireDefense();
                // Replace the first element if the current armor is higher defense
                if (currentFire >= highestFire)
                {
                    tempSetVec.insert(tempSetVec.begin(), a_sets.at(i));
                }
                else
                {
                    // Find where to put the set in temp vec by comparing to other sets in temp vec
                    for (int z = 1; z < tempSetVec.size(); z++)
                    {
                        if (currentFire >= tempSetVec.at(z).GetTotalFireDefense())
                        {
                            tempSetVec.insert(tempSetVec.begin() + z, a_sets.at(i));
                            break;
                        }
                        else if (z + 1 == tempSetVec.size())
                        {
                            // if is the lowest in the vector, push back the set
                            tempSetVec.push_back(a_sets.at(i));
                        }
                    }
                }
            }
            else
            {
                tempSetVec.push_back(a_sets.at(i));
            }
        }
        return tempSetVec;
    }
    if (a_sortMethod == "water")
    {
        vector<ArmorSet> tempSetVec;
        // Sort by water def
        for (int i = 0; i < a_sets.size(); i++)
        {
            if (tempSetVec.size() != 0)
            {
                int currentWater = a_sets.at(i).GetTotalWaterDefense();
                int highestWater = tempSetVec.at(0).GetTotalWaterDefense();
                // Replace the first element if the current armor is higher defense
                if (currentWater >= highestWater)
                {
                    tempSetVec.insert(tempSetVec.begin(), a_sets.at(i));
                }
                else
                {
                    // Find where to put the set in temp vec by comparing to other sets in temp vec
                    for (int z = 1; z < tempSetVec.size(); z++)
                    {
                        if (currentWater >= tempSetVec.at(z).GetTotalWaterDefense())
                        {
                            tempSetVec.insert(tempSetVec.begin() + z, a_sets.at(i));
                            break;
                        }
                        else if (z + 1 == tempSetVec.size())
                        {
                            // if is the lowest in the vector, push back the set
                            tempSetVec.push_back(a_sets.at(i));
                        }
                    }
                }
            }
            else
            {
                tempSetVec.push_back(a_sets.at(i));
            }
        }
        return tempSetVec;
    }
    if (a_sortMethod == "thunder")
    {
        vector<ArmorSet> tempSetVec;
        // Sort by thunder def
        for (int i = 0; i < a_sets.size(); i++)
        {
            if (tempSetVec.size() != 0)
            {
                int currentThunder = a_sets.at(i).GetTotalThunderDefense();
                int highestThunder = tempSetVec.at(0).GetTotalThunderDefense();
                // Replace the first element if the current armor is higher defense
                if (currentThunder >= highestThunder)
                {
                    tempSetVec.insert(tempSetVec.begin(), a_sets.at(i));
                }
                else
                {
                    // Find where to put the set in temp vec by comparing to other sets in temp vec
                    for (int z = 1; z < tempSetVec.size(); z++)
                    {
                        if (currentThunder >= tempSetVec.at(z).GetTotalThunderDefense())
                        {
                            tempSetVec.insert(tempSetVec.begin() + z, a_sets.at(i));
                            break;
                        }
                        else if (z + 1 == tempSetVec.size())
                        {
                            // if is the lowest in the vector, push back the set
                            tempSetVec.push_back(a_sets.at(i));
                        }
                    }
                }
            }
            else
            {
                tempSetVec.push_back(a_sets.at(i));
            }
        }
        return tempSetVec;
    }
    if (a_sortMethod == "ice")
    {
        // Sort by ice def
        vector<ArmorSet> tempSetVec;
        for (int i = 0; i < a_sets.size(); i++)
        {
            if (tempSetVec.size() != 0)
            {
                int currentIce = a_sets.at(i).GetTotalIceDefense();
                int highestIce = tempSetVec.at(0).GetTotalIceDefense();
                // Replace the first element if the current armor is higher defense
                if (currentIce >= highestIce)
                {
                    tempSetVec.insert(tempSetVec.begin(), a_sets.at(i));
                }
                else
                {
                    // Find where to put the set in temp vec by comparing to other sets in temp vec
                    for (int z = 1; z < tempSetVec.size(); z++)
                    {
                        if (currentIce >= tempSetVec.at(z).GetTotalIceDefense())
                        {
                            tempSetVec.insert(tempSetVec.begin() + z, a_sets.at(i));
                            break;
                        }
                        else if (z + 1 == tempSetVec.size())
                        {
                            // if is the lowest in the vector, push back the set
                            tempSetVec.push_back(a_sets.at(i));
                        }
                    }
                }
            }
            else
            {
                tempSetVec.push_back(a_sets.at(i));
            }
        }
        return tempSetVec;
    }
    if (a_sortMethod == "dragon")
    {
        // Sort by dragon def
        vector<ArmorSet> tempSetVec;
        for (int i = 0; i < a_sets.size(); i++)
        {
            if (tempSetVec.size() != 0)
            {
                int currentDragon = a_sets.at(i).GetTotalDragonDefense();
                int highestDragon = tempSetVec.at(0).GetTotalDragonDefense();
                // Replace the first element if the current armor is higher defense
                if (currentDragon >= highestDragon)
                {
                    tempSetVec.insert(tempSetVec.begin(), a_sets.at(i));
                }
                else
                {
                    // Find where to put the set in temp vec by comparing to other sets in temp vec
                    for (int z = 1; z < tempSetVec.size(); z++)
                    {
                        if (currentDragon >= tempSetVec.at(z).GetTotalDragonDefense())
                        {
                            tempSetVec.insert(tempSetVec.begin() + z, a_sets.at(i));
                            break;
                        }
                        else if (z + 1 == tempSetVec.size())
                        {
                            // if is the lowest in the vector, push back the set
                            tempSetVec.push_back(a_sets.at(i));
                        }
                    }
                }
            }
            else
            {
                tempSetVec.push_back(a_sets.at(i));
            }
        }
        return tempSetVec;
    }

    // If none of these if statements returned something is wrong with the parameter, return the original
    // vector to avoid loss of data
    return a_sets;
}/*vector<ArmorSet> Search::SortSetsBy(vector<ArmorSet> a_sets, string a_sortMethod);*/