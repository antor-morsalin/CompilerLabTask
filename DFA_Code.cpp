#include<iostream>
using namespace std;

bool Q5(int i, string &s)
{
    if(i >= s.size())
    {
        return true;
    }
    if(s[i]=='b')
    {
        return Q5(i+1, s);
    }
    return false;
}
bool Q4(int i, string &s)
{
    if(i >= s.size())
    {
        return true;
    }
    if(s[i]=='b')
    {
        return Q5(i+1, s);
    }
    return false;
}
bool Q3(int i, string &s)
{
    if(i >= s.size())
    {
        return true;
    }
    if(s[i]=='a')
    {
        return Q3(i+1, s);
    }
    return false ;
}
bool Q2(int i, string &s)
{
    if(i >= s.size())
    {
        return true;
    }
    if(s[i]=='a')
    {
        return Q3(i+1, s);
    }
    else if(s[i]=='b')
    {
        return Q4(i+1, s);
    }
    return false ;
}
bool Q1(int i, string &s)
{
    if(i >= s.size())
    {
        return true;
    }
    if(s[i] == 'a')
    {
        return Q2(i+1, s);
    }
    return false ;
}


int main()
{
    while(true)
    {
        cout<<"Enter the string : ";
        string s ; cin>>s ;
        if(Q1(0, s))
        {
            cout<<"The given string is ACCEPTED"<<endl<<endl;
        }
        else
        {
            cout<<"The given string is REJECTED"<<endl<<endl;
        }
    }

    return 0 ;
}







