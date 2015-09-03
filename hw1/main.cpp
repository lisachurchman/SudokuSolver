//
//  main.cpp
//  hw1
//
//  Created by Lisa Churchman on 8/28/15.
//  Copyright (c) 2015 Lisa Churchman. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

class Cell
{
public:
    int row;   // row of specific cell
    int column;  // colun of specific cell
};

Cell FirstZero (int A[9][9]) {
    Cell zeroCell;
    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            if (A[i][j] == 0){
                zeroCell.row = i;
                zeroCell.column = j;
                return zeroCell;
            }
        }
    }
    zeroCell.row= -1;
    zeroCell.column = -1;
    return zeroCell;
};

vector<int> Candidates (int puzzle[9][9], int row, int col){
    vector<int> options { 1,2,3,4,5,6,7,8,9 };
    vector<int>::iterator itr;
    for (int i=0; i < 9; i++){
        itr = find (options.begin(), options.end(), puzzle[row][i]);
        if (itr != options.end()){
            options.erase(remove(options.begin(), options.end(), *itr), options.end());
        }
        else{
           // cout<<"not in vector" <<endl;
        }
    }

    //col
    for (int i=0; i < 9; i++){
        itr = find (options.begin(), options.end(), puzzle[i][col]);
        if (itr != options.end()){
            options.erase(remove(options.begin(), options.end(), *itr), options.end());
        }
        else{
            //cout<<"not in vector" <<endl;
        }
    }

    
   //box
for (int i=0; i < 9; i++){
            for (int j = 0; j <9; ++j){
                if((row/3 == i/3) && (col/3 == j/3)){
                    //cout << row << col <<endl;
                    itr = find (options.begin(), options.end(), puzzle[i][j]);
                    if (itr != options.end()){
                        options.erase(remove(options.begin(), options.end(), *itr), options.end());
                    }
                    else{
                        //cout<<"not in vector" <<endl;
                    }
                }
            }
}


    return options;
};

int nodes;

bool DFS_Solve (int puzzle [9][9]) {
    Cell cell = FirstZero(puzzle);
    if (cell.row == -1 && cell.column == -1) return true;
    else {
        vector<int> cellCandidates;
        cellCandidates= Candidates(puzzle, cell.row, cell.column);
        for (int i=0; i < cellCandidates.size(); i++){
            puzzle[cell.row][cell.column] = cellCandidates[i];
            if (DFS_Solve(puzzle)) return true;
        }

        puzzle[cell.row][cell.column] = 0;
        nodes +=1;
        return false;
    }
}



int main(int argc, const char * argv[]) {

    int matrix [9][9] = {
        {8,5,0,0,0,2,4,0,0},
        {7,2,0,0,0,0,0,0,9},
        {0,0,4,0,0,0,0,0,0},
        {0,0,0,1,0,7,0,0,2},
        {3,0,5,0,0,0,9,0,0},
        {0,4,0,0,0,0,0,0,0},
        {0,0,0,0,8,0,0,7,0},
        {0,1,7,0,0,0,0,0,0},
        {0,0,0,0,3,6,0,4,0}
    };

    

    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    

    cout << endl <<endl <<endl;
    bool isSolved;
    isSolved= DFS_Solve(matrix);
    
    cout << "Solution" <<endl;
    cout << "Nodes visited: "<< nodes << endl << endl;
    
    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    
    return 0;
}
