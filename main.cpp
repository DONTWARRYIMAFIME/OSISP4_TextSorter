#include <fstream>
#include <iostream>
#include "queueTaskExcecutorService/QueueTaskExecutorService.h"

using namespace std;

void printVector(const vector<string>& vector);
vector<string> readTextFromFile(string &path);
void writeTextToFile(string &path, const vector<string>& vector);

int main()
{
    string pathToInFile = "../input.txt";
    string pathToOutFile = "../output.txt";

    vector<string> vector = readTextFromFile(pathToInFile);
    QueueTaskExecutorService service(vector, 4);

    cout <<"Before sorting:" << "\n";
    printVector(vector);

    cout << "\n";

    service.execute();
    vector = service.getVector();

    cout <<"After sorting:" << "\n";
    printVector(vector);

    writeTextToFile(pathToOutFile, service.getVector());

    return 0;
}

void printVector(const vector<string>& vector)
{
    for (const string& str: vector)
    {
        cout << str << " ";
    }

    cout << "\n";
}

vector<string> readTextFromFile(string &path)
{
    ifstream inFile;
    vector<string> vector;

    inFile.open(path);
    if (!inFile)
    {
        cout << "Unable to open file: " + path << "\n";
        exit(1);
    }

    string input;
    while (inFile >> input)
    {
        vector.push_back(input);
    }

    inFile.close();
    return vector;
}

void writeTextToFile(string &path, const vector<string>& vector)
{
    ofstream outFile(path);
    for (const string& str: vector)
    {
        outFile << str << " ";
    }
    outFile.close();
}
