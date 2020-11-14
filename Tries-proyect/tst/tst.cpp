#include <iostream>
#include <list>
#include <map>
#include "node.cpp"
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
struct tst
{
    node* root;
    string name;
    tst(string n): name(n),root(nullptr){
      ifstream dir(n);
      dir.seekg(0);
      string line;
      while(!dir.eof())
      {
        unsigned long pos=dir.tellg();
        getline(dir,line);
        string file =extract_file(line);
        auto aux=find_node(file);
        if(aux!=nullptr)
        {
          aux->repeticiones.push_back(pos);
        }
        else{
          auto nuevo=insert(file);
          nuevo->repeticiones.push_back(pos);
        }
      }
    };
    node* insert(string word)
    {
        char* data;
        data=&word[0];
        if(!root) root=new node(*data);
        return root->insert(data);
    }

    node* find(node* current, char* data)
    {
        if(current==nullptr)
            return nullptr;
        if(*data<current->value)
        {
            return find(current->left,data);
        }
        else if(*data>current->value)
        {
            return find(current->right,data);
        }
        else
        {
            if(!*(data+1))
            {
                return current;
            }
            else return find(current->mid,data+1);
        }

    }

    node* find_node(string word)
    {
        char* data;
        data=&word[0];
        return find(root,data);
    }

    list<string> find(string file)
    {
      list<string> v;
      ifstream dir(name);
      string line;
      auto a=find_node(file);
      if(a!=nullptr)
      {
        if(a->end)
        {
          for(auto i:a->repeticiones)
          {
            dir.seekg(i);
            getline(dir,line);
            v.push_back(line);
            cout<<line<<endl;
          }
        }
        else cout<<"No se encuentra"<<endl;
      }
      else
      {std::cout << "No se encuentra" << '\n';}
      dir.close();
      return v;
    }

    void find_repetidos(string f)
    {

        auto v=find(f);
        map<string,vector<string>>files;
        if(v.empty())
          cout<<"No se encuentra"<<endl;
        else
        {
            files[v.front()]={v.front()};
            v.pop_front();
            while(!v.empty())
            {
              bool repetido=false;
              bool nuevo=true;
              for(auto i:files)
              {
                string c="diff "+v.front()+" "+i.first;
                cout<<c<<endl;
                char* comand;
                comand=&c[0];
                if(!system(comand))
                {
                  repetido=true;
                  cout<<"REPETIDO"<<endl;
                  files[i.first].push_back(v.front());
                  break;
                }
              }
              if(!repetido)
                files[v.front()]={v.front()};
              v.pop_front();
            }
        }
          int k=1;
          for(auto i:files)
          {
            cout<<"El ";
            cout<<k;
            cout<<" archivo se encuentra en repetido: "<<i.second.size()<<" veces, en"<<endl;
            for(auto j:i.second)
            cout<<j<<endl;
            k++;
          }
    }


    int go_down(node * current,int& size)
    {
      if(current!=nullptr)
      {
          ifstream f(name);
          for(auto i:current->repeticiones)
          {
            f.seekg(i);
            string line;
            getline(f,line);
            cout<<line<<endl;
          }
          size+=sizeof(*current)+sizeof(current);
          int l=go_down(current->left,size);
          int m=go_down(current->mid,size);
          int r=go_down(current->right,size);
          return current->repeticiones.size()+l+r+m;
      }
      return 0;
    }

    int go_down_count(node * current,int& size)
    {
      if(current!=nullptr)
      {
          ifstream f(name);
          for(auto i:current->repeticiones)
          {
            f.seekg(i);
            string line;
            getline(f,line);
            cout<<line<<endl;
          }
          size+=sizeof(*current)+sizeof(current)+current->repeticiones.size();
          int l=go_down_count(current->left,size);
          int m=go_down_count(current->mid,size);
          int r=go_down_count(current->right,size);

          return current->repeticiones.size()+l+r+m;
      }
      return 0;


    }




    void find_inician_con(string word)
    {
      auto aux=find_node(word);

      if(aux==nullptr)
        cout<<"No se encuentra"<<endl;
      else
      {
        int i=0;
        int total=go_down(aux,i);
        cout<<"Hubieron "<<total<<" archivos"<<endl;
      }
    };

    pair<int,int> ram()
    {
      int size=0;
      int numero=go_down_count(root,size);
      // cout << "Hay "<<numero << " nodos." <<endl;
      // cout << "Se ocupan "<<size<< " bytes" << endl;
      return {numero,size};

    }
};
