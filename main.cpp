#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

//I don't like using namespace std, but convenient in this module.
using namespace std;

void main()
{
	//Create a vector of vectors to read in strings
	vector <vector <string>> data;
	ifstream infile("input2.txt");
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

	vector<float> clustersAvg;
	int Threshold = 25;                 //User defined threshold
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
	f1.open("output2_farnam.txt", ios::out);
	{
		for (const auto& avg : clustersAvg)
		{
			//Write comma seperated with no space
			f1 << avg << ",";
		}
	}
	f1.close();
	cout << "Output File created containing cluster averages.";
}