#include<iostream>
#include<fstream>
#include<string>
using namespace std;

string infunction(string line);
string outfunction(string line);

int main()
{
    string filename;
    ofstream output;
    ifstream input;
    string text;

    cout<<"input filename:";
    cin>>filename;

    input.open(filename);
    output.open("ofile.txt");

    if(input.fail())
    {
        cout<<"input open error";
        exit(1);
    }
    if(output.fail())
    {
        cout<<"output open error"<<endl;
        exit(1);
    }

    while(!input.eof())
    {
        getline(input,text);
        for(int i=0;i<text.size();i++)
        {
            if((text[i] == 'c') and (text[i+1] == 'i') and (text[i+2] == 'n'))
            {
                string temp;
                temp = text.substr(0,i+3);
                
                for(int j=i+3;j<text.length();j++)
                {
                    if(text[j] != ' ')
                    {
                        temp = temp + ' ' +  text.substr(j);;
                        break;
                    }
                }
                
                text = infunction(temp);
                break;
            }
            else if((text[i] == 'c') and (text[i+1] == 'o') and (text[i+2] == 'u') and (text[i+3] == 't'))
            {
                string temp;
                temp = text.substr(0,i+4);
                for(int j=i+4;j<text.length();j++)
                {
                    if(text[j] != ' ')
                    {
                        temp = temp + ' ' +  text.substr(j);;
                        break;
                    }
                }
                text = outfunction(temp);
                break;
            }  
        } 
        output<<text;
        if(!input.eof())
        output<<endl;
    }
    input.close();
    output.close();
    return 0;
}

string infunction(string line)
{
    bool light = false;

    for(int i=0;i<line.size();i++)
    {
        if(line[i] == '"')
        {
            light = !light;
        }
        if(light == false && line[i] == '<' && line[i+1] == '<' )
        {
            line[i] = '>';
            line[i+1]= '>';
        }
    }
    return line;
}

string outfunction(string line)
{
    bool light = false;

    for(int i=0;i<line.size();i++)
    {
        if(line[i] == '"')
        {
            light = !light;
        }
        if(light == false && line[i] == '>' && line[i+1] == '>' )
        {
            line[i] = '<';
            line[i+1]= '<';
        }
    }
    return line;
}