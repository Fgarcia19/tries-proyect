
#include <iostream>
#include <vector>
using namespace std;
struct node
{
    char value;
    bool end;
    node* left,*mid,*right;
    vector<unsigned long> repeticiones;
    node(char data){

        value=data;
        end=false;
        left=nullptr;
        right=nullptr;
        mid=nullptr;

    }
    node* insert(char* data){
        if(*data<value)
        {
            if(left==nullptr) left=new node(*data);
            return left->insert(data);
        }
        else if(*data>value)
        {
            if(right==nullptr) right=new node(*data);
            return right->insert(data);
        }
        else
        {

            if(*(data+1))
            {

                if(mid==nullptr) mid=new node(*(data+1));
                return mid->insert((data+1));
            }
            else
            {
                end=true;
                return this;
            }

        }


    }
};
