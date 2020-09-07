#include "CommonHeaders.h"
using namespace std;
void LogMsg(const char *format, ...);

std::ofstream Log;
void OpenAndCleanFiles(){
	string rootfolder = "c://GitCodes//ResiV2//OutPut//";
	Log.open(rootfolder+"Log.txt", ios::trunc | ios::app);
	if (Log.is_open()) printf("Log File Not Open\n");

	ofstream  OutFile;
	OutFile.open(rootfolder+"Summary.txt", ios::trunc);
	OutFile.close();
	OutFile.open(rootfolder+"ModelPara.txt", ios::trunc);
	OutFile.close();
	OutFile.open(rootfolder+ "CSAconverge.txt", ios::trunc);
	OutFile.close();
	OutFile.open(rootfolder+"GAconverge.txt", ios::trunc);
	OutFile.close();
	OutFile.open(rootfolder+"Summary.txt", ios::trunc);
	OutFile.close();
	OutFile.open(rootfolder+"BestSolLink.txt", ios::trunc);
	OutFile.close();
	OutFile.open(rootfolder+"BestSolOD.txt", ios::trunc);
	OutFile.close();
	OutFile.open(rootfolder+"PrintSols.txt", ios::trunc);
	OutFile.close();
	OutFile.open(rootfolder+"LinkData.txt", ios::trunc);
	OutFile.close();
	OutFile.open(rootfolder+"DemandData.txt", ios::trunc);
	OutFile.close();
	OutFile.open(rootfolder+"CSAConvergeBasedOnSol.txt", ios::trunc);
	OutFile.close();
	OutFile.open(rootfolder+"GAConvergeBasedOnSol.txt", ios::trunc);
	OutFile.close();
	AssertLog.open(rootfolder+"AssertLog.txt", ios::trunc);


}

void CloseFiles(){
	Log.close();
	AssertLog.close();
	//TestPara.close();
	//OutPutFlow.close();
	//SettingSuammry.close();
	//Converge.close();
	//ParadoxSumary.close();
}
