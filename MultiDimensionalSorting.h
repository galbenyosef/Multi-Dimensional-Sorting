#ifndef MDS_H_
#define _MDS_H_

#include "myElement.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <time.h>

using std::exception;

static const unsigned max_population = 1000; // PRE_DEFINED
static const unsigned max_n = 100; // PRE_DEFINED

class MDS{
public:
	MDS();
	MDS(char* argv[]);
	~MDS();


private:
	vector<myElement> Elements_vector;

	unsigned population,n,m,iterations;
	vector<vector<int> > grouped_bases_vectors;  
	vector<vector<int> > grouped_variables_vectors;  
	vector<vector<int> > grouped_targets_vectors;  

	void setup(char* []);
	void input_handler(char*);
	void output_handler(char*);

	unsigned sum_of_Abs(const vector<int>& v);
	vector<int> randomVec();
	void run();

	void Rank(vector<myElement>&);
	void MakeTargets(vector<myElement>&);
	void Create(vector<myElement>&);
	void Half(vector<myElement>&);
	void Sort(vector<myElement>&);
	void Update(vector<myElement>&);

	MDS(const MDS&);
	MDS& operator=(const MDS&);

};

template <typename Iterator> void quickSort(Iterator start, Iterator end);

#endif