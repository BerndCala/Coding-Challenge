#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <bits/stdc++.h>

using namespace std;

//Die 255 Char restriction mit cin.getline(char c,255); ??

string print_menu()
{
    cout << "Quiz Master\n";
    cout << "Please make a selection:\n";
    cout << "(1) Ask a question\n";
    cout << "(2) Add new question\n";
    string option;
    cin >> option;
    return option;
}

vector<string> loadTxtFile(string textFile)
{
    string str;
    ifstream in(textFile);
    vector<string> newVector;

    // Read the next line from File until it reaches the end.
    while (getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        if (str.size() > 0)
            newVector.push_back(str);
    }

    return newVector;
}

void save_vector_to_txt_file(string fileName, vector<string> myVector)
{
    ofstream output_file(fileName);
    ostream_iterator<string> output_iterator(output_file, "\n");
    copy(myVector.begin(), myVector.end(), output_iterator);
}

void splitString(string str, string delimiter = " ")
{
    int start = 0;
    int end = str.find(delimiter);
    while (end != -1)
    {
        cout << str.substr(start, end - start) << endl;
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }
    cout << str.substr(start, end - start);
}

void ask_question(vector<string> questions_list, vector<string> answer_list)
{
        cout << "Ask your specific question.\n\n";
        string userInput;
        getline(cin >> ws,userInput);
        int i = 0;
        bool notfound = false;
        while(i < questions_list.size())
        {
            if(userInput == questions_list.at(i)) 
            {
                splitString(answer_list[i]);
                return;
            }
            i++;
        }
        notfound = true;
        if(notfound == true)    
        {
            cout << "the answer to life, universe and everything is 42 according to The hitchhikers guide to the Galaxy \n";

        }        
}

int main()
{
    vector<string> questions_list = loadTxtFile("questions_list.txt");
    vector<string> answers_list = loadTxtFile("answers_list.txt");

    string selection = print_menu();

    if (selection == "1")
    {
        ask_question(questions_list,answers_list);
    }
    else
    {
        cout << "Add your question." << endl;
        string add_question;
        string question;
        string answers;
        getline(cin >> ws,add_question);    // ws....white space
        int pos = add_question.find("?");
        answers = add_question.substr(pos + 2);
        answers.resize(255);                //Restrictions 255 chars
        question = add_question.substr(0,pos + 1);
        question.resize(255);               //Restrictions 255 chars
        questions_list.push_back(question);
        answers_list.push_back(answers);
        cout << "Your question has been added." << endl;

        save_vector_to_txt_file("./questions_list.txt", questions_list);
        save_vector_to_txt_file("./answers_list.txt", answers_list);

    }

    return 0;
}