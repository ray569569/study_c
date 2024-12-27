#include<iostream>
#include<cstring>
#include<cctype>
using namespace std;

int main()
{
    string input;
    cout<<"Enter a sentence: ";
    getline(cin,input);
    int count[26] = {0},i,wordCount=0;
    for(i = 0; i< input.size();i++)
    {
        if(((input[i]>='a' && input[i] <= 'z')||(input[i]>='A' && input[i] <= 'Z'))&&(input[i+1]=='.'||input[i+1]==','||input[i+1]==' '))
            wordCount++;
        if(input[i]>='a' && input[i] <= 'z')
            count[input[i]-'a']++;
        if(input[i]>='A' && input[i] <= 'Z')
            count[input[i]-'A']++;
    }
    char x = input[input.size()-1];
    if(x != '.' && x != 'z' && x!= ' ')
        wordCount++;
    cout<<endl<<wordCount<<" words "<<endl;
    for(i=0; i<26; i++)
    {
        if(count[i]>0)
        cout<<count[i]<<" "<<(char)('a'+i)<<endl;
    }
    return 0;
}