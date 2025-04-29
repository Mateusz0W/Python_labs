#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib> 
#include <ctime> 
#include<algorithm>
#include<cmath>

#define MAX_IT 2000
#define ITTERATIONS 1000

using namespace std;

using  array2D = vector<vector<int>> ;

int random(int max){
    return rand() % max;
}
void readFile(string fileName,array2D &graph){
    ifstream file(fileName);
    string line;
    while (getline(file, line)) {
        size_t spacePos = line.find(' ');
        int x = stoi(line.substr(0,spacePos));
        int y = stoi(line.substr(spacePos+1));
        vector<int> v ={x,y};
        graph.push_back(v);
    }
    file.close();
    graph.push_back(graph[0]);
}
void saveFile(string fileName,array2D &graph){
    ofstream file(fileName);
    for(int i=0;i<graph.size();i++){
        for(auto v: graph[i])
            file<<v<<" ";
        file<<endl;
    }
    file.close();
}

array2D randomizeEdges(array2D &graph){
    array2D new_graph = graph;
    vector<int> indexes ;
    while (true)
    {
        indexes.push_back(random(graph.size()));
        indexes.push_back(random(graph.size()));
        sort(indexes.begin(),indexes.end());
        bool flag =true;
        if(indexes[1] - indexes[0] <=2)
            flag=false;
        if (flag)
            break;
    }

    vector<int> temp = new_graph[indexes[0]+1];
    new_graph[indexes[0]+1] = new_graph[indexes[1]];
    new_graph[indexes[1]] = temp;

    reverse(new_graph.begin() + indexes[0] +2,new_graph.begin() +indexes[1]);

    return new_graph;

}

int calcluateLength(array2D &graph){
    int sum=0;
    auto vectorLength = [&sum](vector<int> v1, vector<int> v2){
        sum+= sqrt( pow(v2[0] - v1[0],2) - pow(v2[1] - v1[1],2));
    };

    for(int idx=0;idx<graph.size()-1;idx++)
        vectorLength(graph[idx],graph[idx+1]);

    return sum;
}

array2D& simulatedAnnealing(array2D &graph){
    for(int i=100;i>0;i--){
        cout<<"\r Postep wyszarzania = "<<(100-i) *100<<" % "<<endl;
        double T = 0.001 * pow(i,2);
        for(int it=0;it<MAX_IT;it++){
            array2D new_graph = randomizeEdges(graph);
            double dNew= calcluateLength(new_graph);
            double d = calcluateLength(graph);
            if(dNew<d){
                graph=new_graph;
            }    
            else{
                int r= random(2);
                if( r< exp(-(dNew - d)/T))
                    graph=new_graph;
            }
        }
       
    }
    return graph;
}
int main(void){
    srand(time(0));
    array2D graph;
    readFile("data.csv",graph);
    for(int i=0;i<ITTERATIONS;i++){
        graph=simulatedAnnealing(graph);
        cout<<"\r Postep algorytmu = "<<i/ITTERATIONS *100<<" % "<<endl;
    }
    saveFile("out.csv",graph);
}
