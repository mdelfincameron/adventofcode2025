#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>
#include <math.h>
#include <algorithm>
#include <set>

using namespace std;

class Box{
public:
    const int64_t x;
    const int64_t y;
    const int64_t z;
    bool operator< (const Box& other) {
        return x < other.x || y < other.y || z < other.z;
    }
    bool operator== (const Box& other) {
        return x == other.x && y == other.y && z == other.z;
    }
    Box(int64_t xPos, int64_t yPos, int64_t zPos) : x(xPos), y(yPos), z(zPos) {};
};

class Connection{
public:
    Box* box1;
    Box* box2;
    double distance;
    bool operator< (const Connection& other) {
        return distance < other.distance;
    }
    Connection(Box* b1, Box* b2){
        box1 = b1;
        box2 = b2;
        distance = sqrt(pow(box1->x - box2->x, 2) + pow(box1->y - box2->y, 2) + pow(box1->z - box2->z, 2));
    };
};

bool circuitCompare(set<Box*> circuit1, set<Box*> circuit2){
    return circuit1.size() < circuit2.size();
}

int main(){
    string filename;
    fstream file;
    int64_t sum = 0;
    vector<Box> boxes;
    vector<Connection> connectionList;
    vector<set<Box*>> circuits;
    size_t numConnections;

    //Get filename, open file
    cout << "Please input filename: ";
    cin >> filename;
    cout << "Please input number of connections: ";
    cin >> numConnections;

    file.open(filename,ios::in);

    if(file.is_open()){

        string line;

        while(getline(file,line)){
            int64_t x = stoll(line.substr(0, line.find(',')));
            line = line.substr(line.find(',') + 1);
            int64_t y = stoll(line.substr(0, line.find(',')));
            line = line.substr(line.find(',') + 1);
            int64_t z = stoll(line);
            Box b(x, y, z);
            boxes.push_back(b);
        }

    }

    file.close();

    for(int i = 0; i < boxes.size(); i++){
        for(int j = i + 1; j < boxes.size(); j++){
            Connection c(&boxes[i], &boxes[j]);
            connectionList.push_back(c);
        }
        set<Box*> newCircuit;
        newCircuit.insert(&boxes[i]);
        circuits.push_back(newCircuit);
    }

    sort(connectionList.begin(), connectionList.end());

    /*
    for(auto & circuit : circuits){
        cout << "Circuit:" << endl;
        for(auto boxPtr : circuit){
            cout << "  Box at (" << boxPtr->x << "," << boxPtr->y << "," << boxPtr->z << ")" << endl;
        }
    }
    */

    for(size_t i = 0; i < numConnections; i++){
        Connection& c = connectionList[i];
        /*cout << "Adding connection between (" << c.box1->x << "," << c.box1->y << "," << c.box1->z << ") and ("
             << c.box2->x << "," << c.box2->y << "," << c.box2->z << ") with distance " << c.distance << endl;
             */   
        set<Box*>* box1Circuit = nullptr;
        set<Box*>* box2Circuit = nullptr;     
        for(auto& circuit : circuits){

            set<Box*>::iterator box1Iter = circuit.find(c.box1);
            set<Box*>::iterator box2Iter = circuit.find(c.box2);
            if(box1Iter != circuit.end()){
                box1Circuit = &circuit;
            }
            if(box2Iter != circuit.end()){
                box2Circuit = &circuit;
            }
        }
        if(box1Circuit != box2Circuit){
                merge(box1Circuit->begin(), box1Circuit->end(),
                      box2Circuit->begin(), box2Circuit->end(),
                      inserter(*box1Circuit, box1Circuit->end()));
                circuits.erase(remove(circuits.begin(), circuits.end(), *box2Circuit), circuits.end());
        }
    }

    sort(circuits.begin(), circuits.end(), circuitCompare);
    reverse(circuits.begin(), circuits.end());

    /*
    for(auto & circuit : circuits){
        cout << "Circuit:" << endl;
        for(auto boxPtr : circuit){
            cout << "  Box at (" << boxPtr->x << "," << boxPtr->y << "," << boxPtr->z << ")" << endl;
        }
    }
    */

    cout << circuits[0].size() * circuits[1].size() * circuits[2].size() << endl;

    exit(0);
}