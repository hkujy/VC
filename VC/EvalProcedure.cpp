#include "CommonHeaders.h"
#include "DefGloVar.h"
using namespace std;

void disruptOneLink(GRAPH &_g, ObjectManager &_man, const int _lid);
void restoreOneLink(GRAPH &_g, ObjectManager &_man, const int _lid);
//void disruptOneLink(GRAPH &_g, ObjectManager &_man,const int _lid)
//{
//	_g.disruptLink(_lid); _man.disruptLink(_lid);
//}
//void restoreOneLink(GRAPH &_g, ObjectManager &_man, const int _lid) {
//	_g.restoreLink(_lid);
//	double ca0 = _g.Links.at(_lid).CaInput;
//	double t0 = _g.Links.at(_lid).T0;
//	_man.restoreLink(_lid, t0, ca0);
//}
// this only applies to the full disruption
void GRAPH::disruptLink(const int _lid)
{
	this->Links.at(_lid).CaRevise = ZeroCap;
}
void GRAPH::restoreLink(const int _lid)
{
	this->Links.at(_lid).IniCap();
}
void ObjectManager::disruptLink(const int _lid)
{
	this->getNet()->getLink(_lid)->getLinkFnc()->setCapacity(ZeroCap);
	//this->getNet()->getLink(_lid)->getLinkFnc()->setFreeFlowTime(std::numeric_limits<FPType>::infinity());
	//this->getNet()->getLink(_lid)->setTime(std::numeric_limits<FPType>::infinity());
}
void ObjectManager::restoreLink(const int _lid,const double _t0,const double _ca0)
{
	this->getNet()->getLink(_lid)->getLinkFnc()->setCapacity(_ca0);
	this->getNet()->getLink(_lid)->getLinkFnc()->setFreeFlowTime(_t0);
	this->getNet()->getLink(_lid)->setTime(_t0);
}

// evaluate the and carry out UE for each component
void Evaluate_One_Remove(GRAPH &_g, ObjectManager &_man)
{

	_g.ReadVunLinks(mf.rootfolder + "Input\\" + NetworkName + "_VulnerableLinks.txt");

	if (WriteOutTo == file || WriteOutTo == both) cout << "Output converge file" << endl;
	else std::cout << "converge file is not written" << endl;
	// step 1 solve a base network 
	_g.NowVulLink = -1;  // representing the base graph, 
	_g.NowRecoverCase = -1;  // set the dummy value of the recover case
	_g.EvaluteGraph(_man, _man.getEqAlgo());
	// todo 
	//1. after evaluate the network, set the link cost to be infinity 
	//2. for the annhhim network, the zone connected the links
	//3. that is why there is no other links 
	//4. need to ensure that these LINKs can not be removed
	for (size_t l = 0; l < _g.VulnerableLinks.size(); l++)
	{
		CHROME VunSol;
		std::cout << "link = " << _g.VulnerableLinks.at(l) << ",";
		std::cout << "Dof = " << _g.VulnerableLinksDof[l].at(0).first << ",";
		std::cout << "Pro = " << _g.VulnerableLinksDof[l].at(0).second << endl;
		int linkId = _g.VulnerableLinks.at(l);
		// check the node of the link
		//curNode->getIsZone()
		int tail = _man.getNet()->getLink(linkId)->getNodeFrom();
		int head = _man.getNet()->getLink(linkId)->getNodeTo();
		cout << "Tail = " << tail << ", Head = " << head << endl;
		//if (manager.getNet()->getnod)
		if (_man.getNet()->getNodeWithLinks(tail)->getIsZone())
		{
			std::cout << "Node:" << tail << " is a zone node" << endl;
			system("PAUSE");
		}
		if (_man.getNet()->getNodeWithLinks(head)->getIsZone())
		{
			std::cout << "Node:" << head << " is a zone node" << endl;
			system("PAUSE");
		}
		//for (int lol = 0; lol < _g.Nodes.at(tail).OutLinks.size(); lol++)
		//{
		//	std::cout << "Leaving link index = " << _g.Nodes.at(tail).OutLinks.at(lol)->ID << endl;
		//}
		if (_man.getNet()->getNodeWithLinks(tail)->getIsZone())
		{
			if (_g.Nodes.at(tail).OutLinks.size() == 1) {
				std::cout << "********The tail node is a zone and there is only one link leaving the node" << std::endl;
				system("PAUSE");
				continue;
			}
		}
		VunSol.VulnerableLinks.push_back(_g.VulnerableLinks.at(l));
		VunSol.VulnerableLinkDof.push_back(_g.VulnerableLinksDof[l].at(0).first);
		VunSol.VulnerableLinkDofProb.push_back(_g.VulnerableLinksDof[l].at(0).second);
		_g.NowVulLink = _g.VulnerableLinks.at(l);
		_man.setAlgoNull();
		VunSol.EvaluateSol(_g, _man);
	}
	std::cout << "Cheers" << endl;

}
// evaluate the and carry out UE for each component
void Evaluate_One_RestoreBack(GRAPH &_g, ObjectManager &_man)
{
	// step 1 : read the initial disrupted network 
	_g.ReadIniDisrup(mf.rootfolder + "Input\\" + NetworkName + "_IniDisrupt.txt");
	cout << "*******************************************************" << endl;
	cout << "Check the input links" << endl;
	for (auto l:_g.IniDisruptLinks)
	{
		int tail = _man.getNet()->getLink(l)->getNodeFrom();
		int head = _man.getNet()->getLink(l)->getNodeTo();
		//if (manager.getNet()->getnod)
		if (_man.getNet()->getNodeWithLinks(tail)->getIsZone())
		{
			std::cout << "Node:" << tail << " is a zone node" << endl;
			system("PAUSE");
		}
		if (_man.getNet()->getNodeWithLinks(head)->getIsZone())
		{
			std::cout << "Node:" << head << " is a zone node" << endl;
			system("PAUSE");
		}
	}
	cout << "done" << endl;
	cout << "*******************************************************" << endl;
	//_g.NowRecoverCase = -99;
	//_g.EvaluteGraph(_man, _man.getEqAlgo());
	// step 2: compute the base network based on the disrupted scenario
	cout << "Start to evaluate the disrupted network as the base case" << endl;
	for (const auto &l:_g.IniDisruptLinks)
	{
		disruptOneLink(_g, _man, l);
	}
	_g.EvaluteGraph(_man, _man.getEqAlgo());
	cout << "done" << endl;
	cout << "*******************************************************" << endl;
	
	// step 3: for all the cases restore the links

	_g.NowRecoverCase = 0;
	_g.ReadRestoreCase(mf.rootfolder + "Input\\" + NetworkName + "_recover.txt");
	for (size_t c = 0; c < _g.RestoreCases.size(); c++)
	{
		for (size_t l = 0; l < _g.RestoreCases.at(c).size();l++)
		{
			int linkid = _g.RestoreCases.at(c).at(l);
			cout << "Add recover link : " << linkid << endl;
			restoreOneLink(_g, _man, linkid);
			_man.setAlgoNull();
			_g.NowVulLink = linkid;
			_g.EvaluteGraph(_man, _man.getEqAlgo());
		}
		cout << "all links has been added back" << endl;	
		_g.NowRecoverCase++;
		// before evaluate the next case, remove all the disrupted links
		for (const auto &l:_g.IniDisruptLinks)
		{
			disruptOneLink(_g, _man, l);
		}
	}

}
