
#ifndef GLOBALVAR
#define GLOBALVAR
#include <fstream>
#include <random>
#include <string.h>
#include "Classes.h"
#include "MyFileClass.h"
//Constant
enum OutPutChanal
{
	screen, file, both
};
enum class Procedure
{
	EvalOne = 0,    // evaluate each one based on the complete network
	RecoverOne = 1,    // recover element one by one
	None = -1			// not specified       
};
extern std::string NetworkName;
extern int NumOrig;
extern int NumDest;
extern int NumLinks;
extern int NumNodes;
extern int NumOD;
//extern std::ofstream TestStepSize/*;*/
extern int TestIndex;
extern double UEeps;
extern bool isWriteConverge;
extern OutPutChanal WriteOutTo;
extern Procedure VCprocedure;
const double ZeroCap = 1.0e-10;
extern MyFiles mf;



#endif