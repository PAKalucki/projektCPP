#include "TdoubleList.h"

TdoubleList::TdoubleList()
{
	front = back = NULL;
	counter = 0;
}


TdoubleList::~TdoubleList()
{
	TlistElement * p;
	while (front)
	{
		p = front->next;
		delete front;
		front = p;
	}
}


unsigned TdoubleList::size()
{
	return counter;
}


void TdoubleList::push_front(TlistElement * p)
{
	p->next = front; 
	p->prev = NULL;
	if (front) 
		front->prev = p;
	front = p;
	if (!back) 
		back = front;
	counter++;
}

TlistElement * TdoubleList::pop_front()
{
	TlistElement * p;

	if (front)
	{
		p = front;
		front = front->next;
		if (!front) 
			back = NULL;
		else 
			front->prev = NULL;
		counter--;
		return p;
	}
	else return NULL;
}

TlistElement * TdoubleList::index(unsigned n)
{
	TlistElement * p;

	if ((!n) || (n > counter))
		return NULL;
	else if (n == counter)
		return back;
	else if (n < counter / 2)//sprawdzanie w ktorej polowie listy jest szukana
	{
		p = front;
		while (--n)
			p = p->next;
		return p;
	}
	else
	{
		p = back;
		while (counter > n++)
			p = p->prev;
		return p;
	}
}

TlistElement * TdoubleList::pop_back()
{
	TlistElement * p;

	if (back)
	{
		p = back;
		if (p == front) front = back = NULL;
		else
		{
			back = back->prev;
			back->next = NULL;
		};
		counter--;
		return p;
	}
	else return NULL;
}

void TdoubleList::push_back(TlistElement * p)
{
	if (back) back->next = p;
	p->next = NULL; p->prev = back;
	back = p;
	if (!front) front = back;
	counter++;
}
