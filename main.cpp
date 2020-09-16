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
#include <string.h>
#include <iomanip>
using namespace std;
#define INF 999

int numberOfrouters;
vector<string> nameOfrouters;
int numberOflinks;
vector<string> detailsOflinks;
string destinations;
int numberofChanges;
vector<string> changeOfdetails;

bool on_of = true;
int t = 1;
// bool on_of1 = true;
struct Node
{
    string name;
    vector<string> neibor_name;
    vector<int> neibor_distance;
    vector<vector<int> > distanceTable;
    vector<vector<int> > clone_distanceTable; 
    bool on_of1;
    bool next_on_of1;
    bool on_of2;
    bool next_on_of2;
};

vector<Node*> name_arr;


class DistanceVector
{
public:
    DistanceVector();
    DistanceVector(string first, string second);
    void setup(Node *n); //initialize the node's val, and initialize the table
    void print_table_t1(Node *p);//t=0 situation
    void print_change_table_t1(Node *p);
    int helper_index(string n); //help to find the position
    int helper_getval(string n, Node *p);//help to find the position's value 
    void input(string filename,int count);//read file
    void set_up_change(Node *p, int);

};
//constructor for the different file input
DistanceVector::DistanceVector(string first, string second){
    input(first,1);
    input(second,2);

}
//setup the node's neighbor name and it's distance
void DistanceVector::setup(Node *n) 
{    
   for (int i = 0; i < detailsOflinks.size(); ++i)
   {
    string get_val= detailsOflinks[i].substr(4,detailsOflinks[i].length()-4);
    int int_val = stoi(get_val);
    if(detailsOflinks[i].substr(0,1) == n->name)
    {      

      n->neibor_name.push_back(detailsOflinks[i].substr(2,1));
      n->neibor_distance.push_back(int_val);
  }
  else if(detailsOflinks[i].substr(2,1)== n->name)
  {                 

   n->neibor_name.push_back(detailsOflinks[i].substr(0,1));
   n->neibor_distance.push_back(int_val);
}

}
// initialization of the distance table
vector<vector<int> >dp(numberOfrouters, vector<int>(numberOfrouters,INF));  
n->distanceTable = dp;

}
//update node's neighbor distance and print
void DistanceVector::set_up_change(Node* p, int p_index){
    for(int i = 0; i < changeOfdetails.size(); i++){
        if(p->name == changeOfdetails[i].substr(0,1)){

            int n_index = helper_index(changeOfdetails[i].substr(2,1));
            int cost = stoi(changeOfdetails[i].substr(4,changeOfdetails[i].length()-4));

            p->distanceTable[n_index][n_index] = cost;

            cout << "t=0 distance from "<< p->name << " to " << nameOfrouters[n_index]
             << " via " << nameOfrouters[n_index] << " is " << cost << endl;
             p->on_of2 = true;
        }
        else if(p->name == changeOfdetails[i].substr(2,1)){

            int n_index = helper_index(changeOfdetails[i].substr(0,1));
            int cost = stoi(changeOfdetails[i].substr(4,changeOfdetails[i].length()-4));

            p->distanceTable[n_index][n_index] = cost;

            cout << "t=0 distance from "<< p->name << " to " << nameOfrouters[n_index]
             << " via " << nameOfrouters[n_index] << " is " << cost << endl;
             p->on_of2 = true;
         }
    }
}
//the helper function aimed to find the index of the neighbor name
int DistanceVector:: helper_index(string n){    
    int index = INF;
    for (int i = 0; i < numberOfrouters; ++i)
    {
        if (n==nameOfrouters[i])
        {
            index = i;
            return index;
        }
    }
    return index;
}
//the helper function aimed to find the val of the neighbour
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
//print the output and give the value to the distance table
//also clone the table for future use
void DistanceVector::print_table_t1(Node *p){   

    int row = numberOfrouters;

    for (int i = 0; i < p->neibor_name.size(); ++i)
    {

        int val;
        int index;
        index = helper_index(p->neibor_name[i]);
        val = helper_getval(p->neibor_name[i],p);
        p->distanceTable[index][index] = val;
        cout<<"t=0"<<" distance from "<< p->name<<" to "<<p->neibor_name[i]<<" via "<<p->neibor_name[i]<<" is "<<val<<endl;

    }
    cout << '\n';
    p->clone_distanceTable = p->distanceTable;
    p->on_of1 = true;
}


// store the value into the vector 
// count =1 means config, count =2 means changeconfig
void DistanceVector::input(string filename,int count){ 
    ifstream file;
    string secondVal;
    string fourthVal;
    string temp1;
    string temp2;
    string changeval;
    string changeline;

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
    if (count == 2)
    {
        getline(file,changeval);
        numberofChanges = stoi(changeval);
    }
    for (int i = 0; i < numberofChanges; ++i)
    {
        getline(file,changeline);
        changeOfdetails.push_back(changeline);
    }

}


//used to find the index of the min value
int find_min_vector(vector<int> values){
    int min = 9999;
    int index = INF;
    for(int i = 0; i < values.size(); i++){
        if(values[i] < min && values[i] != INF){
            index = i;
            min = values[i];
        }
    }
    return index;

}
//used to find min value
int find_min_value(vector<int> values){
    int min = INF;
    int index = INF;
    for(int i = 0; i < values.size(); i++){
        if(values[i] < min && values[i] != INF){
            index = i;
            min = values[i];
        }
    }
    return min;
}

//find the node's name and then find the it's min distance with via node
void initial(Node* p, int p_index){
    for(int i = 0; i < p->distanceTable.size(); i++){
        if(i == p_index){
            continue;
        }
        int index = find_min_vector(p->distanceTable[i]);
        for(int j = 0; j < p->distanceTable[i].size(); j++){
            if(j == index){
                cout << "router " << p->name << ": "<< nameOfrouters[i] << 
                " is " << p->distanceTable[i][j] << " routing through " << nameOfrouters[j] << endl;
            }
        }
    }
}

// handle input, initialize the value of edge
//print the output of start and initial
//read the changeconfig file and update the latest val of edge
//output of update and final
int main(int argc, char* argv[]){

    DistanceVector ds(argv[1],argv[2]);
    name_arr.resize(numberOfrouters);
    cout<<"#START"<<endl;
    for (int i = 0; i < numberOfrouters; ++i)
    {

       Node* tmp = new Node;
       tmp->name = nameOfrouters[i];
       ds.setup(tmp);
       ds.print_table_t1(tmp);
       name_arr[i] = tmp;
    }
    while(on_of==true)
    {
        on_of =false;
        for(int i = 0; i < numberOfrouters; i++){
            Node *p = name_arr[i];
            vector<string> tmp_neigh = p->neibor_name;
            for(int j = 0; j < tmp_neigh.size(); j++){
                int n_index = ds.helper_index(tmp_neigh[j]);
                Node *neigh = name_arr[n_index];
                if(neigh->on_of1 != false){
                    for(int k = 0; k < neigh->clone_distanceTable.size(); k++){
                        if(k == n_index || k == i){
                            continue;
                        }
                        int min = find_min_value(neigh->clone_distanceTable[k]);
                        int cost = min + p->clone_distanceTable[n_index][n_index];
                        if(p->distanceTable[k][n_index] != cost){
                            p->distanceTable[k][n_index] = cost;
                            cout << "t=" << t <<" distance from "<< p->name << " to " << nameOfrouters[k]
                            << " via " << nameOfrouters[n_index] << " is " << cost << endl;
                            if(p->clone_distanceTable[ds.helper_index(neigh->name)][ds.helper_index(neigh->name)] + min != p->clone_distanceTable[k][ds.helper_index(neigh->name)]){
                                p->next_on_of1 = true;
                                on_of = true;
                            }
                        }
                    }
                }
            }
        }
        for(int i = 0; i < numberOfrouters; i++)
        {
            name_arr[i]->clone_distanceTable = name_arr[i]->distanceTable;
            //name_arr[i]->on_of1 = name_arr[i]->next_on_of1;
            name_arr[i]->next_on_of1 = false;
        }
        t++;
    }
    cout << "#INITIAL\n\n";

    for(int i = 0; i < numberOfrouters; i++)
    {
        initial(name_arr[i], i);
    }


    cout << "#UPDATE\n\n";

    for (int i = 0; i < numberOfrouters; ++i)
    {
        Node* p = name_arr[i];
        ds.set_up_change(p, i);
    }

    on_of = true;
    t = 1;

    for(int i = 0; i < numberOfrouters; i++){
        name_arr[i]->clone_distanceTable = name_arr[i]->distanceTable;
    }
    while(on_of==true)
    {
        on_of =false;
        for(int i = 0; i < numberOfrouters; i++){
            Node *p = name_arr[i];
            vector<string> tmp_neigh = p->neibor_name;
            for(int j = 0; j < tmp_neigh.size(); j++){
                int n_index = ds.helper_index(tmp_neigh[j]);
                Node *neigh = name_arr[n_index];
                if(neigh->on_of2 != false){
                    for(int k = 0; k < neigh->clone_distanceTable.size(); k++){
                        if(k == n_index || k == i){
                            continue;
                        }
                        int min = find_min_value(neigh->clone_distanceTable[k]);
                        int cost = min + p->clone_distanceTable[n_index][n_index];
                        if(p->distanceTable[k][n_index] != cost){
                            p->distanceTable[k][n_index] = cost;
                            cout << "t=" << t <<" distance from "<< p->name << " to " << nameOfrouters[k]
                            << " via " << nameOfrouters[n_index] << " is " << cost << endl;
                            if(p->clone_distanceTable[ds.helper_index(neigh->name)][ds.helper_index(neigh->name)] + min != p->clone_distanceTable[k][ds.helper_index(neigh->name)]){

                                p->next_on_of2 = true;
                                on_of = true;
                            }
                        }
                    }
                }
            }
        }
        for(int i = 0; i < numberOfrouters; i++){
            name_arr[i]->clone_distanceTable = name_arr[i]->distanceTable;
            name_arr[i]->on_of2 = name_arr[i]->next_on_of2;
            name_arr[i]->next_on_of2 = false;
        }
        t++;
    }

    cout << "#FINAL\n\n";

    for(int i = 0; i < numberOfrouters; i++){
        initial(name_arr[i], i);
    }

}

