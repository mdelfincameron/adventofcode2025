#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>

using namespace std;

int main(){
    string filename;
    fstream file;
    int64_t sum = 0;

    //Get filename, open file
    cout << "Please input filename: ";
    cin >> filename;

    file.open(filename,ios::in);

    if(file.is_open()){

        string line;

        getline(file,line);
        vector<bool> isBeamed(line.size(), false);
        isBeamed[line.find('S')] = true;

        while(getline(file,line)){
            size_t splitter = line.find('^');
            while(splitter != string::npos){
                if(isBeamed[splitter]){
                    isBeamed[splitter - 1] = true;
                    isBeamed[splitter + 1] = true;
                    isBeamed[splitter] = false;
                    sum++;
                }
                /*
                for(size_t i = 0; i < isBeamed.size(); i++){
                    cout << (isBeamed[i] ? '|' : '.');
                }
                cout << endl;
                */
                splitter = line.find('^', splitter + 1);
            }
            //cout << sum << endl;

        }

    }

    file.close();

    cout << sum << endl;

    exit(0);
}