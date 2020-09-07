#include "CommonHeaders.h"
void FirstProcedureFunc(CHROME &Chrom, vector<double> DofVarSet);
void addNewNodeFunc(CHROME &Chrom, vector<double> DofVarSet);
void removeNodeDofFunc(CHROME &Chrom);
void exchangeNodeDofFunc(CHROME &Chrom, const vector<double> &DofVarSet);

// void decreaseDof(double &NowDof, vector<double> DofVarSet);

void decreaseDof(double &NowDof,double &NowDofProb, vector<pair<double, double>> DofVarSet);
void increasdof(double &NowDof, double &NowDofProb, vector<pair<double,double>> DofVarSet);
void SetDofAndProb(const std::vector<pair<double,double>> &Vec,
				   double &setdof, double &setdofprob);
// void increasdof(double &NowDof, vector<double> DofVarSet);