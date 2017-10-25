#include <iostream>
#include <stdlib.h>
#include <stack>
#include <cassert>
#include <fstream>
#include <string>

using namespace std;
stack<string> check;

void keyWord(string temp, int line)
{
	if (temp == "begin")
	{
		check.push(temp);
	}
	else
	{
		if (check.empty())
		{
			cout << "Error in line " << line << ". You should use 'Begin' at the start of a code block." << endl;
			exit(0);
		}
		if (temp == "if")
		{
			if (check.top() != "if")
			{
				check.push(temp);
			}
			else
			{
				cout << "Error in line " << line << ". You shoud not use 'if' after 'if'." << endl;
				exit(0);
			}
		}
		else if (temp == "then")
		{
			if (check.top() == "if")
			{
				check.push(temp);
			}
			else
			{
				cout << "Error in line " << line << ". No match 'if' before 'then'." << endl;
				exit(0);
			}
		}
		else if (temp == "else")
		{
			if (check.top() == "then")
			{
				check.pop();
				check.pop();
			}
			else
			{
				cout << "Error in line " << line << ". No match 'then' before 'else'." << endl;
				exit(0);
			}
		}
		else if (temp == "end")
		{
			if (check.top() == "then")
			{
				check.pop();
				check.pop();
			}
			if (check.top() == "begin")
			{
				check.pop();
			}
			else
			{
				cout << "Error in line " << line << ". No match 'begin' before 'end'." << endl;
				exit(0);
			}
		}
	}
}

void judgePac(string file)
{
	ifstream infile;               // 读取文件
	infile.open(file.data());
	assert(infile.is_open());

	string s;
	int line = 0;
	cout << "Opening file " << file << " success! \nStart checking..." << endl;
	while (getline(infile, s)) // 按行读取
	{
		line += 1;
		if (!s.empty())	 // 过滤掉空白行
		{
			string temp("");
			s += ';';               // 方便取出最后一个词
			for (unsigned int i = 0; i < s.size(); i++) // 按字节读取
			{
				if (temp == "//" || temp == "{") break;      // 遇到注释符号跳过
				if (s[i] == ' ' || s[i] == '(' || s[i] == ')' || s[i] == '\t' || s[i] == ';') // 遇到停顿符号取出前一个词
				{
					if (temp == "begin" || temp == "end" || temp == "if" || temp == "then" || temp == "else") keyWord(temp, line);     // 为关键词则执行判定
					temp = "";
				}
				else // 不是停顿词则累加当前字符
				{
					temp += s[i];
				}
			}
		}
	}
	if (check.empty()) // 程序结束后判断堆栈是否为空
	{
		cout << "Correct!" << endl;
	}
	else
	{
		cout << "Incorrect! 'end' missed at the end." << endl;
		exit(0);
	}
	infile.close();
}

int main()
{
  //cout << "21709155    " << "梅海洋    " << "计算机科学与技术学院" << "\n";
	judgePac("test_pascal.pas");            // 执行判定程序
	cout << "Checking finished!" << endl;

	return 0;
}
