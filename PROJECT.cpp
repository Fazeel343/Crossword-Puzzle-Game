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
class HashMap{
	private:
		Node **htable;
		int size;
	public:
		HashMap(int size)
		{
			this->size=size;
			htable=new Node*[size];
			for (int i=0;i<size;i++)
				htable[i] = NULL;
		}
		int generateKey(string str)
		{
			int key=0;
			int p=0;
			for(int i=0;i<str.length();i++,p++)
			{
				char c=str[i]-96;
				key=key+pow(c,p);
			}
			return key;
		}
		int HashFunc(string str)
		{
			char c=str[0]-97;
			return c%26;
		}
		void Insert(string word,string hint)
		{
			int key=generateKey(word);
			Node *newNode=new Node(key,word,hint);
			int i=HashFunc(word);
			if(htable[i]==NULL)
			{
				htable[i]=newNode;
			}
			else
			{
				Node *ptr=htable[i];
				while(ptr->next!=NULL)
				{
					ptr=ptr->next;
				}
				ptr->next=newNode;
			}
		}
		void Insert(string word,string hint,int ind)
		{
			int key=generateKey(word);
			Node *newNode=new Node(key,word,hint,ind);
			int i=HashFunc(word);
			if(htable[i]==NULL)
			{
				htable[i]=newNode;
			}
			else
			{
				Node *ptr=htable[i];
				while(ptr->next!=NULL)
				{
					ptr=ptr->next;
				}
				ptr->next=newNode;
			}
		}
		int SearchWithIndex(string str)
		{
			int i=HashFunc(str);
			int k=generateKey(str);
			Node *ptr=htable[i];
			int val=-1;
			while(ptr!=NULL)
			{
				if(k==ptr->key)
				{
					val=ptr->index;
				}
				ptr=ptr->next;
			}
			ptr=NULL;
			return val;
			
		}
		bool Search(string str)
		{
			int i=HashFunc(str);
			int k=generateKey(str);
			Node *ptr=htable[i];
			while(ptr!=NULL)
			{
				if(k==ptr->key)
				{
					return true;
				}
				ptr=ptr->next;
			}
			ptr=NULL;
			return false;
		}
		Node* getNewWord(char c)
		{
			int i=c-97;
			Node *ptr=htable[i];
			string val="";
			int count=0;
			while(ptr!=NULL)
			{
				count++;
				ptr=ptr->next;
			}
			ptr=htable[i];
			rep:
			int random=rand()%count;
			for(int i=0;i<random;i++)
			{
				ptr=ptr->next;
			}
			if(ptr->used==true)
			{
				goto rep;
			}
			Node *temp=ptr;
			ptr->used=true;
			return temp;
		}
	void clearTable()
    {
        for(int i=0;i<size;++i)
        {
            Node *current=htable[i];
            while(current!=NULL)
            {
                Node* next=current->next;
                delete current;
                current=next;
            }
            htable[i]=NULL;
        }
    }
    void DeleteAndInsertUsed(HashMap &h)
    {
    	for(int i=0;i<size;i++)
    	{
    		Node *ptr=h.htable[i];
    		while(ptr!=NULL)
			{
				if(ptr->Word!="")
				{
					Delete(ptr->Word);
					Insert(ptr->Word,ptr->Hint);	
				}
				
				ptr=ptr->next;
			}
			ptr=NULL;	
		}
		
	}
		void Delete(string str)
		{
		    
			if(Search(str))
			{
				int i=HashFunc(str);
				int k=generateKey(str);
				Node *ptr=htable[i];
				if(ptr->key==k)
				{
					Node *temp=ptr;
					ptr=ptr->next;
					delete temp;
					htable[i]=ptr;
				}
				else
				{
					Node *ptr=htable[i];
					Node *prev=htable[i];
					while(ptr->key!=k)
					{
						prev=ptr;
						ptr=ptr->next;	
					}	
					prev->next=ptr->next;
					Node *temp=ptr;
					delete temp;
				}
			}
			else
			{
				cout<<"Key Not Found!\n";
			}
			
		}		
};
void printGrid(char grid[GRID_SIZE][GRID_SIZE]) 
{
    for (int i=0;i<GRID_SIZE;++i) 
	{
        for (int j=0;j<GRID_SIZE;++j) 
		{
            if(grid[i][j]>='A' && grid[i][j]<='Z' || grid[i][j]>='a' && grid[i][j]<='z')
            {
            	setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            	cout<<grid[i][j]<< " ";
            	resetColor();
            	
			}
			else{
				cout<<grid[i][j]<< " ";	
			}
			
        }
        cout << endl;
    }
    cout << endl;
}
