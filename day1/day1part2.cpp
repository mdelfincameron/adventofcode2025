#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    string filename;
    fstream file;
    long password = 0;

    cout << "Please input filename: ";
    cin >> filename;
    
    file.open(filename,ios::in);

    if(file.is_open()){

        string line;
        int sum = 50;

        while(getline(file,line)){

            int num = 0;
            bool zeroStart = !sum;
            int length = line.length();

            //Get number
            for(int i = 1; i < length; i++){
                num *= 10;
                num += line[i] - '0';
            }

            //Simulate rotation
            sum += (line[0] == 'R' ? num : -1 * num);

            //cout << line << " " << num;
            
            //Check if rotation crosses 0, exception for starting on 0
            if(!zeroStart && sum < 0){
                password++;
            }

            //Add more rotations for every time 0 would be crossed
            password += abs(sum) / 100;

            //Check if rotation lands on 0
            if(!sum){
                password++;
            }

            //Adjust sum such that it is within the valid range
            sum = ((sum % 100) + 100) % 100;

            
        }
    }

    file.close();

    cout << password << endl;

    exit(0);
}