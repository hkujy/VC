#include "CommonHeaders.h"
using namespace std;

int CsaTestMain(GRAPH &BaseGraph, vector<CHROME> &BestSol, vector<double> &CpuTimeVec, ObjectManager &manager);
int GATestMain(GRAPH &BaseGraph, vector<CHROME> &BestSol, vector<double> &CpuTimeVec, ObjectManager &manager);
void OutputSummary(vector<CHROME> &BestSol, GRAPH &Graph, vector<double> &CpuTime, ObjectManager &manager);




void TestEnumerate(ObjectManager &manager, GRAPH &BaseGraph)
{
	Algorithms Brute;
	Brute.Enumerate(BaseGraph, manager);
}


int TestCSAandGA(ObjectManager &manager, GRAPH &BaseGraph)
{
	int ErrMsg = -1;
	// step 2: Initialize basic parameters
	vector<CHROME> BestSol;
	vector<double> CpuTimeVec;
	vector<double> BestSolSummary;
	/// TEST CSA

	cout << "Remark: Stop Criteria = 0: total number iter for the algorithm" << endl;
	cout << "Remark: Stop Criteria = 1: total number of solution evaluated" << endl;
	for (StopCriteria = 0; StopCriteria < 2; StopCriteria++)
	{
		if (StopCriteria == 0)
		{
			cout << "only compare fixed number of number of solutions" << endl;
			continue;
		}
		BestSol.clear();
		CpuTimeVec.clear();
		ErrMsg = CsaTestMain(BaseGraph, BestSol, CpuTimeVec,manager);
		OutputSummary(BestSol, BaseGraph, CpuTimeVec, manager);
		for (int i = 0; i < (int)BestSol.size(); i++)
		{
			BestSolSummary.push_back(BestSol[i].Fitness);
		}
		cout << "Complete CSA Criteria " << StopCriteria << endl;
	}
	
	cout << "**************test Csa is Ok***************" << endl;

	cout << "just test clone method =0" << endl;
	//return 0;
	/// TEST GA
	for (StopCriteria = 0; StopCriteria < 2; StopCriteria++)
	{
		if (StopCriteria == 0)
		{
			cout << "only compare fixed number of number of solutions" << endl;
			continue;
		}
		BestSol.clear();
		CpuTimeVec.clear();
		ErrMsg = GATestMain(BaseGraph, BestSol, CpuTimeVec,manager);
		OutputSummary(BestSol, BaseGraph, CpuTimeVec, manager);
		for (int i = 0; i < (int) BestSol.size(); ++i)
		{
			BestSolSummary.push_back(BestSol[i].Fitness);
		}
		cout << "Complete GA Criteria " << StopCriteria << endl;
	}

	std::ofstream BestSolSumFile;
	BestSolSumFile.open("c://GitCodes//ResiV2//OutPut//BestSolSummar.txt", ios::trunc);
	BestSolSumFile << "*****Best solution obtained from each seed" << endl;

	BestSolSumFile << "CSAStopCrtier1,CSAStopCriter2,GAstopCriter1,GAStopCriter2" << endl;
	int NumSeed =(int) BestSolSummary.size() / 4;
	for (int i = 0; i < NumSeed; i++)
	{
		BestSolSumFile << BestSolSummary.at(i) << ",";
		BestSolSumFile << BestSolSummary.at(i + NumSeed) << ",";
		BestSolSumFile << BestSolSummary.at(i + 2 * NumSeed) << ",";
		BestSolSumFile << BestSolSummary.at(i + 3 * NumSeed) << ",";
		BestSolSumFile << endl;
	}

	return 0;

}

int TuneCsaPara(ObjectManager &manager, GRAPH &BaseGraph)
{
	int ErrMsg = -1;
	//ModelIndex = 3; //SiouxFallsNetwork
	ofstream RemarkFile;
	AssertLog.open("c://GitCodes//ResiV2//OutPut//AssertLog.txt", ios::trunc);
	RemarkFile.open("c://GitCodes//ResiV2//OutPut//TestRemark.txt", ios::trunc);

	//RemarkFile << "This test is adjust CsaConle Beta from 0.2 to 1.0" << endl;
	RemarkFile << "This test is adjust CsaRepRatio from 0.2 to 1.0" << endl;
	CsaCloneBeta = 0.2f;
	for (int i = 0; i < 5; i++)
	{
		CsaRepRatio = 0.2f + i * 0.2f;
		vector<CHROME> BestSol;
		vector<double> CpuTimeVec;
		ErrMsg = CsaTestMain(BaseGraph, BestSol, CpuTimeVec, manager);
		//ErrMsg = GATestMain(BaseGraph, NodeProbMatrix, LinkProbMatrix, BestSol, CpuTimeVec);
		//DebugMain();
		OutputSummary(BestSol, BaseGraph, CpuTimeVec, manager);
	}
	AssertLog.close();
	RemarkFile.close();

	return 0;

}