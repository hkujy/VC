#include "CommonHeaders.h"
#include <assert.h>
#include <math.h>       /* pow */
using namespace std;

CHROME::CHROME(){
	this->ID = InvaildInt;
	this->VulnerableLinks.reserve(NumLinks);
	this->VulnerableLinkDof.reserve(NumLinks);
	this->VulnerableLinkDofProb.reserve(NumLinks);
	SolProb = InvaildFloat;
	TotalCost = InvaildFloat;
	UNPM = InvaildFloat;
	ImpactValue = InvaildFloat;
	Fitness = InvaildFloat;
}
CHROME::~CHROME(){
	this->VulnerableLinks.clear();
	this->VulnerableLinkDof.clear();
	this->VulnerableLinkDofProb.clear();
};

void CHROME::ReviseCap(GRAPH &Graph, ObjectManager &manager) {
	
	for (unsigned int i = 0; i < this->VulnerableLinks.size(); i++)
	{
		int LinkId = this->VulnerableLinks[i];
		Graph.Links.at(LinkId).CaRevise
			= Graph.Links.at(LinkId).CaInput * (1.0f - this->VulnerableLinkDof.at(i));
			// min(Graph.Links.at(LinkId).CaRevise / Graph.Links.at(LinkId).CaInput, 1.0f - this->VulnerableLinkDof.at(LinkId));
		// manager.getNet()->getLink(i)->getLinkFnc()->setCapacity(Graph.Links.at(i).CaRevise);
		manager.getNet()->getLink(LinkId)->getLinkFnc()->setCapacity(Graph.Links.at(LinkId).CaRevise);
	}
}


void CHROME::IniCap(GRAPH &_Graph, ObjectManager &manager) {
	for (unsigned int i = 0; i < this->VulnerableLinks.size(); i++)
	{
		int LinkiD = this->VulnerableLinks[i];
		_Graph.Links.at(LinkiD).IniCap();
		manager.getNet()->getLink(LinkiD)->getLinkFnc()->setCapacity(_Graph.Links.at(LinkiD).CaInput);

	}

	//for (int i = 0; i < this->VulnerableLinks.size(); i++)
	//{
	//	int link_ID = VulnerableLinks.at(i);
	//	cout << "after ini cap link=" << i << ", cap=" << manager.getNet()->getLink(link_ID)->getLinkFnc()->getCapacity() << endl;
	//	//manager.getNet()->getLink(LinkId)->getLinkFnc()->setCapacity(Graph.Links.at(LinkId).CaRevise);


	//}



}

double CHROME::getSolProb(){
	double r = 1.0;
	for (auto p = this->VulnerableLinkDofProb.begin(); p != this->VulnerableLinkDofProb.end(); p++)
	{
		r = r*(*p);
	}
	return r;
}

void CHROME::EvaluateSol(GRAPH &Graph, const double BaseUNPM, ObjectManager &manager)
{
	// step 1 update cost:
	Graph.TotalSystemCost = 0.0f;
	Graph.UNPM = 0.0f;
	this->ReviseCap(Graph,manager);
	// Step 2  Probability of scenarios 
	this->SolProb = getSolProb();
	// Step 3 UE evaluate 
	//bool allZeor = true;
	//for each (auto val in this->VulnerableLinkDof)
	//{
	//	if (val > 0) allZeor = false;
	//}
	//if (allZeor)
	//	cout << "check" << endl;


	Graph.EvaluteGraph(manager,manager.getEqAlgo());
	//assert(Graph.PrintLinks(AssertLog));
	this->IniCap(Graph,manager); // after revising the capacity and change it back
	
	//Graph.EvaluteGraph(manager, manager.getEqAlgo());

	this->UNPM = Graph.UNPM;
	this->TotalCost = Graph.TotalSystemCost;
	this->ImpactValue = (BaseUNPM - this->UNPM) / BaseUNPM;
	this->Fitness = this->ImpactValue*this->SolProb;
	if (Fitness < 0)
	{
		cout << "WTF: Fitness is less than 0. If enumerate, then the ID  = "<<this->ID << endl;
	}
}


int CHROME::PrintSol(ofstream &fout){

	//if ( this->VulnerableLinks.size()>0)
	//{
	//	vector<bool> isFailLink(this->VulnerableLinks.size(), false);
	//	for (auto i = this->VulnerableLinks.begin(); i != this->VulnerableLinks.end(); i++)
	//	{
	//		//int LinkId = this->VulnerableLinks.at(*i);
	//		//isFailLink[*i] = true;
	//		isFailLink[*i] = true;
	//	}
	//	for (int i = 0; i < this->VulnerableLinks.size(); i++)
	//	{
	//		if (!isFailLink[i]) continue;
	//		for (unsigned int j = 0; j < this->VulnerableLinks.size(); j++)
	//		{
	//			if (this->VulnerableLinks.at(j) == i)
	//			{
	//				fout << this->VulnerableLinkDof.at(j) << ",";
	//			}
	//		}
	//	}
	//	fout << endl;
	//}

	for (int i = 0; i < this->VulnerableLinks.size()-1; i++)
	{
		fout << this->VulnerableLinkDof.at(i) << ",";
	}
	fout << this->VulnerableLinkDof.back() <<endl;
	//fout << endl;
	return 1;
}

// copy constructor 
void CHROME::Copy(const CHROME& FromSource){
	this->ID = FromSource.ID;
	this->SolProb = FromSource.SolProb;
	this->UNPM = FromSource.UNPM;
	this->ImpactValue = FromSource.ImpactValue;
	this->TotalCost = FromSource.TotalCost;
	this->Fitness = FromSource.Fitness;
	this->VulnerableLinks.clear(); this->VulnerableLinkDof.clear(); this->VulnerableLinkDofProb.clear();

	if (FromSource.VulnerableLinks.size() != FromSource.VulnerableLinkDof.size()
		|| FromSource.VulnerableLinks.size() != FromSource.VulnerableLinkDofProb.size()
		|| FromSource.VulnerableLinkDof.size() != FromSource.VulnerableLinkDofProb.size())
	{
		TRACE("From source link size inconsistant \n");
	}
	for (unsigned int i = 0; i < FromSource.VulnerableLinks.size();i++)
	{
		this->VulnerableLinks.push_back(FromSource.VulnerableLinks.at(i));
		this->VulnerableLinkDof.push_back(FromSource.VulnerableLinkDof.at(i));
		this->VulnerableLinkDofProb.push_back(FromSource.VulnerableLinkDofProb.at(i));
	}
};

void CHROME::clear(){
	this->ID = 0;
	this->VulnerableLinks.clear();
	this->VulnerableLinkDof.clear();
	this->VulnerableLinkDofProb.clear();
	this->SolProb = InvaildFloat;
	this->TotalCost = InvaildFloat;
	this->UNPM = InvaildFloat;
	this->Fitness = InvaildFloat;
	this->ImpactValue = InvaildFloat;
}

bool CHROME::isSame(const CHROME &CompareSource)
{
	bool isSame = true;
	for (unsigned int i = 0; i < this->VulnerableLinkDof.size(); i++)
	{
		assert(this->VulnerableLinks.at(i) == CompareSource.VulnerableLinks.at(i)); // should have the same index?
		if (!isEqual(this->VulnerableLinkDof.at(i), CompareSource.VulnerableLinkDof.at(i)))
		{
			isSame = false;
			return isSame;
		}
	}

	return isSame;
	
}

