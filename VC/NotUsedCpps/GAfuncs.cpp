#include "CommonHeaders.h"
#include <assert.h>
#include <math.h>       /* pow */
#include "RandomFuncs.h"
using namespace std;

void RecordSolVal(double &SolFit, double &CurrentBest, int &NumCount, ofstream &fout);
void Algorithms::GAselectParent(int &Father, int &Mother,const int NumPop){

	double LargeConst = 1e+30;
	vector<double> Prob(NumPop + 1, 0.0f);
	double sumFit = 0.0;
	for (auto c = this->Chroms.begin(); c < this->Chroms.begin() + NumPop; c++)
	{
		//sumFit += c->Fitness;
		sumFit += c->Fitness*LargeConst;
		//cout << c->Fitness << "," << sumFit << endl;
	}	
	assert(sumFit > 0);
	Prob.at(0) = 0.0f;
	for (int i = 0; i <NumPop;i++)
	{
		Prob.at(i + 1) = Prob.at(i) + (this->Chroms.at(i).Fitness*LargeConst) / sumFit;// cumulative prob
		//Prob.at(i + 1) = Prob.at(i) + (this->Chroms.at(i).Fitness)/(sumFit);// cumulative prob
	}

	double f=GenRandomReal();
	for (size_t i = 0; i < Prob.size()-1;i++)
	{
		if (f >= Prob.at(i) && f<Prob.at(i+1))
		{
			Father = (int) i;
			break;
		}
	}
	int whilecounter = 0;
	do
	{
		double m = GenRandomReal();
		for (size_t i = 0; i < Prob.size() - 1; i++)
		{
			if (m >= Prob.at(i) && m < Prob.at(i + 1))
			{
				Mother = (int)i;
				break;
			}
		}
		whilecounter++;
	} while (Father == Mother&&whilecounter<=100);

}

void Algorithms::GACrossOver(CHROME &Father, CHROME &Mother, CHROME &BigBro, CHROME &CuteSis)
{
	//step: 1 sect a location
	int pos;
	do
	{
		// pos = GenRandomPos((unsigned int)this->LinkVarSet.size() - 1);
		pos = GenRandomPos((unsigned int)this->LinkVarSet.size() - 1);
	} while (pos == 0);
	if (BigBro.VulnerableLinks.size() == 0 || CuteSis.VulnerableLinks.size() == 0)
	{
		BigBro.VulnerableLinks.assign(Father.VulnerableLinks.size(), 0);
		BigBro.VulnerableLinkDof.assign(Father.VulnerableLinks.size(), 0.0f);
		BigBro.VulnerableLinkDofProb.assign(Father.VulnerableLinks.size(), 0.0f);
		CuteSis.VulnerableLinks.assign(Father.VulnerableLinks.size(), 0);
		CuteSis.VulnerableLinkDof.assign(Father.VulnerableLinks.size(), 0.0f);
		CuteSis.VulnerableLinkDofProb.assign(Father.VulnerableLinks.size(), 0.0f);
	}
	for (int i = 0; i < pos; i++)
	{
		BigBro.VulnerableLinks.at(i) = Father.VulnerableLinks.at(i);
		BigBro.VulnerableLinkDof.at(i) = Father.VulnerableLinkDof.at(i);
		BigBro.VulnerableLinkDofProb.at(i) = Father.VulnerableLinkDofProb.at(i);
		CuteSis.VulnerableLinks.at(i) = Mother.VulnerableLinks.at(i);
		CuteSis.VulnerableLinkDof.at(i) = Mother.VulnerableLinkDof.at(i);
		CuteSis.VulnerableLinkDofProb.at(i) = Mother.VulnerableLinkDofProb.at(i);
	}
	for (size_t i = pos; i < this->LinkVarSet.size(); i++)
	{
		BigBro.VulnerableLinks.at(i) = Mother.VulnerableLinks.at(i);
		BigBro.VulnerableLinkDof.at(i) = Mother.VulnerableLinkDof.at(i);
		BigBro.VulnerableLinkDofProb.at(i) = Mother.VulnerableLinkDofProb.at(i);
		CuteSis.VulnerableLinks.at(i) = Father.VulnerableLinks.at(i);
		CuteSis.VulnerableLinkDof.at(i) = Father.VulnerableLinkDof.at(i);
		CuteSis.VulnerableLinkDofProb.at(i) = Father.VulnerableLinkDofProb.at(i);
	}
	BigBro.Fitness = 0.0f;
	BigBro.UNPM = 0.0f;
	BigBro.TotalCost = 0.0f;
	BigBro.ImpactValue = 0.0f;
	BigBro.SolProb = 0.0f;
	CuteSis.Fitness = 0.0f;
	CuteSis.UNPM = 0.0f;
	CuteSis.TotalCost = 0.0f;
	CuteSis.ImpactValue = 0.0f;
	CuteSis.SolProb = 0.0;

}

void Algorithms::GAmain(GRAPH &Graph, const int NumPop, const int NumChild, ofstream &ConvergeFile,ObjectManager &manager)
{
	//phase 1 Generate Initial Solution
	ofstream fsolconv;   // write file of the best solutions
	fsolconv.open("c://GitCodes//VC//OutPut//GAConvergeBasedOnSol.txt", ios::app);
	double CurrentBestFitness = -1.0f;
	int NumSolEvaluated = 0;

	for (int i = 0; i < NumPop; i++)
	{
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
Repeat:
	IterCounter++;
	int Father, Mother;
	for (int i = 0; i < NumChild;i = i+2)
	{
		this->GAselectParent(Father, Mother, NumPop);
		int BigBro = NumPop + i;
		int CuteSis = NumPop + i + 1;
		this->GACrossOver(this->Chroms.at(Father), this->Chroms.at(Mother),
			this->Chroms.at(BigBro), this->Chroms.at(CuteSis));
		//cout << "after cross over size = " << Chroms.at(0).Links.size() << endl;
		if (GenRandomReal() <= GaMutationRate)
		{
			bool isRepeat;
			do
			{
				isRepeat = false;
				this->HyperMutateMain(this->Chroms.at(BigBro));
				for (int kk = 0; kk < BigBro; kk++)
				{
					if (this->Chroms.at(BigBro).isSame(this->Chroms.at(kk)))
					{
						isRepeat = true;
						break;
					}
				}
			} while (isRepeat);
			do
			{
				isRepeat = false;
				this->HyperMutateMain(this->Chroms.at(CuteSis));
				for (int kk = 0; kk < CuteSis; kk++)
				{
					if (this->Chroms.at(CuteSis).isSame(this->Chroms.at(kk)))
					{
						isRepeat = true;
						break;
					}
				}
			} while (isRepeat);
		}
				
		//cout << "after mutation size = " << Chroms.at(0).Links.size() << endl;
		this->Chroms.at(BigBro).getSolProb();
		Chroms.at(BigBro).EvaluateSol(Graph, BaseUNPM,manager);
		RecordSolVal(Chroms.at(BigBro).Fitness, CurrentBestFitness, NumSolEvaluated, fsolconv);
		
		if (StopCriteria == 1&& NumSolEvaluated >= MaxNumSolEval)
		{
			goto FinalSort;
		}

		this->Chroms.at(CuteSis).getSolProb();
		Chroms.at(CuteSis).EvaluateSol(Graph, BaseUNPM,manager);
		RecordSolVal(Chroms.at(CuteSis).Fitness, CurrentBestFitness, NumSolEvaluated, fsolconv);
	
		if (StopCriteria == 1&& NumSolEvaluated >= MaxNumSolEval)
		{
			goto FinalSort;
		}
	}
FinalSort:
	this->SortSol((unsigned int)Chroms.size());

	if (WriteOutTo == both)
	{
		if(isWriteConverge) ConvergeFile << IterCounter << "," << this->Chroms.at(0).Fitness << endl;
		cout << "GAiter = "<<IterCounter << ", CurrentBest = " << this->Chroms.at(0).Fitness << endl;
	}
	if (isWriteConverge == file&&isWriteConverge)
	{
	 	ConvergeFile << IterCounter << "," << this->Chroms.at(0).Fitness << endl;
	}
	if (WriteOutTo == screen)
	{
		cout << "GAiter = "<<IterCounter << ", CurrentBest = " << this->Chroms.at(0).Fitness << endl;
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

		if (IterCounter < MaxGAIter) goto Repeat;
		else
		{
			fsolconv.close();
			return;
		}
	}
	fsolconv.close();
}