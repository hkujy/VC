#include "CommonHeaders.h"
#include "DefGloVar.h"


using namespace std;
void OpenAndCleanFiles();
int TuneCsaPara(ObjectManager &manager, GRAPH &BaseGraph);
int TestCSAandGA(ObjectManager &manager, GRAPH &MyNet);
void CloseFiles();
int IniInterFace(ObjectManager &manager, GRAPH &MyNet);
bool ReadModelParas();
void TestEnumerate(ObjectManager &manager, GRAPH &BaseGraph);

int CsaTestMain(GRAPH &BaseGraph, vector<CHROME> &BestSol, vector<double> &CpuTimeVec, ObjectManager &manager);
void OutputSummary(vector<CHROME> &BestSol, GRAPH &Graph, vector<double> &CpuTime, ObjectManager &manager);

//int pmain() 
int main(int argc, char *argv[])
{

	OpenAndCleanFiles();
	// step. 1 read para
	if (!ReadModelParas()) cerr << "Read Model Fails" << endl;// Must before
#pragma region ReadManagerNet
	// std::string dirConv = ""; std::string dirFlows = ""; std::string dirCounters = ""; std::string dirPathSet = "";
	std::string fileParams = "C:\\GitCodes\\ResiV2\\Input\\input.params";
	Params params;
	ParseParams parser;
	parser.execute(fileParams, &params);
	Timer objCreationTimer;
	ObjectManager manager(&params);
	//NetworkName = "SiouxFalls";
	params.setParameter("PRECISION",std::to_string(UEeps));
	params.setParameter("NETWORK", "C:\\GitCodes\\ResiV2\\Input\\" + NetworkName + "_net.txt");
	params.setParameter("OD_MATRIX", "C:\\GitCodes\\ResiV2\\Input\\" + NetworkName + "_trips.txt");
	//params.setParameter("SHOW_CONVERGENCE", "yes");  // if want to show the convergence
	params.setParameter("SHOW_CONVERGENCE", "");
	cout << "PRECISION = "<<params.getParam("PRECISION") << endl;
	cout <<"NETWORK = "<< params.getParam("NETWORK") << endl;
	cout <<"OD_MATRIX = "<< params.getParam("OD_MATRIX") << endl;
	cout <<"MaxNumSolStop = "<< MaxNumSolEval << endl;
	cout << "Remark: If the assignment method is FW/BFW/CFW, need to double check the initialization function" << endl;
	cout << "Current version do not deal the with case, in which the number of links != vunlerable links" <<endl;
#pragma endregion
	NumNodes = manager.getNet()->getNbNodes();
	NumLinks = manager.getNet()->getNbLinks();
	NumOD = manager.getODMatrix()->getNbODPairs();

	GRAPH MyGraph;
	IniInterFace(manager, MyGraph);
	MyGraph.CreateOriginSet();
	MyGraph.CreateNodes();
	MyGraph.ReadVunLinks("C:\\GitCodes\\ResiV2\\Input\\" + NetworkName + "_VulnerableLinks.txt");
	//isWriteConverge = screen; 

	//WriteOutTo = file;
	//isWriteConverge = false;
	//isWriteConverge = true;

	if (WriteOutTo == file || WriteOutTo == both) cout << "Output converge file" << endl;
	else cout << "converge file is not written" << endl;
	StopCriteria = -1;
	CSACloneMethod = 1; // proportion to the fitness value
	//CSACloneMethod = 0; // proportion to the fitness value
	// step 2
	//cout << "Case 1: TestNagurenyNetwork" << endl;
	//cout << "Case 2: TestMedium" << endl;
	//cout << "Case 3: TestAlgorithmPara" << endl;
	//cout << "Case 4: TestCSAandGA" << endl;
	//TestNagurenyNetwork(); 
	//TestMedium();
	//TestAlgorithmPara();
	//TuneCsaPara(manager,MyGraph);
	//MaxNumSolEval = 20;
	vector<CHROME> BestSol;
	vector<double> CpuTimeVec;
	vector<double> BestSolSummary;
	int ErrMsg;
	switch (TestIndex)
	{
	case 0:
		TestEnumerate(manager, MyGraph);
		StopCriteria = 1;
		BestSol.clear();
		CpuTimeVec.clear();
		ErrMsg = CsaTestMain(MyGraph, BestSol, CpuTimeVec, manager);
		OutputSummary(BestSol, MyGraph, CpuTimeVec, manager);
		cout << "Complete CSA Criteria " << StopCriteria << endl;

		break;
	case 1:
		TestCSAandGA(manager,MyGraph);
		break;
	default:
		break;
	}

	CloseFiles();
	
	cout << "Cheers" << endl;
	return 0;

}