//============================================================================
// Name        : ProbabilityMatrix2.cpp
// Author      : Dachi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Read.h"
#include "ProbabilityMatrix.h"

using namespace std;

int main() {
	string line;
	int lineCounter;

	vector<Read> leftVector;
	vector<Read> rightVector;

	string left_sequenceID;
	string left_sequence;
	string left_score;

	string right_sequenceID;
	string right_sequence;
	string right_score;

	//Read left file
	ifstream left_file ("left.txt", ios::in);
	if (left_file.is_open())
	{
		lineCounter = 0;
		while (getline(left_file, line))
		{
			switch (lineCounter%5)
			{
			  case 0: left_sequenceID = line; break;
			  case 1: left_sequence = line; break;
			  case 3:
			  {
				  left_score = line;

				  //Add to vector
				  Read left_read(left_sequence,left_score);
				  leftVector.push_back(left_read);
			  } break;
			  default: break;
			}
			lineCounter++;
		}
		left_file.close();
	}

	//Read right file
	ifstream right_file ("right.txt", ios::in);
	if (right_file.is_open())
	{
		lineCounter = 0;
		while (getline(right_file, line))
		{
			switch (lineCounter%5)
			{
			  case 0: right_sequenceID = line; break;
			  case 1: right_sequence = line; break;
			  case 3:
			  {
				  right_score = line;
				  //Add to vector
				  Read right_read(right_sequence,right_score);
				  right_read.calculateReadInverse();
				  rightVector.push_back(right_read);
			  } break;
			  default: break;
			}
			lineCounter++;
		}
		right_file.close();
	}

	for(unsigned int vi = 0; vi < leftVector.size() && vi < rightVector.size();vi++)
	{
		ProbabilityMatrix resultingMatrix(
				rightVector.at(vi).getSequence()+
				leftVector.at(vi).getSequence(),
				rightVector.at(vi).getScore()+
				leftVector.at(vi).getScore());

		resultingMatrix.applyBigram(401); // window size 401
		resultingMatrix.applyQualityScore(100); // QS:BiGram = 100:1

		cout<<resultingMatrix.getSequence()<<endl;
		cout<<resultingMatrix.getScore()<<endl;
		resultingMatrix.printMatrix();
	}
	return 0;
}
