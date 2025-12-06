#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>
#include <regex>

using namespace std;

int main(){
    string filename;
    fstream file;
    vector<string> grid;
    vector<string> countGrid;
    int sum = 0;
    regex paper("@");

    //Get filename, open file
    cout << "Please input filename: ";
    cin >> filename;

    file.open(filename,ios::in);

    if(file.is_open()){

        string line;

        getline(file,line);
        int length = line.length() + 2;
        file.seekg(0);

        grid.push_back(string(length,'.'));

        while(getline(file,line)){            
            grid.push_back("." + line + ".");
        }

        grid.push_back(string(length,'.'));
    }

    file.close();

    countGrid = grid;

    int loopSum = 0;
    do{
        sum += loopSum;
        loopSum = 0;
        for(int i = 1; i < grid.size() - 1; i++){

            auto begin = sregex_iterator(grid[i].begin(),grid[i].end(),paper);
            auto end = sregex_iterator();
            smatch m;

            //Check adjacent chars to each regex found in line 
            for(sregex_iterator j = begin; j != end; j++){
                int start = j->position();

                string adjacentChars = grid[i - 1].substr(start - 1, 3) +  
                                            grid[i + 1].substr(start - 1, 3) +
                                            grid[i].substr(start - 1, 1) +
                                            grid[i].substr(start + 1, 1);
                                        
                //If there is an adjacent symbol, add to sum
            
            
                //cout << std::count(adjacentChars.begin(), adjacentChars.end(), '@') << endl;
                if(std::count(adjacentChars.begin(), adjacentChars.end(), '@') < 4){
                    grid[i][start] = '.';
                    loopSum++;
                }
            } 

        }
        /*
        for(auto line : grid){
            cout << line << endl;
        }
        cout << "Loop sum: " << loopSum << endl;
        */
    }
    while(loopSum > 0);

    std::cout << sum << endl;

    exit(0);
}