
#include "0MyGlobal.h"
#include "LabelCorrectingAl.h"
#include "StarNetwork.h"
#include "StarNode.h"
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include <limits>
#include <sstream>


LabelCorrectingAl::LabelCorrectingAl(StarNetwork *netPointer) : 
							netPointer_(netPointer), 
							nbNodes_(netPointer->getNbNodes()), originIndex_(-1) {

	nodeList_ = new nodeInfo[nbNodes_];
	for (int i = 0; i < nbNodes_; ++i) {
		nodeList_[i].dist = 0.0;
		nodeList_[i].linkIndex = -1;
	}
	
};

LabelCorrectingAl::~LabelCorrectingAl(){
	delete[] nodeList_;
};

FPType LabelCorrectingAl::getCost(int destIndex) const{
	assert((destIndex >= 0) && (destIndex < nbNodes_));
	return nodeList_[destIndex].dist;	
};

StarLink* LabelCorrectingAl::getInComeLink(int destIndex) const {
	assert((destIndex >= 0) && (destIndex < nbNodes_));
	int linkIndex = nodeList_[destIndex].linkIndex;
	if (linkIndex == -1) return NULL;
	return netPointer_->getLink(linkIndex); 
};

int LabelCorrectingAl::getCurrentOrigin() const {
	return originIndex_;
}; 

void LabelCorrectingAl::calculate(int originIndex){

	originIndex_ = originIndex;
	
	//int sequenceList[this->nbNodes_ + 1]; // +1 - because we have one additional pointer:
	int* sequenceList = new int[this->nbNodes_ + 1]; // +1 - because we have one additional pointer:
					// sequenceList[nbNodes_] - contains the index of the current 
					// last node in the sequenceList
	int firstInSequence = -1;
	sequenceList[0] = -1;
	for (int i = 0; i < nbNodes_; ++i){
		nodeList_[i].dist = std::numeric_limits<FPType>::infinity();
		nodeList_[i].linkIndex = -1;
		sequenceList[i + 1] = -1;
	}
	nodeList_[originIndex].dist = 0.0;
	firstInSequence = originIndex; 
	sequenceList[originIndex] = nbNodes_;
	sequenceList[nbNodes_] = originIndex;
	
	int topNode = -1;
	StarLink *nextLink = NULL;
	StarNode *curNode = NULL;
	int nextNodeIndex = -1;
	FPType distToNextNode = 0;
	
	// main loop
	while (firstInSequence != nbNodes_) { // while sequence list is not empty
		
		topNode = firstInSequence; 
		curNode = netPointer_->beginNode(topNode);
		distToNextNode = 0;
		nextNodeIndex = -1;
		//if (originIndex == 1)
		//{
		//	std::cout << "curNode=" << curNode->getIndex() << ", tonod=" << topNode << std::endl;
		//	if (curNode->getIndex() == 0 && topNode == 0)
		//	{
		//		std::cout << "wtf" << std::endl;
		//	}
		//}
		if (proceed(curNode, topNode)) { // special condition for zone nodes
	/*		if (originIndex == 1)
			{
				std::cout << "proceed" << std::endl;
			}*/
			for (nextLink = netPointer_->beginLink(); nextLink != NULL; nextLink = netPointer_->getNextLink()) {
				
				nextNodeIndex = nextLink->getNodeToIndex();
	/*			if (originIndex == 1)
				{
					std::cout << "nextnode=" << nextNodeIndex << ", Dist=" << distToNextNode << ", time=" << nextLink->getTime() << std::endl;
				}*/
				
				distToNextNode = nodeList_[topNode].dist + nextLink->getTime(); 
				std::cout << "wtf" << nodeList_[nextNodeIndex].dist << std ::endl;
				if ( distToNextNode < nodeList_[nextNodeIndex].dist) { 
					//if (originIndex == 1)
					//{
					//	std::cout << "proceed"<<std::endl;
					//}
					nodeList_[nextNodeIndex].dist = distToNextNode;
					nodeList_[nextNodeIndex].linkIndex = nextLink->getIndex(); 
					if (sequenceList[nextNodeIndex] < 0) { // nextNode is not on sequenceList
						if (sequenceList[nextNodeIndex] == -1) { // nextNode has never been on sequenceList
							// place nextNode on the bottom of sequenceList
							sequenceList[nextNodeIndex] = nbNodes_; // nextNode is the last in sequenceList
							sequenceList[sequenceList[nbNodes_]] = nextNodeIndex; // previously last node points to nextNode now
							sequenceList[nbNodes_] = nextNodeIndex; // last pointer points to nextNodeIndex 
						} else {
							// place nextNode after topNode
							sequenceList[nextNodeIndex] = sequenceList[topNode]; // nextNode now points to the node to which topNode was pointing
							sequenceList[topNode] = nextNodeIndex; // topNodes now points to nextNode
							if (sequenceList[nextNodeIndex] == nbNodes_) { // if topNode was the last one
								sequenceList[nbNodes_] = nextNodeIndex; // update last pointer
							}				
						}
					}
				}
			}
		} 

		// topNode does not have out-going links to examine
		firstInSequence = sequenceList[topNode]; 
		sequenceList[topNode] = -2;
	}
	// add by jy 
	delete[] sequenceList;
};

//
//bool LabelCorrectingAl::proceed(StarNode* curNode, int topNode) const {
//	return ((curNode != NULL) && (!curNode->getIsZone() || (topNode == originIndex_)));
//};
//
bool LabelCorrectingAl::proceed(StarNode* curNode, int topNode) const {

	//change by Jy:2020 -Sep-08
	if (OriginVersionForbidReturn2Zone)
	{
		return ((curNode != NULL) && (!curNode->getIsZone() || (topNode == originIndex_)));
	}
	else if (!OriginVersionForbidReturn2Zone)
	{
		return ((curNode != NULL));
	}
	else
	{
		std::cout << "WTF: this should not be used" << std::endl;
		return ((curNode != NULL));
	}

};
