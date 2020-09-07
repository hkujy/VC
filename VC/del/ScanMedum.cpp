#include "CommonHeaders.h"
using namespace std;

void Enumerate(vector<CHROME> &Sol );
//
//int ScanMedium(GRAPH &BaseGraph, vector<CHROME> &BestSol,
//	const NODEPROMATRIX &NodeProbMatrix, const LINKPROMATRIX &LinkProbMatrx,ObjectManager &manager)
//{
//	try
//	{
//
//		//Step 0: compute basic value 
//		BaseGraph.EvaluteGraph(manager);
//		// step 1 enumerate all possibilities 
//		vector<CHROME> Sol;
//		EnumerateMedium(Sol, NodeProbMatrix);
//		double BaseUNPM = BaseGraph.UNPM;
//
//		CHROME tmc;
//		Sol.push_back(tmc);
//		BestSol.push_back(tmc);
//		BestSol.back().ImpactValue = 0.0;
//		BestSol.back().Fitness = 0.0;
//
//		//for (int i = 0; i < NumNodes; i++)
//		//{
//		//	//Sol.back().VulnerableNodes.push_back(i);
//		//	Sol.back().VulnerableLinks.push_back(i);
//		//}
//		/*0	0	0.8	0	0	0	0	0.6*/
//	/*	Sol.back().Dof.push_back(0.0f);
//		Sol.back().Dof.push_back(0.0f);
//		Sol.back().Dof.push_back(0.8f);
//		Sol.back().Dof.push_back(0.0f);
//		Sol.back().Dof.push_back(0.0f);
//		Sol.back().Dof.push_back(0.0f);
//		Sol.back().Dof.push_back(0.0f);
//		Sol.back().Dof.push_back(0.6f);
//		Sol.back().getSolProb(Pmatrix);*/
//
//		for (auto s = Sol.begin(); s != Sol.end(); s++ )
//		{
//			s->EvaluateSol(BaseGraph, BaseUNPM, NodeProbMatrix,LinkProbMatrx,manager);
//			//cout << "S->Fit = " << s->Fitness << endl;
//			//cout << "Best->Fit = " << BestSol.back().Fitness << endl;
//			if (s->Fitness > BestSol.back().Fitness)
//			{
//				BestSol.back().Copy(*s);
//			}
//		}
//#ifdef DEBUG
//		std::ofstream AllScanSol;
//		AllScanSol.open("..//OutPut//ScanSol.txt", ios::trunc);
//		for (auto s = Sol.begin(); s != Sol.end(); s++)
//		{
//			for (auto r = s->VulnerableNodeDof.begin(); r != s->VulnerableNodeDof.end(); r++)
//			{
//				AllScanSol << *r << ",";
//			}
//			AllScanSol << s->SolProb << ",";
//			AllScanSol << s->UNPM << ",";
//			AllScanSol << s->ImpactValue << ",";
//			AllScanSol << s->TotalCost << ",";
//			AllScanSol << s->ImpactValue * s->SolProb << ",";
//			AllScanSol << endl;
//		}
//#endif
//
//
//		return 1;
//	}
//	catch (exception& e)
//	{
//		TRACE("%s", e);
//
//		return 0;
//	}
//}
//void EnumerateNagureny(vector<CHROME> &Sol);

int ScanNagurenyNetwork(GRAPH &BaseGraph, vector<CHROME> &BestSol,ObjectManager &manager)
{
	try
	{

		//Step 0: compute basic value 

		BaseGraph.EvaluteGraph(manager,manager.getEqAlgo());
		// step 1 enumerate all possibilities 
		int NumSol = 0;
		vector<CHROME> Sol;
		//EnumerateNagureny(Sol );
		double BaseUNPM = BaseGraph.UNPM;

		CHROME tmc;
	/*	Sol.push_back(tmc);*/
		BestSol.push_back(tmc);
		BestSol.back().ImpactValue = 0.0;
		BestSol.back().Fitness = 0.0;

		int scount = 0;
		for (auto s = Sol.begin(); s != Sol.end(); s++)
		{
			s->EvaluateSol(BaseGraph, BaseUNPM,manager);
			if (s->Fitness > BestSol.back().Fitness)
			{
				BestSol.back().Copy(*s);
			}
			scount++;
		}
		std::ofstream AllScanSol;
		AllScanSol.open("..//OutPut//ScanSol.txt", ios::trunc);
		for (auto s = Sol.begin(); s != Sol.end(); s++)
		{
			//for (auto r = s->NodeDof.begin(); r != s->NodeDof.end(); r++)
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

		return 1;
	}
	catch (exception& e)
	{
		TRACE("%s", e);

		return 0;
	}
}