// Damien Sudol
// VowelFinder.cpp
// CPSC5042 P1
// V:1.0
// 4/19/18

#include<pthread.h>
#include<string>
#include<fstream>
#include<iostream>
#include<queue>
#include<sstream>

using namespace std;

//fucntion prototypes
void welcomeMessage();
void * countVowels(void *vs);

//initialize global mutex object
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexAddA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexAddE = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexAddI = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexAddO = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexAddU = PTHREAD_MUTEX_INITIALIZER;





//Struct holds data-structures/types for to meet needs of the class
//for creating threads, and tracking all vowels accross input files. 
//container for thread ids(id[]), tracking vowel counts(vowel Arr), container
//for unique file paths(fileID), integer for tracking completed vowel 
//count for individual file(count), string holding path to directory
//(path)
struct vowelStruct
{

int vowelArr[5];
int count;
pthread_t id[20];
string path;
queue <string> fileID;

}; 

int main()
{
//initialize struct with pointer to dynamic memory
struct vowelStruct *vs;
vs = new struct vowelStruct;
//display welcome message/prompt user for file path
welcomeMessage();
//store file-path supplied by user
getline(cin, vs->path);
	//condition statement to handle and format filepath if user
	//is in CWD which contains files to process
	if(vs->path == "")
	{
		for(int i = 1; i < 21; i++)
		{
			string fileValue = to_string(i);
			string finalPath ="";
			finalPath =vs->path+ "file"+fileValue+".txt";
			vs->fileID.push(finalPath);
		}
	}
	//If not in CWD, format and store all filepaths in FileID queue
	else
	{
		for(int i = 1; i < 21; i++)
		{
			string fileValue = to_string(i);
			string finalPath ="";
			finalPath =vs->path+ "/file"+fileValue+".txt";
			cout<<finalPath<<endl;
			vs->fileID.push(finalPath);
		}
	}
	//For loop creating 20 unique threads
	//each thread will process a unique file
	for(int i = 0; i < 20; i++)
	{
		pthread_create(&vs->id[i], NULL, countVowels,(void*) vs);
	}
	//while loop halts program until all threads have completed 
	while(vs->count!=20){}

	//format and display results for all respective vowels accross
	//all files
	cout << " Vowel Counts: " << endl;

	for(int i = 0; i < 5; i++)
	{
		if(i == 0)
			cout << " a:  "<< vs->vowelArr[i] << endl;
		else if(i == 1)
			cout << " e:  "<< vs->vowelArr[i] << endl;
		else if(i == 2)
			cout << " i:  "<< vs->vowelArr[i] << endl;
		else if(i == 3)
			cout << " o:  "<< vs->vowelArr[i] << endl;
		else
			cout << " u:  "<< vs->vowelArr[i] << endl;

	}
//delete dynamic memory allocated for vs
delete vs;
return 0;
}

//thread function for processing an individual file
void * countVowels(void *vs)
{

//cast parameter back to its original type, vowelStruct
struct vowelStruct * vsp = (struct vowelStruct *) vs;
//create string to hold line of text file.
string line;
//create filestream object
ifstream inFile;
//lock thread for critical point
pthread_mutex_lock(&mutex);
	//extract file to be processed from front  of queue, FileID
	string currentFile = vsp->fileID.front();
	//Open file stream for respective file
	inFile.open(currentFile.c_str());
	if(!inFile.is_open())
		{
			cout<< "ERROR OPENING FILE" << endl;
			exit(EXIT_FAILURE); 
		}
	else{
	//remove newly processed file from FileID queue
	vsp->fileID.pop();
	//un-lock thread
	pthread_mutex_unlock(&mutex);
	//enter while loop which executes until file end
	while(inFile.good())
	{	
		//retrieve current line and assign to string "line"
		getline(inFile, line);
		//check each character against all vowels
		//increment count for each respective vowel encountered
		for(int i=0; i<line.size(); i++)
		{
			if(line[i] == 'a' || line[i] =='A'){
				pthread_mutex_lock(&mutexAddA);
				vsp->vowelArr[0] += 1; 
				pthread_mutex_unlock(&mutexAddA);}	
			else if(line[i] == 'e' || line[i] == 'E'){
				pthread_mutex_lock(&mutexAddE);
				vsp->vowelArr[1] += 1;
				pthread_mutex_unlock(&mutexAddE);}	
			else if(line[i] == 'i' || line[i] == 'I'){
				pthread_mutex_lock(&mutexAddI);
				vsp->vowelArr[2] += 1;
				pthread_mutex_unlock(&mutexAddI);}	
			else if(line[i] == 'o' || line[i] == 'O'){
				pthread_mutex_lock(&mutexAddO);
				vsp->vowelArr[3] += 1;
				pthread_mutex_unlock(&mutexAddO);}	
			else if(line[i] == 'u' || line[i] == 'U'){
				pthread_mutex_lock(&mutexAddU);
				vsp->vowelArr[4] += 1;
				pthread_mutex_unlock(&mutexAddU);}

		}
	}	
	//close ifstream 
	inFile.close();

	//increase global count, indicating file has been processed
	vsp->count++;

	return (void*)vsp;
	}
}

//Welcome Message to user
void welcomeMessage()
{
string star =
"******************************************************************************";
cout << star <<"\n\t\t\t\tWELCOME!!!\n\n\tThanks for choosing VowelFinder" <<
"for your vowel finding needs!\n\n\tVowelFinder will utilize concurrent programming" 
<<" to track\n\tvowels accross 20 text files. Here are some things to remember:\n"
<<"\n\t   -VowelFinder is designed to accept a direcotry path from user.\n" <<
"\t   -Specified directory must contain 20 files with the naming\n"<<
"\t    convention: file1.txt, file2.txt...file19.txt, file20.txt\n"
"\t   -For file path formatting insturctions please see README.txt" <<
"\n\n\tPlease enter the file path containing files to be processed:\n\n"<<star<<endl;





}
