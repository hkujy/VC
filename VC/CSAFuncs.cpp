#include "CommonHeaders.h"
#include <assert.h>
#include <math.h>       /* pow */
#include "RandomFuncs.h"
using namespace std;
void GenerateCloneSet(const vector<CHROME> &Chroms, const int NumPop, const int NumClone,
	vector<int> &CloneSet);
// the compare class is from http://www.cplusplus.com/reference/algorithm/sort/
struct CompareStruct {
	bool operator() (const CHROME &A, CHROME &B) { return (A.Fitness > B.Fitness); }
} SortDecent;
void SetDofAndProb(const std::vector<pair<double, double>> &Vec,
	double &setdof, double &setdofprob, bool isExlcudeZero = false);

//double GenRandomFloat(const std::vector<pair<double,double>> &Vec);
Algorithms::Algorithms(int NumPop, int NumClone, int NumRep)
{
	//Pop solution
	CHROME ts;
	int idCount = 0;
	for (int i = 0; i < NumPop; i++)
	{
		ts.ID = idCount;
		this->Chroms.push_back(ts);
		idCount++;
	}
	// clone
	for (int i = 0; i < NumPop / 2; i++)
	{
		for (int j = 0; j < NumClone; j++)
		{
			ts.ID = idCount;
			this->Chroms.push_back(ts);
			idCount++;
		}
	}
	// Rep
	for (int i = 0; i < NumRep; i++)
	{
		ts.ID = idCount;
		this->Chroms.push_back(ts);
		idCount++;
	}
	//NodeVarSet.reserve(NumNodes);
	//NodeDofVarSet.reserve(NumNodes);

	LinkVarSet.reserve(NumLinks);
	LinkDofSet.reserve(NumLinks);
	AlgorithmIndex = CSA;
};
Algorithms::Algorithms(int NumPop, int NumChild){

	//Pop solution
	CHROME ts;
	int idCount = 0;
	for (int i = 0; i < NumPop; i++)
	{
		ts.ID = idCount;
		this->Chroms.push_back(ts);
		idCount++;
	}
	// child
	for (int i = 0; i < NumChild; i++)
	{
		ts.ID = idCount;
		this->Chroms.push_back(ts);
		idCount++;
	}
	LinkVarSet.reserve(NumLinks);

	AlgorithmIndex = GA;
}
/*Cound the number of solution variables that requires to be recorded*/
void RecordSolVal(double &SolFit, double &CurrentBest,int &NumCount,ofstream &fout){
	if (SolFit>CurrentBest)
	{
		CurrentBest = SolFit;
	}
	NumCount++;
	if (WriteOutTo==screen)
		cout <<"------NumSolCount = "<<NumCount << ", CurrentBest = " << CurrentBest << endl;
	if (isWriteConverge==file&&isWriteConverge) fout << NumCount << "," << CurrentBest << endl;
	if (WriteOutTo==both)
	{
		cout <<"------NumSolCount = "<<NumCount << ", CurrentBest = " << CurrentBest << endl;
		if (isWriteConverge) fout << NumCount << "," << CurrentBest << endl;
	}
}


Algorithms::~Algorithms(){
	this->Chroms.clear();
	//NodeVarSet.clear();
	//NodeDofVarSet.clear();
};
void Algorithms::SortSol(unsigned int Num)
{
	//cout << (this->Chroms.begin() + Num)->ID << endl;
	std::sort(this->Chroms.begin(), this->Chroms.begin() + Num, SortDecent);
	MaxFitValue = Chroms.begin()->Fitness;
	MinFitValue = (Chroms.begin() + Num - 1)->Fitness;

	bool allZero = true;
	for each (auto val in this->Chroms.at(0).VulnerableLinkDof)
	{
		if (val > 0) allZero = false;
	}
	if (allZero)
		cout << "problem id = " << Chroms[0].ID<< endl;

	for (int i = 0; i < Chroms.size(); i++)
	{
		Chroms[i].ID = i;
	}
	//assert(MinFitValue >= -10.0);
};



int Algorithms::GenerateSol(int ChromIndex)
{
	#pragma region OldGenerationMethod
	/******************Random generation procedure***************/
	//vector<int> CandiSet(NodeVarSet);

	//int pos = -1;
	///*this->Chroms.at(ChromIndex).Nodes.clear();
	//this->Chroms.at(ChromIndex).Dof.clear();*/
	//for (unsigned int i = 0; i < NodeVarSet.size(); i++)
	//{
	//	pos = GenRandomPos((unsigned int)CandiSet.size());
	//	//this->Chroms.at(ChromIndex).Nodes.push_back(NodeVarSet.at(pos));
	//	this->Chroms.at(ChromIndex).Nodes.push_back(CandiSet.at(pos));
	//	CandiSet.erase(CandiSet.begin() + pos);
	//	this->Chroms.at(ChromIndex).NodeDof.push_back(GenRandomdouble(NodeDofVarSet));
	//}
	/*******************************************/
	/******************Secquence***************/
	//vector<int> CandiSet(NodeVarSet);
	// for (size_t i = 0; i < NodeVarSet.size(); i++)
	// {
	// 	//cout << "************This is for debug purpose and need to be revised afterwards***********" << endl;
	// 	this->Chroms.at(ChromIndex).VulnerableNodes.push_back(NodeVarSet.at(i));
	// 	this->Chroms.at(ChromIndex).VulnerableNodeDof.push_back(GenRandomFloat(NodeDofVarSet));
	// }
	#pragma endregion O
	double dof,dofprob;
	for (size_t i = 0; i < LinkVarSet.size(); i++)
	{
		this->Chroms.at(ChromIndex).ID = ChromIndex;
		this->Chroms.at(ChromIndex).VulnerableLinks.push_back(LinkVarSet.at(i));
		SetDofAndProb(LinkDofSet[i],dof,dofprob);
		this->Chroms.at(ChromIndex).VulnerableLinkDof.push_back(dof);
		this->Chroms.at(ChromIndex).VulnerableLinkDofProb.push_back(dofprob);
	}

	return 1;
};


//Original Colone section
void Algorithms::CSAmain(GRAPH &Graph, int NumPop, int NumClone, int NumRep, ofstream &ConvergeFile,
	ObjectManager &manager)
{
	//phase 1
	ofstream fsolconv; // converge based on the solution count
	fsolconv.open("c://GitCodes//ResiV2//OutPut//CSAConvergeBasedOnSol.txt",ios::app);
	double CurrentBestFitness = -1.0f;
	int NumSolEvaluated = 0;
	int IdCount = NumPop;
	for (int i = 0; i < NumPop; i++)
	{
		//cout << "Evaluate solution " << i << endl;
		bool isRepeat = false;
		do
		{
			this->Chroms.at(i).clear();
			GenerateSol(i);
			isRepeat = false;
			for (int j = 0; j <= i; j++)
			{
				if (j == i) break;
				if (this->Chroms.at(i).isSame(this->Chroms.at(j)))
				{
					isRepeat = true;
					break;
				}
			}
		} while (isRepeat);
		this->Chroms.at(i).getSolProb();
		Chroms.at(i).EvaluateSol(Graph, BaseUNPM, manager);
		RecordSolVal(Chroms.at(i).Fitness, CurrentBestFitness, NumSolEvaluated, fsolconv);
	}

	int IterCounter = 0;
	this->SortSol((unsigned int)NumPop);
	vector<int> CloneSet(NumClone, -1);
Repeat:
	IterCounter++;
	IdCount = NumPop;
	GenerateCloneSet(this->Chroms, NumPop, NumClone, CloneSet);
	//phase 2
	// clone: for half solution each colon 
	for (size_t i = 0; i < CloneSet.size();i++)
	{
		Chroms.at(IdCount).Copy(Chroms.at(CloneSet.at(i)));
		bool isRepeat;
		do
		{
			isRepeat = false;
			this->HyperMutateMain(Chroms.at(IdCount));
			for (int kk = 0; kk <= IdCount; kk++)
			{
				if (kk == IdCount) break;
				if (this->Chroms.at(IdCount).isSame(this->Chroms.at(kk)))
				{
					isRepeat = true;
					break;
				}
			}
		} while (isRepeat);
		Chroms.at(IdCount).getSolProb();
		Chroms.at(IdCount).EvaluateSol(Graph, BaseUNPM, manager);
		RecordSolVal(Chroms.at(IdCount).Fitness, CurrentBestFitness, NumSolEvaluated, fsolconv);
		
	
		if (StopCriteria == 1&& NumSolEvaluated >= MaxNumSolEval)
		{
			goto FinalSort;
		}
	
		IdCount++;

	}
		
	for (int i = 0; i < NumRep; i++)
	{
		bool isRepeat = false;
		do
		{
			this->Chroms.at(IdCount).clear();
			GenerateSol(IdCount);
			isRepeat = false;
			for (int j = 0; j <= IdCount; j++)
			{
				if (j == IdCount) break;
				if (this->Chroms.at(IdCount).isSame(this->Chroms.at(j)))
				{
					isRepeat = true;
					break;
				}
			}
		} while (isRepeat);
		Chroms.at(IdCount).EvaluateSol(Graph, BaseUNPM, manager);
		this->Chroms.at(IdCount).getSolProb();
		RecordSolVal(Chroms.at(IdCount).Fitness, CurrentBestFitness, NumSolEvaluated, fsolconv);
	
		if (StopCriteria == 1&& NumSolEvaluated >= MaxNumSolEval)
		{
			goto FinalSort;
		}
	
		IdCount++;
	}
FinalSort:
	this->SortSol((unsigned int)Chroms.size());

	if (WriteOutTo == screen)
	{
		cout <<"CasIter = "<<IterCounter << ", CurrentBest = " << this->Chroms.at(0).Fitness << endl;
	}
	if (isWriteConverge == file&&isWriteConverge)
	{
		ConvergeFile << IterCounter << "," << this->Chroms.at(0).Fitness << endl;
	}
	if (WriteOutTo == both)
	{
		if (isWriteConverge) ConvergeFile << IterCounter << "," << this->Chroms.at(0).Fitness << endl;
		cout <<"CasIter = "<<IterCounter << ", CurrentBest = " << this->Chroms.at(0).Fitness << endl;
	}
	
	if (StopCriteria == 1)
	{
		if (NumSolEvaluated >= MaxNumSolEval)
		{
			fsolconv.close();
			return;
		}
		else goto Repeat;
	}
	if (StopCriteria == 0)
	{
		if (IterCounter < MaxCsaIter) goto Repeat;
		else 
		{
			fsolconv.close();
			return;
		}
	}
}
