#pragma once
/********************************************************************************************/
/*

NAME

        armorset.h - obtains the necessary functions to create an armor set from
                     existing armor pieces.

DESCRIPTION

       This header has the functionality of making an armor set


AUTHOR

        Alec Rizzo

*/
/********************************************************************************************/

#include "armor.h"
#include "activeskill.h"
#include "decoration.h"

class ArmorSet
{
private:
    int m_weaponSlots;
    int m_charmSlots;
    Armor m_head;
    Armor m_body;
    Armor m_arms;
    Armor m_waist;
    Armor m_legs;
    Armor m_charm;
    vector<activeSkill> m_skills;
    vector<Decoration> m_weaponDecorations;

public:
    ArmorSet();
    void CalculateActiveSkills(vector<activeSkill> a_activeSkills);
    vector<treeSkill> TreeSkillsOnArmor(Armor a_armor);
    vector<treeSkill> TreeSkillsOnDecorations(vector<Decoration> a_decorations);
    vector<treeSkill> CombineTreeSkillVectors(vector<treeSkill> a_baseVec, vector<treeSkill> a_newVec);

    int GetWeaponSlots();
    int GetCharmSlots();
    Armor GetHead();
    Armor GetBody();
    Armor GetArms();
    Armor GetWaist();
    Armor GetLegs();
    Armor GetCharm();
    vector<activeSkill> GetActiveSkills();
    int GetTotalMaximumDefense();
    int GetTotalFireDefense();
    int GetTotalWaterDefense();
    int GetTotalThunderDefense();
    int GetTotalIceDefense();
    int GetTotalDragonDefense();


    bool IsHeadEmpty();
    bool IsBodyEmpty();
    bool IsArmsEmpty();
    bool IsWaistEmpty();
    bool IsLegsEmpty();
    bool IsCharmEmpty();
    bool IsSkillActive(activeSkill a_activeSkill);
    bool CanSlotDecos();
    bool MeetsRequiredSkills(vector<activeSkill> a_desiredSkills);

    void SetWeaponSlots(int a_weaponSlots);
    void SetCharmSlots(int a_charmSlots);
    void SetHead(Armor a_head);
    void SetBody(Armor a_body);
    void SetArms(Armor a_arms);
    void SetWaist(Armor a_waist);
    void SetLegs(Armor a_legs);
    void SetCharm(Armor a_charm);

    void ClearSet();
    int GetRemainingWeaponDecoSlots();
    void AddDecorationToWeapon(Decoration a_decoration);
    void AddDecorationToSet(Decoration a_decoration);


    int LargestAvailibleDecoSlot();
    int PointsNeededToActivate(activeSkill a_desiredSkill);

    void PrintArmorSet();
};