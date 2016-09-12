#include "MultiDimensionalSorting.h"
//default ctor none used
MDS::MDS()
{

}
//used ctor gets arguments and calls setup and then run
MDS::MDS(char* argv[])
{
	setup(argv);
	run();
	output_handler(argv[2]);
}
//dtor
MDS::~MDS()
{
	Elements_vector.clear();
}
//global operator- for vector<int>
vector<int> operator-(const vector<int>& v1, const vector<int>& v2)
{
	vector<int> result;
    for (unsigned i=0; i< v1.size() ; i++)
		result.push_back(v1[i]-v2[i]);
	return result;
}
//global operator< for vector<int>
bool operator< (const vector<int>& lhs, const vector<int>& rhs){
	
	if (lhs.size() == rhs.size())
	{
		for (unsigned i = 0 ; i < rhs.size(); i++)
			if (lhs[i] > rhs[i])
				return false;
		return true;
	}
	return false;
}
//global operator< for myElement
bool operator<(const myElement& l,const myElement& r){
	
	return(l.getRank() < r.getRank() ?  1 :  0);
}
//call input handler given arguments
void MDS::setup(char* argv[])
{
	char *input;
	input = argv[1];
	input_handler(input);
}
//using single vector , each line is inserted as a new vector, looping and creating
//2D vector of vectors that will be kept for further usage
void MDS::input_handler(char* input)
{
	vector<int> single_vector;

	ifstream stream_out;

	try{
		stream_out.open(input);
		if (!stream_out.is_open())
			throw "Input file error";

		stream_out >> population >> n >> m >> iterations;
		if (stream_out.fail() || stream_out.bad())
			throw "Bad setup parameters";

		//base vectors input
		for (unsigned i = 0; i < m; i++){
			for (unsigned j = 0; j < n; j++){
				int a;
				stream_out >> a;
				if (stream_out.fail() || stream_out.bad())
					throw "Bad base vectors input";
				single_vector.push_back(a);
			}
			grouped_bases_vectors.push_back(single_vector);
			single_vector.clear();
		}

		//variables vectors input
		for (unsigned i = 0; i < population; i++){
			for (unsigned j = 0; j < n; j++){
				int a;
				stream_out >> a;
				if (stream_out.fail() || stream_out.bad())
					throw "Bad variables vectors input";
				single_vector.push_back(a);
			}
			grouped_variables_vectors.push_back(single_vector);
			single_vector.clear();
		}
	}
	catch(const char* err_msg){
		cout << "Error: " << err_msg << endl;
		stream_out.close();
		return;
	}
}
//at the end of run(), moving through Elements vector and printing their target points
void MDS::output_handler(char* output)
{
	ofstream out(output);
	for (unsigned i = 0 ; i < Elements_vector.size() ; i++){
		for (unsigned j = 0 ; j < m ; j ++){
			out << Elements_vector[i].getTarget().at(j) << " ";
		}
		out << endl;
	}
	return;
}
//sum of absolut values
unsigned MDS::sum_of_Abs(const vector<int>& v)
{
	unsigned retVal(0);
	for (unsigned i=0; i<v.size(); i++)
		retVal+=abs(v[i]);
	return retVal;
}
//create random vector within defined range
vector<int> MDS::randomVec()
{
	vector<int> retVal;
	int range[] = {1,2,0,-2,-1};
	for (unsigned i = 0 ; i < n ; i++){

		srand((unsigned)time(NULL));
		int r = rand() % 5;
		retVal.push_back(range[r]);
	}
	return retVal;
}

//start
void MDS::run()
{
	vector<myElement> mewtwo;
	for (unsigned i = 0 ; i < iterations ; i++){
		Create(mewtwo);
		MakeTargets(mewtwo);
		Rank(mewtwo);
		Sort(mewtwo);
		Half(mewtwo);
		Update(mewtwo);
	}

}

//push the original vector and after it push each element new object with offset, total size 2n
void MDS::Create(vector<myElement>& mewtwo)
{
	for (unsigned k = 0 ; k < grouped_variables_vectors.size(); k++)
		mewtwo.push_back( *( new myElement( grouped_variables_vectors[k]) ) );
	for (unsigned k = 0 ; k < grouped_variables_vectors.size(); k++)
		mewtwo.push_back( *( new myElement( grouped_variables_vectors[k] - randomVec() ) ) );
}
//after 2n vector is created, it is needed to calculate the targets of each element
void MDS::MakeTargets(vector<myElement>& new_mewtwo)
{
	vector<int> target;
	vector<int> temp;
	for (unsigned i = 0 ; i < new_mewtwo.size(); i++)
	{
		for (unsigned j = 0 ; j < m ; j++)
		{
			temp = new_mewtwo[i].getVariables() - grouped_bases_vectors[j];
			unsigned result = sum_of_Abs(temp);
			target.push_back(result);
		}
		new_mewtwo[i].setTarget(target);
		target.clear();
	}
}
//after target_space is created, it is needed to Rank each element.target by its owning space
void MDS::Rank(vector<myElement>& new_mewtwo){

	for (unsigned i = 0 ; i < new_mewtwo.size() ; ++i)
	{
		for (unsigned j = 0 ; j < new_mewtwo.size() ; ++j)
		{
			if (&new_mewtwo[i] != &new_mewtwo[j]){
				if ( new_mewtwo[i].getTarget() < new_mewtwo[j].getTarget() && 
					new_mewtwo[i].getTarget() != new_mewtwo[j].getTarget() )
					++new_mewtwo[j];
				}
		}
	}
}
//using generic quicksort
void MDS::Sort(vector<myElement>& mewtwo)
{
	quickSort(mewtwo.begin(),mewtwo.end());
}

template <typename Iterator> 
void quickSort(Iterator start, Iterator end){

    int size = (end - start);
    if ( size <= 0 )
        return; 

	srand((unsigned)time(NULL));
    int pivotIndex = rand() % size + 0;
    typename iterator_traits<Iterator>::value_type pivot = *(start + pivotIndex);
    
    if (pivotIndex != 0)
        swap(*(start + pivotIndex), *start);
    
    int i = 1;
    for (int j = 1; j < size; j++){
        if ( *(start + j) < pivot ){
            swap( *(start+j), *(start+i));
            i++;
        }
    }
    
    swap(*start, *(start + i - 1));
    
    quickSort(start, start+i-1);
    quickSort(start+i, end);
}
//pop out half elements (vector is sorted)
void MDS::Half(vector<myElement>& mewtwo)
{
	unsigned size=mewtwo.size();
	for (unsigned i = 0 ; i < size/2 ; i++)
		mewtwo.pop_back();
}
//update the original Elements_vector at the end
void MDS::Update(vector<myElement>& mewtwo)
{
	Elements_vector.swap(mewtwo);
	mewtwo.clear();
}