#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    string filename;
    fstream file;
    long password = 0;

    //Get filename, open file
    cout << "Please input filename: ";
    cin >> filename;
    
    file.open(filename,ios::in);

    if(file.is_open()){

        //Read line by line through file
        string line;
        int sum = 50;

        while(getline(file,line)){

            
            int num = 0;
            int length = line.length();

            //Get number
            for(int i = 1; i < length; i++){
                num *= 10;
                num += line[i] - '0';
            }

            //cout << line << " " << num;

            sum = (sum + (line[0] == 'R' ? num : -1 * num)) % 100;

            //cout << ": " <<  sum <<endl;

            if(!sum){
                password++;
            }

            
        }
    }

    file.close();

    cout << password << endl;

    exit(0);
}