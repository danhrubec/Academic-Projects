#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

queue<string> GetInput()
{
    queue<string> Q;
    string token;
    
    cin >> token;
	while(token != "#")
	{
		Q.push(token);
		
		cin >> token;
		
	}
	
    return Q;
}

bool EvaluatePostfix(queue<string> input, int& result)
{
	stack<int> operands;
	bool flag = true;
	
	while(input.empty() == false)
	{
		string s = input.front();
		input.pop();
	
		if(isdigit(s[0]) )
		{
			operands.push(stoi(s));
		}
		else
		{
			int num1, num2, num3;
			if(operands.size() >= 2)
			{
				num1 = operands.top();
				operands.pop();
				num2 = operands.top();
				operands.pop();
				
			}
			else
			{
				flag = false;
				result = operands.top();
				return flag;
				break;
			}
		
			if(s[0] == '+')
			{
				num3 = num2 + num1;
				operands.push(num3);
			}
			else if(s[0] == '-')
			{
				num3 = num2 - num1;
				operands.push(num3);
			}
			else if( s[0] == '*')
			{
				num3 = num2 * num1;
				operands.push(num3);
			}
			else if( s[0] == '/')
			{
				num3 = num2 / num1;
				operands.push(num3);
			}
			else
			{
				flag = false;
				operands.push(num2);
				operands.push(num1);
			}
		
		}
	}
	if(operands.size() != 1)
	{
		flag = false;
	}
	result = operands.top();
	return flag;
	
	
	
	
}


int main()
{
    
    queue<string> input = GetInput();
	
	int total;
	
	bool val = EvaluatePostfix(input, total);
    
    if( val == true)
	{
    
		cout << total << endl;
	}
	else
	{
		cout << "invalid" << endl;
	}
    
    return 0;
}