#include "CommonHeaders.h"
#include <assert.h>
#include <math.h>       /* pow */
#include "RandomFuncs.h"
using namespace std;

void FirstProcedureFunc(CHROME &Chrom, vector<double> DofVarSet){
	//if (isUseNodeMatrix)
	//{
	//	for (unsigned int i = 0; i < Chrom.VulnerableNodeDof.size(); i++)
	//	{
	//		Chrom.VulnerableNodeDof.at(i) = GenRandomFloat(DofVarSet);
	//	}
	//}
	
	for (unsigned int i = 0; i < Chrom.VulnerableLinkDof.size(); i++)
	{
		Chrom.VulnerableLinkDof.at(i) = GenRandomFloat(DofVarSet);
	}

}
void addNewNodeFunc(CHROME &Chrom, vector<double> DofVarSet)
{
	// case 1 if node == number of node change select a node with zeor and assing a possitive 
	if (!isUseNodeMatrix) goto ReviseLinkVar;  
	if (Chrom.VulnerableNodes.size() == NumNodes)
	{
		vector<int> ZeroDofNodeSet;
		for (unsigned int i = 0; i < Chrom.VulnerableNodeDof.size(); i++)
		{
			if (isEqual(Chrom.VulnerableNodeDof.at(i), 0.0f))
			{
				ZeroDofNodeSet.push_back(Chrom.VulnerableNodes.at(i));
			}
		}
		if (ZeroDofNodeSet.size() == 0)
		{
			int Rnode = GenRandomInt(Chrom.VulnerableNodes);// random select a node
			double OldValue = Chrom.VulnerableNodeDof.at(Rnode);
			do
			{
				Chrom.VulnerableNodeDof.at(Rnode) = GenRandomFloat(DofVarSet);
			} while (isEqual(OldValue, Chrom.VulnerableNodeDof.at(Rnode)));
		}
		else
		{
			int Rnode = GenRandomInt(ZeroDofNodeSet);// random select a node
			int pos = InvaildInt;
			for (unsigned int i = 0; i < Chrom.VulnerableNodes.size(); i++)
			{
				if (Chrom.VulnerableNodes.at(i) == Rnode)
				{
					do
					{
						Chrom.VulnerableNodeDof.at(i) = GenRandomFloat(DofVarSet);
					} while (isEqual(Chrom.VulnerableNodeDof.at(i), 0.0f));
				}
			}
		}
	}
	else
	{
		// case 1 if node < number 
		// then select a node and add it the vector
		// step find missing node
		vector<bool> NodeStatus(NumNodes, false);
		for (auto i = Chrom.VulnerableNodes.begin(); i != Chrom.VulnerableNodes.end(); i++)
		{
			NodeStatus.at(*i) = true;
		}
		vector<int> CandiSet;
		for (unsigned int i = 0; i < NodeStatus.size(); i++)
		{
			if (!NodeStatus.at(i))
			{
				CandiSet.push_back(i);
			}
		}
		Chrom.VulnerableNodes.push_back(GenRandomInt(CandiSet));
		double dof = 0.0f;
		do
		{
			dof = GenRandomFloat(DofVarSet);
		} while (isEqual(dof, 0.0f));
		Chrom.VulnerableNodeDofProb.push_back(dof);
	}
	TRACE("Check whether the node matrix is used or not");

ReviseLinkVar:

	if (Chrom.VulnerableLinks.size() == NumLinks)
	{
		// vector<int> ZeroDofNodeSet;
		vector<int> ZeroDofLinkSet;
		for (unsigned int i = 0; i < Chrom.VulnerableLinkDof.size(); i++)
		{
			if (isEqual(Chrom.VulnerableLinkDof.at(i), 0.0f))
			{
				ZeroDofLinkSet.push_back(Chrom.VulnerableLinks.at(i));
			}
		}
		if (ZeroDofLinkSet.size() == 0)
		{
			int Rnode = GenRandomInt(Chrom.VulnerableLinks);// random select a node
			double OldValue = Chrom.VulnerableLinkDof.at(Rnode);
			do
			{
				Chrom.VulnerableLinkDof.at(Rnode) = GenRandomFloat(DofVarSet);
			} while (isEqual(OldValue, Chrom.VulnerableLinkDof.at(Rnode)));
		}
		else
		{
			int Rnode = GenRandomInt(ZeroDofLinkSet);// random select a node
			int pos = InvaildInt;
			for (unsigned int i = 0; i < Chrom.VulnerableLinks.size(); i++)
			{
				if (Chrom.VulnerableLinks.at(i) == Rnode) {
					do
					{
						Chrom.VulnerableLinkDof.at(i) = GenRandomFloat(DofVarSet);
					} while (isEqual(Chrom.VulnerableLinkDof.at(i), 0.0f));
				}
			}
		}
	}
	else
	{
		// case 1 if node < number 
		// then select a node and add it the vector
		// step find missing node
		// vector<bool> NodeStatus(NumNodes, false);
		vector<bool> LinkStatus(NumLinks, false);
		for (auto i = Chrom.VulnerableLinks.begin(); i != Chrom.VulnerableLinks.end(); i++)
		{
			LinkStatus.at(*i) = true;
		}
		vector<int> CandiSet;
		for (unsigned int i = 0; i < LinkStatus.size(); i++)
		{
			if (!LinkStatus.at(i))
			{
				CandiSet.push_back(i);
			}
		}
		Chrom.VulnerableLinks.push_back(GenRandomInt(CandiSet));
		double dof = 0.0f;
		do
		{
			dof = GenRandomFloat(DofVarSet);
		} while (isEqual(dof, 0.0f));
		Chrom.VulnerableLinkDofProb.push_back(dof);
	}
}

void removeNodeDofFunc(CHROME &Chrom){
	try
	{
		if (isUseNodeMatrix)
		{
			int Pos = GenRandomPos((int)Chrom.VulnerableNodes.size());// 0 to size
			Chrom.VulnerableNodeDof.at(Pos) = 0.0f;
		}
		int Pos = GenRandomPos((int)Chrom.VulnerableLinks.size());// 0 to size
		Chrom.VulnerableLinkDof.at(Pos) = 0.0f;
		
	}
	catch (exception &e){
		TRACE("%s", e);
	}
}
void exchangeNodeDofFunc(CHROME &Chrom, const vector<double> &DofVarSet){
	
	if (isUseNodeMatrix)
	{
		vector<int> ZeroSet, PostiveSet;
		ZeroSet.reserve(NumNodes); PostiveSet.reserve(NumNodes);
		for (unsigned int i = 0; i < Chrom.VulnerableNodeDof.size(); i++)
		{
			if (isEqual(Chrom.VulnerableNodeDof.at(i), 0.0f)) ZeroSet.push_back(i);
			else PostiveSet.push_back(i);
		}
		int A, B;
		if (ZeroSet.size()==0)
		{
			B = GenRandomInt(PostiveSet);
			Chrom.VulnerableNodeDofProb.at(B) = 0.0f;
		}
		if (PostiveSet.size()==0)
		{
			A = GenRandomInt(ZeroSet);
			Chrom.VulnerableNodeDofProb.at(A) = GenRandomFloat(DofVarSet);
		}
		if (PostiveSet.size()!=0&&ZeroSet.size()!=0)
		{
			A = GenRandomInt(ZeroSet);
			B = GenRandomInt(PostiveSet);
			Chrom.VulnerableNodeDofProb.at(A) = Chrom.VulnerableNodeDofProb.at(B);
			Chrom.VulnerableNodeDofProb.at(B) = 0.0f;
		}
	}

	vector<int> ZeroSet, PostiveSet;
	ZeroSet.reserve(NumLinks); PostiveSet.reserve(NumLinks);
	for (unsigned int i = 0; i < Chrom.VulnerableLinkDof.size(); i++)
	{
		if (isEqual(Chrom.VulnerableLinkDof.at(i), 0.0f)) ZeroSet.push_back(i);
		else PostiveSet.push_back(i);
	}
	int A, B;
	if (ZeroSet.size()==0)
	{
		B = GenRandomInt(PostiveSet);
		Chrom.VulnerableLinkDofProb.at(B) = 0.0f;
	}
	if (PostiveSet.size()==0)
	{
		A = GenRandomInt(ZeroSet);
		Chrom.VulnerableLinkDofProb.at(A) = GenRandomFloat(DofVarSet);
	}
	if (PostiveSet.size()!=0&&ZeroSet.size()!=0)
	{
		A = GenRandomInt(ZeroSet);
		B = GenRandomInt(PostiveSet);
		Chrom.VulnerableLinkDofProb.at(A) = Chrom.VulnerableLinkDofProb.at(B);
		Chrom.VulnerableLinkDofProb.at(B) = 0.0f;
	}

}

// void increasdof(double &NowDof, vector<double> DofVarSet){
void increasdof(double &NowDof, double &NowDofProb, vector<pair<double,double>> DofVarSet){

	// if (isEqual(NowDof, DofVarSet.back())) return;
	if (isEqual(NowDof, DofVarSet.back().first)) return;
	for (unsigned int i = 0; i < DofVarSet.size();i++)
	{
		if (isEqual(NowDof,DofVarSet.at(i).first))
		{
			NowDof = DofVarSet.at(i + 1).first;
			NowDofProb = DofVarSet.at(i + 1).second;
			return;
		}
	}
}

void decreaseDof(double &NowDof,double &NowDofProb, vector<pair<double, double>> DofVarSet){
	if (isEqual(NowDof, DofVarSet.begin()->first)) return;
	for (unsigned int i = 0; i < DofVarSet.size();i++)
	{
		if (isEqual(NowDof,DofVarSet.at(i).first))
		{
			NowDof = DofVarSet.at(i - 1).first;
			NowDofProb = DofVarSet.at(i-1).second;
		}
	}
}

