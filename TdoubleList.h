#include<string>
using namespace std;

class TlistElement //element listy dwukierunkowej
{
public:
	TlistElement * next, *prev;
	string key;
};

class TdoubleList // lista
{
public:
	
	TdoubleList();
	~TdoubleList();
	
	TlistElement * index(unsigned n);
	unsigned size();
	void push_front(TlistElement * p);
	void push_back(TlistElement * p);
	TlistElement * pop_front();
	TlistElement * pop_back();
	TlistElement * front, *back;
private:
	unsigned counter;
};

