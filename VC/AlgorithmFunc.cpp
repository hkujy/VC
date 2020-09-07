#include "CommonHeaders.h"
#include "RandomFuncs.h"

using namespace std;


void Algorithms::init(GRAPH &Graph, ObjectManager &manager)
{
	for (int i = 0; i < Graph.VulnerableLinks.size(); ++i)
	{
		LinkVarSet.push_back(Graph.VulnerableLinks.at(i));
	}
	for (int i = 0; i < Graph.VulnerableLinks.size(); ++i)
	{
		// CsaTest.LinkDofVarSet.push_back(0);
		LinkDofSet.push_back(Graph.VulnerableLinksDof[i]);
	}
}

Algorithms::Algorithms()
{

	LinkVarSet.reserve(NumLinks);
	LinkDofSet.reserve(NumLinks);
	AlgorithmIndex = BruteForce;

}
void Algorithms::Enumerate(GRAPH &BaseGraph, ObjectManager &manager)
{

	clock_t ST = clock();


	init(BaseGraph,manager);
	if (BaseGraph.VulnerableLinks.size() != 10) cerr << "There should be only 5 vulnerable links" << endl;
	
	CHROME tmc;
	int scount = 0;

	int NumSol = 0;
#pragma region BrutefoceAllSolutions
	//for (int d0 = 0; d0 < LinkDofSet[0].size(); ++d0)
	//{
	//	for (int d1 = 0; d1 < LinkDofSet[1].size(); ++d1)
	//	{
	//		for (int d2 = 0; d2 < LinkDofSet[2].size(); ++d2)
	//		{
	//			for (int d3 = 0; d3 < LinkDofSet[3].size(); ++d3)
	//			{
	//				for (int d4 = 0; d4 < LinkDofSet[4].size(); ++d4)
	//				{
	//					for (int d5 = 0;d5 < LinkDofSet[5].size();++d5)
	//					{
	//						for (int d6 = 0;d6 < LinkDofSet[6].size();++d6)
	//						{
	//							for (int d7 = 0;d7 < LinkDofSet[7].size();++d7)
	//							{
	//								for (int d8 = 0;d8 < LinkDofSet[8].size();++d8)
	//								{
	//									for (int d9 = 0;d9 < LinkDofSet[9].size();++d9)
	//									{
	//										//if (NumSol==100) break;
	//										Chroms.push_back(tmc);
	//										Chroms.back().clear();
	//										Chroms.back().VulnerableLinks.push_back(LinkVarSet[0]);
	//										Chroms.back().VulnerableLinks.push_back(LinkVarSet[1]);
	//										Chroms.back().VulnerableLinks.push_back(LinkVarSet[2]);
	//										Chroms.back().VulnerableLinks.push_back(LinkVarSet[3]);
	//										Chroms.back().VulnerableLinks.push_back(LinkVarSet[4]);
	//										Chroms.back().VulnerableLinks.push_back(LinkVarSet[5]);
	//										Chroms.back().VulnerableLinks.push_back(LinkVarSet[6]);
	//										Chroms.back().VulnerableLinks.push_back(LinkVarSet[7]);
	//										Chroms.back().VulnerableLinks.push_back(LinkVarSet[8]);
	//										Chroms.back().VulnerableLinks.push_back(LinkVarSet[9]);
	//										Chroms.back().VulnerableLinkDof.push_back(LinkDofSet[0].at(d0).first);
	//										Chroms.back().VulnerableLinkDof.push_back(LinkDofSet[1].at(d1).first);
	//										Chroms.back().VulnerableLinkDof.push_back(LinkDofSet[2].at(d2).first);
	//										Chroms.back().VulnerableLinkDof.push_back(LinkDofSet[3].at(d3).first);
	//										Chroms.back().VulnerableLinkDof.push_back(LinkDofSet[4].at(d4).first);
	//										Chroms.back().VulnerableLinkDof.push_back(LinkDofSet[5].at(d5).first);
	//										Chroms.back().VulnerableLinkDof.push_back(LinkDofSet[6].at(d6).first);
	//										Chroms.back().VulnerableLinkDof.push_back(LinkDofSet[7].at(d7).first);
	//										Chroms.back().VulnerableLinkDof.push_back(LinkDofSet[8].at(d8).first);
	//										Chroms.back().VulnerableLinkDof.push_back(LinkDofSet[9].at(d9).first);
	//										Chroms.back().VulnerableLinkDofProb.push_back(LinkDofSet[0].at(d0).second);
	//										Chroms.back().VulnerableLinkDofProb.push_back(LinkDofSet[1].at(d1).second);
	//										Chroms.back().VulnerableLinkDofProb.push_back(LinkDofSet[2].at(d2).second);
	//										Chroms.back().VulnerableLinkDofProb.push_back(LinkDofSet[3].at(d3).second);
	//										Chroms.back().VulnerableLinkDofProb.push_back(LinkDofSet[4].at(d4).second);
	//										Chroms.back().VulnerableLinkDofProb.push_back(LinkDofSet[5].at(d5).second);
	//										Chroms.back().VulnerableLinkDofProb.push_back(LinkDofSet[6].at(d6).second);
	//										Chroms.back().VulnerableLinkDofProb.push_back(LinkDofSet[7].at(d7).second);
	//										Chroms.back().VulnerableLinkDofProb.push_back(LinkDofSet[8].at(d8).second);
	//										Chroms.back().VulnerableLinkDofProb.push_back(LinkDofSet[9].at(d9).second);
	//										Chroms.back().ID = NumSol;
	//										NumSol++;

	//									}
	//								}
	//							}
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//}


	cout << "total = " << Chroms.size() << endl;
#pragma endregion

	std::ofstream AllScanSol;
	AllScanSol.open("c://GitCodes//VC//OutPut//ScanSol.txt", ios::trunc);


	clock_t BaseST = clock();
	BaseGraph.EvaluteGraph(manager,manager.getEqAlgo());
	BaseUNPM = BaseGraph.UNPM;
	clock_t BaseET = clock();
	cout<<"Evaluate Base Time is "<<((double)(BaseET - BaseST) / CLOCKS_PER_SEC); // time unit is second

	vector<CHROME> BestSol;
	BestSol.push_back(tmc);
	BestSol.back().ImpactValue = 0.0;
	BestSol.back().Fitness = 0.0;

	for (auto s = Chroms.begin(); s != Chroms.end(); s++)
	{
		s->EvaluateSol(BaseGraph, BaseUNPM, manager);
		if (s->Fitness > BestSol.back().Fitness)
		{
			BestSol.back().Copy(*s);
		}
		scount++;
	}

	clock_t ET = clock();
	double CpuTime=((double)(ET - ST) / CLOCKS_PER_SEC); // time unit is second

	AllScanSol << "********Best Solution*********************************************"<<endl;
	for (auto r = BestSol.back().VulnerableLinkDof.begin(); r != BestSol.back().VulnerableLinkDof.end()-1; r++)
	{
		AllScanSol << *r << ",";
	}
	AllScanSol << BestSol.back().VulnerableLinkDof[BestSol.back().VulnerableLinkDof.size() - 1];
	AllScanSol << endl;
	AllScanSol << "Fit = " << BestSol.back().Fitness << endl;
	AllScanSol << "SolProb = " << BestSol.back().SolProb << endl;
	AllScanSol << "UNPM = "<<BestSol.back().UNPM <<endl;
	AllScanSol << "ImpactValue = "<<BestSol.back().ImpactValue << endl;
	AllScanSol << "TotalCost = "<<BestSol.back().TotalCost << endl;
	AllScanSol << "CpuTime = " << CpuTime << endl;
	
	AllScanSol << "********All Solution*******************************************" << endl;
	for (auto s = Chroms.begin(); s != Chroms.end(); s++)
	{
		for (auto r = s->VulnerableLinkDof.begin(); r != s->VulnerableLinkDof.end(); r++)
		{
			AllScanSol << *r << ",";
		}
		AllScanSol << s->SolProb << ",";
		AllScanSol << s->UNPM << ",";
		AllScanSol << s->ImpactValue << ",";
		AllScanSol << s->TotalCost << ",";
		AllScanSol << endl;
	}

	cout << "Brute Force is complete" << endl;

}