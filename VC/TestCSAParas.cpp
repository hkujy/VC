#include "CommonHeaders.h"
using namespace std;

int CsaTestMain(GRAPH &BaseGraph, vector<CHROME> &BestSol, vector<double> &CpuTimeVec, ObjectManager &manager);
int GATestMain(GRAPH &BaseGraph, vector<CHROME> &BestSol, vector<double> &CpuTimeVec, ObjectManager &manager);
void OutputSummary(vector<CHROME> &BestSol, GRAPH &Graph, vector<double> &CpuTime,ObjectManager &manager);
bool ReadModelParas();
