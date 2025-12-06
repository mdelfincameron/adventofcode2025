#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>


using namespace std;

int main(){
    string filename;
    fstream file;
    vector<string> data;
    int64_t sum = 0;

    //Get filename, open file
    cout << "Please input filename: ";
    cin >> filename;

    file.open(filename,ios::in);

    if(file.is_open()){

        string line;

        while(getline(file,line)){
            data.push_back(line);
        }

    }

    file.close();

    vector<int64_t> columnNums;
    for(int i = data[0].size() - 1; i >= 0; i--){

        int64_t currentNum = 0;

        for(size_t j = 0; j < data.size() - 1; j++){
            if(isdigit(data[j][i])){
                currentNum = currentNum * 10 + (data[j][i] - '0');
            }
        }
        if(currentNum != 0){
        columnNums.push_back(currentNum);
        }

        char operation = data[data.size() - 1][i];
        if(operation == '+'){
            int64_t result = 0;
            for(auto num : columnNums){
                //cout << num << " ";
                result += num;
            }
            //cout << result << endl;
            sum += result;
            columnNums.clear();
        } 
        else if(operation == '*'){
            int64_t result = 1;
            for(auto num : columnNums){
                //cout << num << " ";
                result *= num;
            }
            //cout << result << endl;
            sum += result;
            columnNums.clear();
        }
    }

    cout << sum << endl;

    exit(0);
}