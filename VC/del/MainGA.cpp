#include "CommonHeaders.h"
#include "RandomFuncs.h"
using namespace std;
bool ReadSeedVec(std::vector<int> &SeedVec, FILE *fin);
int GATestMain(GRAPH &BaseGraph,  vector<CHROME> &BestSol,
	vector<double> &CpuTimeVec, ObjectManager &manager)
{

	try
	{
		vector<int> SeedVec;
		FILE * fin;
		//step 1: read CSA seed parameter
		fopen_s(&fin, "c://GitCodes//VC//Input//Seed.txt", "r");
		if (!ReadSeedVec(SeedVec, fin)) TRACE("Read Seed File Fails \n");
		fin = nullptr;
		ofstream ConvergeFile;
		ConvergeFile.open("c://GitCodes//VC///OutPut//GAconverge.txt", ios::app);
		Algorithms GATest(GANumPop,GANumChild);
		GATest.init(BaseGraph, manager);
		BaseGraph.EvaluteGraph(manager,manager.getEqAlgo());
		GATest.BaseUNPM = BaseGraph.UNPM;
#ifdef DEBUG
		cout << "BaseUNPM=" << BaseGraph.UNPM << endl;
		cout << ",unpm=" << BaseGraph.UNPM << endl;
#endif // DEBUG
	for (unsigned int i = 0; i < SeedVec.size(); i++)
		{
			clock_t ST = clock();
			GenRan.seed((unsigned)SeedVec.at(i));
			if (WriteOutTo == file)	ConvergeFile << "SeedNum,"<< (unsigned)SeedVec.at(i) << endl;
			GATest.GAmain(BaseGraph, GANumPop, GANumChild, ConvergeFile,manager);
			BestSol.push_back(GATest.Chroms.at(0));
			if (WriteOutTo == file) ConvergeFile << "BestSolu," << BestSol.back().Fitness<< endl;
			clock_t ET = clock();
			CpuTimeVec.push_back((double)(ET - ST) / CLOCKS_PER_SEC); // time unit is second
			cout << "GA: seed = " << i << ", BestSolu =" << BestSol.back().Fitness << endl;
		}

		ConvergeFile.close();
		return 1;
	}
	catch (exception& e)
	{
		TRACE("%s", e);
		return 0;
	}
}