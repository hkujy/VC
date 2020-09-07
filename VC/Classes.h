
#ifndef MyClasses
#define MyClasses
#include <vector>
#include <map>
#include <direct.h> // _getcwd
#include "Parameters.h"
#include "TempleteFunc.h"
#include "GlobalVar.h"
#include "..\MyAssign\ObjectManager.h"
using namespace std;

class LINK
{
	// Tail ---> Head 
public:
	int ID;
	int Tail;
	int Head;
	double T0;
	double CaInput;
	double CaRevise;
	double Cost;
	double Flow;
	double AlphaBpr; // parameter in the BPR  // 0.15
	double BetaBBpr; // parameter in the BPR  // 4.0
	double CleanLinkFlow();
	double BPRCost();
	double IniCost();
	void IniCap();
	LINK();
	LINK(const LINK& OtherLink);
	~LINK();
};

class NODE
{
	// Head ---> Tail
public:
	int ID;
	std::vector<const LINK*> OutLinks;
	std::vector<const LINK*> InLinks;
	NODE(){
		OutLinks.reserve(10);
		InLinks.reserve(10);
	}
	~NODE(){
		OutLinks.clear();
		InLinks.clear();
	}
};

class OD
{
public:
	int ID;
	int Orign;
	int Dest;
	double Demand;
	double MinCost;
	bool isConnected;
	OD(){
		Orign = InvaildInt;
		Dest = InvaildInt;
		isConnected = false;
		Demand = InvaildFloat;
		MinCost = InvaildFloat;
	}
	~OD(){
		Orign = InvaildInt;
		Dest = InvaildInt;
		isConnected = false;
		Demand = InvaildFloat;
		MinCost = InvaildFloat;
	}
};

class OriginBasedOD
{
public:
	int Onode;
	std::vector<const OD*>  ODset;
	OriginBasedOD(){
		Onode = InvaildInt;
		ODset.reserve(NumNodes);
	};
	~OriginBasedOD(){
		Onode = InvaildInt;
		ODset.clear();
	}
};

class GRAPH
{
public:
	std::vector<OD> OdPairs;
	std::vector<LINK> Links;
	std::vector<NODE> Nodes;
	std::vector<OriginBasedOD> OriginSet;
	std::vector<int> VulnerableLinks;
	std::vector<vector<pair<double,double>>>  VulnerableLinksDof;
	int NowVulLink;
	double UNPM;
	double TotalSystemCost;
	int **MinPathPredLink;
	GRAPH();
	~GRAPH();
	/*Shortest Path*/
	int SP(const int Orig, std::vector<double> &Lable);
	/*Update minimum cost of all routes*/
	int FindMinCostRoutes();
	/*Old flank wolf method for UE*/
	int FW_UE();
	/**Create origin set data**/
	void CreateOriginSet();
	/**Create forward and backward node-link structure**/
	void CreateNodes();
	/*print link*/
	int PrintLinks(std::ofstream &fout);
	int PrintOD(std::ofstream &fout);
	int PrintSp(int Orign, int Dest, std::ofstream &fout);
	/*read vulunerable links*/
	void ReadVunLinks(string VunerableFileName);
	/**Compute graph total cost and UNPM**/
	//void EvaluteGraph(ObjectManager &Man);
	void EvaluteGraph(ObjectManager &Man, DecoratedEqAlgo *algo);
	void PrintGraph(ObjectManager &Man);
	friend class CHROME;
	friend class Algorithms;
};

class TEST
{
public:
	int getID() const {return ID;}
	void setID(int _id) {ID=_id;}
	TEST(){ ID = InvaildInt; }
private:
	int ID;
};

class CHROME // ==  scenario
{
public:
	int ID;
	vector<int> VulnerableLinks;
	vector<double> VulnerableLinkDof;
	vector<double> VulnerableLinkDofProb;
	double SolProb;
	double TotalCost;
	double UNPM;
	double ImpactValue;
	double Fitness;
	/*clear the chromsome values*/
	void clear();
	/*evaluate a solution*/
	void EvaluateSol(GRAPH &Graph, const double BaseUNPM, ObjectManager &manager);
	/*evaluate a solution*/
	void EvaluateSol(GRAPH &Graph, ObjectManager &manager);
	/*Revise capacity*/
	void ReviseCap(GRAPH &Graph, ObjectManager &manager);
	/*set original capacity*/
	void IniCap(GRAPH &Graph,ObjectManager &manager);
	/*get scenario probability*/
	double getSolProb();
	/*print sol*/
	void Copy(const CHROME& FromSource); // does not copy solution ID
	bool isSame(const CHROME &CompareSource);
	CHROME();
	~CHROME();
	friend class Algorithms;
};

class Algorithms // ==  scenario
{
public:
	double BaseUNPM;
	/*max fitness values*/
	double MaxFitValue;
	/*minmium fitness values*/
	double MinFitValue;
	AlgorithmType AlgorithmIndex;  // 1: CSA, 2:GA
	/*each link has it own degree of failure*/
	vector<int> LinkVarSet;
	/*for each link, there is a vector record the dof and dofprob*/
	std::vector<vector<pair<double, double>>>  LinkDofSet;
	vector<CHROME> Chroms;
	/*generate inital solution*/
	void init(GRAPH &Graph, ObjectManager &manager);
	void Enumerate(GRAPH &BaseGraph, ObjectManager &manager);

	//Algorithms(int NumPop, int NumClone, int NumRep);//CSA
	//Algorithms(int NumPop, int NumChild);//GA
	Algorithms();  // enuerate
	//~Algorithms();
};


class MyFiles
{
public:
	std::ofstream printOD;
	std::ofstream printLink;
	std::ofstream printSummary;
	std::ofstream printModelPara;
	std::ofstream printLog;
	std::string rootfolder;
	MyFiles() { set_root_folder(); IniFiles(); };
	~MyFiles()
	{
		printOD.close(); printLink.close(); printSummary.close();
		printModelPara.close(); printLog.close();
	};
	void IniFiles()
	{
		printOD.open(rootfolder + "OutPut//" + "OD.txt", ios::trunc);
		printOD << "VulLink,Origin,Dest,ODIndex,Demand,UECost" << endl;
		printLink.open(rootfolder + "OutPut//" + "Link.csv", ios::trunc);
		printLink << "VulLink,ID,Tail,Head,T0,Flow,Cap,Alpha,Beta,Cost" << endl;
		printModelPara.open(rootfolder + "OutPut//" + "ModelPara.csv", ios::trunc);
		printSummary.open(rootfolder + "OutPut//" + "Summary.", ios::trunc);
		printLog.open(rootfolder + "OutPut//" + "MsgLog.csv", ios::trunc); printLog.close(); printLog.clear();
		printLog.open(rootfolder + "OutPut//" + "Log.txt", ios::trunc);
	}
	void set_root_folder()
	{
		char* buffer;
		if ((buffer = _getcwd(NULL, 0)) == NULL) perror("_getcwd error");
		string ff(buffer);
		std::vector<std::string> SubStrs, ResidualStr;
		std::string::size_type Sub1Begin, Sub1End;
		Sub1Begin = 0;
		SubStrs.clear();
		Sub1End = ff.find("\\");
		do
		{
			SubStrs.push_back(ff.substr(Sub1Begin, Sub1End - Sub1Begin));
			Sub1Begin = Sub1End + 1;
			Sub1End = ff.find("\\", Sub1End + 1);
		} while (Sub1End != std::string::npos);
		SubStrs.push_back(ff.substr(Sub1Begin, Sub1End - Sub1Begin));
		for (size_t i = 0; i < SubStrs.size() - 1; i++)
		{
			if (SubStrs[i + 1]._Equal("VC"))
			{
				rootfolder = rootfolder + SubStrs[i];
				break;
			}
			else
			{
				rootfolder = rootfolder + SubStrs[i] + "\\";
			}
		}
		rootfolder = rootfolder + "\\VC\\";
	}
};

extern MyFiles mf;

#endif