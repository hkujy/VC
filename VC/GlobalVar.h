
#ifndef GLOBALVAR
#define GLOBALVAR
#include <fstream>
#include <random>
#include <string.h>
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
extern double OneDimEsp;
extern int TestIndex;
extern double UEeps;
extern int UEmaxIter;
extern std::default_random_engine GenRan;
extern int MaxCsaIter;
//extern int ModelIndex;
extern int CsaNumPop;
extern double CsaCloneBeta;
extern double CsaRepRatio;
extern bool isWriteConverge;
extern int MaxGAIter;
extern int GANumPop;
extern int GANumChild;
extern int MaxNumSolEval;
extern OutPutChanal WriteOutTo;
extern int StopCriteria;  

#endif