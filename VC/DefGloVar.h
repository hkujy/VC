// define global variables
#ifndef DGV
#define DGV
#include <string.h>
#include <random>
#include "GlobalVar.h"
//defines global
int NumOrig;
int NumDest;
int NumLinks;
int NumNodes;
int NumOD;
double  OneDimEsp;
double  UEeps;
int	   UEmaxIter;
int TestIndex;
int MaxCsaIter;
//int ModelIndex;
OutPutChanal WriteOutTo;
int MaxNumSolEval;
bool isWriteConverge;
std::string NetworkName;
MyFiles mf;

#endif
