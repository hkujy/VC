#include "CommonHeaders.h"
//#include "DefGloVar.h"

using namespace std;

Procedure VCprocedure;
int IniInterFace(ObjectManager &manager, GRAPH &MyNet);
bool ReadModelParas();
void Evaluate_By_Removing(GRAPH &_g, ObjectManager &_man);
void Evaluate_One_by_Restore_from_Disruption(GRAPH &_g, ObjectManager &_ma);

/***********************************************/
/*allow to pass through the origin node*/
/*this could produce close benchmark results in sioux fall network*/
bool OriginVersionForbidReturn2Zone = false;
//bool OriginVersionForbidReturn2Zone = true;
/******************************************/

int main(int argc, char *argv[])
{

	// Step. 1: Read para

	if (!ReadModelParas()) cerr << "Read Model Fails" << endl;// Must before
	mf.IniFiles();

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
#ifdef DEBUG
	std::cout << "PRECISION = "<<params.getParam("PRECISION") << endl;
	std::cout <<"NETWORK = "<< params.getParam("NETWORK") << endl;
	std::cout <<"OD_MATRIX = "<< params.getParam("OD_MATRIX") << endl;
	std::cout << "Remark: If the assignment method is FW/BFW/CFW, need to double check the initialization function" << endl;
#endif // DEBUG

#pragma endregion
	NumNodes = manager.getNet()->getNbNodes();
	NumLinks = manager.getNet()->getNbLinks();
	NumOD = manager.getODMatrix()->getNbODPairs();
	
	GRAPH MyGraph;
	IniInterFace(manager, MyGraph);
	MyGraph.CreateOriginSet();
	MyGraph.CreateNodes();

	if (VCprocedure == Procedure::EvalEachOneByRemove)
	{
		cout << "------C++ TEST CASE: Evaluate Each Link Measure By Removing the link------" << endl;
		Evaluate_By_Removing(MyGraph, manager);
	}
	else if (VCprocedure == Procedure::EvalBaseAndOneNet)
	{
		cout << "------C++ TEST CASE: Evaluate One Base Net and One disrupted scenario------" << endl;
		Evaluate_By_Removing(MyGraph, manager);
	}
	else if (VCprocedure == Procedure::RecoverOne)
	{
		cout << "-------Test on recover of a sequence of links-------" << endl;
		cout <<"Warning: This Should NOT Be Called" << endl;
		system("PAUSE");
		Evaluate_One_by_Restore_from_Disruption(MyGraph, manager);
	}

	return 0;

}