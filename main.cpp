/*
 
COMP2123 Mini Group Project Members List
 
Name                StudentID
Chan Tik Shun       3035536553
Lui Kin Ping        3035537363
 
*/
 
#include <iostream>
#include <stdlib.h> // for system()
#include <string> // for storing, processing and validating command
#include <ctime> // for clock_t and clock()
#include <list>
#include <algorithm>

using namespace std;
 
typedef struct history {
    string command;
    double runTime;
} History;

/*
void historyInsert(history *& h, const string & c, const double & r) ;
 
void printHistory(history *h, int displayed);
 
void copyHistory(history *source, history *&destin);
 
bool isSorted(history *h) ;
 
void sortHistory(history *&h);
*/
string normalize(const string original_string) { // delete optional space and determine whether the string fits the format
    string temp_string;
    bool potential_sbu = true;
   
    for(int i=0; i < original_string.size(); i++) { // check every character one by one
        if (original_string[i] != ' ') // omit the space character
            temp_string += ((char)(original_string[i])); // directly input the character
           
        if (temp_string == "history" && potential_sbu) {
            if( ((original_string.size() - 1 - i) >= 6) && potential_sbu ) { // check length of remaining string after "(optional space)history" (prevent array index out of bound!!!)
                string remain_option = original_string.substr(i+1, original_string.size()-1-i); // remaining string
               
                if(remain_option[0] != ' ' || remain_option[remain_option.size()-1] != ' ') // omit "(optional space)history(NO space)-sbu(optional space)", "(optional space)history(optional space)-sbu(NO space)"
                    potential_sbu = false;
               
                string temp_substring; // for storing remaining string without spaces
                for(int j=0; (j < remain_option.size() && potential_sbu); j++) {
                    if (remain_option[j] != ' ') // omit the space character
                        temp_substring += ((char)(remain_option[j])); // directly input the character
                }
               
                if(temp_substring == "-sbu" && potential_sbu) // whether remaining string after "(optional space)history" is "(one or more space)-sbu(one or more space)"
                    return "history -sbu ";
            } else {
                potential_sbu = false; // treat "(optional space)history(more than one space)-sbu(optional space)" as a normal command
            }
        }
    }
   
    if (temp_string == "history" || temp_string == "exit")
        return temp_string; // history or exit command
   
    return original_string; // return the original string as command and keep all the sapces
}

bool operator< (const History &a, const History &b) { // overload < operator to sort the list by runTime
	return a.runTime > b.runTime;
}

int main() {
   
    string command;
    //history *listOfHistory = NULL;
    
   	list <History> listOfHistory;
   	list <History> sortedHistory;
   	
    while ( (cout << "tinyshell>") && (getline(cin, command)) ) {  // store the user input into command (whole line)
       
        string new_command = normalize(command); // remove any optional space and check whether it matches the format of built-in command
       
        clock_t begin = clock();
       	/*
        if(new_command == "history") {
            // display last 5 commands, later command first
            printHistory(listOfHistory, 1); // print first 5 history, or until the end
           
        } else if (new_command == "history -sbu ") {
            history *sortedHistory = NULL;
            copyHistory(listOfHistory, sortedHistory);
            sortHistory(sortedHistory);
            printHistory(sortedHistory, 1);
        } else if (new_command == "exit") {
            // terminate program
            exit(0);
        } else {
            // pass the command to the terminal
            system(command.c_str());
           
            clock_t end = clock();
            double runTime = double(end - begin) / CLOCKS_PER_SEC; // return total execution time
            historyInsert(listOfHistory, command, runTime); //update history
        }
       
        cout << endl; // break line
        */
        if(new_command == "history") {
            // display last 5 commands, later command first
            int count = 0;
			list<History>::iterator itr = listOfHistory.begin();
            while( count != 5 && itr != listOfHistory.end()) {
            	cout << itr->command << "  " << itr->runTime << "s" << endl;
            	count++;
            	itr++;
			}
        } else if (new_command == "history -sbu ") {
        	// display slowest 5 commands, slower command first
            int count = 0;
            sortedHistory = listOfHistory; // copy the list into a new list
            
            sortedHistory.sort(); // sort the new list by runTime
            
			list<History>::iterator itr = sortedHistory.begin();
            while( count != 5 && itr != sortedHistory.end()) {
            	cout << itr->command << "  " << itr->runTime << "s" << endl;
            	count++;
            	itr++;
			}
        } else if (new_command == "exit") {
            // terminate program
            exit(0);
        } else {
            // pass the command to the terminal
            system(command.c_str());
           	
            clock_t end = clock();
            double runTime = double(end - begin) / CLOCKS_PER_SEC; // return total execution time
            
            History temp_his;
            temp_his.command = command;
            temp_his.runTime = runTime;
            
            listOfHistory.push_front(temp_his);
        }
    	
        cout << endl; // break line        
    }
}
/*
void historyInsert(history *& h, const string & c, const double & r) {
    history *newH = new history;
    newH -> command = c;
    newH -> runTime = r;
    newH -> next = h;
    h = newH;
}
 
void printHistory(history *h, int displayed) {
    if ( (h == NULL) || (displayed > 5) )
        return;
    else {
        cout << h -> command << "  " << h -> runTime << endl;
        printHistory(h->next, displayed+1);
    }
}
 
void copyHistory(history *source, history *&destin){
    destin = source;
}
 
bool isSorted(history *h) {
    if (h == NULL || h->next == NULL) {
        return true;
    } else if (h->runTime >= h->next->runTime){
        return isSorted(h->next);
    } else {
        return false;
    }
}
 
void sortHistory(history *&h) {
    if (h == NULL || h->next == NULL)
        return;
    while (!isSorted(h)){
        if (h->runTime >= h->next->runTime){
            sortHistory(h->next);
        } else {
            history *tempHistory = new history;
            tempHistory->command = h->command;
            tempHistory->runTime = h->runTime;
            tempHistory->next = h->next->next;
            h->next->next = tempHistory;
            h = h->next;
            sortHistory(h->next);
        }
    }
}
*/


