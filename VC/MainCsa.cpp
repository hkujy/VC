#include "CommonHeaders.h"
#include "RandomFuncs.h"
using namespace std;
bool ReadSeedVec(std::vector<int> &SeedVec,
	FILE *fin){
	int SeedValue;
	SeedVec.clear();
	if (nullptr == fin){
		perror("Read Seed File Fails \n");
		return false;
	}
	else
	{
		while (!feof(fin))
		{
			fscanf_s(fin, "%i",
				&SeedValue);
			if (SeedValue != EOF){
				SeedVec.push_back(SeedValue);
			}
		}
	}
	//SeedVec.erase(SeedVec.begin()+SeedVec.size()-1);

	return true;
}
/*Main program to test CSA*/
int CsaTestMain(GRAPH &BaseGraph,vector<CHROME> &BestSol, vector<double> &CpuTimeVec, ObjectManager &manager)
{
		vector<int> SeedVec;
		FILE * fin;
#pragma region ReadSeed
		fopen_s(&fin, "c://GitCodes//ResiV2//Input//Seed.txt", "r");
		if (!ReadSeedVec(SeedVec, fin)) TRACE("Read Seed File Fails \n");
		fin = nullptr;
#pragma endregion
		ofstream ConvergeFile;
		ConvergeFile.open("c://GitCodes//ResiV2///OutPut//CSAconverge.txt",ios::app);
		assert(ConvergeFile.is_open());
		int NumClone = (int)(CsaCloneBeta*CsaNumPop);
		int NumRep = (int)(CsaRepRatio*CsaNumPop);
		if (NumClone == 0 || NumRep == 0) { cerr << "Csa Num population is not read" << endl;system("pause"); }
		// initialize Csa Parameters
		Algorithms CsaTest(CsaNumPop, NumClone, NumRep);
		CsaTest.init(BaseGraph, manager);
		// compute base values
		BaseGraph.EvaluteGraph(manager,manager.getEqAlgo());
		CsaTest.BaseUNPM = BaseGraph.UNPM;
#ifdef DEBUG
		cout << "BaseUNPM=" << BaseGraph.UNPM << endl;
#endif // DEBUG
		for (unsigned int i = 0; i < SeedVec.size();i++)
		{
			clock_t ST = clock();
			GenRan.seed((unsigned)SeedVec.at(i));
			if (isWriteConverge == file) ConvergeFile << "SeedNum," << (unsigned)SeedVec.at(i) << endl;

			CsaTest.CSAmain(BaseGraph, CsaNumPop, NumClone, NumRep, ConvergeFile, manager);
			BestSol.push_back(CsaTest.Chroms.at(0));
			clock_t ET = clock();
			CpuTimeVec.push_back((double)(ET - ST) / CLOCKS_PER_SEC); // time unit is second
			cout <<"Csa: seed = "<<i<< ", BestSolu =" << BestSol.back().Fitness << endl;
			if (WriteOutTo == screen) cout<< "BestSolu," << BestSol.back().Fitness << endl;
			if (WriteOutTo == both){ ConvergeFile << "BestSolu," << BestSol.back().Fitness << endl; 
				cout << "BestSolu," << BestSol.back().Fitness << endl;
			}
	}
		
		ConvergeFile.close();
		return 1;
}