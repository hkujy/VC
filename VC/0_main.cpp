#include "CommonHeaders.h"
#include "DefGloVar.h"

using namespace std;

Procedure VCprocedure;
int IniInterFace(ObjectManager &manager, GRAPH &MyNet);
bool ReadModelParas();
void Evaluate_One_Remove(GRAPH &_g, ObjectManager &_man);
void Evaluate_One_RestoreBack(GRAPH &_g, ObjectManager &_ma);

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
	std::cout << "PRECISION = "<<params.getParam("PRECISION") << endl;
	std::cout <<"NETWORK = "<< params.getParam("NETWORK") << endl;
	std::cout <<"OD_MATRIX = "<< params.getParam("OD_MATRIX") << endl;
	std::cout << "Remark: If the assignment method is FW/BFW/CFW, need to double check the initialization function" << endl;
#pragma endregion
	NumNodes = manager.getNet()->getNbNodes();
	NumLinks = manager.getNet()->getNbLinks();
	NumOD = manager.getODMatrix()->getNbODPairs();
	GRAPH MyGraph;
	IniInterFace(manager, MyGraph);
	MyGraph.CreateOriginSet();
	MyGraph.CreateNodes();

	if (VCprocedure == Procedure::EvalOne)
	{
		cout << "------Evaluate Each Link Measure By Removing the link------" << endl;
		Evaluate_One_Remove(MyGraph, manager);
	}
	else if (VCprocedure == Procedure::RecoverOne)
	{
		cout << "-------Test on recover of a sequence of links-------" << endl;
		Evaluate_One_RestoreBack(MyGraph, manager);
	}

	return 0;

}