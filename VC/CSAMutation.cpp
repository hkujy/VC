#include "CommonHeaders.h"
#include <assert.h>
#include <math.h>       /* pow */
// #include "MutationFuncHeader.h"
#include "RandomFuncs.h"
using namespace std;

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


void SetDofAndProb(const std::vector<pair<double, double>> &Vec,
	double &setdof, double &setdofprob, bool isExlcudeZero = false);
int CaseIndex(double Fit, double MaxFit, double MinFit){
	double Fp = MaxFit - MinFit;
	assert(Fp >= 0.0f);
	if (Fit <= MaxFit&&Fit > MaxFit - 0.05f*Fp) return 0;
	if (Fit <= MaxFit - 0.05f*Fp&&Fit > MaxFit - 0.2f*Fp) return 1;
	if (Fit <= MaxFit - 0.20f*Fp&&Fit > MaxFit - 0.4f*Fp) return 2;
	if (Fit <= MaxFit - 0.4f*Fp&&Fit > MaxFit - 0.6f*Fp) return 3;
	if (Fit <= MaxFit - 0.6f*Fp&&Fit > MaxFit - 0.8f*Fp) return 4;
	if (Fit <= MaxFit - 0.8f*Fp&&Fit >= MinFit) return 5;
	return InvaildInt;
}

void Algorithms::FirstProcedure(CHROME &Chrom){

	double dof, dofprob;
	for (unsigned int i = 0; i < Chrom.VulnerableLinks.size(); i++)
	{
		SetDofAndProb(LinkDofSet[i],dof, dofprob);
		Chrom.VulnerableLinkDof.at(i) = dof;
		Chrom.VulnerableLinkDofProb.at(i) =dofprob;
	}
}

void Algorithms::addNewNode(CHROME &Chrom){
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
		int pos = -1;
		int Rnode = GenRandomInt(Chrom.VulnerableLinks,pos);// random select a node
		double OldValue = Chrom.VulnerableLinkDof.at(pos);
		double dof, dofprob;
		do
		{
			SetDofAndProb(LinkDofSet[pos],dof,dofprob);
		} while (isEqual(OldValue, dof));
		Chrom.VulnerableLinkDof.at(pos) = dof;
		Chrom.VulnerableLinkDofProb.at(pos) = dofprob;
	}
	else
	{
		int pos = -1;
		int Rnode = GenRandomInt(ZeroDofLinkSet, pos);// random select a node
		//int pos = InvaildInt;
		double dof, dofprob;
		for (unsigned int i = 0; i < Chrom.VulnerableLinks.size(); i++)
		{
			if (Chrom.VulnerableLinks.at(i) == Rnode) {
				do
				{
					SetDofAndProb(LinkDofSet[i],dof,dofprob,true);			
					Chrom.VulnerableLinkDof.at(i) = dof;
					Chrom.VulnerableLinkDofProb.at(i) = dofprob;
				} while (isEqual(Chrom.VulnerableLinkDof.at(i), 0.0f) );// generate non zero
			}
		}
	}
}

void Algorithms::removeNodeDof(CHROME &Chrom){
try
{
	int Pos = GenRandomPos((int)Chrom.VulnerableLinks.size());// 0 to size
	Chrom.VulnerableLinkDof.at(Pos) = 0.0f;
	Chrom.VulnerableLinkDofProb.at(Pos) =  LinkDofSet.at(Pos).at(0).second;
	/*Remark: the first Dof level must equals to zero*/
	assert(isEqual(LinkDofSet[Pos].at(0).first,0.0));
}
catch (exception &e){
	TRACE("%s", e);
}

}

void Algorithms::exchangeNodeDof(CHROME &Chrom){
	// if (isUseNodeMatrix) exchangeNodeDofFunc(Chrom,this->NodeDofVarSet);
	// exchangeNodeDofFunc(Chrom,this->LinkDofVarSet);

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
		int Pos;
		B = GenRandomInt(PostiveSet,Pos);
		Chrom.VulnerableLinkDof.at(B) = 0.0f;
		Chrom.VulnerableLinkDofProb.at(B) = LinkDofSet.at(B).at(0).second;
	}
	if (PostiveSet.size()==0)
	{
		int pos;
		A = GenRandomInt(ZeroSet,pos);
		double dof, dofprob;
		SetDofAndProb(LinkDofSet[A],dof, dofprob);
		Chrom.VulnerableLinkDof.at(A) = dof;
		Chrom.VulnerableLinkDofProb.at(A) = dofprob;
		// Chrom.VulnerableLinkDofProb.at(A) = GenRandomFloat(DofVarSet);
	}
	if (PostiveSet.size()!=0&&ZeroSet.size()!=0)
	{
		int pos;
		A = GenRandomInt(ZeroSet,pos);
		B = GenRandomInt(PostiveSet,pos);

		Chrom.VulnerableLinkDof[A] = Chrom.VulnerableLinkDof[B];
		Chrom.VulnerableLinkDofProb[A] =  Chrom.VulnerableLinkDofProb[B];
		Chrom.VulnerableLinkDof[B] = 0.0f;
		Chrom.VulnerableLinkDofProb[B] = LinkDofSet[B].at(0).second;

	}
}

void Algorithms::SecondProcedure(CHROME &Chrom, double Ratio){
	
	int NumOfRepeate = (int)((double)NumNodes*Ratio);
	std::vector<int> v = { 1, 2, 3 }; //a,b,c, three operators
	for (int i = 0; i < NumOfRepeate; i++)
	{
		int pos;
		int Index = GenRandomInt(v,pos);
		//cout << "index = " << Index<<endl;
		switch (Index)
		{
		//add a new failed node and assign it dof value
		case 1: addNewNode(Chrom); break;
		case 2: removeNodeDof(Chrom); break;
		case 3: exchangeNodeDof(Chrom); break;
		default:
			TRACE("SecondProcedure generate wrong Index");
			system("PAUSE");
			break;
		}
	}
	
}
int getMutationIndex(const double f)
{
	int MutatorIndex = -1;
	if (f < double(1.0f / 6.0f))
	{
		MutatorIndex = 0;
	}
	if (f < double(2.0f / 6.0f) && f >= double(1.0f / 6.0f))
	{
		MutatorIndex = 1;	
	}
	if (f < double(3.0f / 6.0f) && f >= double(2.0f / 6.0f))
	{
		MutatorIndex = 2;	
	}
	if (f < double(4.0f / 6.0f) && f >= double(3.0f / 6.0f))
	{
		MutatorIndex = 3;
	}
	if (f < double(5.0f / 6.0f) && f >= double(4.0f / 6.0f))
	{
		MutatorIndex = 4;
	}
	if (f <= double(6.0f / 6.0f) && f >= double(5.0f / 6.0f))
	{
		MutatorIndex = 5;  
	}
	return MutatorIndex;
}
void Algorithms::HyperMutateMain(CHROME &Chrom){

// Remark: 21-Oct-2019: It seems both GA and CSA use the same mutation index
	int MutatorIndex;  // from 1 to 5
	double f;
	switch (AlgorithmIndex)
	{
		case CSA:
			f = GenRandomReal();
			MutatorIndex = getMutationIndex(f); break;
		case GA:
			f = GenRandomReal();
			MutatorIndex = getMutationIndex(f); break;
			#pragma region oldMutationIndex
			// if (f < double(1.0f / 6.0f))
			// {
			// 	MutatorIndex = 0;	break;
			// }
			// if (f < double(2.0f / 6.0f) && f >= double(1.0f / 6.0f))
			// {
			// 	MutatorIndex = 1;	break;
			// }
			// if (f < double(3.0f / 6.0f) && f >= double(2.0f / 6.0f))
			// {
			// 	MutatorIndex = 2;	break;
			// }
			// if (f < double(4.0f / 6.0f) && f >= double(3.0f / 6.0f))
			// {
			// 	MutatorIndex = 3;	break;
			// }
			// if (f < double(5.0f / 6.0f) && f >= double(4.0f / 6.0f)) 
			// {
			// 	MutatorIndex = 4;	break;
			// }
			// if (f <= double(6.0f / 6.0f) && f >= double(5.0f / 6.0f))
			// {
			// 	MutatorIndex = 5;
			// 	break;
			// }
			#pragma endregion 
		
	default:
		cerr << "Algorithm index is not proper defined" << endl;
		system("PAUSE");
		break;
	}
	
	switch (MutatorIndex)
	{
	case 0:
		// random increase or decrease 
		for (unsigned int i = 0; i < Chrom.VulnerableLinkDof.size();i++)
		{
			if (GenRandomReal()>=0.5f) 
			{
				increasdof(Chrom.VulnerableLinkDof.at(i), Chrom.VulnerableLinkDofProb.at(i), LinkDofSet.at(i));
			}

			else decreaseDof(Chrom.VulnerableLinkDof.at(i), Chrom.VulnerableLinkDofProb.at(i), LinkDofSet.at(i));
		}
		break;
	case 1:
		if (GenRandomReal() <= 0.1f) this->FirstProcedure(Chrom);
		else this->SecondProcedure(Chrom, 0.2f);
		break;
	case 2:
		if (GenRandomReal() <= 0.2f) this->FirstProcedure(Chrom);
		else this->SecondProcedure(Chrom, 0.4f);
		break;
	case 3:
		if (GenRandomReal() <= 0.3f) this->FirstProcedure(Chrom);
		else this->SecondProcedure(Chrom, 0.6f);
		break;
	case 4:
		if (GenRandomReal() <= 0.4f) this->FirstProcedure(Chrom);
		else this->SecondProcedure(Chrom, 0.8f);
		break;
	case 5:
		if (GenRandomReal() <= 0.5f) this->FirstProcedure(Chrom);
		else this->SecondProcedure(Chrom, 1.0f);
		break;
	default:	
		TRACE("CSA Hypermutation main generates wrong Index");
		system("PAUSE");
		break;
	}

};