
#ifndef GLOBALVAR
#define GLOBALVAR
#include <fstream>
#include <random>
#include <string.h>
#include "Classes.h"
//Constant
enum OutPutChanal
{
	screen, file, both
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


#endif