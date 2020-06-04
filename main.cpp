/*
**   Detecting feature clusters for a given dataset 
** 
** A non-robust brute force method to determine average
** or middle value of each cluster contained in a 2D dataset. 
** This module is dependent on the visual assumptions made 
** from plotting the input datasets. 
**
** For a more robust solution, look to K-means.
**
** Farnam Adelkhani - June 2020
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

//I don't like using namespace std, but convenient in this module.
using namespace std;

string filename = "input0.txt";                          //Assign input file
string output_filename = "Solution_output0_farnam.txt";  //Choose output filename

//User defined threshold:
//Decided on this value by visually analyzing all five input scatter plots
//Values between 20-30 should work just as well.
int Threshold = 25;                 

void main()
{
	//Create a vector of vectors to read in strings
	vector <vector <string>> data;
	ifstream infile(filename);
	vector<double> inputDataset;
	while (infile)
	{
		//Read from file into s
		string s;
		if (!getline(infile, s)) break;

		//Create stringstream from text
		istringstream string_stream(s);

		//Temp to hold strings read-in from the line
		vector <string> inputData;

		while (string_stream)
		{
			//Push the value leading up to the comma into temp vector 'inputData'
			string s;
			if (!getline(string_stream, s, ',')) break;
			inputData.push_back(s);
		}
		//Pushing the temp vector onto the outer vector representing the file
		data.push_back(inputData);

		//Transform
		inputDataset.reserve(inputData.size());
		transform(inputData.begin(), inputData.end(), back_inserter(inputDataset),
			[](string const& val) {return stod(val); });
	}

	vector<float> clustersAvg;          //Vector for storing cluster avg values

	int K = 4;                          //Find K by inspection
	int clusterCount = 0;               //Current cluster size
	float clusterSum = 0.0f;            //Current cluster summation
	float lastSample = inputDataset[0]; //Keep track of last sample
	int outliers = 0;                   //Outlier count

	//Check if threshold is reached
	for (const auto& inputDataset : inputDataset)
	{
		//If threshold is not reached
		if (abs(inputDataset - lastSample) <= Threshold)
		{
			//Add to current cluster summation and count
			clusterSum += inputDataset;
			clusterCount++;
		}
		else
		{
			//Only execute when cluster count is over 1 to eliminate outliers.
			while (clusterCount > 1)
			{
				//Threshold reached!
				//Take average of current summation
				clustersAvg.push_back(clusterSum / clusterCount);
				clusterSum = inputDataset;
				clusterCount = 1;
			}
		}
		//Keep track of which point was left on
		lastSample = inputDataset;
	}
	//Summation of last cluster
	clustersAvg.push_back(clusterSum / clusterCount);

	//Writing average values to output .txt file
	fstream f1;
	f1.open(output_filename, ios::out);
	{
		bool first = true;
		for (const auto& avg : clustersAvg)
		{
			if (!first) f1 << ",";
			first = false;
			//Write comma seperated with no space
			f1 << avg;
		}
	}
	f1.close();
	cout << "Output File created containing cluster averages.";
}