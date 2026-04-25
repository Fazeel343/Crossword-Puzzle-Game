#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <bits/stdc++.h>
#include <iomanip> 
#include <windows.h>
#define FOREGROUND_BLACK       0x00

using namespace std;
using namespace chrono;

const int GRID_SIZE =33;
const int numWords = 6;
void setColor(int colorCode) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}

void resetColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7); 
}
class User{
	public:
		string name[101];
		float time_u[101];
		int size_u;
		
		User()
		{
			size_u=0;	
			time_u[0]=-1;
		}
		
		void insert_min_user(float value,string str){
			size_u=size_u+1;
			int i=size_u;
			name[i]=str;
			time_u[i]=value;
			
			while(i>1){
				int temp=i/2;
				if(time_u[temp]>time_u[i]){
					swap(time_u[temp],time_u[i]);
					swap(name[temp],name[i]);
					i=temp;
				}
				else{
					 return;
				}
			}
		}
		
		void user_min_sort(int n){
			while(n>1){
				swap(time_u[1],time_u[n]);
				swap(name[1],name[n]);
				n--;
				heapify_min(1,n);
			}
		}
		
		void heapify_min(int index,int num){
			int large=index;
			int left=2*index;
			int right=2*index +1;
			
			if(left<=num && time_u[large]<time_u[left]){
				large=left;
			}
			if(right<=num && time_u[large]<time_u[right]){
				large=right;
			}
			
			if(large!=index){
				swap(time_u[large],time_u[index]);
				swap(name[large],name[index]);
				
				heapify_min(large,num);
			}
			return;
		}
		
		void print_score(){
			setColor(FOREGROUND_BLUE|FOREGROUND_INTENSITY);
			cout << "\n\n\t*SCORE CARD*\n\n";
			cout << "Names\t\tTime\n\n";
			
			for(int i=1;i<=size_u;i++){
				cout << name[i] << "\t\t" << time_u[i] << " seconds\n";
			}
			cout << endl;
			resetColor();
		}
		
};
int HintCounter=0;
class Node{
	public: 
		int key;
		string Word;
		string Hint;
		Node *next;
		bool used;
		int index;
		Node(int k,string word,string hint,int ind)
		{
			key=k;
			Word=word;
			Hint=hint;
			next=NULL;
			used=false;
			index=ind;
		}
		Node(int k,string word,string hint)
		{
			key=k;
			Word=word;
			Hint=hint;
			next=NULL;
			used=false;
			index=-1;
		}
		Node()
		{
			next=NULL;
			key=0;
			Word="";
			Hint="";
			used=false;
			index=-1;
		}
};
