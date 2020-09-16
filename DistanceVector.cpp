#include <utility>
#include <map>
#include <algorithm>
#include <cmath> 
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream> 
#include <stdlib.h> 
#include <iostream>
#include <string>
using namespace std;

int numberOfrouters;
vector<string> nameOfrouters;
int numberOflinks;
vector<string> detailsOflinks;
string destinations;


struct Node
{
    string name;
    vector<string> neibor_name;
    vector<int> neibor_distance;
    vector<vector<int> > distanceTable;

};

class DistanceVector
{
public:
    DistanceVector(string first, string second);
    void setup(Node *n); //initialize the node's val, and initialize the table
    void print_table_t1(Node *p);
    int helper_index(string n); //help to find the position
    int helper_getval(string n, Node *p);//help to find the position's value
    void print_table_tn(Node *p,int times);
    void input(string filename,int count);
    
};
DistanceVector::DistanceVector(string first, string second){
    input(first,1);
    input(second,2);
}
void DistanceVector::setup(Node *n){
     string temp = n->name;
     for (int i = 0; i < detailsOflinks.size(); ++i)
     {
       for (int j = 0; j < detailsOflinks[i].length(); ++j)
       {

            string get_val;
            get_val= detailsOflinks[i].substr(4,detailsOflinks[i].length()-4);
            int int_val;
         int_val = stoi(get_val);
           if (detailsOflinks[i].substr(j,1) == temp && j==0)
           {
                n->neibor_name.push_back(detailsOflinks[i].substr(2,1));
                n->neibor_distance.push_back(int_val);
           }
           else if (detailsOflinks[i].substr(j,1)== temp && j==2)
           {
                n->neibor_name.push_back(detailsOflinks[i].substr(0,1));
                n->neibor_distance.push_back(int_val);
           }
       }
     }
     // initialization of the distance table
    vector<vector<int>>dp(n->neibor_name.size()+1, vector<int>(numberOfrouters+1,-1));
     n->distanceTable = dp;
     for (int i = 0; i < numberOfrouters; ++i)
     {
         for (int j = 0; j < n->neibor_name.size(); ++j)
         {
            string temp;
            temp = n->neibor_name[j];
            int temp2;
            temp2 = n->neibor_distance[j];
            int rowIndex =0;
            int columIndex =0;

            for (int k = 0; k < nameOfrouters.size(); ++k)
            {
                if (temp == nameOfrouters[k])
                {
                    rowIndex = k;
                    break;
                }
            }
            for (int p = 0; p < n->neibor_name.size(); ++p)
            {
                if (temp == n->neibor_name[p])
                {
                    columIndex = p;
                    break;
                }
            }
            n->distanceTable[rowIndex][columIndex] = temp2;
         }
     }

}
int DistanceVector:: helper_index(string n){
    int index;
    for (int i = 0; i < nameOfrouters.size(); ++i)
    {
        if (n==nameOfrouters[i])
        {
            index = i;
            break;
        }
    }
    return index;
}
int DistanceVector:: helper_getval(string n, Node *p){
    int col_index;
    for (int i = 0; i < p->neibor_name.size(); ++i)
    {
        if (n == p->neibor_name[i])
        {
            col_index = i;
            break;
        }
    }
    int val;
    val = p->neibor_distance[col_index];
    return val;
}
void DistanceVector::print_table_t1(Node *p){
    int row = numberOfrouters;

    for (int i = 0; i < p->neibor_name.size(); ++i)
    {
        int val;
        val = helper_getval(p->neibor_name[i],p);
        cout<<"t=0"<<" distance from "<< p->name<<" to "<<p->neibor_name[i]<<" via "<<p->neibor_name[i]<<" is "<<val<<endl;

    }
}
// void print_table_tn(Node *p){

// }


void DistanceVector::input(string filename,int count){ // store the value into the vector 
    ifstream file;
    string secondVal;
    string fourthVal;
    string temp1;
    string temp2;

    file.open(filename.c_str());
    if (count == 1)
    {
        getline(file,temp1);
        numberOfrouters = stoi(temp1);
        for (int i = 0; i < numberOfrouters; ++i)
        {   
            getline(file,secondVal);
            nameOfrouters.push_back(secondVal);
            }
            getline(file,temp2);
            numberOflinks = stoi(temp2);
            for (int i = 0; i < numberOflinks; ++i)
            {
                getline(file,fourthVal);
                detailsOflinks.push_back(fourthVal);
            }
        }

    }











int main(int argc, char* argv[]){

   DistanceVector ds(argv[1],argv[2]);
  ;
   Node *name_arr[numberOfrouters];
   cout<<"#START"<<endl;
   for (int i = 0; i < numberOfrouters; ++i)
   {
       name_arr[i] = new Node;
       name_arr[i]->name = nameOfrouters[i];
       ds.setup(name_arr[i]);
       ds.print_table_t1(name_arr[i]);
   }


// for(int k=0;k<numberOfrouters;k++){
//     for (int i = 0; i < numberOfrouters ; ++i)
//      {
//         for (int j = 0; j < name_arr[k]->neibor_name.size(); ++j)
//         {
           
//         }
//         cout << endl;
//      }
//      cout<<"---------"<<endl;
// }
   
 }

