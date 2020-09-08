// uniform_int_distribution
#include "CommonHeaders.h"
#include <iostream>
#include <random>
#include <vector>
int GenRandomInt(const std::vector<int> &Vec,int &pos)
{
	std::uniform_int_distribution<unsigned int> distribution(0,(unsigned int) (Vec.size()-1));
	unsigned int Num = distribution(GenRan);
	pos = Num;
	return Vec.at(Num);
}


void SetDofAndProb(const std::vector<pair<double,double>> &Vec,
				   double &setdof, double &setdofprob, bool isExlcudeZero=false)
{
	setdof = 0.0; setdofprob = 0.0;
	if (isExlcudeZero)
	{
		std::uniform_int_distribution<unsigned int> distribution(1, (unsigned int)(Vec.size()-1));
		unsigned int Num = distribution(GenRan);
		setdof = Vec.at(Num).first;
		setdofprob = Vec.at(Num).second;
	}
	else
	{
		std::uniform_int_distribution<unsigned int> distribution(0, (unsigned int)(Vec.size()-1));
		unsigned int Num = distribution(GenRan);
		setdof = Vec.at(Num).first;
		setdofprob = Vec.at(Num).second;
	}
	// return Vec.at(Num).second;
}

// double GenRandomFloat(const std::vector<pair<double,double>> &Vec)
// {
// 	std::uniform_int_distribution<unsigned int> distribution(0, (unsigned int)(Vec.size()-1));
// 	unsigned int Num = distribution(GenRan);
// 	return Vec.at(Num).second;
// }

int GenRandomPos(unsigned int siz)
{
	std::uniform_int_distribution<unsigned int> distribution(0, siz-1);
	return distribution(GenRan);
}
double GenRandomReal()
{
	std::uniform_real_distribution<double> distribution(0.0f,1.0f);
	return distribution(GenRan);
}
