#include "CommonHeaders.h"
using namespace std;
void LogMsg(const char *format, ...);

std::ofstream Log;
//void OpenAndCleanFiles(){
//
//	string outfolder = rootfolder + "OutPut//";
//	Log.open(outfolder+"Log.txt", ios::trunc | ios::app);
//	if (Log.is_open()) printf("Log File Not Open\n");
//
//	ofstream  OutFile;
//	OutFile.open(outfolder+"Summary.txt", ios::trunc);
//	OutFile.close();
//	OutFile.open(outfolder+"ModelPara.txt", ios::trunc);
//	OutFile.close();
//	OutFile.open(outfolder+"Summary.txt", ios::trunc);
//	OutFile.close();
//	OutFile.open(outfolder+"BestSolLink.txt", ios::trunc);
//	OutFile.close();
//	OutFile.open(outfolder+"BestSolOD.txt", ios::trunc);
//	OutFile.close();
//	OutFile.open(outfolder+"PrintSols.txt", ios::trunc);
//	OutFile.close();
//	OutFile.open(outfolder+"LinkData.txt", ios::trunc);
//	OutFile.close();
//	OutFile.open(outfolder+"DemandData.txt", ios::trunc);
//	OutFile.close();
//	OutFile.open(outfolder+"GAConvergeBasedOnSol.txt", ios::trunc);
//	OutFile.close();
//	AssertLog.open(outfolder+"AssertLog.txt", ios::trunc);
//}
//
//void CloseFiles(){
//	Log.close();
//	AssertLog.close();
//}
