#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

class RadixNode{
  private:
    string name;
    map<char,RadixNode*> childrens;
    vector<int> index;
  public:
    int cantidad;
    RadixNode(string _name){
      name=_name;
      cantidad=0;
    }
    map<char,RadixNode*> get_childrens(){
      return childrens;
    }
    vector<int> get_index(){
      return index;
    }
    void copy_node(RadixNode* source_node){
      childrens=source_node->get_childrens();
      cantidad=source_node->cantidad;
      index = source_node->get_index();
    }
    string get_name(){
      return name;
    }
    void add_child(string _child_name,int direc){
      if(name==_child_name){
        cantidad++;
        index.push_back(direc);
        return;
      }
      int i= 0;
      while(name[i]==_child_name[i])i++;

      //cout <<"Nueva palabra es mas larga que nodo actual"<<endl;
      if(i==name.length() ){
        if(childrens.count(_child_name[i])==0){
          RadixNode* n_nodo = new RadixNode(string(_child_name,i,_child_name.length()-i));
          childrens.insert(make_pair(_child_name[i],n_nodo));
          n_nodo->cantidad++;
          n_nodo->index.push_back(direc);
        }
        else{
          childrens[_child_name[i]]->add_child(string(_child_name,i,_child_name.length()-i),direc);
        }
      }//Nueva palabra es mas chica que el nodo actual
      else if(i==_child_name.length()){
        RadixNode* n_nodo1 = new RadixNode(string(name,i,name.length()-i));
        n_nodo1->copy_node(this);

        childrens.clear();
        index.clear();
        childrens.insert(make_pair(name[i],n_nodo1));
        name = string(name,0,i);
        cantidad = 1;
        index.push_back(direc);

      }
      else{
        //cout <<"caso 3"<<endl;
        RadixNode* n_nodo1 = new RadixNode(string(name,i,name.length()-i));
        RadixNode* n_nodo2 = new RadixNode(string(_child_name,i,_child_name.length()-i));
        n_nodo1->copy_node(this);

        childrens.clear();
        index.clear();
        childrens.insert(make_pair(name[i],n_nodo1));
        childrens.insert(make_pair(_child_name[i],n_nodo2));
        name = string(name,0,i);
        cantidad = 0;

        n_nodo2->cantidad++;
        n_nodo2->index.push_back(direc);
      }

    }
    RadixNode* find(string obj){
      if(obj.length()==0){
        cout<<"no existe"<<endl;
        return nullptr;
      }
      if(name==obj){
        return this;
      }
      int i= 0;
      while(name[i]==obj[i])i++;
      if(i==obj.length())return nullptr;
      if(childrens.count(obj[i])==0){
        cout<<"no existe"<<endl;
        return nullptr;
      }
      return childrens[obj[i]]->find(string(obj,i,obj.length()-i));

    }
    RadixNode* find2(string obj){
      if(obj.length()==0){
        cout<<"no existe"<<endl;
        return nullptr;
      }
      if(name==obj){
        return this;
      }
      int i= 0;
      while(name[i]==obj[i])i++;
      if(i==obj.length())return this;
      if(childrens.count(obj[i])==0){
        cout<<"no existe"<<endl;
        return nullptr;
      }
      return childrens[obj[i]]->find2(string(obj,i,obj.length()-i));

    }
    void print(int level){
      for(auto it=childrens.begin();it!=childrens.end();it++){
        for (int k = 0; k < level; k++) {
          cout << "    ";
        }
        it->second->print(level+1);

      }
      cout <<" "<< name<<endl;
    }

    void print2(int level){
      cout << name<<"-"<<cantidad<<"-"<<index.size()<<endl;
      for(auto it=childrens.begin();it!=childrens.end();it++){
        for (int k = 0; k < level; k++) {
          cout << "    ";
        }
        it->second->print2(level+1);

      }
    }
    void print_all(ifstream* file){
      if(cantidad>0){
        for(int i=0;i<cantidad;i++)
        {
          string line;
          file->clear();
          file->seekg(index[i],file->beg);
          getline(*file, line);
          cout<<line<<endl;
        }
      }
      if(!childrens.empty()){
        for(auto e:childrens){
          e.second->print_all(file);
        }
      }
    }

    void print_all(ifstream* file,list<string>& f){
      if(cantidad>0){
        for(int i=0;i<cantidad;i++)
        {
          string line;
          file->clear();
          file->seekg(index[i],file->beg);
          getline(*file, line);
          cout<<line<<endl;
          f.push_back(line);
        }
      }
      if(!childrens.empty()){
        for(auto e:childrens){
          e.second->print_all(file,f);
        }
      }
    }
};

class RadixTree{
  private:
    RadixNode* root;
    ifstream infile;
  public:
    RadixTree(string file){
      root=new RadixNode("");
      infile.open(file);
      string line;
      int pos = infile.tellg();

      while (getline(infile, line))
      {
          int i = line.length()-1;
          string nombre;
          for(i;i>=0;i--){
            if(line[i]=='/'){
              nombre=line.substr(i+1,line.length()-i);
              break;
            }
          }
          // cout<<nombre<<endl;
          insert(nombre,pos);
          pos = infile.tellg();
      }

    }
    void insert(string word,int direc){
      root->add_child(word,direc);
    }
    RadixNode* find(string obj){
      return root->find(obj);
    }

    void find_all(string obj){
      RadixNode* node = root->find2(obj);
      if(node==nullptr){
        cout<<"Find2 retorno nullptr"<<endl;
        return;
      }
      node->print_all(&infile);
    }

    void find_repe(string obj){
      RadixNode* node = root->find2(obj);
      if(node==nullptr){
        cout<<"Find2 retorno nullptr"<<endl;
        return;
      }
      map<string,vector<string>>files;

      list<string> v;
      node->print_all(&infile,v);
      // cout<<"REPETIDOS"<<endl;
      // for(auto i:f)
      // cout<<i<<endl;
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



    void print(){
      root->print2(0);
    }
    void print_node(RadixNode* node){
      if(node==nullptr){
        cout<<"nodo no existe"<<endl;
      }
      string line;
      cout<<"Cantidad: "<<node->cantidad<<endl;
      cout<<endl;
      for(auto e: node->get_index()){
        infile.clear();
        infile.seekg(e,infile.beg);
        getline(infile, line);
        cout<<line<<endl;
      }
    }

    pair<long,long> ram_usage(){
      vector<RadixNode*> nodes;
      int ram_usage=0;
      int cant_nodos=0;
      nodes.push_back(root);
      while(!nodes.empty()){
        cant_nodos++;
        RadixNode* current = nodes.back();
        nodes.pop_back();
        for(auto e:current->get_childrens()){
          nodes.push_back(e.second);
        }
        ram_usage = ram_usage + current->get_name().length();
        ram_usage = ram_usage + current->cantidad*sizeof(int);
        ram_usage = ram_usage + sizeof(map<char,RadixNode*>);
        ram_usage = ram_usage + sizeof(vector<int>);
        ram_usage = ram_usage + current->get_childrens().size()*10;

      }
      cout<<"cantidad de nodos: "<<cant_nodos<<endl;
      cout<<"memoria usada: "<< ram_usage << " bytes"<<endl;
      return {cant_nodos,ram_usage};
    }
};
