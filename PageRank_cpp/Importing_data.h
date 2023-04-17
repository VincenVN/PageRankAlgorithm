#ifndef Importing_Data_H
#define Importing_Data_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Naive_MV_Multi_AR.h"
using namespace std;

AR_TM DG_to_TM_AR(string Network_file_name){
    AR_TM S;
    S.Node_num = 0;
    S.Edge_num = 0;
    S.Network_name = "";
    int i = 0;
    for(char c :Network_file_name){
        if(c=='.'){
            break;
        }
        else{
            S.Network_name += c;
        }
    }
    // Open the file of the Directed Graph
    ifstream Driected_graph_file ("./Directed_Graphs/"+Network_file_name);
    if(Driected_graph_file.is_open()){
        
        string line;

        int line_idx = 0;

        while(getline(Driected_graph_file, line)){
            if(line[0]!='#'){
                break;
            }
            else if(line_idx==2){
                line_idx++;
                int p=0;
                for(int i=(line.length()-1); i>(-1); i--){
                    if(('0'<=line[i])&&(line[i]<='9')){
                        S.Node_num += (line[i] - '0')*pow(10, p);
                        p++;
                    }
                    else if((p>0)&&(S.Edge_num==0)){
                        p = 0;
                        S.Edge_num = S.Node_num;
                        S.Node_num = 0;
                    }
                    else{
                        continue;
                    }
                }
            }
            else{
                line_idx++;
            }
        }
        
        // Assuming every node is related to itself
        S.NZ_num = vector<int> (S.Node_num, 1);
        for(int i=0; i<S.Node_num; i++){
            S.row.push_back(i);
            S.col.push_back(i);
        }

        // input the non-zero elements of the adjacency matrix
        int ij[2] = {0,0};
        int p = 0;
        for(int k=line.length(); k>(-1); k--){
            if(('0'<=line[k])&&(line[k]<='9')){
                ij[0] += (line[k]-'0')*pow(10,p);
                p++;
            }
            else if(p>0){
                ij[1] = ij[0];
                ij[0] = 0;
                p = 0;
            }
            else{
                continue;
            }
        }
        vector<int> &Col = S.col;
        vector<int> &Row = S.row;

        S.NZ_num[ij[0]]++;

        Col.push_back(ij[1]);
        Row.push_back(ij[0]);
        int L = 0;

        while(getline(Driected_graph_file, line)){
            int ij[2] = {0,0};
            int p = 0;
            for(int k=line.length(); k>(-1); k--){

                if(('0'<=line[k])&&(line[k]<='9')){
                    ij[0] += (line[k]-'0')*pow(10, p);   
                    p++;
                }
                else if(p>0){
                    ij[1] = ij[0];
                    ij[0] = 0;
                    p = 0;
                }
                else{
                    continue;
                }
            }
            S.NZ_num[ij[0]]++;
            if(ij[0]!=ij[1]){
                Col.push_back(ij[1]);
                Row.push_back(ij[0]);
            }
            L++;
        }
        Driected_graph_file.close();
    }
    else{
        cout << "fail to open the file, return empty transition matrix" << endl;
    }
    return S;
}

#endif