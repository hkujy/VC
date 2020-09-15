#include "CommonHeaders.h"
#include "DefGloVar.h"

using namespace std;

int IniInterFace(ObjectManager &manager, GRAPH &MyNet);
bool ReadModelParas();

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
	//MyGraph.ReadVunLinks("C:\\GitCodes\\VC\\Input\\" + NetworkName + "_VulnerableLinks.txt");
	MyGraph.ReadVunLinks(mf.rootfolder + "Input\\" + NetworkName + "_VulnerableLinks.txt");
	if (WriteOutTo == file || WriteOutTo == both) cout << "Output converge file" << endl;
	else std::cout << "converge file is not written" << endl;
// step 1 solve a base network 
	MyGraph.NowVulLink = -1;  // representing the base graph, 
	//MyGraph.EvaluteGraph(manager, manager.getEqAlgo());
	//system("PAUSE");


	// todo 
	//1. after evaluate the network, set the link cost to be infinity 
	//2. for the annh him network, the zone nected the links
	//3. that is why there is no other links 
	//4. need to ensure that these LINKs can not be removed
	//
	for (int l = 0; l < MyGraph.VulnerableLinks.size(); l++)
	{
		CHROME VunSol;
		std::cout << "link = " << MyGraph.VulnerableLinks.at(l) << ",";
		std::cout << "Dof = " << MyGraph.VulnerableLinksDof[l].at(0).first << ",";
		std::cout << "Pro = " << MyGraph.VulnerableLinksDof[l].at(0).second << endl;
		int linkId = MyGraph.VulnerableLinks.at(l);
		// check the node of the link
		//curNode->getIsZone()
		int tail = manager.getNet()->getLink(linkId)->getNodeFrom();
		int head = manager.getNet()->getLink(linkId)->getNodeTo();
		//if (manager.getNet()->getnod)
		if (manager.getNet()->getNodeWithLinks(tail)->getIsZone())
		{
			std::cout << "Node:" << tail << " is a zone node" << endl;
		}
		if (manager.getNet()->getNodeWithLinks(head)->getIsZone())
		{
			std::cout << "Node:" << head << " is a zone node" << endl;
		}
		// complete check
		for (int lol = 0; lol < MyGraph.Nodes.at(tail).OutLinks.size(); lol++)
		{
			std::cout << "Leaving link index = " << MyGraph.Nodes.at(tail).OutLinks.at(lol)->ID << endl;
		}
		if (manager.getNet()->getNodeWithLinks(tail)->getIsZone())
		{
			if (MyGraph.Nodes.at(tail).OutLinks.size() == 1) {
				std::cout << "********The tail node is a zone and there is only one link leaving the node" << std::endl;
				continue;
			}
		}
		std::cout << MyGraph.Links.at(l).T0 << std::endl;
		//
		system("PAUSE");
		VunSol.VulnerableLinks.push_back(MyGraph.VulnerableLinks.at(l));
		VunSol.VulnerableLinkDof.push_back(MyGraph.VulnerableLinksDof[l].at(0).first);
		VunSol.VulnerableLinkDofProb.push_back(MyGraph.VulnerableLinksDof[l].at(0).second);
		MyGraph.NowVulLink = MyGraph.VulnerableLinks.at(l);
		manager.setAlgoNull();
		VunSol.EvaluateSol(MyGraph, manager);
	}
	std::cout << "Cheers" << endl;
	return 0;

}