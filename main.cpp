//
//  Project 1 Starter Code - DNA Profiling
//  Name: Imran Khan
//  UIN:654046372
//  IDE Used: Clion on a Windows Platform
//
/*Milestone 6: for this function to work, first u have to call All_Combinations and then it will ask you for one of the txt files where it has the long DNA strand in it and you should input 1.txt to 20.txt any text file between this. Then it will ask what the length of each combination it should be you and type in any letter and then it will display all the combinations which can be made with that DNA txt file in the length that you asked it to be: You should try 1.txt and length of 4*/ 

#include "ourvector.h"
#include <fstream>
#include <sstream>

using namespace std;

/* A struct is made to store the name of the person in the small and large txt and a vector of integers is in the structs which contains the dna counts of the person that the name is related to  */
struct AllDNA{             
  string name;         
  ourvector<int> DNAcounts;
}; 

/* In this function a temp vecotr is created to store the data then the temp vector is pushed back into the vector in the structs. Then that struct is passed down to a vector which would contain all the structs or is called a vector of structs it returns allstructs which is a vector of all structs and a string vector called vect which has the names as strings and the column val to read the value as a string for the name */
void vectofStructs(ourvector<string>&vect,string &columnVal,ourvector<AllDNA> &allStructs){
  string temps;
  struct AllDNA temp;

  //for loop to run through the file and store it in the given vector
  for(int i=0; i < vect.size(); i++){
    
    temp.DNAcounts.clear();
    stringstream str(vect[i]);
    getline(str, columnVal, ',');//skipping the first coloumn
    temp.name = columnVal;
    
    while (str.good()) {
      
      getline(str,temps,',');
      temp.DNAcounts.push_back(stoi(temps));
      
    }
    
    allStructs.push_back(temp);
    
  }
  
}//end of vectofStructs

/*This fucntion is used to capture the fist line exl=cluding the name and stroring the other characters of the str in a single character type in a vector of char. It returns temp2 which is used to get the first line and store the datat as char values by using the indexes*/
void firstline(string &substr,ourvector<char> &temp2){
  temp2.clear();

  //for loop to run through the string from the read in file
  for (int i = 0; i < substr.size(); i++) {
    
    temp2.push_back(substr.at(i));
    
  }
}//end of firstLine


/*This function is used to load into the database when load_db is called in the console by the user. It returns vect which contains the names of the people in the txt file and the first line which has the char values of the str and allstructs which contains the vector of structs. Also the theFirstLine */
void loadingDatabase(string fileName, ourvector<string>&vect,ourvector<AllDNA> &allStructs,ourvector<ourvector<char>>&theFirstLine){
  // ourvector<char> temp2;
  string filename2;
  string columnVal;
  string row;

  //if the filename is not the same as the other filename it resets tge other vectors to zero
  if(filename2 != fileName){
    
    theFirstLine.clear();
    allStructs.clear();
    vect.clear();
    
  }
  
  filename2= fileName;
  ifstream infile(fileName); 

  //reading the file
  if(infile.fail()){
    
    cout<<"Error: unable to open '"<<fileName<<"'"<<endl;
    
  }
  if(getline(infile, row)){
    ourvector<char> temp2;
    
    stringstream s_stream(row);
    getline(s_stream, columnVal, ',');
    
    while (s_stream.good()) {
      
        string substr;
        getline(s_stream, substr, ',');
        firstline(substr,temp2);
        theFirstLine.push_back(temp2);
      
     }
    
    }
  //storing into another vector of the database file
  while(getline(infile, row)){
    
    vect.push_back(row);
    
  }
  
  vectofStructs(vect, columnVal,allStructs);
  infile.close();
}//end of loadingDatabase


/* this function is used to display the databaase that was accessed by the user using load_db and when the user inputs display this shows the database that was accessed beforehand it returns the vector of structs and is used as a parameter */
void displayDB(ourvector<AllDNA> &allStructs){
  //for loops through the all structs vector which is a vector of structs
    for(int i=0; i < allStructs.size(); i++){
      
      cout << allStructs.at(i).name<<" ";//prints the name
      
      for(int j=0; j < allStructs.at(i).DNAcounts.size(); j++){
        
        cout << allStructs.at(i).DNAcounts.at(j)<<" ";//displays the dna count at that name reference
        
       }
      
      cout<<endl;
      
  }
  
}//end of displayDB

/*This function takes in theFirstLine and processed DNA which we processed in another function and was returned back to the main and forwarded in this function so we can show the processed dna on the console. we used a temp fucntion to temporarily store the char and forward it in another loop */
void displayProcessed(ourvector<ourvector<char>>&theFirstLine,ourvector<int>&processedDNA){
  // ourvector<char>temp;

  //loops through the douvble vector to show the file at that instance
  for (int i = 0; i < theFirstLine.size(); i++){
    ourvector<char>temp;
    for (int j = 0; j < theFirstLine[i].size(); j++){
      
      temp.push_back(theFirstLine[i][j]);
      
    }  
    for(int j = 0 ; j<temp.size(); j++){
      
      cout<<temp[j];
      
    }
    
    cout<<": ";
    cout<<processedDNA[i]<<endl;
    temp.clear();
  }
}//end of displayProcessed

/*In this function we check if the database or the dna or the processed dna have been occured or not if they are not opened or processed then we display the accurate respond to let the user know what they are missing and show them what the have accesed by using the menu options beforehand.  */
void forDisplay(ourvector<string> &vect,ourvector<char>& DNAStrand,ourvector<int>&processedDNA,ourvector<ourvector<char>>&theFirstLine,ourvector<AllDNA> &allStructs){
  //if database is loaded
  if(vect.size()!=0){
    
    cout<<"Database loaded: "<<endl;
    displayDB(allStructs);
    
  }
    //if the vector is empty
  else{
    
    cout<<"No database loaded."<<endl;
  }

  //if the dna vector is not empty
  if(DNAStrand.size()!=0){
    
    cout<<endl;
    cout<<"DNA loaded: "<<endl;
    
  }
    //if the dna vector is not empty
  else{
    
    cout<<"No DNA loaded."<<endl;
    
  }
  
  for(int i=0; i < DNAStrand.size(); i++){
    
    cout<<DNAStrand[i];
    
  }
  
  cout<<endl;

  //displaying the processed dna on the console
  if(processedDNA.size()!=0){
    
    cout<<endl;
    cout<<"DNA processed, STR counts: "<<endl;
    displayProcessed(theFirstLine,processedDNA);
    
    }
    
  else{
    
    cout<<"No DNA has been processed."<<endl;
    
  }
  
} //end of forDisplay


/* This function checks if the vecotr is empty and show the appropriate response to let the user know if they are opened or not so we use the vect and DNAStrand and processed DNA vectors which were used for load_db and load_dna and process */
void checkDisplay(ourvector<string> &vect,ourvector<char> &DNAStrand,ourvector<int> &processedDNA){
  //checking vectors if they are empty or not
  if (vect.size() == 0){
    
    cout<<"No database loaded."<<endl;
    
  }
  
  if(DNAStrand.size() == 0) {
    
    cout<<"No DNA loaded."<<endl;
    
  }
  
  if(processedDNA.size() == 0){
    
    cout<<"No DNA has been processed."<<endl;
    
  }
  
}//end of checkDisplay

/*In this function the filename is in the parameter to check if the file name is valid and that we have in our system and then the loaded Dna is the vector at whcih it will be stored one by one by characters into that vector so it will have all the dna strands in a seperate index */
void loadingDna(string fileName, ourvector<char>& DNAStrand){
  cin>>fileName;
  cout<<"Loading DNA..."<<endl;

  
  ifstream infile(fileName); 
  string filename2;
  
  if(filename2 != fileName){
    
    DNAStrand.clear();
    
  }

  //checking if the file is opened
  if(infile.fail()){
    
    cout<<"Error: unable to open '" <<fileName<<"'"<<endl;
    
  }
  
  string row;

  //storing the document as a char
  while(getline(infile, row)){
    
    for (auto &ch : row) {
      
      DNAStrand.push_back(ch);
      
    }
    
  }
  

}//end of loadingDna


/*This function is a part of the process menu option which clears out the datat from the vector which are being used again in the loop so they do not pile up and be used efficiently they return those vectors in the parameter */
void ending(int counter2, int maximum,ourvector<int>&max,ourvector<int>&sequence,ourvector<int>&processedDNA){
  //clearing the vectors
  counter2  = maximum;
  max.clear();
  sequence.clear();
  processedDNA.push_back(counter2);
}//end of ending

/* This is part of the process menu option and it works if the str length that the user id looking for is on five length I counted the length by the .size() method and to run the file if the value would be 5 or not and then it will run though the whole number of possibilitiesd to find the str which the user is looking for and add that to the counter and used that counter to put it into a vector and run that vector to find the maximum value and move that value to the processed DNA vector which is displayed by using the display menu option. It returns the vectors which are used like the temp vector and the processed dna whcih hold the number of occurances of the str in that file and also the sequence vector which temporarily hold the value of the sequence and the max to find the max value in that vector and the counters are returned which are resette back in another function which they are called back to. The distance is calculated to see if the distance between the indexes at which the str was found is equal to the length of the str which we need to find and if it is then we add that counter if not then we reset the counter and add that value to the vector.*/
void for5str(int &counter2,int &counter,int& distance,ourvector<ourvector<char>>&temp3,ourvector<char>&temp,ourvector<int>&sequence,ourvector<int>&max,ourvector<int>&processedDNA) {
  counter2 =0;
  
  if(counter == 5){
    
    for(int i = 0; i < temp3.size(); i++){
      //checking for the str
      if(temp3[i][0] == temp[0] && temp3[i][1] == temp[1]&& temp3[i][2] == temp[2]&& temp3[i][3] == temp[3]&& temp3[i][4] == temp[4]){
        
        sequence.push_back(i);
        
        }
      
      }
    
    }
  
   if(counter == 5){
     
    counter2 =1;
    sequence.push_back(0);
     
    for(int i = 0; i<sequence.size()-1;i++){
      //checking if the distance between the previous indexes are equal to the size of the str which needs to be searched
      distance = sequence[i+1]-sequence[i];
      
      if(distance == 5){
        
        counter2++;
        
      }
        
      else{
        //storing the counter in another vector
        max.push_back(counter2);
        counter2 = 1;
        
      }
      
    }
     
  int maximum = 0;
     
  for(int i = 0 ; i< max.size() ; i++){
    
    if(maximum <max.at(i)){
    // finding the maximum integer in that vector
      maximum = max.at(i);
      
    }
    
  }
     
  ending(counter2, maximum,max,sequence,processedDNA);
     
  }
  
}//end of for5str

/* This is part of the process menu option and it works if the str length that the user id looking for is on eight length I counted the length by the .size() method and to run the file if the value would be 5 or not and then it will run though the whole number of possibilitiesd to find the str which the user is looking for and add that to the counter and used that counter to put it into a vector and run that vector to find the maximum value and move that value to the processed DNA vector which is displayed by using the display menu option.It returns the vectors which are used like the temp vector and the processed dna whcih hold the number of occurances of the str in that file and also the sequence vector which temporarily hold the value of the sequence and the max to find the max value in that vector and the counters are returned which are resette back in another function which they are called back to. The distance is calculated to see if the distance between the indexes at which the str was found is equal to the length of the str which we need to find and if it is then we add that counter if not then we reset the counter and add that value to the vector.*/
void for8str(int &counter2,int &counter,int& distance,ourvector<ourvector<char>>&temp3,ourvector<char>&temp,ourvector<int>&sequence,ourvector<int>&max,ourvector<int>&processedDNA){
  
  counter2 =0;
  if(counter == 8){
    
    for(int i = 0; i < temp3.size(); i++){
      //checking str
      if(temp3[i][0] == temp[0] && temp3[i][1] == temp[1]&& temp3[i][2] == temp[2]&& temp3[i][3] == temp[3]&& temp3[i][4] == temp[4]&& temp3[i][5] == temp[5]&& temp3[i][6] == temp[6]&& temp3[i][7] == temp[7]){
        
          sequence.push_back(i);
        
        }
      
      }
    
    }
  
  if(counter == 8){
    
  counter2 =1;
  sequence.push_back(0); 
    
  for(int i = 0; i<sequence.size()-1;i++){
    //checking if the distance between the previous indexes are equal to the size of the str which needs to be searched
    distance = sequence[i+1]-sequence[i];
    
    if(distance == 8){
      
      counter2++;
      
    }
      
    else{
      
      max.push_back(counter2);
      counter2 = 1;
      
    }
    
  }
    
  int maximum = 0;
    
  for(int i = 0 ; i< max.size() ; i++){
    
    if(maximum <max.at(i)){
      //checking max value in the vector
      maximum = max.at(i);
      
    }
    
  }
    
  ending(counter2, maximum,max,sequence,processedDNA);
    
  }
  
}//end of for8str

/* This is part of the process menu option and it works if the str length that the user id looking for is on four length I counted the length by the .size() method and to run the file if the value would be 5 or not and then it will run though the whole number of possibilitiesd to find the str which the user is looking for and add that to the counter and used that counter to put it into a vector and run that vector to find the maximum value and move that value to the processed DNA vector which is displayed by using the display menu option.It returns the vectors which are used like the temp vector and the processed dna whcih hold the number of occurances of the str in that file and also the sequence vector which temporarily hold the value of the sequence and the max to find the max value in that vector and the counters are returned which are resette back in another function which they are called back to. The distance is calculated to see if the distance between the indexes at which the str was found is equal to the length of the str which we need to find and if it is then we add that counter if not then we reset the counter and add that value to the vector.*/
void for4str(int &counter2,int &counter,int& distance,ourvector<ourvector<char>>&temp3,ourvector<char>&temp,ourvector<int>&sequence,ourvector<int>&max,ourvector<int>&processedDNA){
  
  counter2 =0;
  
  if(counter == 4){
    
    for(int i = 0; i < temp3.size(); i++){
      //checking str
      if(temp3[i][0] == temp[0] && temp3[i][1] == temp[1]&& temp3[i][2] == temp[2]&& temp3[i][3] == temp[3]){
        
        sequence.push_back(i);
        
      }
      
    }
    
  }
  
  if(counter == 4){
    
  counter2 =1;
  sequence.push_back(0);
    
    for(int i = 0; i<sequence.size()-1;i++){
      //checking if the distance between the previous indexes are equal to the size of the str which needs to be searched
      distance = sequence[i+1]-sequence[i];
      
      if(distance == 4){
        
        counter2++;
        
      }
        
      else{
        
        max.push_back(counter2);
        counter2 = 1;
        
      }
      
    }
    
  int maximum = 0;
    
  for(int i = 0 ; i< max.size() ; i++){
    
    if(maximum <max.at(i)){
      
      maximum = max.at(i);
      
    }
    
  }
    
  ending(counter2, maximum,max,sequence,processedDNA);
    
  }
  
} //end of for4str

/* In this function the process takes place and runs the last 3 function within it and using the vectors which are made in this fucntion to find the str length at which it is repeated at I clear the vecotors so that they can be reused again. Also loaded dna and processed dna and the vector firline dna are used to compare the str we need to fine and are returned agian to the main at which the function is called at. */
void process(ourvector<char>&DNAStrand,ourvector<int>&processedDNA,ourvector<ourvector<char>>&theFirstLine){
  int distance=0;
  ourvector<int>sequence;
  int counter = 0;int counter2 = 0;
  cout<<"Processing DNA..."<<endl;
  //making temp vector to run through it
  for (int i = 0; i < theFirstLine.size(); i++){
      ourvector<int>max;
      ourvector<char>temp;
      ourvector<char>temp2;
      ourvector<ourvector<char>>temp3;
    
    for (int j = 0; j < theFirstLine[i].size(); j++){
      
      temp.push_back(theFirstLine[i][j]);
      
    }  
    
    counter = temp.size();

    //adding counters to the vector
    for (int i=0; i < (DNAStrand.size()-counter); i++){
      
      for(int j = 0 ; j<counter; j++){
        
       temp2.push_back(DNAStrand[i+j]);
        
        if(temp2.size() == counter){
          
          temp3.push_back(temp2);
          temp2.clear();
          
        }
        
      } 
      
    }
    
  for4str(counter2,counter,distance,temp3,temp,sequence,max,processedDNA);
  for5str(counter2,counter,distance,temp3,temp,sequence,max,processedDNA);
  for8str(counter2,counter,distance,temp3,temp,sequence,max,processedDNA);
  temp3.clear();
  temp.clear();
  }
  
}//end of process



/*In this function we first check if we have all the things that we need o run the process function and it can be seen that we use the processed dna to be again used as a parameter in the process function and the loaded dna is not empty and the firline vector is not empty too*/
void firstprocess(ourvector<int>&processedDNA,ourvector<ourvector<char>>&theFirstLine,ourvector<AllDNA> &allStructs,ourvector<char>&DNAStrand){
  bool checker = true;
  //checking if the things needed to run the processes is uploaded in the given vectors
  
  if(theFirstLine.size() == 0){
    
    cout<<"No database loaded."<<endl;
    checker = false;
    
  }
    
  else if(DNAStrand.size() == 0){
    
    cout<<"No DNA loaded."<<endl;
    checker = false;
    
  }
  
  if(checker == true){
    
   process(DNAStrand,processedDNA,theFirstLine);
    
  }
  
}//end of firstprocess


/*In this functyion we used the search menuoption in which we search the database to find the person to which the long dna strand that we pushed into the DNAStrand vector so we used the processedDNA vector to compare it which the other people in the struct and the all structs contains the name and the str of that person so its easier to find the persons name and the loaded dna has the whole dna inside it char by char*/
void search(ourvector<int>&processedDNA,ourvector<AllDNA> &allStructs,ourvector<char>&DNAStrand){
  cout<<"Searching database..."<<endl;

  int temp4 = 0;
  bool ifValid= false;
  string name;

  //using the previous vectors and running through it
  for(int i = 0; i<allStructs.size(); i++ ){
    ourvector<int> temp3;
    for(int j =0  ; j<allStructs[i].DNAcounts.size();j++){

      temp4 =allStructs[i].DNAcounts[j];
      temp3.push_back(temp4);
    }
    
   if(temp3[0]==processedDNA[0] && temp3[1]==processedDNA[1] && temp3[2]==processedDNA[2]){
     
     name = allStructs[i].name;
     ifValid= true;
     
   }
     
    else if (ifValid == false){
      
      ifValid = false;
      
    }
    
    temp3.clear();
    
  }
  //checking if the boolean returns the value and checks if the name is in the database
  if(ifValid == false){
    
    cout<<"Not found in database."<<endl;
    
  }
    
  else{
    
    cout<<"Found in database!  DNA matches: "<<name<<endl;
    
  } 
  
}//end of search


/*in this function which is called in the main is used to check if the nessecary files are loaded into the vectores which would be used in the search function adn if they are not then the user gets the accurate display of which of the menuoptions need to be completed so theat the searching begins and if that all has been stored into the respected vectors then we run the search function to find the name. Thats why we need the processed DNA , the structs, firstline, DNAStrand as the parameter ro make it function*/
void firstSearch(ourvector<int>&processedDNA,ourvector<ourvector<char>>&theFirstLine,ourvector<AllDNA> &allStructs,ourvector<char>&DNAStrand){
  
  bool checker = true;
  //checking if the vectors are loaded
  if(theFirstLine.size() == 0){
    
    cout<<"No database loaded."<<endl;
    checker = false;
    
  }
    
  else if(DNAStrand.size() == 0){
    
    cout<<"No DNA loaded."<<endl;
    checker = false;
    
  }
    
  else if(processedDNA.size() == 0){
    
    cout<<"No DNA processed."<<endl;
    checker = false;
    
  }
  
  if(checker == true){
    
   search(processedDNA,allStructs,DNAStrand);
    
  }
  
}//end of firstSearch



/*It stores all the dna combinations in a Dna strand vextor which is a char vector and then recalls the vector back to the function it was called at. This is the opening file phase for my own unique menu option*/
void allcombinationspt2(string fileName,ourvector<char>&DNAStrand){
  
  ifstream infile(fileName); 
  string filename2;
  //checking if the file is in the code
  if(filename2 != fileName){
    
    DNAStrand.clear();
    
  }
  //if the files open
  if(infile.fail()){
    
    cout<<"Error: unable to open '" <<fileName<<"'"<<endl;
    
  }
  
  string row;
  //storing char in a vector
  while(getline(infile, row)){
    
    for (auto &ch : row) {
      
      DNAStrand.push_back(ch);
      
    }
    
  }
  
}//end fo allcombinationspt2

/*In this function I would display all the possible combinations the user wanted in the specific dna length chosen by the user*/
void allcombinationspt3(int length,ourvector<char>&tempcombinations){
  
  if (length == tempcombinations.size()){
    
    //showing the different combinations
    for(int k = 0 ; k< tempcombinations.size() ; k++){

      cout<<tempcombinations[k];
      
    }
    
    cout<<",";
    
    tempcombinations.clear();
    
    }
}//end of allcombinationspt2



/*In  this function I take in values from the user and store them in variable which then i use to comprehend the DNA char vector and break it down to what the user wans to be display. It dsiplats all the combination in the txt file of the dna chosen by the user and the first dna stand is also chosen and it shows that specific combinations of that dna strand starting with the users character they inputed*/
void allcombinations(string fileName,ourvector<char>&loadedDNA){
  int length;
  ourvector<char>tempcombinations;
  cout<<"Please select a file you want all the combinitions of (eg: '1.txt'): ";
  cin>>fileName;
  allcombinationspt2(fileName,loadedDNA);
  cout<<"Which combination of str length would you like to be provided with: ";
  cin>>length;

  for (int i=0; i < (loadedDNA.size()-length); i++){
    
    for(int j = 0 ; j<=length; j++){  
      
      tempcombinations.push_back(loadedDNA[i+j]);
      allcombinationspt3(length,tempcombinations);
      
    }
    
  }
  cout<<endl;
  loadedDNA.clear();
  
}//end of allcombinations

/*In this function we run the if else statement for the menuoption chosen by the user and does the specific menu option and loads into that function at which it finishs the work at*/
int main(){
  cout<<"Welcome to the DNA Profiling Application."<<endl;
  ourvector<AllDNA> allStructs;
  ourvector<string>vect;
  ourvector<ourvector<char>>theFirstLine;
  ourvector<char>DNAStrand;
  ourvector<int>processedDNA;
  string option;
  string fileName;
  bool appstatus = true;

  while (appstatus == true) {
    
    cout<<"Enter command or # to exit:";
    cin>>option;

    if(option == "load_db"){
      
      cin>>fileName;
      cout<<"Loading database..."<<endl;
      loadingDatabase(fileName,vect,allStructs,theFirstLine);
      
    }
      
    else if(option == "display"){
      
      forDisplay(vect,DNAStrand, processedDNA,theFirstLine,allStructs);
      
    }
      
    else if(option == "load_dna"){
      
      loadingDna(fileName,DNAStrand);
      
    }
      
    else if(option == "process"){
      
      firstprocess(processedDNA,theFirstLine,allStructs,DNAStrand);
      
    }
      
    else if(option == "search"){
      
      firstSearch(processedDNA,theFirstLine,allStructs,DNAStrand);
      
    }
 
    else if(option == "All_Combinations"){
      
      allcombinations(fileName,DNAStrand);
      
    }
      
    else if(option == "#"){
      
      appstatus = false;
      
    }
    
  }
  
  return 0;
  
}
