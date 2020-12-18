/**
*author: Ezgi ÖZDÝKYAR
*/
#include<string>
#include<stack>
#include<sstream>
#include<iostream>
using namespace std;

int precedence(char operatorr)
{
    if (operatorr == '^')
        return 3;
    else if (operatorr == '*' || operatorr == '/')
        return 2;
    else if (operatorr == '+' || operatorr == '-')
        return 1;
    else
        return -1;
}
///----------------------------------------------------------------------------------
/// Given an expression in infix-notation, converts it to a string in post-fix notation 
/// 

string Infix2Postfix(string &s) {
    stack<char> postfix;
    stringstream tempStr(s);
    string result;
    char splitedCh;
    while (tempStr >> splitedCh)
    {
        if (isdigit(splitedCh))
            result += splitedCh;
        else if (splitedCh == '(')
            postfix.push('(');
        else if (splitedCh == ')')
        {
            while (!postfix.empty() && postfix.top() != '(')
            {
                result += ' '; 
                result += postfix.top();
                postfix.pop();
            }
            postfix.pop();
        }
        else
        {
            result += ' ';
            while (!postfix.empty() && precedence(splitedCh) <= precedence(postfix.top()))
            {
                result += postfix.top();
                result += ' ';
                postfix.pop();
            }
            postfix.push(splitedCh);
        }
    }

    while (!postfix.empty())
    {
        result += ' ';
        result += postfix.top();
        postfix.pop();
    }
    return result;
} // end-Infix2Postfix

///----------------------------------------------------------------------------------
/// Given a string in post-fix notation, evaluates it and returns the result
/// 
int EvaluatePostfixExpression(string& s) {
	stack<int> result;
    stringstream tempStr(s);
    string splitedStr;
    while (tempStr >> splitedStr)
    {
        if (splitedStr != "-" && splitedStr != "+" && splitedStr != "*" && splitedStr != "/")
            result.push(stoi(splitedStr));
        else
        {
            int number1 = result.top();
            result.pop();
            int number2 = result.top();
            result.pop();
            if (splitedStr == "+")
                result.push(number1 + number2);
            else if (splitedStr == "-")
                result.push(number2 - number1);
            else if (splitedStr == "*")
                result.push(number2 * number1);
            else if (splitedStr == "/")
                result.push(number2 / number1);
        }
    }
    return result.top();
} // end-EvaluatePostfixExpression
