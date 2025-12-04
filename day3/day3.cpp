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

        while(getline(file,line)){

            int maxFirst = 9;
            int maxSecond = 9;

            for(;maxFirst > 0; maxFirst--){

                size_t loc = line.find(maxFirst + '0');
                if(loc != string::npos && loc != line.size() - 1){

                    //cout << "First digit is " << maxFirst << endl;
                    string substr = line.substr(loc + 1);
                    //cout << substr << endl;

                    for(;maxSecond > 0; maxSecond--){
                        if(substr.find(maxSecond + '0') != string::npos){
                            //cout << "Second digit is " << maxSecond << endl;
                            sum += maxFirst * 10 + maxSecond;
                            break;
                        }
                    }
                    break;
                }
            }
        }

    }

    file.close();

    cout << sum << endl;

    exit(0);
}