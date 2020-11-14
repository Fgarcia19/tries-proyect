#include <iostream>
#include <ctime>
#include "fstream"
#include "tst/tst.cpp"
#include "trie/Trie.h"
#include "radix/radix_tree.h"


int main()
{
    vector<string> consultas;
    vector<string> ini;

    unsigned t0, t1;
    tst t("direcciones.txt");
    Trie tr("direcciones.txt");
    RadixTree rt("direcciones.txt");
    ifstream c("consultas.txt");
    ifstream inician("inician.txt");

    string line;
    while (!c.eof()) {
        getline(c,line);
        consultas.push_back(line);

    }

    while (!inician.eof()) {
        getline(inician,line);
        ini.push_back(line);
    }

    /* Para el trie*/
    double time_trie_repetidos;

    for(auto i:consultas)
    {
      t0=clock();
      tr.find(i);
      t1=clock();
      time_trie_repetidos+=(double(t1-t0)/CLOCKS_PER_SEC);
    }

    double time_trie_inician;

    for(auto i:ini)
    {
      t0=clock();
      tr.printPrefix(i);
      t1=clock();
      time_trie_inician+=(double(t1-t0)/CLOCKS_PER_SEC);
    }

    time_trie_repetidos/=100;
    time_trie_inician/=100;

    auto s_trie=tr.countRam();


    /* Para el time_radix_repetidos*/
    double time_radix_repetidos;
    double time_radix_inician;


    for(auto i:consultas)
    {
      t0=clock();
      rt.find_all(i);
      t1=clock();
      time_radix_repetidos+=(double(t1-t0)/CLOCKS_PER_SEC);
    }


    for(auto i:ini)
    {
      t0=clock();
      rt.find_all(i);
      t1=clock();
      time_radix_inician+=(double(t1-t0)/CLOCKS_PER_SEC);
    }

    time_radix_repetidos/=100;
    time_radix_inician/=100;
    auto s_radix=rt.ram_usage();

    /* Para el tst*/

    double time_ternary_repetidos;
    double time_ternary_inician;


    for(auto i:consultas)
    {
      t0=clock();
      t.find(i);
      t1=clock();
      time_ternary_repetidos+=(double(t1-t0)/CLOCKS_PER_SEC);
    }

    for(auto i:ini)
    {
      t0=clock();
      t.find_inician_con(i);
      t1=clock();
      time_ternary_inician+=(double(t1-t0)/CLOCKS_PER_SEC);
    }

    time_ternary_repetidos/=100;
    time_ternary_inician/=100;

    auto s_ter=t.ram();


    cout<<"In trie: "<<endl;
    cout<<"Repetidos: "<<time_trie_repetidos<<endl;
    cout<<"Inician: "<<time_trie_inician<<endl;
    cout<<"Nodos "<<s_trie.first<<" ,Tamano "<<s_trie.second<<endl;

    cout<<"In Radix: "<<endl;
    cout<<"Repetidos: "<<time_radix_repetidos<<endl;
    cout<<"Inician: "<<time_radix_inician<<endl;
    cout<<"Nodos "<<s_radix.first<<" ,Tamano "<<s_radix.second<<endl;



    cout<<"In TST: "<<endl;
    cout<<"Repetidos: "<<time_ternary_repetidos<<endl;
    cout<<"Inician: "<<time_ternary_inician<<endl;
    cout<<"Nodos "<<s_ter.first<<" ,Tamano "<<s_ter.second<<endl;

}
