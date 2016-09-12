
#include "MultiDimensionalSorting.h"

int main(int argc, char* argv[]){

	try{
	if (argc != 3)
		throw "Invalid arguments number";
	}
	catch(const char* err_msg){
		cout << "Error: " << err_msg << endl;
		return 1;
	}

	MDS Object(argv);

	cout << "End" << endl;
	return 0;
}