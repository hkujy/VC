#pragma once

#ifndef MyFileClass
#define MyFileClass
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class MyFiles
{
public:
	std::ofstream printDisruptOD;
	std::ofstream printDIsruptLink;
	std::ofstream printDisruptSummary;
	std::ofstream printRecoverOD;
	std::ofstream printRecoverLink;
	std::ofstream printRecoverSummary;
	std::ofstream printModelPara;
	std::ofstream printLog;
	std::string rootfolder;
	MyFiles() {
		set_root_folder(); IniFiles();
	}
	~MyFiles()
	{
		printDisruptOD.close(); printDIsruptLink.close(); printDisruptSummary.close();
		printModelPara.close(); printLog.close(); printRecoverOD.close();
		printRecoverLink.close(); printDisruptSummary.close();

	}
	void IniFiles()
	{
		printDisruptOD.open(rootfolder + "OutPut//" + "DisruptOD.csv", ios::trunc);
		printDisruptOD << "VulLink,Origin,Dest,ODIndex,Demand,UECost" << endl;

		printRecoverOD.open(rootfolder + "OutPut//" + "RecoverOD.csv", ios::trunc);
		printRecoverOD << "VulLink,Origin,Dest,ODIndex,Demand,UECost" << endl;

		printDIsruptLink.open(rootfolder + "OutPut//" + "DisrutpLink.csv", ios::trunc);
		printDIsruptLink << "VulLink,ID,Tail,Head,T0,Flow,Cap,Alpha,Beta,Cost" << endl;

		printRecoverLink.open(rootfolder + "OutPut//" + "RecoverLink.csv", ios::trunc);
		printRecoverLink << "VulLink,ID,Tail,Head,T0,Flow,Cap,Alpha,Beta,Cost" << endl;

		printDisruptSummary.open(rootfolder + "OutPut//" + "DisruptSummary.txt", ios::trunc);
		printRecoverSummary.open(rootfolder + "OutPut//" + "RecoverSummary.txt", ios::trunc);


		printModelPara.open(rootfolder + "OutPut//" + "ModelPara.csv", ios::trunc);
		printLog.open(rootfolder + "OutPut//" + "MsgLog.csv", ios::trunc); printLog.close(); printLog.clear();
		printLog.open(rootfolder + "OutPut//" + "Log.txt", ios::trunc);
	}
	void set_root_folder()
	{
		char* buffer;
		if ((buffer = _getcwd(NULL, 0)) == NULL) perror("_getcwd error");
		std::string ff(buffer);
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

#endif
