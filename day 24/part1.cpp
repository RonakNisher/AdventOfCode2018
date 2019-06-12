// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <utility>
#include <algorithm>    // std::find

using namespace std;

struct group 
{
	int id;
	int type; //0 = immune, 1 = infection
	int noOfUnits;
	int hitPoint;
	int damage;
	int initiative;
	string attackType;
	vector<string> weakTo;
	vector<string> immuneTo;
	
	// calculated properties
	bool isAlive = true;
	int target;
	int effectivePower;
	int targetedById = -1;

	group (int id, int type, int noOfUnits, int hitPoint, int damage, int initiative, string attackType,
			vector<string> weakTo, vector<string> immuneTo):
			id(id),
			type(type),
			noOfUnits(noOfUnits),
			hitPoint(hitPoint),
			damage(damage),
			initiative(initiative),
			attackType(attackType),
			weakTo(move(weakTo)),
			immuneTo(move(immuneTo))
			{}
			
	void print()
	{
		cout<<"id: "<<id<<" type:"<<(type == 0 ? "Immune":"infection")<<", noOfUnits:"<<noOfUnits<<", hitPoint:"<<hitPoint<<", damage:"<<damage
			<<", initiative:"<<initiative<<", attackType:"<<attackType<<endl;
		
		if (!immuneTo.empty())
		{
			cout<<"Immune to ";
			for (const string& s : immuneTo)
				cout<<s<<" ";
			cout<<endl;
		}
		
		if (!weakTo.empty())
		{
			cout<<"Weak to ";
			for (const string& s : weakTo)
				cout<<s<<" ";
			cout<<endl;
		}
	}
	
	int calculateEffectivePower()
	{
		effectivePower = noOfUnits * damage;
		return effectivePower;
	}
	
	int effectiveHealth()
	{
		return noOfUnits * hitPoint;
	}
	
	int calculatedamage(group& g)
	{
		int damageMultiplier = 1;
						
		auto weakIt = find(g.weakTo.begin(), g.weakTo.end(), attackType);
		
		if (weakIt != g.weakTo.end())
			damageMultiplier = 2;
			
		int damageDone = noOfUnits * damage * damageMultiplier;
	}
};

bool areBothGroupsAlive(const vector<group>& groups)
{
	bool immuneAlive = false;
	bool infectionAlive = false;
	
	for (const group& g : groups)
	{
		if (g.isAlive)
		{
			if (g.type == 0)
			{
				immuneAlive = true;
			}
			else
			{
				infectionAlive = true;
			}
		}
	}
	
	return immuneAlive && infectionAlive;
}

void print(vector<int>& groupsStillAlive)
{
	for (const int g : groupsStillAlive)
	{
		cout<<g<<", ";
	}
	cout<<endl;
}

group* findGroupById(int i, vector<group>& groups)
{
	for (group& g : groups)
	{
		if (g.id == i)
		{
			return &g;
		}
	}
	
	return nullptr;
}

void printStats(vector<group>& groups)
{
	for (group& g : groups)
	{
		if (g.isAlive)
			cout<<"group "<<g.id<<", noOfUnits:"<<g.noOfUnits<<endl;
	}
}

int main()
{ 
	vector<int> groupsStillAlive;
	vector<group> groups;
	int noOfImmuneGroups = 2;
	int noOfInfectionGroups = 2;
	
	// Immune systems
	vector<string> g1Immune = {};
	vector<string> g1Weak = {};
	groups.emplace_back(1 /*id*/, 0 /*type*/, 790 /*noOfUnits*/, 3941 /*hitPoint*/, 48 /*damage*/, 5 /*initiative*/, "bludgeoning" /*attackType*/, 
						g1Weak /*weakTo*/, g1Immune /*immuneTo*/);
						
	vector<string> g2Immune = {};
	vector<string> g2Weak = {};
	groups.emplace_back(2 /*id*/, 0 /*type*/, 624 /*noOfUnits*/, 2987 /*hitPoint*/, 46 /*damage*/, 16 /*initiative*/, "bludgeoning" /*attackType*/, 
						g2Weak /*weakTo*/, g2Immune /*immuneTo*/);
						
	vector<string> g3Immune = { "bludgeoning", "slashing", "fire" };
	vector<string> g3Weak = {};
	groups.emplace_back(3 /*id*/, 0 /*type*/, 5724 /*noOfUnits*/, 9633 /*hitPoint*/, 16 /*damage*/, 9 /*initiative*/, "slashing" /*attackType*/, 
						g3Weak /*weakTo*/, g3Immune /*immuneTo*/);
						
	vector<string> g4Immune = { };
	vector<string> g4Weak = { };
	groups.emplace_back(4 /*id*/, 0 /*type*/, 1033 /*noOfUnits*/, 10664 /*hitPoint*/, 89 /*damage*/, 1 /*initiative*/, "slashing" /*attackType*/, 
						g4Weak /*weakTo*/, g4Immune /*immuneTo*/);

	vector<string> g5Immune = {};
	vector<string> g5Weak = { "slashing" };
	groups.emplace_back(5 /*id*/, 0 /*type*/, 6691 /*noOfUnits*/, 9773 /*hitPoint*/, 13 /*damage*/, 12 /*initiative*/, "bludgeoning" /*attackType*/, 
						g5Weak /*weakTo*/, g5Immune /*immuneTo*/);
						
	vector<string> g6Immune = { };
	vector<string> g6Weak = { "bludgeoning" };
	groups.emplace_back(6 /*id*/, 0 /*type*/, 325 /*noOfUnits*/, 11916 /*hitPoint*/, 276 /*damage*/, 8 /*initiative*/, "slashing" /*attackType*/, 
						g6Weak /*weakTo*/, g6Immune /*immuneTo*/);
						
	vector<string> g7Immune = {};
	vector<string> g7Weak = { };
	groups.emplace_back(7 /*id*/, 0 /*type*/, 1517 /*noOfUnits*/, 6424 /*hitPoint*/, 35 /*damage*/, 13 /*initiative*/, "bludgeoning" /*attackType*/, 
						g7Weak /*weakTo*/, g7Immune /*immuneTo*/);
						
	vector<string> g8Immune = { "bludgeoning" };
	vector<string> g8Weak = { };
	groups.emplace_back(8 /*id*/, 0 /*type*/, 1368 /*noOfUnits*/, 9039 /*hitPoint*/, 53 /*damage*/, 4 /*initiative*/, "slashing" /*attackType*/, 
						g8Weak /*weakTo*/, g8Immune /*immuneTo*/);

	vector<string> g9Immune = { "cold", "radiation" };
	vector<string> g9Weak = { "fire" };
	groups.emplace_back(9 /*id*/, 0 /*type*/, 3712 /*noOfUnits*/, 5377 /*hitPoint*/, 14 /*damage*/, 14 /*initiative*/, "slashing" /*attackType*/, 
						g9Weak /*weakTo*/, g9Immune /*immuneTo*/);
						
	vector<string> g10Immune = { };
	vector<string> g10Weak = { "bludgeoning" , "slashing" };
	groups.emplace_back(10 /*id*/, 0 /*type*/, 3165 /*noOfUnits*/, 8703 /*hitPoint*/, 26 /*damage*/, 11 /*initiative*/, "radiation" /*attackType*/, 
						g10Weak /*weakTo*/, g10Immune /*immuneTo*/);

	// Infections
						
	vector<string> g11Immune = { "bludgeoning" };
	vector<string> g11Weak = { "radiation" };
	groups.emplace_back(11 /*id*/, 1 /*type*/, 1113 /*noOfUnits*/, 44169 /*hitPoint*/, 57 /*damage*/, 7 /*initiative*/, "fire" /*attackType*/, 
						g11Weak /*weakTo*/, g11Immune /*immuneTo*/);
						
	vector<string> g12Immune = { };
	vector<string> g12Weak = { "radiation", "cold" };
	groups.emplace_back(12 /*id*/, 1 /*type*/, 3949 /*noOfUnits*/, 20615 /*hitPoint*/, 9 /*damage*/, 6 /*initiative*/, "bludgeoning" /*attackType*/, 
						g12Weak /*weakTo*/, g12Immune /*immuneTo*/);

	vector<string> g13Immune = { "bludgeoning", "cold" };
	vector<string> g13Weak = { "fire" };
	groups.emplace_back(13 /*id*/, 1 /*type*/, 602 /*noOfUnits*/, 35167 /*hitPoint*/, 93 /*damage*/, 20 /*initiative*/, "radiation" /*attackType*/, 
						g13Weak /*weakTo*/, g13Immune /*immuneTo*/);
						
	vector<string> g14Immune = { };
	vector<string> g14Weak = { };
	groups.emplace_back(14 /*id*/, 1 /*type*/, 1209 /*noOfUnits*/, 34572 /*hitPoint*/, 55 /*damage*/, 3 /*initiative*/, "bludgeoning" /*attackType*/, 
						g14Weak /*weakTo*/, g14Immune /*immuneTo*/);
						
	vector<string> g15Immune = { "fire" };
	vector<string> g15Weak = { };
	groups.emplace_back(15 /*id*/, 1 /*type*/, 902 /*noOfUnits*/, 12983 /*hitPoint*/, 28 /*damage*/, 19 /*initiative*/, "fire" /*attackType*/, 
						g15Weak /*weakTo*/, g15Immune /*immuneTo*/);
						
	vector<string> g16Immune = { };
	vector<string> g16Weak = { };
	groups.emplace_back(16 /*id*/, 1 /*type*/, 1132 /*noOfUnits*/, 51353 /*hitPoint*/, 66 /*damage*/, 15 /*initiative*/, "radiation" /*attackType*/, 
						g16Weak /*weakTo*/, g16Immune /*immuneTo*/);

	vector<string> g17Immune = { "bludgeoning" };
	vector<string> g17Weak = { };
	groups.emplace_back(17 /*id*/, 1 /*type*/, 7966 /*noOfUnits*/, 49894 /*hitPoint*/, 9 /*damage*/, 10 /*initiative*/, "cold" /*attackType*/, 
						g17Weak /*weakTo*/, g17Immune /*immuneTo*/);
						
	vector<string> g18Immune = {};
	vector<string> g18Weak = { "radiation" };
	groups.emplace_back(18 /*id*/, 1 /*type*/, 3471 /*noOfUnits*/, 18326 /*hitPoint*/, 8 /*damage*/, 18 /*initiative*/, "fire" /*attackType*/, 
						g18Weak /*weakTo*/, g18Immune /*immuneTo*/);
						
	vector<string> g19Immune = { "fire" };
	vector<string> g19Weak = { "bludgeoning" };
	groups.emplace_back(19 /*id*/, 1 /*type*/, 110 /*noOfUnits*/, 38473 /*hitPoint*/, 640 /*damage*/, 2 /*initiative*/, "slashing" /*attackType*/, 
						g19Weak /*weakTo*/, g19Immune /*immuneTo*/);
						
	vector<string> g20Immune = { };
	vector<string> g20Weak = { "slashing" };
	groups.emplace_back(20 /*id*/, 1 /*type*/, 713 /*noOfUnits*/, 42679 /*hitPoint*/, 102 /*damage*/, 17 /*initiative*/, "bludgeoning" /*attackType*/, 
						g20Weak /*weakTo*/, g20Immune /*immuneTo*/);
	
	// for (group& g : groups)
	// {
	// 	g.print();
	// 	cout<<endl;
	// }
	
	for (int i = 1; i <= 20; i++)
	{
		groupsStillAlive.push_back(i);
	}
	
	int i = 0;
	while (areBothGroupsAlive(groups))
	{
		// printStats(groups);
		
		// TARGET SELECTION
		for (group& g : groups)
		{
			g.calculateEffectivePower();
			// cout<<g.id<<"->"<<g.effectivePower<<endl;
		}
		
		sort(begin(groupsStillAlive), end(groupsStillAlive), [&groups] (const int& lhs, const int& rhs)
		{
			group* left;
			group* right;
			for (group& g : groups)
			{
				if (g.id == lhs)
					left = &g;
				else if (g.id == rhs)
					right = &g;
			}
			
			// cout<<lhs<<" vs "<<rhs<<" -> "<<(left->effectivePower < right->effectivePower && left->initiative < right->initiative)<<endl;
			// cout<<"left "<<left->effectivePower<<" and right "<<right->effectivePower<<endl;
			
			if (left->effectivePower != right->effectivePower)
				return left->effectivePower > right->effectivePower;
			else
				return left->initiative > right->initiative;
		});
		
		cout<<"Target selection phase order is "<<endl;
		print(groupsStillAlive);
		
		// select targets
		for (const int i : groupsStillAlive)
		{
			group* grp = findGroupById(i, groups);
			group* targetGroup = nullptr;
			// cout<<"selecting target fro grp "<<grp->id<<endl;
			
			int maxDamage = 0;
			for (group& g : groups)
			{
				if (g.isAlive && g.type != grp->type && g.targetedById == -1)
				{
					auto immuneIt = find(g.immuneTo.begin(), g.immuneTo.end(), grp->attackType);
					if (immuneIt == g.immuneTo.end())
					{
						int damageMultiplier = 1;
						
						auto weakIt = find(g.weakTo.begin(), g.weakTo.end(), grp->attackType);
						
						if (weakIt != g.weakTo.end())
							damageMultiplier = 2;
							
						int damageDone = grp->calculatedamage(g);
						
						if (damageDone > maxDamage)
						{
							targetGroup = &g;
							maxDamage = damageDone;
						}
						else if (damageDone == maxDamage)
						{
							// cout<<targetGroup->effectivePower<<" < "<<g.effectivePower<<endl;
							if (targetGroup->effectivePower < g.effectivePower)
								targetGroup = &g;
							else if (targetGroup->effectivePower == g.effectivePower && targetGroup->initiative < g.initiative)
								targetGroup = &g;
						}
					}
				}
			}
			
			if (targetGroup != nullptr)
			{
				targetGroup->targetedById = grp->id;
				grp->target = targetGroup->id;
				// cout<<grp->id<<" is targeting "<<grp->target<<" with damage "<<maxDamage<<endl;
			}
			else
			{
				grp->target = -1;
			}
		}
		
		// ATTACKING PHASE
		
		// sort des by initiative
		sort(begin(groupsStillAlive), end(groupsStillAlive), [&groups] (const int& lhs, const int& rhs)
		{
			group* left;
			group* right;
			for (group& g : groups)
			{
				if (g.id == lhs)
					left = &g;
				else if (g.id == rhs)
					right = &g;
			}
			
			return left->initiative > right->initiative;
		});
		
		cout<<"Attacking phase order is "<<endl;
		print(groupsStillAlive);
		
		// Start Attacking
		for (const int i : groupsStillAlive)
		{
			group* attackingGroup = findGroupById(i, groups);
			if (attackingGroup->target == -1)
				continue;
			group* defendingGroup = findGroupById(attackingGroup->target, groups);
			
			// cout<<" group "<<attackingGroup->id<<" attacking "<<defendingGroup->id<<endl;
			
			int damageToBeDone = attackingGroup->calculatedamage(*defendingGroup);
			int defendingGroupEffectiveHealth = defendingGroup->effectiveHealth();
			
			// cout<<damageToBeDone<<"->"<<defendingGroupEffectiveHealth<<endl;
			
			if (defendingGroupEffectiveHealth <= damageToBeDone)
			{
				defendingGroup->isAlive = false;
				cout<<" group "<<attackingGroup->id<<" killed all units of group "<<defendingGroup->id<<endl;
			}
			else
			{
				int noOfUnitsKilled = damageToBeDone / defendingGroup->hitPoint;
				defendingGroup->noOfUnits -= noOfUnitsKilled;
				// cout<<" group "<<attackingGroup->id<<" killed "<<noOfUnitsKilled<<" of group "<<defendingGroup->id<<endl;
			}
		}
		
		// clean up
		for (group& g : groups)
		{
			// cout<<"Group "<<g.id<<" isAlive "<<g.isAlive<<endl;
			if (!g.isAlive)
			{
				auto it = find(groupsStillAlive.begin(), groupsStillAlive.end(), g.id);
				if (it != groupsStillAlive.end())
					groupsStillAlive.erase(it);
				
			}
			g.target = 0;
			g.targetedById = -1;
		}
		
		// print(groupsStillAlive);
		cout<<"New size is "<<groupsStillAlive.size()<<endl;
		
		cout<<endl<<endl<<endl;
		// break;
		
		i++;
		
		// if (i == 3)
		// 	break;
	}
	
	print(groupsStillAlive);
	
	int res = 0;
	for (int g : groupsStillAlive)
	{
		group* grp = findGroupById(g, groups);
		res += grp->noOfUnits;
	}
	
	cout<<"total No of units left "<<res<<endl;
	cout<<"Done"<<endl;

	return 0;
}