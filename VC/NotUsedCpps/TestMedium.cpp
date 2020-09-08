#include "CommonHeaders.h"
using namespace std;

//int ScanMedium(GRAPH &BaseGraph, vector<CHROME> &BestSol, const NODEPROMATRIX &Pmatrix, const LINKPROMATRIX &LinkMatrx,ObjectManager &manager);
int CsaTestMain(GRAPH &BaseGraph,vector<CHROME> &BestSol, vector<double> &CpuTimeVec, ObjectManager &manager); 
int GATestMain(GRAPH &BaseGraph, vector<CHROME> &BestSol, vector<double> &CpuTimeVec, ObjectManager &manager);
void OutputSummary(vector<CHROME> &BestSol, GRAPH &Graph, vector<double> &CpuTime, ObjectManager &manager);
//void ReadDataMain(GRAPH &BaseGraph, NODEPROMATRIX &Pmatrix);
bool ReadModelParas();
int TestMedium(ObjectManager &manager, GRAPH &BaseGraph)
{
	int ErrMsg = -1;
	//ModelIndex = 1; //medium size network is test
	cout << "medium size network is testing" << endl;

	if (!ReadModelParas()) cerr << "Read Model Fails" << endl;// Must before 
	AssertLog.open("..//OutPut//AssertLog.txt", ios::trunc);
	// step 2: Initialize basic parameters
	vector<CHROME> BestSol;
	vector<double> CpuTimeVec;
	//cout << "Start test CSA on Medium " << endl;
	string testindicator;
	cout << "1: Test Medium csa" << endl;
	cout << "2: Test Medium scan" << endl;
	cout << "3: Test Medium both" << endl;
	cin >> testindicator;
	ofstream  fSummay;

	if (testindicator.compare("2") == 0) goto Scan;

	cout << "start test CSA " << endl;
	clock_t ST = clock();
	ErrMsg = CsaTestMain(BaseGraph,BestSol, CpuTimeVec,manager);
	clock_t ET = clock();
	CpuTimeVec.push_back((double)(ET - ST) / CLOCKS_PER_SEC); // time unit is second
	cout << "CSA Complete " << endl;
	OutputSummary(BestSol, BaseGraph, CpuTimeVec,  manager);

	fSummay.open("..//OutPut//Summary.txt", ios::app);
	fSummay << "The following results from scan" << endl;

	if (testindicator.compare("1") == 0) return 0;
Scan:
	cout << "Start Scan Medium " << endl;
	ST = clock();
	fSummay << "start time is " << ST << endl;
	//ErrMsg = ScanMedium(BaseGraph, BestSol, NodeProbMatrix, LinkProbMatrix,manager);
	ET = clock();
	fSummay << "end time is " << ET << endl;
	CpuTimeVec.push_back((double)(ET - ST) / CLOCKS_PER_SEC); // time unit is second
	cout << "Scan Medium Complete " << endl;
	fSummay << "duration is " << (double)(ET - ST) / CLOCKS_PER_SEC<<" seconds" << endl;
	
	OutputSummary(BestSol, BaseGraph, CpuTimeVec, manager);

	return 0;

}