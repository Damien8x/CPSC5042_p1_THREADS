#include<pthread.h>
#include<cstring>
#include<fstream>
#include<iostream>

using namespace std;

void * countVowels(void *vs);

struct vowelStruct
{

int vowelArr[5];
int count;
pthread_t id[20];

}; 

int main()
{
struct vowelStruct *vs;
vs = new struct vowelStruct;

for(int i = 0; i < 20; i++)
{
	pthread_create(&vs->id[i], NULL, countVowels,(void*) vs);
}
while(vs->count!=20){}
for(int i = 0; i < 5; i++)
{
	cout << vs->vowelArr[i] << endl;
}
return 0;
}


void * countVowels(void *vs)
{
string line;
struct vowelStruct * vsp = (struct vowelStruct *) vs;
ifstream inFile;
inFile.open("file1.txt");
while(inFile.good())
{
getline(inFile, line);
for(int i=0; i<line.size(); i++)
{
if(line[i] == 'a' || line[i] =='A')
	vsp->vowelArr[0] += 1; 
else if(line[i] == 'e' || line[i] == 'E')
	vsp->vowelArr[1] += 1;
else if(line[i] == 'i' || line[i] == 'I')
	vsp->vowelArr[2] += 1;
else if(line[i] == 'o' || line[i] == 'O')
	vsp->vowelArr[3] += 1;
else if(line[i] == 'u' || line[i] == 'U')
	vsp->vowelArr[4] += 1;

}
vsp->count++;
return (void*)vsp;
}

}
