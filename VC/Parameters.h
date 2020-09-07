#ifndef PARA
#define PARA
#include <string>
const int InvaildInt=-1;
const double InvaildFloat = -999.9f;
const double Zero = 1.0e-6f;
const double LargeNum = 1.0e+20f;
const double RemoveLinkCost = 99999.0f;
const double InvalidMinCost = 99999.0f;
const int MaxNumNodes = 1000;
const int MaxNumDof = 10;
enum AlgorithmType
{
	CSA, GA, BruteForce
};

#endif // !PARA
