#ifndef myElement_H_
#define myElement_H_

#include <vector>

using namespace std;

class myElement{
public:

	myElement(const vector<int>& new_vars):variables(new_vars){rank = 0;}
	~myElement(){}

	myElement(const myElement& new_elem){ rank = new_elem.getRank(), variables=new_elem.getVariables();}
	myElement& operator=(const myElement& new_elem){ rank = new_elem.getRank(), variables=new_elem.getVariables();return *this;}

	const vector<int>& getVariables()const{ return variables; }
	const vector<int>& getTarget()const{ return target; }
	unsigned getRank()const{ return rank; }

	void setTarget(const vector<int>& new_target){ target=new_target; }

	//Implemention of ++ prefix
	myElement operator+(int n)
		{rank+=n;return *this;}
	myElement& operator++()
		{*this + 1; return *this;} //pre-fix

private:
	unsigned rank;
	vector<int> variables; // variables vector
	vector<int> target; // target vector

};


#endif