//
//  main.cpp
//  ccanol_Tasgin_CelalCanol_HW3
//
//  Created by Canol Tasgin on 4/8/20.
//  Copyright © 2020 Canol Tasgin. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "HashTable.h"

using namespace std;

struct item {           // Struct for items.
    string str1, str2;  // 2 strings for pairing process
    double sup;         // support value
    double counter;     // for counting number of items
    
    item (string s1 = "", string s2 = "", double sp = 0.0, double c = 1.0) : str1(s1), str2(s2), sup(sp), counter(c){}
    
    bool operator != (const item & rhs) {      //Necessary operations for item
        if (((this->str1 == rhs.str1 && this->str2 == rhs.str2)) ||
            ((this->str1 == rhs.str2 && this->str2 == rhs.str1)))
            return false;
        else
            return true;
    }
    
    bool operator == (const item & rhs) {
        if (((this->str1 == rhs.str1 && this->str2 == rhs.str2)) ||
            ((this->str1 == rhs.str2 && this->str2 == rhs.str1)))
            return true;
        else
            return false;
    }
    
    item&operator ++ (int rhs){   // for incerasing the counter in Hashtable.h
        counter ++;
        return *this;
    }
};


void Pair(vector<item> aboveTH, HashTable<item> & hashTable, vector <item>& pairs){ //Function for pairing all items which have support value above threshold
   
    item temp;

        for (int k = 0; k < aboveTH.size(); k++) {
            for (int i = k; i < aboveTH.size(); i++) {
                if (aboveTH[k] != aboveTH[i]) {
                    temp.str1 = aboveTH[i].str1;
                    temp.str2 = aboveTH[k].str1;
                    hashTable.insert(temp);
                    pairs.push_back(temp);
                }
            }
        }
    /* CHECKED IF WORKING HERE-------------------------------------------------

for (int k = 0; k < pairs.size(); k++)
{
    cout<<pairs[k].str1<<" "<<pairs[k].str2<<" "<<endl;
}
     -------------------------------------------------*/

}


 void supportPair (vector<item> &aboveTHP,double transactionCount, vector<vector<item> > matrix, HashTable<item> & hashTable, double supVal,vector <item> pairs){ //Found item pairs which have support value larger than Threshold
 
     
      for (int i = 0; i < pairs.size(); i++) {
          double occur = 0.0;
          item & temp = hashTable.find(pairs[i]);
          bool foundFirstItem = false;
          bool foundSecondItem = false;
 
          for (int j = 0; j < matrix.size(); j++) {
              for (int k = 0; k < matrix[j].size(); k++){
                  if(matrix[j][k]==temp.str1)
                      foundFirstItem = true;
                  else if(matrix[j][k]==temp.str2)
                      foundSecondItem = true;
                  else
                      ;
              }
          }
          if(foundFirstItem && foundSecondItem)
              occur++;
          
          temp.sup = occur / transactionCount;
          if (temp.sup >= supVal)
              aboveTHP.push_back(temp);
          
          }
    /* CHECKED IF WORKING HERE-------------------------------------------------
     for (int i=0;i<aboveTHP.size();i++)
    cout<<aboveTHP[i].str1<<" "<<aboveTHP[i].str2<<" "<<aboveTHP[i].sup<<endl;
    ------------------------------------------------------------------------*/
      }
      


 void Rules(vector<vector<item> > matrix,double transactionCount, vector<item> aboveTH,
     vector<item> &aboveTHP, HashTable<item> & hashTable, double confVal){
     //Created a function for making last calculations but didn't have enough time.
     
     int rules = 0;
     int totalThings = aboveTHP.size() + aboveTH.size();
     ofstream outputFile;
     outputFile.open("results.txt");
     double confidence = 0.0;

     
     // Didnt Have enough Time :(
     
     
  }

 

int main() {
    
    string inputFile,line;
    double supportVal, confidenceVal;
    cout<<"Please enter the transaction file name: ";
    cin>>inputFile;
    cout<<"Please enter support and confidence values between 0 and 1: ";
    cin>>supportVal>>confidenceVal;
    
    ifstream input(inputFile);                                    //opened file
    
    item notFoundItem;          //empty struct
    HashTable<item> hashTable(notFoundItem,103);
    
    item temporary;
    
    double transactionCount = 0.0;
    vector<vector<item> > vec;
    string temp = "";
    string space = " ";
    while(getline(input,line)){  //Created a matrix which have all strings seperately
        line+=" ";
        vector <item> transactions;
        for(int i = 0 ; i <= line.length()-1;i++){
            string letter = line.substr(i,1);
            if(letter!=space){
                temp += line[i];
            }
            else
            {
                temporary.str1=temp;
                transactions.push_back(temporary);
                temp = "";
            }
            
        }
        vec.push_back(transactions);
        transactionCount++;         // Counted the lines for keeping track of transaction number
    }
    
  
    item tempItem;
    
    vector<item> allitems;
    
    int productCount = 0;
    
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++){
           
            item tempItem=vec[i][j];
            
            if (hashTable.find(tempItem) == notFoundItem && tempItem.str1!=""){
                allitems.push_back(tempItem);                                   //all items without duplicating
            }
            else
                ;
            
            hashTable.insert(tempItem);                                        //Implemented items to hashtable
            productCount++;
        }
    }
    
    vector<item> aboveThreshold;
    
    cout<<endl;
    
    for (int i = 0; i < productCount; i++) {
        item temp;
        temp.str1=allitems[i].str1;
        if (hashTable.find(temp).str1!=""){ // since i created with matrix there were some empty structs in it. Checked if the current item is empty.
            temp.sup = hashTable.find(temp).counter / transactionCount;            //calculated supportvalues of items and put all in a vector
            if (temp.sup >= supportVal)
            aboveThreshold.push_back(temp);
        }
    }
    
    
    /* CHECKING IF EVERYTHING WORKS FINE -----------------------------------------------------------
    cout<<endl;
    
    for (int i=0;i<aboveThreshold.size();i++)
        cout<<aboveThreshold[i].str1<<" "<<aboveThreshold[i].sup<<endl;
    
    cout<<endl;
    for (int i = 0; i < productCount; i++) {
        item temp;
        temp.str1=allitems[i].str1;
        if (hashTable.find(temp).str1!="")
            cout<<"There are "<< hashTable.find(temp).counter<<" "<<hashTable.find(temp).str1<<endl;
    }
    
    cout<<endl;
    
    cout<< endl ;
    //PRINT MATRIX
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++)
            cout << vec[i][j].str1 << " ";
        cout << endl;
        
    }
    ---------------------------------------------------------------------------*/
    
    vector<item> pairs,aboveTHP;
    Pair(aboveThreshold, hashTable, pairs);   // Pairing Operations
    supportPair(aboveTHP,transactionCount, vec, hashTable, supportVal,pairs);  // Calculating support values of pairs
    //findRules(allTransactions, aboveTH, aboveTHP, hashTable, confidenceVal);
    Rules(vec,transactionCount,aboveThreshold,aboveTHP, hashTable,confidenceVal);
  
    return 0;
}
