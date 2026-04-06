#include<iostream>
#include<fstream>
using namespace std;

string keywords[] = {"int", "cout", "endl", "return"};
string operators[] = {"=", "<<", ">>", "+", "*"};
string punctuations[] = {"(", ")", "{", "}", ";"};

string code = "";
int i = 0;

void tokenize(string value, string type)
{
    cout << "(" << value << ", " << type << ")" << endl;
}

string getTerm(int start)
{
    string word = "";

    while(start < code.length() && code[start] == ' ')
    {
        start++;
    }

    while(start < code.length() && code[start] != ' ')
    {
        word += code[start];
        start++;
    }

    i = start;
    return word;
}

bool isNumeric(string word)
{
    for(int j = 0; j < word.length(); j++)
    {
        if(word[j] < '0' || word[j] > '9')
        {
            return false;
        }
    }

    return true;
}

string isString(int start)
{
    string word = "";

    while(start < code.length() && code[start] == ' ')
    {
        start++;
    }

    if(start < code.length() && code[start] == '"')
    {
        word += code[start];
        start++;

        while(start < code.length())
        {
            word += code[start];

            if(code[start] == '"')
            {
                start++;
                i = start;
                return word;
            }

            start++;
        }
    }

    return "none";
}

string isKeyword(int start)
{
    string word = "";

    while(start < code.length() && code[start] != ' ')
    {
        word += code[start];
        start++;
    }

    for(int j = 0; j < 4; j++)
    {
        if(word == keywords[j])
        {
            i = start;
            return word;
        }
    }

    return "none";
}

bool isOperator(string word)
{
    for(int j = 0; j < 5; j++)
    {
        if(word == operators[j])
        {
            return true;
        }
    }

    return false;
}

bool isPunctuation(string word)
{
    for(int j = 0; j < 5; j++)
    {
        if(word == punctuations[j])
        {
            return true;
        }
    }

    return false;
}

int main()
{
    ifstream file("sourceCode.txt");
    string line = "";

    while(getline(file, line))
    {
        code += line;
        code += " ";
    }

    while(i < code.length())
    {
        if(code[i] == ' ')
        {
            i++;
        }
        else
        {
            string result = isKeyword(i);

            if(result != "none")
            {
                tokenize(result, "keyword");

                if(result == "int")
                {
                    string id = getTerm(i);

                    if(isNumeric(id))
                    {
                        tokenize(id, "constant");
                    }
                    else
                    {
                        tokenize(id, "identifier");
                    }

                    string next = getTerm(i);

                    if(isPunctuation(next))
                    {
                        tokenize(next, "punctuation");
                    }
                    else if(next == "=")
                    {
                        tokenize(next, "operator");

                        string value = getTerm(i);

                        if(isNumeric(value))
                        {
                            tokenize(value, "constant");
                        }
                        else
                        {
                            tokenize(value, "identifier");
                        }
                    }
                }
                else if(result == "cout")
                {
                    while(i < code.length())
                    {
                        string next = getTerm(i);

                        if(next == "<<")
                        {
                            tokenize(next, "operator");

                            string str = isString(i);

                            if(str != "none")
                            {
                                tokenize(str, "constant");
                            }
                            else
                            {
                                string value = getTerm(i);

                                if(isNumeric(value))
                                {
                                    tokenize(value, "constant");
                                }
                                else
                                {
                                    tokenize(value, "identifier");
                                }
                            }
                        }
                        else if(next == ";")
                        {
                            tokenize(next, "punctuation");
                            break;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
            else
            {
                string term = getTerm(i);

                if(isOperator(term))
                {
                    tokenize(term, "operator");
                }
                else if(isPunctuation(term))
                {
                    tokenize(term, "punctuation");
                }
            }
        }
    }

    return 0;
}
