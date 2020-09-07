#include "CommonHeaders.h"
#include <assert.h>
#include <math.h>       /* pow */
using namespace std;

// input the p matrix and brute force all the impossibility 
//
//void Enumerate_Samll_1(vector<CHROME> &Sol)
//{
//	cout << "TODO: write enumerate small case" << endl;
//
//	// TOOD brute force on the sioux fall network 
//	//unsigned int n1 = 1, n2 = 2, n3 = 3;
//	//CHROME tmc;
//	//tmc.VulnerableNodes.push_back(1);
//	//tmc.VulnerableNodes.push_back(2);
//	//tmc.VulnerableNodes.push_back(3);
//	//for (unsigned int d1 = 0; d1 < Prob.Dof.size(); d1++)
//	//{
//	//	for (unsigned int d2 = 0; d2 < Prob.Dof.size(); d2++)
//	//	{
//	//		for (unsigned int d3 = 0; d3 < Prob.Dof.size(); d3++)
//	//		{
//	//			Sol.push_back(tmc);
//	//			Sol.back().VulnerableNodeDof.push_back(Prob.Dof.at(d1));
//	//			Sol.back().VulnerableNodeDof.push_back(Prob.Dof.at(d2));
//	//			Sol.back().VulnerableNodeDof.push_back(Prob.Dof.at(d3));
//
//	//			Sol.back().VulnerableNodeDofProb.push_back(Prob.Matrix[d1][n1]);
//	//			Sol.back().VulnerableNodeDofProb.push_back(Prob.Matrix[d2][n2]);
//	//			Sol.back().VulnerableNodeDofProb.push_back(Prob.Matrix[d3][n3]);
//
//	//		}
//	//	}
//	//}
//}
////
////void BruteForceFor3NodeSmall(NODEPROMATRIX &NodeProbMatrix,
////	GRAPH &Graph, LINKPROMATRIX &LinkMatrix, ObjectManager &manager)
////{
////	// step 1 enumerate all possibilities 
////	int NumSol = 0;
////	vector<CHROME> Sol;
////	Enumerate_Samll_1(Sol, NodeProbMatrix);
////
////	for (unsigned int i = 0; i < Sol.size(); i++)
////	{
////		for (unsigned int j = 0; j < Sol.at(i).VulnerableNodes.size(); j++) //each node associated with one degree
////		{
////			AssertLog << Sol.at(i).VulnerableNodeDof.at(j) << ",";
////		}
////		AssertLog << endl;
////	}
////	// step 2 compute base scenario 
////	Graph.EvaluteGraph(manager);
////	double BaseUNPM = Graph.UNPM;
////	for (auto s = Sol.begin(); s != Sol.end(); s++)
////	{
////		s->EvaluateSol(Graph, BaseUNPM, NodeProbMatrix, LinkMatrix,manager);
////	}
////	for (auto s = Sol.begin(); s != Sol.end(); s++)
////	{
////		assert(s->PrintSol(AssertLog));
////	}
////
////}
////
////

/*brute force on the Sioux fall network*/
void Enumerate(vector<CHROME> &Sol,GRAPH &BaseGraph)
{
	cout << "TODO: to write enumerate medium" << endl;

	if (BaseGraph.VulnerableLinks.size() != 5) cerr << "There should be only 5 vulnerable links" << endl;
	unsigned int n[5];
	for (unsigned int i = 0; i < 5; i++)
	{
		n[i] = i;
	}
	CHROME tmc;
	

	for (int i = 0; i < 5; i++)
	{
		tmc.VulnerableLinks.push_back(BaseGraph.VulnerableLinks[i]);
	}

	//int NumSol = 0;
	//for (int d0=0;d0<)
	//{
	//}


	//for (unsigned int d0 = 0; d0 < Prob.Dof.size(); d0++)
	//{
	//	for (unsigned int d1 = 0; d1 < Prob.Dof.size(); d1++)
	//	{
	//		for (unsigned int d2 = 0; d2 < Prob.Dof.size(); d2++)
	//		{
	//			for (unsigned int d3 = 0; d3 < Prob.Dof.size(); d3++)
	//			{
	//				for (unsigned int d4 = 0; d4 < Prob.Dof.size(); d4++)
	//				{
	//					for (unsigned int d5 = 0; d5 < Prob.Dof.size(); d5++)
	//					{
	//						for (unsigned int d6 = 0; d6 < Prob.Dof.size(); d6++)
	//						{
	//							for (unsigned int d7 = 0; d7 < Prob.Dof.size(); d7++)
	//							{

	//								//if (NumSol > 10) continue;
	//								Sol.push_back(tmc);
	//								Sol.back().VulnerableNodeDof.push_back(Prob.Dof.at(d0));
	//								Sol.back().VulnerableNodeDof.push_back(Prob.Dof.at(d1));
	//								Sol.back().VulnerableNodeDof.push_back(Prob.Dof.at(d2));
	//								Sol.back().VulnerableNodeDof.push_back(Prob.Dof.at(d3));
	//								Sol.back().VulnerableNodeDof.push_back(Prob.Dof.at(d4));
	//								Sol.back().VulnerableNodeDof.push_back(Prob.Dof.at(d5));
	//								Sol.back().VulnerableNodeDof.push_back(Prob.Dof.at(d6));
	//								Sol.back().VulnerableNodeDof.push_back(Prob.Dof.at(d7));
	//								Sol.back().VulnerableNodeDofProb.push_back(Prob.Matrix[d0][n[0]]);
	//								Sol.back().VulnerableNodeDofProb.push_back(Prob.Matrix[d1][n[1]]);
	//								Sol.back().VulnerableNodeDofProb.push_back(Prob.Matrix[d2][n[2]]);
	//								Sol.back().VulnerableNodeDofProb.push_back(Prob.Matrix[d3][n[3]]);
	//								Sol.back().VulnerableNodeDofProb.push_back(Prob.Matrix[d4][n[4]]);
	//								Sol.back().VulnerableNodeDofProb.push_back(Prob.Matrix[d5][n[5]]);
	//								Sol.back().VulnerableNodeDofProb.push_back(Prob.Matrix[d6][n[6]]);
	//								Sol.back().VulnerableNodeDofProb.push_back(Prob.Matrix[d7][n[7]]);
	//								NumSol++;
	//							}
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
}

//
//void EnumerateNagureny(vector<CHROME> &Sol)
//{
//
//	unsigned int n[5];   // number of links
//	for (unsigned int i = 0; i < 5; i++)
//	{
//		n[i] = i;
//	}
//	CHROME tmc;
//
//
//
//
//	for (int i = 0; i < 5; i++)
//	{
//		tmc.VulnerableLinks.push_back(i);
//	}
//	int NumSol = 0;
//	for (unsigned int d0 = 0; d0 < Prob.Dof.size(); d0++)
//	{
//		for (unsigned int d1 = 0; d1 < Prob.Dof.size(); d1++)
//		{
//			for (unsigned int d2 = 0; d2 < Prob.Dof.size(); d2++)
//			{
//				for (unsigned int d3 = 0; d3 < Prob.Dof.size(); d3++)
//				{
//					for (unsigned int d4 = 0; d4 < Prob.Dof.size(); d4++)
//					{
//
//						bool isRemove = false;
//						//if (NumSol > 10) continue;
//						Sol.push_back(tmc);
//						Sol.back().VulnerableLinkDof.push_back(Prob.Dof.at(d0));
//						Sol.back().VulnerableLinkDof.push_back(Prob.Dof.at(d1));
//						Sol.back().VulnerableLinkDof.push_back(Prob.Dof.at(d2));
//						Sol.back().VulnerableLinkDof.push_back(Prob.Dof.at(d3));
//						Sol.back().VulnerableLinkDof.push_back(Prob.Dof.at(d4));
//
//						Sol.back().VulnerableLinkDofProb.push_back(Prob.Matrix[d0][n[0]]);
//						Sol.back().VulnerableLinkDofProb.push_back(Prob.Matrix[d1][n[1]]);
//						Sol.back().VulnerableLinkDofProb.push_back(Prob.Matrix[d2][n[2]]);
//						Sol.back().VulnerableLinkDofProb.push_back(Prob.Matrix[d3][n[3]]);
//						Sol.back().VulnerableLinkDofProb.push_back(Prob.Matrix[d4][n[4]]);
//						NumSol++;
//						// exclude the dis connectivities cases
//
//						//if (Sol.back().LinkDof.at(3) > 0.9)
//						//{
//						//	if (Sol.back().LinkDof.at(0) > 0.99 ||
//						//		Sol.back().LinkDof.at(1) > 0.99)
//						//	{
//						//		isRemove = true;
//						//	}
//						//}
//						//if (Sol.back().LinkDof.at(4)> 0.9)
//						//{
//						//	if (Sol.back().LinkDof.at(0) > 0.9 ||
//						//		Sol.back().LinkDof.at(2) > 0.9)
//						//	{
//						//		isRemove = true;
//						//	}
//						//}
//						//if (isRemove) 
//						//{
//						//	Sol.pop_back();
//						//	NumSol--;
//						//}
//
//					}
//				}
//			}
//		}
//	}
//
//
//}