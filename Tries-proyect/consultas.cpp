#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;

string extract_file(string line)
{
    string file;
    for(int i=line.size()-1;i>=0;i--)
    {
        if(line[i]=='/')
        return file;

        file=line[i]+file;
    }
}


string partir(string word)
{
  int i=rand()%(word.size()-1)+1;
  return word.substr(0,i);
}

int main()
{
  srand (time(NULL));
  // cout<<partir("hola");
  ifstream c("consultas.txt");
  ofstream i("inician.txt");
  string line;
  c.seekg(0);
  while(!c.eof())
  {
    getline(c,line);
    if(line.size()!=0)
    {
      string a=partir(line);
      i<<a<<endl;
      cout<<a<<endl;
    }
  }
  // fstream f("direcciones.txt");
  // ofstream c("consultas.txt");
  // string line;
  // std::vector<string> v;
  // vector<int> n;
  // f.seekg(0);
  //
  // while(n.size()!=100)
  // {
  //   int a=rand()%129543;
  //   if(find(n.begin(),n.end(),a)==n.end())
  //   {
  //     n.push_back(a);
  //   }
  // }
  // sort(n.begin(), n.end());
  //
  // int i=0;
  // int pos=0;
  // while(!f.eof())
  // {
  //   getline(f,line);
  //   string w=extract_file(line);
  //   if(i==n[pos])
  //   {
  //       c<<w<<endl;
  //       cout<<w<<endl;
  //       v.push_back(w);
  //       pos++;
  //   }
  //   i++;
  // }
}
