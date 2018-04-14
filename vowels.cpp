#include<pthread.h>
#include<string>
#include<fstream>
#include<iostream>
#include<queue>
#include<sstream>

using namespace std;

void * countVowels(void *vs);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct vowelStruct
{

int vowelArr[5];
int count;
pthread_t id[20];
string path;
string line;
queue <string> fileID;

}; 

int main()
{
struct vowelStruct *vs;
vs = new struct vowelStruct;



cout << "enter path to directory containing files." << endl;
cout << "if in current directory just hit enter." << endl;
getline(cin, vs->path);
	if(vs->path == "")
	{
		for(int i = 1; i < 21; i++)
		{
			string fileValue = to_string(i);
			string finalPath ="";
			finalPath =vs->path+ "file"+fileValue+".txt";
			cout<<finalPath<<endl;
			vs->fileID.push(finalPath);
		}
	}
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
	
	for(int i = 0; i < 20; i++)
	{
		pthread_create(&vs->id[i], NULL, countVowels,(void*) vs);
	}
	while(vs->count!=20){}


	for(int i = 0; i < 5; i++)
	{
		if(i == 0)
			cout << "a:\t"<< vs->vowelArr[i] << endl;
		else if(i == 1)
			cout << "e:\t"<< vs->vowelArr[i] << endl;
		else if(i == 2)
			cout << "i:\t"<< vs->vowelArr[i] << endl;
		else if(i == 3)
			cout << "o:\t"<< vs->vowelArr[i] << endl;
		else
			cout << "u:\t"<< vs->vowelArr[i] << endl;

	}
return 0;
}


void * countVowels(void *vs)
{

struct vowelStruct * vsp = (struct vowelStruct *) vs;

ifstream inFile;

pthread_mutex_lock(&mutex);

string currentFile = vsp->fileID.front();

inFile.open(currentFile.c_str());

vsp->fileID.pop();

pthread_mutex_unlock(&mutex);

	while(inFile.good())
	{
		getline(inFile, vsp->line);
		for(int i=0; i<vsp->line.size(); i++)
		{
			if(vsp->line[i] == 'a' || vsp->line[i] =='A')
				vsp->vowelArr[0] += 1; 
			else if(vsp->line[i] == 'e' || vsp->line[i] == 'E')
				vsp->vowelArr[1] += 1;
			else if(vsp->line[i] == 'i' || vsp->line[i] == 'I')
				vsp->vowelArr[2] += 1;
			else if(vsp->line[i] == 'o' || vsp->line[i] == 'O')
				vsp->vowelArr[3] += 1;
			else if(vsp->line[i] == 'u' || vsp->line[i] == 'U')
				vsp->vowelArr[4] += 1;

		}
	}	
	vsp->count++;
	return (void*)vsp;

}
