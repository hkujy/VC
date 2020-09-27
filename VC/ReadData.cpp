#include "CommonHeaders.h"
#include <string>
#include "TempleteFunc.h"
using namespace std;

bool ReadLinkData(std::vector<LINK> &Links,
	ifstream &fin) {
	LINK tl;
	int IDcount = 0;
	//int tail, head;
	//float t0, ca0;
	//float BprAlph, BprBeta;
	vector<string> fields;
	string line;

	while (getline(fin, line))
	{
		splitf(fields, line, ",");
		if ( std::stoi(fields[0])<0)
			continue;
	/*	fscanf_s(fin, "%i %i %f %f %f %f",
			&tail, &head, &t0, &ca0, &BprAlph, &BprBeta);*/
		Links.push_back(tl);
		Links.back().ID = IDcount;
		Links.back().Tail = std::stoi(fields[0]);
		Links.back().Head = std::stoi(fields[1]);
		Links.back().T0 = std::stof(fields[2]);
		Links.back().CaInput = std::stof(fields[3]);
		Links.back().CaRevise = std::stof(fields[3]);
		Links.back().AlphaBpr = std::stof(fields[4]);
		Links.back().BetaBBpr = std::stof(fields[5]);
		IDcount++;
	}
	return true;
}

bool ReadDemandData(vector<OD> &ODPairs,
	ifstream &fin) {

	int IDcount = 0;
	//int or , de;
	//float dd;
	vector<string> fields;
	string line;
	OD tod;

	while (getline(fin, line))
	{
		splitf(fields, line, ",");
		if (std::stoi(fields[0])<0)
			continue;

		ODPairs.push_back(tod);
		ODPairs.back().ID = IDcount;
		ODPairs.back().Orign = std::stoi(fields[0]);
		ODPairs.back().Dest = std::stoi(fields[1]);
		ODPairs.back().Demand = std::stof(fields[2]);
		IDcount++;
	}

	return true;
}

bool PrintModelParas(){

	ofstream fout;
	//fout.open("c://GitCodes//VC//OutPut//ModelPara.txt");
	fout.open(mf.rootfolder + "OutPut//ModelPara.txt");
	fout << "NumNodes" << "," << NumNodes << endl;
	fout << "NumOD" << "," << NumOD << endl;
	fout << "NumLinks" << "," << NumLinks << endl;
	fout.close();

	return true;
}
/*Read My own parameters for the algorithm */
bool ReadModelParas(){

	//ifstream fin; fin.open("c://GitCodes//VC//InPut//Para.txt");
	ifstream fin; 
	fin.open(mf.rootfolder+"InPut//Para.txt");
	std::string line;
	std::vector<string> fields;
	std::cout<<"Remark: NumOD, NumNode, NumLinks are set based manger network"<<endl;
	while (getline(fin, line))
	{
		splitf(fields, line, ",");
		if (fields.size() != 2) continue;
		if (fields[0] == "UEeps")	UEeps = stof(fields[1]);
		if (fields[0] == "Network")  NetworkName = fields[1];
		if (fields[0] == "WhereToWrite")
		{
			if (fields[1]._Equal("0")) WriteOutTo = screen;
			if (fields[1]._Equal("1")) WriteOutTo = file;
			if (fields[1]._Equal("2")) WriteOutTo = both;
		}
		if (fields[0] == "isWriteConverge")
		{
			if (fields[1]._Equal("0")) isWriteConverge = false;
			if (fields[1]._Equal("1")) isWriteConverge = true;
		}
		if (fields[0] == "TestIndex")  TestIndex = stoi(fields[1]);
		if (fields[0] == "EvalOne") VCprocedure = Procedure::EvalOne;
		if (fields[0] == "RecoverOne") VCprocedure = Procedure::RecoverOne;
	}
	fin.close();

	return PrintModelParas();
}

