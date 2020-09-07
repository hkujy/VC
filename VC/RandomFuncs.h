#ifndef RANFUNS
#define RANFUNS
#include <vector>
double GenRandomReal();
//int GenRandomInt(const std::vector<int> &Vec);
//double GenRandomFloat(const std::vector<double> &Vec);
int GenRandomInt(const std::vector<int> &Vec, int &pos);
int GenRandomPos(unsigned int siz);
#endif // !RANFUNS
