
#include "Classes.h"
#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <stdlib.h>
#include "CommonHeaders.h"


int FromAlgToMyNet(ObjectManager &manager, GRAPH &MyNet)
{
	try
	{
		LINK tl;
		NODE nd;
		OD ww;
		for (auto l = manager.getNet()->beginOnlyLink(); l != NULL; l = manager.getNet()->getNextOnlyLink())
		{
			// push node
			MyNet.Links.push_back(tl);
			MyNet.Links.back().ID = l->getIndex();
			MyNet.Links.back().Tail = l->getNodeFrom();
			MyNet.Links.back().Head = l->getNodeTo();
			MyNet.Links.back().T0 = l->getTime();
			MyNet.Links.back().CaInput = l->getLinkFnc()->getCapacity();
			MyNet.Links.back().CaRevise = l->getLinkFnc()->getCapacity();
			MyNet.Links.back().AlphaBpr = l->getLinkFnc()->getAlpha();
			MyNet.Links.back().BetaBBpr = l->getLinkFnc()->getPower();
		}
		for (auto n = manager.getNet()->beginNode(); n != NULL; n = manager.getNet()->getNextNode())
		{
			//std::cout << n->getID() << "," << std::endl;
			MyNet.Nodes.push_back(nd);
			MyNet.Nodes.back().ID = n->getID();
		}

		for (ConstOriginIterator it = manager.getODMatrix()->begin(); it != manager.getODMatrix()->end(); ++it)
		{
			Origin* origin = *it;
			for (PairODIterator destIt = origin->begin(); destIt != origin->end(); ++destIt)
			{
				PairOD* dest = *destIt;
				//std::cout << "origin = " << origin->getIndex() << "dest =" << dest->getIndex() << "demand =" << dest->getDemand()<<std::endl;
				MyNet.OdPairs.push_back(ww);
				MyNet.OdPairs.back().ID = dest->getODIndex();
				MyNet.OdPairs.back().Orign = origin->getIndex();
				MyNet.OdPairs.back().Dest = dest->getIndex();
				MyNet.OdPairs.back().Demand = dest->getDemand();
			}
		}
	}
	catch (Error error)
	{
		std::cout << "Error has occurred during execution: " << error.getMessage() << std::endl;
		return 0;
	}
	return 1;
}

int IniObjManger(ObjectManager &manager)
{
	try
	{
	
	}
	catch (Error error)
	{
		std::cout << "Error has occurred during execution: " << error.getMessage() << std::endl;
		return 0;
	}
	return 1;
}
/** convert manager to my network **/
int IniInterFace(ObjectManager &manager, GRAPH &MyNet)
{
try
{
	FromAlgToMyNet(manager, MyNet);
	cout<<"Complete Network Conversion"<<endl;
#ifdef DEBUG
	MyNet.PrintLinks(AssertLog);
	MyNet.PrintOD(AssertLog);
#endif
	return 1;
	cout<<"Complete tranfer manger to my own network"<<endl;
}
catch (Error error) 
{
	std::cout << "Error has occurred during execution: " << error.getMessage() << std::endl;
	return 0;

}

}


int AssignMain() {
	try {
		// For registering total CPU time 
		Timer timer; // time is started being measured on object creation
		srand((unsigned)time(NULL));

		//std::string fileParams = argv[1];
		//
		std::string dirConv = "";
		std::string dirFlows = "";
		std::string dirCounters = "";
		std::string dirPathSet = "";

		std::string fileParams = "C:\\GitCodes\\Assign\\input.params";
		Params params;
		ParseParams parser;
		parser.execute(fileParams, &params);

		Timer objCreationTimer;
		ObjectManager manager(&params);

		DecoratedEqAlgo *algo = manager.getEqAlgo(dirConv, dirFlows);
		FPType objCreationTime = objCreationTimer.getTimePassed();

		StarNetwork *cn = manager.getNet();


		Timer exeTimer;
		int nbIter = algo->execute();

		FPType executionTime = exeTimer.getTimePassed();

		FPType maxDiffTest = Utils::checkFeasibility(manager.getNet(), manager.getODMatrix());

		FPType timePassed = timer.getTimePassed();
		std::stringstream ss;
		ss << "<TotalTime> : {" << timePassed << "}; <ObjectCreationTime> : {" << objCreationTime <<
			"}; <InitialisationTime> : {" << algo->getInitialisationTime() <<
			"}; <ExecutionTime> : {" << executionTime <<
			"}; <ConvTime> : {" << algo->getTotalConvTime() <<
			"}; <PureIterationTime> : {" << algo->getTotalPureIterTime() <<
			"}; <NodeFlowFeasibilityMaxChange> : {" << maxDiffTest <<
			"}; <nbIter> : {" << nbIter << "};\n";
		std::cout << ss.str();

		if (params.getParam("PATH_SET") != "") {
			std::string filename = params.getParam("PATH_SET");
			if (filename == "AUTO")
				filename = dirPathSet + params.getAutoFileName() + ".paths";
			PathSetPrinterToFile writePathSet(manager.getODMatrix()); //, *manager.getTolls());
			writePathSet.writePathSetToFile(manager.getPathSet(), filename);
		}

		if (params.getParam("LATEX_OUTPUT") != "") {
			std::cout << "Writing latex file to: " << params.getParam("LATEX_OUTPUT") <<
				std::endl;

			LatexNetOutput latex(manager.getNet());
			latex.printToLaTeX(params.getParam("NODES"), params.getParam("LATEX_OUTPUT"),
				true, 0.3);
		}

	}
	catch (Error error) {
		std::cout << "Error has occurred during execution: " << error.getMessage() << std::endl;
		return 1;
	}

	return 0;
};
