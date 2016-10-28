#include "ShuttingYardAlgorithm.h"

int ShuttingYardAlgorithm::verifyInput(string &s)
{
	int parenthise = 0;
	int numbers = 0;
	size_t found;
	string expected = "0123456789+-*/^%.sincotglqr!exp()~";
	for (unsigned i = 0; i < s.size(); i++)
	{

		found = expected.find(s[i]);
		if (found == string::npos)
			return 0;

		if (isdigit(s[i]))
			numbers++;

		if (s[i] == '(')
		{
			parenthise++;
			if (s[i + 1] == ')')
				return 0;
		}
		
		if (s[i] == ')')
			parenthise--;

		if (s[i] == '.' && i==0)
			return 0;

		if (i>0 && s[i] == '.' && (!(isdigit(s[i - 1])) || !(isdigit(s[i + 1]))) )
			return 0;

		if (s[i] == '-' && i == 0)
			s[i] = '~';

		if (s[i] == '-' && i > 0 && !(isdigit(s[i - 1])))
			s[i] = '~';

		if (s[i] == 's' && i > 0 && isdigit(s[i - 1]))
			return 0;

		if (s[i] == 'c' && i > 0 && isdigit(s[i - 1]))
			return 0;

		if (s[i] == 't' && i > 0 && isdigit(s[i - 1]))
			return 0;

		if (s[i] == 'e' && i > 0 && isdigit(s[i - 1]))
			return 0;

		if (s[i] == 'l' && i > 0 && isdigit(s[i - 1]))
			return 0;
	}

	if (numbers <= 0 || parenthise != 0)
		return 0;
	else return 1;
}

int ShuttingYardAlgorithm::priorityCheck(string s)
{
	if (s == "(")
		return -1;
	if (s == ")")
		return 5;
	if (s == "~")
		return 4;
	if (s == "sin" || s == "cos" || s == "tg" || s == "ctg" || s == "log" || s == "ln" || s == "!" || s == "exp")
		return 3;
	if (s == "^" || s == "sqrt")
		return 2;
	if (s == "*" || s == "/")
		return 1;
	if (s == "+" || s == "-")
		return 0;

	
}

myVector<token> ShuttingYardAlgorithm::GenerateRPN(string s)
{
	TlistElement * p;
	s.erase(remove_if(s.begin(), s.end(), isspace), s.end());//usuwanie bialych znakow
	myVector<token> output;
	//output.clear();
	stringstream buffer;
	regex e("((\\d*\\.\\d+)|(\\d+)|([\\+\\-\\*/\\(\\)\\!~%\\^)])|(sin)|(cos)|(ctg)|(tg)|(sqrt)|(log)|(ln)|(exp))");
	regex_iterator<std::string::iterator> rit(s.begin(), s.end(), e);
	regex_iterator<std::string::iterator> rend;

	if (verifyInput(s) == 1)
	{
		while (rit != rend)
		{
			
			token t;
			buffer.clear();
			buffer << (rit->str());
			++rit;
			if (isdigit(buffer.peek()))
			{
				buffer >> t.val;
				output.push_back(t);
			}
			else
			{
				buffer >> t.op;
				if (stack.size() != 0)
				{
					if (priorityCheck(t.op) == -1)//nawias otwierajacy na stos
					{
						p = new TlistElement;
						p->key = t.op;
						stack.push_front(p);
					}
					else
					{
						if (priorityCheck(t.op) == 5)
						{// jesli nawias zamykajacy do ze stosu do wyjscia az do znalezienia nawiasu otwierajacego, nawias otwierajacy ze stosu
							while (stack.front ->key != "(")
							{
								p = new TlistElement;
								p = stack.pop_front();
								token tt;
								tt.op = p->key;
								output.push_back(tt);
							}
							stack.pop_front();
						}
						else
						{
							p = new TlistElement;
							p = stack.front;
							if (t.op == "^")
							{
								while (stack.size() >= 1 && priorityCheck(t.op) < priorityCheck(stack.front->key))
								{
									p = stack.pop_front();
									token ttt;
									ttt.op = p->key;
									output.push_back(ttt);
								}
								p = new TlistElement;
								p->key = t.op;
								stack.push_front(p);
							}
							else
							{
								if (priorityCheck(t.op) > priorityCheck(stack.front->key))
								{//jesli czytany operator ma wyzszy prioritet niz poprzednik to na stos
									p = new TlistElement;
									p->key = t.op;
									stack.push_front(p);
								}
								else
								{// jesli t.op jest grupowany od lewej do prawej i ma prioritet mniejszy lub rowny operatorowi na stosie
									while (stack.size() >= 1 && priorityCheck(t.op) <= priorityCheck(stack.front->key))
									{
										
										p = stack.pop_front();
										token tttt;
										tttt.op = p->key;
										output.push_back(tttt);
									}
									p = new TlistElement;
									p->key = t.op;
									stack.push_front(p);
								}
							}
						}
					}
				}
				else
				{	//jesli jest 1 operatorem
					p = new TlistElement;
					p->key = t.op;
					stack.push_front(p);
				}
			}
		}
	}
	while (stack.size() != 0)
	{
		p = new TlistElement;
		p = stack.pop_front();
		token ttttt;
		ttttt.op = p->key;
		output.push_back(ttttt);
	}
	return output;
}

string ShuttingYardAlgorithm::Evaluation(myVector<token>input, bool mode)
{//+ - * ^ sqrt sin cos tg ctg ! ~ log ln
	myVector<double> calc;

	//calc.clear();
	double x, y;
	string output;
	//string erroutput = "Error";
	for (unsigned i = 0; i<input.size(); i++)
	{
		if (input[i].op.empty())
		{
			calc.push_back(input[i].val);
		}
		else
		{
			if (input[i].op == "+")
			{
				if (calc.size() < 2)
					throw 0;
				x = calc.back();
				calc.pop_back();
				y = calc.back();
				calc.pop_back();
				calc.push_back(x+y);
			}
			if (input[i].op == "-")
			{
				if (calc.size() < 2)
					throw 0;
				x = calc.back();
				calc.pop_back();
				y = calc.back();
				calc.pop_back();
				calc.push_back(y-x);
			}
			if (input[i].op == "*")
			{
				if (calc.size() < 2)
					throw 0;
				x = calc.back();
				calc.pop_back();
				y = calc.back();
				calc.pop_back();
				calc.push_back(x*y);
			}
			if (input[i].op == "/")
			{
				if (calc.size() < 2)
					throw 0;
				x = calc.back();
				if (x == 0)
					throw 0;
				calc.pop_back();
				y = calc.back();
				calc.pop_back();
				calc.push_back(y/x);
			}
			if (input[i].op == "exp")
			{
				if (calc.size() < 1)
					throw 0;
				x = calc.back();
				if (x < 1)
					throw 0;
				calc.pop_back();
				calc.push_back(exp(x));
			}
			if (input[i].op == "^")
			{
				if (calc.size() < 2)
					throw 0;
				x = calc.back();
				calc.pop_back();
				y = calc.back();
				calc.pop_back();
				calc.push_back(pow(y,x));
			}
			if (input[i].op == "~")
			{
				if (calc.size() < 1)
					throw 0;
				x = calc.back();
				calc.pop_back();
				calc.push_back(0-x);
			}
			if (input[i].op == "!")
			{
				if (calc.size() < 1)
					throw 0;
				x = calc.back();
				calc.pop_back();
				calc.push_back(factorial(x));
			}
			if (input[i].op == "log")
			{
				if (calc.size() < 1)
					throw 0;
				x = calc.back();
				if (x <= 0)
					throw 0;
				calc.pop_back();
				calc.push_back(log10(x));
			}
			if (input[i].op == "ln")
			{
				if (calc.size() < 1)
					throw 0;
				x = calc.back();
				if (x <= 0)
					throw 0;
				calc.pop_back();
				calc.push_back(log(x));
			}
			if (input[i].op == "sqrt")
			{
				if (calc.size() < 1)
					throw 0;
				x = calc.back();
				if (x < 0)
					throw 0;
				calc.pop_back();
				calc.push_back(sqrt(x));
			}
			if (input[i].op == "sin")
			{// mode = true rad , false deg
				if (calc.size() < 1)
					throw 0;
				if (mode == true)
				{
					x = calc.back();
					calc.pop_back();
					calc.push_back(sin(x));
				}
				else
				{
					x = calc.back();
					calc.pop_back();
					calc.push_back(sin(x*3.14159265358979323846 / 180));
				}
			}
			if (input[i].op == "cos")
			{
				if (calc.size() < 1)
					throw 0;
				if (mode == true)
				{
					x = calc.back();
					calc.pop_back();
					calc.push_back(cos(x));
				}
				else
				{
					x = calc.back();
					calc.pop_back();
					calc.push_back(cos(x*3.14159265358979323846 / 180));
				}
			}
			if (input[i].op == "tg")
			{
				if (calc.size() < 1)
					throw 0;
				if (mode == true)
				{
					x = calc.back();
					if (x == 3.14159265358979323846 / 2)
						throw 0;
					calc.pop_back();
					calc.push_back(tan(x));
				}
				else
				{
					x = calc.back();
					calc.pop_back();
					calc.push_back(tan(x*3.14159265358979323846 / 180));
				}
			}
			if (input[i].op == "ctg")
			{
				if (calc.size() < 1)
					throw 0;
				if (mode == true)
				{
					x = calc.back();
					calc.pop_back();
					calc.push_back(tan((3.14159265358979323846/2) - x));
				}
				else
				{
					x = calc.back();
					calc.pop_back();
					calc.push_back(tan(((3.14159265358979323846 / 2) - x)*3.14159265358979323846 / 180));
				}
			}
		}
	}


	if (calc.size() > 1)
		throw 0;
	else
	{
		if (calc[0] == INFINITY)
			throw 0;
		output = to_string(calc[0]);
		return output;
	}
}

double ShuttingYardAlgorithm::factorial(double x)
{
	double silnia=1;
	int y;
	y = x;
	if (x - y != 0)
		throw 0;
	else
	{
		if (x == 0)
			return 1;
		else
		{
			if (x > 0)
			{
				for (int i = 1; i <= x; i++)
					silnia = i*silnia;
				return silnia;
			}
			else
				throw 0;
		}
	}

}