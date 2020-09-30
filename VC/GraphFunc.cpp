#include "CommonHeaders.h"
#include <assert.h>
#include <tuple>
#include <math.h>       /* pow */
#include "TempleteFunc.h"
using namespace std;


GRAPH::GRAPH(){
	this->OdPairs.reserve(NumOD + 1);
	this->OriginSet.reserve(NumNodes + 1);
	this->Nodes.reserve(NumNodes + 1);
	this->Links.reserve(NumLinks + 1);
	this->NowCase = -1;
	//int** MinPathPredLink;
	if (NumNodes==0)
	{
		cerr << "Input node should be known before construct graph" << endl;
	}
	//this->MinPathPredLink
	//	= Create2DAarray<int>(NumNodes + 1, NumNodes + 1);
	//for (int i = 0; i < NumNodes + 1; i++)
	//{
	//	for (int j = 0; j < NumNodes + 1; j++)
	//	{
	//		this->MinPathPredLink[i][j] = InvaildInt;
	//	}
	//}
	this->NowVulLink = -1;
	this->IniDisruptLinks.reserve(NumLinks + 1);

};
GRAPH::~GRAPH(){
	//Free2DArrey<int>(this->MinPathPredLink, NumNodes + 1);
	OdPairs.clear(); Links.clear(); Nodes.clear(); OriginSet.clear();
	VulnerableLinks.clear(); VulnerableLinksDof.clear();
};

//int GRAPH::FindMinCostRoutes(){
//
//	try{
//		int StatusMsg;
//		std::vector<double> Lable;
//		for (auto o = this->OriginSet.begin(); o != this->OriginSet.end(); o++)
//		{
//			int Orig = o->Onode;
//			StatusMsg = this->SP(o->Onode, Lable);// shortest path
//			assert(StatusMsg);
//			//printf("Find min tree for Onode = %d \n", Orig);
//			//Minpath(Orig, MinPathPredLink[Orig], Lable, Nodes, Links, ModeType);
//			for (auto d = o->ODset.begin(); d != o->ODset.end(); d++)
//			{
//				int Dest = (*d)->Dest;
//#ifdef __DEBUG__ 
//				if (isnan(Lable[Dest])) DEBUG("Od Pair %d,mincost is NaN", *d);
//#endif	
//				this->OdPairs.at((*d)->ID).MinCost = Lable[Dest];
//
//				//ODPairs.at(*d).MinCost.at(ModeType) = Lable[Dest];
//				if (this->OdPairs.at((*d)->ID).MinCost < InvalidMinCost)
//				{
//					this->OdPairs.at((*d)->ID).isConnected = true;
//				}
//				/*if (ODPairs.at(*d).MinCost.at(ModeType) < InvalidMinCost)
//					ODPairs.at(*d).isConnected = true;*/
//			}
//		}
//		return 1;
//	}
//
//	catch (exception& e)
//	{
//		TRACE("FindMinCostRoutes %s", e.what());
//		return 0;
//	}
//}
//
void GRAPH::CreateOriginSet()
{
	OriginBasedOD Oset;
	vector<bool> isOrign(NumNodes, false);
	for (auto od = this->OdPairs.begin(); od != this->OdPairs.end(); od++)
	{
		isOrign.at(od->Orign) = true;
	}
	for (int n = 0; n < NumNodes; n++) {
		if (isOrign.at(n))
		{
			Oset.Onode = n;
			this->OriginSet.push_back(Oset);
		}
	}
	for (auto od = this->OdPairs.begin(); od != this->OdPairs.end(); od++)
	{
		this->OriginSet.at(od->Orign).ODset.push_back(&*od);
	}
}

void GRAPH::ReadRestoreCase(string RestoreFileName)
{
	cout << "Read Restore link file: " << RestoreFileName << endl;
	ifstream fin;
	fin.open(RestoreFileName);
	std::string line;
	std::vector<string> fields;
	int num = 0;
	while (getline(fin, line))
	{
		vector<int> _tp;
		splitf(fields, line, ",");
		if (fields.size() <= 1)
		{
			TRACE("Num of restore link is <=1, are you sure?");
			continue;
		}
		for (size_t i = 0; i < fields.size(); i++)
		{
			_tp.push_back(std::stoi(fields[i]));
		}
		RestoreCases.push_back(_tp);
	}
	fin.close();
	cout << "**************************************" << endl;
	cout << "Check Read Restore Disrupted links" << endl;
	for (size_t i = 0; i < RestoreCases.size(); i++)
	{
		cout << "RestoreCase_" << i << ":";
		for (size_t l=0;l<RestoreCases.at(i).size()-1;l++)
		{
			cout << RestoreCases.at(i).at(l) << ",";
		}
		cout << RestoreCases.at(i).back() << endl;
	}
	cout << endl;
	cout << "**************************************" << endl;
}


void GRAPH::ReadIniDisrup(string IniFileName)
{
	cout << "Read vulnerable link file: " << IniFileName << endl;
	ifstream fin;
	fin.open(IniFileName);
	std::string line;
	std::vector<string> fields;
	int num = 0;
	while (getline(fin, line))
	{
		splitf(fields, line, ",");
		if (fields.size() <= 1)
		{
			TRACE("Num of ini disrupt link is <=1, are you sure?");
			continue;
		}
		
		for (size_t i = 0; i < fields.size(); i++)
		{
			IniDisruptLinks.push_back(std::stoi(fields[i]));
		}
	}
	fin.close();
	cout << "**************************************" << endl;
	cout << "Check Read Ini Disrupted links" << endl;
	for (auto l : IniDisruptLinks)
	{
		cout << l << ",";
	}
	cout << endl;
	cout << "**************************************" << endl;
	
}

void GRAPH::ReadVunLinks(string VunerableFileName)
{
try
{
	cout << "Read vulnerable link file: " << VunerableFileName << endl;
	ifstream fin;
	fin.open(VunerableFileName);
	std::string line;
	std::vector<string> fields;
#ifdef DEBUG
	std::cout << "Remark: NumOD, NumNode, NumLinks are set based manger network" << endl;
#endif // DEBUG
	int num = 0;
	int LinkId;
	double dof, prob;
	while (getline(fin, line))
	{
		splitf(fields, line, ",");
		if (fields.size() <=2) continue;
		LinkId = stoi(fields[0]);
		this->VulnerableLinks.push_back(LinkId);
		num = stoi(fields[1]);
		// cout << "node = " << LinkId << endl;
		vector<pair<double, double>> ele;
		for (int l=0;l<num;++l)
		{
			dof = stof(fields[2 + l * 2]);
			prob = stof(fields[3 + l * 2]);
			// cout << "----" << dof << "," << prob << endl;
			ele.push_back(std::make_pair(dof, prob));
		}
		this->VulnerableLinksDof.push_back(ele);
	}
	// how to use this data structure
	// cout << VulnerableLinksDof[0].begin()->first<< endl;
	// cout << VulnerableLinksDof[0].begin()->second<< endl;
	// cout << VulnerableLinksDof[0].at(0).first << endl;
	// cout << VulnerableLinksDof[0].at(1).second << endl;
	//cout << (VulnerableElment[0].begin())<< endl;
	fin.close();
}
catch (Error error)
{
	std::cout << "Error has occurred during execution: " << error.getMessage() << std::endl;
}

}
void GRAPH::CreateNodes(){
	assert(this->Links.size() > 0);
	if (this->Nodes.size() == 0)
	{
		NODE tnode;
		for (int i = 0; i < NumNodes; i++)
		{
			this->Nodes.push_back(tnode);
			this->Nodes.back().ID = i;
		}
	}
	else
	{
		for (auto l = this->Links.begin(); l != this->Links.end(); l++)
		{
			this->Nodes.at(l->Tail).OutLinks.push_back(&*l);
			this->Nodes.at(l->Head).InLinks.push_back(&*l);
		}
	}
}

int GRAPH::PrintLinks(std::ofstream &fout){

	try{
		assert(fout.good());
		fout.setf(ios::fixed);
		fout << left << setw(6) << "VunLink" << ",";
		fout << left << setw(6) << "ID" << ",";
		fout << left << setw(12) << "Tail" << ",";
		fout << left << setw(12) << "Head" << ",";
		fout << left << setw(12) << "T0" << ",";
		fout << left << setw(12) << "Ca0" << ",";
		fout << left << setw(12) << "CaRev" << ",";
		fout << left << setw(12) << "Cost" << ",";
		fout << left << setw(12) << "Flow" << ",";
		fout << endl;
		for (auto l = this->Links.begin(); l != this->Links.end(); l++)
		{
			fout << l->ID << ",";
			fout << l->Tail << ",";
			fout << l->Head << ",";
			fout << l->T0 << ",";
			fout << l->CaInput << ",";
			fout << l->CaRevise << ",";
			fout << l->Cost << ",";
			fout << l->Flow << ",";
			fout << endl;
		}
		return 1;
	}
	catch (exception &e)
	{
		TRACE("%s", e);
		return 0;
	}
}

int GRAPH::PrintOD(std::ofstream &fout)
{
	try
	{
		assert(fout.good());
		fout.setf(ios::fixed);
		fout << left << setw(6) << "ID" << ",";
		fout << left << setw(12) << "Origin" << ",";
		fout << left << setw(12) << "Dest" << ",";
		fout << left << setw(12) << "Demand" << ",";
		fout << left << setw(12) << "MinCost" << ",";
		fout << endl;
		for (auto od = this->OdPairs.begin(); od != this->OdPairs.end(); od++)
		{
			fout << od->ID << ",";
			fout << od->Orign << ",";
			fout << od->Dest << ",";
			fout << od->Demand << ",";
			fout << od->MinCost << ",";
			fout << endl;
		}
		return 1;
	}
	catch (exception &e)
	{
		TRACE("%s", e);
		return 0;
	}

}
//
//int GRAPH::PrintSp(int Orign, int Dest, std::ofstream &fout)
//{
//	try{
//		vector<int> Path;
//		for (auto o = this->OriginSet.begin(); o != this->OriginSet.end(); o++)
//		{
//			for (auto od = o->ODset.begin(); od != o->ODset.end(); od++)
//			{
//				if ((*od)->Orign == Orign && Dest == (*od)->Dest)
//				{
//					Path.clear();
//					int CurrentNode = (*od)->Dest;
//					while (CurrentNode != (*od)->Orign)
//					{
//						int k = this->MinPathPredLink[(*od)->Orign][CurrentNode];
//						Path.push_back(k);
//						CurrentNode = this->Links.at(k).Tail;
//					}
//					for (auto i = Path.rbegin(); i != Path.rend(); i++)
//					{
//						fout << *i << ",";
//					}
//					fout << endl;
//				}
//			}
//		}
//		return 1;
//	}
//	catch (exception &e)
//	{
//		TRACE("%s", e);
//		return 0;
//	}
//}

void GRAPH::PrintGraph(ObjectManager &Man,std::ofstream &OD_out,std::ofstream &Link_out)
{
	// first: print OD pairs
	for (ConstOriginIterator it = Man.getODMatrix()->begin(); it != Man.getODMatrix()->end(); ++it)
	{
		Origin* origin = *it;
		for (PairODIterator destIt = origin->begin(); destIt != origin->end(); ++destIt)
		{
			PairOD* dest = *destIt;
			OD_out<< NowCase << ",";
			OD_out<< NowVulLink << ",";
			OD_out << origin->getIndex() << ",";
			OD_out << dest->getIndex() << ",";
			OD_out << dest->getODIndex() << ",";
			OD_out << dest->getDemand() << ",";
			OD_out<< dest->getODminCost();
			OD_out << endl;
		}
	}
	OD_out.flush();

	// Second: print links

	for (auto l = Man.getNet()->beginOnlyLink(); l != NULL; l = Man.getNet()->getNextOnlyLink())
	{
		Link_out << NowCase << ",";
		Link_out << NowVulLink << ",";
		Link_out << l->getIndex() << ",";
		Link_out << l->getNodeFrom() << ",";
		Link_out << l->getNodeTo() << ",";
		Link_out << l->getLinkFnc()->getFreeFlowTime() << ",";
		Link_out << l->getFlow() << ",";
		Link_out << l->getLinkFnc()->getCapacity() << ",";
		Link_out << l->getLinkFnc()->getAlpha() << ",";
		Link_out << l->getLinkFnc()->getPower() << ",";
		Link_out << l->getTime();
		Link_out << endl;
	}
	Link_out.flush();


}

void GRAPH::EvaluteGraph(ObjectManager &Man, DecoratedEqAlgo *algo)
{
	int nbIter = algo->execute();
	FPType tc = 0.0;
	for (ConstOriginIterator it = Man.getODMatrix()->begin(); it != Man.getODMatrix()->end(); ++it)
	{
		Origin* origin = *it;
		for (PairODIterator destIt = origin->begin(); destIt != origin->end(); ++destIt)
		{
			PairOD* dest = *destIt;
			tc += dest->getDemand()*dest->getODminCost();
			assert(dest->getODminCost() > 0.0f);
		}
	}
	if (VCprocedure == Procedure::EvalEachOneByRemove ||
		VCprocedure == Procedure::EvalBaseAndOneNet)
	{
		PrintGraph(Man,mf.printDisruptOD,mf.printDIsruptLink);
	}
	else if (VCprocedure == Procedure::RecoverOne)
	{
		PrintGraph(Man,mf.printRecoverOD,mf.printRecoverLink);
	}
}




