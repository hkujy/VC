﻿#include "CommonHeaders.h"
#include "DefGloVar.h"

using namespace std;
MyFiles mf;

int IniInterFace(ObjectManager &manager, GRAPH &MyNet);
bool ReadModelParas();
void TestEnumerate(ObjectManager &manager, GRAPH &BaseGraph);
void OutputSummary(vector<CHROME> &BestSol, GRAPH &Graph, vector<double> &CpuTime, ObjectManager &manager);
//int pmain() 

int main(int argc, char *argv[])
{

// step 0: set root folder and clean files
	//OpenAndCleanFiles();
	// step. 1 read para

	if (!ReadModelParas()) cerr << "Read Model Fails" << endl;// Must before
#pragma region ReadManagerNet
	std::string fileParams = mf.rootfolder + "Input\\input.params";
	Params params;
	ParseParams parser;
	parser.execute(fileParams, &params);
	Timer objCreationTimer;
	ObjectManager manager(&params);
	//NetworkName = "SiouxFalls";
	params.setParameter("PRECISION",std::to_string(UEeps));
	params.setParameter("NETWORK", mf.rootfolder + "Input\\" + NetworkName + "_net.txt");
	params.setParameter("OD_MATRIX", mf.rootfolder + "Input\\" + NetworkName + "_trips.txt");
	//params.setParameter("SHOW_CONVERGENCE", "yes");  // if want to show the convergence
	params.setParameter("SHOW_CONVERGENCE", "");
	cout << "PRECISION = "<<params.getParam("PRECISION") << endl;
	cout <<"NETWORK = "<< params.getParam("NETWORK") << endl;
	cout <<"OD_MATRIX = "<< params.getParam("OD_MATRIX") << endl;
	cout << "Remark: If the assignment method is FW/BFW/CFW, need to double check the initialization function" << endl;
#pragma endregion
	NumNodes = manager.getNet()->getNbNodes();
	NumLinks = manager.getNet()->getNbLinks();
	NumOD = manager.getODMatrix()->getNbODPairs();
	GRAPH MyGraph;
	IniInterFace(manager, MyGraph);
	MyGraph.CreateOriginSet();
	MyGraph.CreateNodes();
	//MyGraph.ReadVunLinks("C:\\GitCodes\\VC\\Input\\" + NetworkName + "_VulnerableLinks.txt");
	MyGraph.ReadVunLinks(mf.rootfolder + "Input\\" + NetworkName + "_VulnerableLinks.txt");
	if (WriteOutTo == file || WriteOutTo == both) cout << "Output converge file" << endl;
	else cout << "converge file is not written" << endl;
// step 1 solve a base network 
	MyGraph.NowVulLink = -1;  // representing the base graph, 
	MyGraph.EvaluteGraph(manager, manager.getEqAlgo());
	//system("PAUSE");

	CHROME VunSol;
	for (int l = 0; l < MyGraph.VulnerableLinks.size(); l++)
	{
		cout << "link = " << MyGraph.VulnerableLinks.at(l) << ",";
		cout << "Dof = " << MyGraph.VulnerableLinksDof[l].at(0).first << ",";
		cout << "Pro = " << MyGraph.VulnerableLinksDof[l].at(0).second << endl;
		VunSol.VulnerableLinks.push_back(MyGraph.VulnerableLinks.at(l));
		VunSol.VulnerableLinkDof.push_back(MyGraph.VulnerableLinksDof[l].at(0).first);
		VunSol.VulnerableLinkDofProb.push_back(MyGraph.VulnerableLinksDof[l].at(0).second);
		MyGraph.NowVulLink = MyGraph.VulnerableLinks.at(l);
		// only carry out the UE assignment
		VunSol.EvaluateSol(MyGraph, manager);
	}
	//vector<CHROME> BestSol;
	//vector<double> CpuTimeVec;
	//vector<double> BestSolSummary;
	//switch (TestIndex)
	//{
	//case 0:
	//	TestEnumerate(manager, MyGraph);
	//	StopCriteria = 1;
	//	BestSol.clear();
	//	CpuTimeVec.clear();
	//	//ErrMsg = CsaTestMain(MyGraph, BestSol, CpuTimeVec, manager);
	//	OutputSummary(BestSol, MyGraph, CpuTimeVec, manager);
	//	cout << "Complete CSA Criteria " << StopCriteria << endl;
	//	break;
	//case 1:
	//	TestCSAandGA(manager,MyGraph);
	//	break;
	//default:
	//	break;
	//}

	cout << "Cheers" << endl;
	return 0;

}