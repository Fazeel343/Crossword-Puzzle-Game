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
void CopyGrid(char grid[GRID_SIZE][GRID_SIZE],char grid2[GRID_SIZE][GRID_SIZE])
{
	for (int i=0;i<GRID_SIZE;++i) 
	{
        for (int j=0;j<GRID_SIZE;++j) 
		{
            if(grid[i][j]>='A' && grid[i][j]<='Z' || grid[i][j]>='a' && grid[i][j]<='z')
            {
            	grid2[i][j]='-';
			}
        }
    }
}
bool CompareGrids(char grid[GRID_SIZE][GRID_SIZE],char grid2[GRID_SIZE][GRID_SIZE])
{
	bool flag=true;
	for (int i=0; i<GRID_SIZE;++i) 
	{
        for (int j=0;j< GRID_SIZE;++j) 
		{
            if(grid[i][j]!=grid2[i][j])
            {
            	flag=false;
			}
        }
    }
	return flag;
}
bool isValid(int row,int col) 
{
    return (row>=0 && row<GRID_SIZE && col>=0 && col<GRID_SIZE);
}
bool HorizontalUpdate(char grid[][GRID_SIZE],string str,char grid2[][GRID_SIZE],int row,int col,int index) 
{
    if(index==str.length()-2) 
	{
		if(grid2[row][col]==grid[row][col] && grid2[row][col+1]==grid[row][col+1])
		{
			return false;
		}
        grid2[row][col]=grid[row][col];
        grid2[row][col+1]=grid[row][col+1];
        resetColor();
        return true;
    }
	if(isValid(row,col) && grid[row][col]==str[index]) 
	{
        char temp=grid2[row][col];
        setColor(32);
        grid2[row][col]=grid[row][col];
        if(HorizontalUpdate(grid,str,grid2,row,col+1,index+1)) 
		{
            return true;
        }
        resetColor();
		grid2[row][col]=temp;
    }
    return false;
}
bool VerticalUpdate(char grid[][GRID_SIZE],string str,char grid2[][GRID_SIZE],int row,int col,int index) 
{
    if (index==str.length()-2) 
	{
		if(grid2[row][col]==grid[row][col] && grid2[row+1][col]==grid[row+1][col])
		{
			return false;
		}
		grid2[row][col]=grid[row][col];
		grid2[row+1][col]=grid[row+1][col];
		resetColor();
    	return true;
	}
    if(isValid(row,col) && grid[row][col]==str[index]) 
	{
		char temp=grid2[row][col];
		setColor(32); 
        grid2[row][col]=grid[row][col];
        if(VerticalUpdate(grid,str,grid2,row+1,col,index+1)) 
		{
            return true;
        }
        resetColor();
    	grid2[row][col]=temp;
	}
    return false;
}
bool HorizontalVerticalUpdate(char grid[][GRID_SIZE],string str,char grid2[][GRID_SIZE],int row, int col,int index) 
{
    if(HorizontalUpdate(grid,str,grid2,row,col,index)) 
	{
        return true;
    }
    if(VerticalUpdate(grid,str,grid2,row,col,index)) 
	{
        return true;
    }
    return false;
}
void updateDisplayGrid(char grid[GRID_SIZE][GRID_SIZE],char grid2[GRID_SIZE][GRID_SIZE],string str)
{
    bool found=false;
    for (int i=0;i<GRID_SIZE;++i) 
	{
        for (int j=0;j<GRID_SIZE;++j) 
		{
            if(HorizontalVerticalUpdate(grid,str,grid2,i,j,0)) 
			{
                found=true;
                break;
            }
        }
        if(found) 
		{
            break;
        }
    }
}

bool LinearSearch(string* arr, int n, string key)
{
    for(int i=0;i<n;i++)
    {
        if(arr[i]==key)
            return true;
    }
    return false; 
}
void EmptyHints(string *hints2,int n,int *index)
{
	for(int i=0;i<n;i++)
	{
		hints2[i]="";
		index[i]=-1;
	}
	HintCounter=0;
}
void HintsDisplayer(string *hints2,int *index)
{
	setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout<<"HINTS : \n";
	resetColor();
	for(int i=0;i<HintCounter;i++)
	{
		if(index[i]!=-1)
		{
			setColor(FOREGROUND_BLACK | FOREGROUND_INTENSITY);
			cout<<i+1<<". "<<hints2[i]<<endl;	
			resetColor();
		}
		else
		{
			cout<<i+1<<". "<<hints2[i]<<endl;
		}
		
	}
	
}
void generateCrossword(char grid[GRID_SIZE][GRID_SIZE],string *words,string *hints,int n,HashMap h,HashMap h2,string *hints2)
{
	
	srand(time(0));
	
	bool isHorizontal=false;
	int randomIndex = rand() % n;
    
	string currentWord = words[randomIndex];
	hints2[HintCounter]=hints[randomIndex];
	
	h2.Insert(currentWord,hints[randomIndex],HintCounter);
    HintCounter++;
	int startRow=0;
    int startCol=0;
    char randomChar=currentWord[(rand() % (currentWord.length()-1))+1];
    int iIndex;
    int jIndex;
	for (int i=0;i<currentWord.length();++i) 
	{
        if(currentWord[i]==randomChar)
        {
            iIndex=0;
            jIndex=startCol+i;
        }
        grid[startRow][startCol+i]=currentWord[i];
    }
    
    for (int wordCount=1; wordCount<numWords;++wordCount) 
	{
		Node *temp=h.getNewWord(randomChar);
		currentWord=temp->Word;
		
		hints2[HintCounter]=temp->Hint;
    	h2.Insert(currentWord,temp->Hint,HintCounter);
        
		HintCounter++;
        
		startRow =iIndex;
        startCol=jIndex;
        randomChar=currentWord[(rand() % (currentWord.length()-1))+1];
        for (int i=0; i < currentWord.length(); ++i) {
            if(isHorizontal)
            {
                if(i==0)
                {
                    jIndex++;
                    continue;
                }
                if(currentWord[i]==randomChar)
                {
                    jIndex=startCol + i;
                }
                grid[startRow][startCol+i]=currentWord[i];
            }
            else
            {
                if(i==0)
                {
                    iIndex++;
                    continue;
                }
                if(currentWord[i]==randomChar)
                {
                    iIndex=startRow+i;
                }
                grid[startRow+i][startCol]=currentWord[i];
            }
            
        }
        if(isHorizontal)
        {
            isHorizontal=false;
        }
        else
        {
            isHorizontal=true;
        }
    }
}
void EmptyGrid(char GRID[GRID_SIZE][GRID_SIZE],int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			GRID[i][j]=' ';
		}
	}
}
int main() {
	const int DATASET_SIZE = 500;
    string dummyWords[DATASET_SIZE];
    string dummyHints[DATASET_SIZE];
    
    for(int i=0;i<DATASET_SIZE;i++)
    {
        dummyWords[i] = "dummyword" + to_string(i);
        dummyHints[i] = "dummy hint for word " + to_string(i);
    }
    
    HashMap dummyHash(26);
    for(int i=0;i<DATASET_SIZE;i++)
    {
        dummyHash.Insert(dummyWords[i], dummyHints[i]);
    }

	HashMap h(26);
    HashMap h2(26);
    string hints2[numWords]={""};
    int index[numWords];
    char grid[GRID_SIZE][GRID_SIZE];
    char  grid2[GRID_SIZE][GRID_SIZE];
    
    for(int i=0; i<GRID_SIZE;++i) {
        for (int j=0;j<GRID_SIZE;++j) {
            grid[i][j]=' ';
            grid2[i][j]=' ';
        }
    }
	
    string words[] = {
        "abandon","ability","absence","academy","account","achieve","acquire","address","advance","advice",
        "airport","ancient","analyze","approve","arrange","arrival","artificial","assistant","attempt","balance",
        "battery","behavior","benefit","bicycle","boundary","building","campaign","capacity","capital","capture",
        "category","celebrate","ceremony","challenge","chemical","citizen","civilization","climate","collapse","collect",
        "combine","comfort","command","commerce","committee","community","company","compare","compete","complete",
        "computer","concept","concern","confirm","connect","constant","construct","consume","contact","context",
        "control","convert","convince","creative","culture","currency","decision","decline","defense","deliver",
        "democracy","describe","design","develop","difference","digital","direction","discover","distance","district",
        "document","domestic","economy","education","effective","efficient","electric","emergency","employee","engineer",
        "environment","equipment","essential","estimate","evaluate","evidence","exchange","exercise","experience","experiment",
        "facility","feature","feedback","festival","finance","foundation","freedom","function","generate","government",
        "graduate","graphics","guarantee","guidance","hardware","heritage","history","hospital","identity","imagine",
        "implement","improve","industry","influence","inform","initial","innovation","inquiry","insurance","integrate",
        "intelligence","interest","internet","interview","investigate","investment","knowledge","language","learning","library",
        "location","machine","management","marketing","material","medicine","memory","message","monitor","movement",
        "network","nutrition","objective","operation","opportunity","organization","performance","philosophy","physical","platform",
        "politics","population","position","potential","practice","predict","pressure","priority","procedure","process",
        "product","profession","progress","property","protection","psychology","quality","reaction","research","resource"
    };

    
    string hints[] = {
        "To leave something behind","The skill to do something","The state of being away","A place of learning","A record of financial activity",
        "To successfully reach a goal","To gain possession","A location or place","To move forward","Guidance or suggestion",
        "A place for airplanes","Very old in history","To examine closely","To officially accept","To put in order",
        "The act of reaching a place","Made by humans","Someone who helps","An effort to do something","A state of stability",
        "A device that stores power","The way someone acts","An advantage","A two-wheeled vehicle","A dividing line",
        "A structure with walls","An organized effort","The ability to hold","A city of government","To take control",
        "A group or class","To honor an event","A formal occasion","A difficult task","Related to chemistry",
        "A member of a country","An advanced society","Weather patterns","A sudden failure","To gather together",
        "To mix or unite","A feeling of ease","To give orders","Trade activities","A decision-making group",
        "A group of people","A business organization","To examine similarities","To compete with others","To finish fully",
        "An electronic computing device","An idea or thought","A worry or interest","To verify something","To link together",
        "Unchanging over time","To build something","To use resources","Communication with others","Surrounding circumstances",
        "To manage power","To change form","To persuade","Original thinking","Shared traditions",
        "A form of money","A choice made","To become smaller","Protection against attack","To transport something",
        "Rule by the people","To explain in words","To plan","To grow or improve","A way things are not the same",
        "Related to computers","A path or course","To find something new","The space between","A specific area",
        "A written record","Related to home affairs","A system of money","The process of learning","Producing desired results",
        "Working well","Powered by electricity","A serious situation","A worker","A technical professional",
        "Natural surroundings","Tools or machinery","Very important","To calculate roughly","To judge something",
        "Proof or facts","The act of trade","Physical activity","Knowledge gained","A scientific test",
        "A building or service","A special part","Response to information","A celebration","Money management",
        "The base of something","Liberty","A purpose","To create","A governing body",
        "Someone who completed studies","Visual designs","A promise","Direction or advice","Computer components",
        "Cultural inheritance","Past events","A medical facility","Who someone is","To form a picture in mind",
        "To put into action","To make better","Business activity","Power to affect","To tell information",
        "The first step","New ideas","A question or investigation","Protection coverage","To combine systems",
        "Ability to think","Curiosity or concern","A global network","A formal conversation","To examine deeply",
        "The act of putting money","Understanding gained","A system of words","The process of study","A place with books",
        "A position","A mechanical device","The act of managing","Selling activities","Substance used",
        "Medical treatment","The ability to remember","Information sent","To observe","Motion or change",
        "Connected systems","Food science","A goal","The act of working","A chance",
        "A structured group","How well something works","Study of thought","Relating to the body","A base for software",
        "Government activity","People in an area","A role or job","Hidden ability","Repeated activity",
        "To forecast","Force applied","Level of importance","A series of steps","A method",
        "An item for sale","A career","Forward movement","Ownership","Safety",
        "The study of the mind","Standard of excellence","Response to action","Systematic study","A supply source"
	};

	srand(time(0)); 
    string target = dummyWords[DATASET_SIZE / 2]; 
    
    auto start = high_resolution_clock::now();
    for(int i=0;i<DATASET_SIZE;i++) {
    dummyHash.Search(dummyWords[i]);
    }

	auto end = high_resolution_clock::now();
    auto hashTime = duration_cast<nanoseconds>(end - start).count();
    
    start = high_resolution_clock::now();
    for(int i=0;i<DATASET_SIZE;i++) {
    LinearSearch(dummyWords, DATASET_SIZE, dummyWords[i]);
    } 

	end = high_resolution_clock::now();
    auto linearTime = duration_cast<nanoseconds>(end - start).count();
    
    setColor(14);
    cout << "\n=========== PERFORMANCE COMPARISON ===========\n";
    resetColor();
    cout << left << setw(25) << "Algorithm" << setw(15) << "Time (ns)\n";
    cout << "--------------------------------------------\n";
    cout << setw(25) << "Hash Table Search" << setw(15) << hashTime << endl;
    cout << setw(25) << "Linear Search" << setw(15) << linearTime << endl;
    
    cout << "\nConclusion: ";
    if(hashTime < linearTime)
        cout << "Hashing is more efficient due to O(1) average complexity.\n";
    else
        cout << "Linear search performed better for this dataset size.\n";

    int n=sizeof(words)/sizeof(words[0]);
    for(int i=0;i<n;i++)
    {
    	h.Insert(words[i],hints[i]);
	}
	srand(time(0));
	string ptr;
	int choice;
	
	User u;
	int count=0;
	while(1)
	{
		EmptyHints(hints2,sizeof(hints2)/sizeof(hints2[0]),index);
		EmptyGrid(grid,27);
		EmptyGrid(grid2,27);
		h.DeleteAndInsertUsed(h2);
		h2.clearTable();
		cout << "\n\nEnter User Name: ";
		fflush(stdin);
		getline(cin,ptr);
		cout << "\n\n";
		
		generateCrossword(grid,words,hints,sizeof(words)/sizeof(words[0]),h,h2,hints2);
		CopyGrid(grid,grid2);
		auto start_time=high_resolution_clock::now();  			
		
		while(1){
			printGrid(grid2);
			HintsDisplayer(hints2,index);
			if(CompareGrids(grid,grid2))
			{
				break;
			}
			
			string str;
			cout << "\nEnter Word To Fill Crossword: ";
			cin >> str;
			
			if(h2.Search(str))
			{
				int ind=h2.SearchWithIndex(str);
				if(ind!=-1)
				{
					index[ind]=ind;
				}
			    updateDisplayGrid(grid,grid2,str);
			}
			else{
				cout << "\nIncorrect\n\n";
			}
			 
		}
		auto end_time=high_resolution_clock::now(); 		
		auto duration_user=duration_cast<seconds>(end_time - start_time).count();  
		
		u.insert_min_user(duration_user,ptr);
		int temp=u.size_u;
		for(int i=temp/2;i>0;i--){
			u.heapify_min(i,temp);   
		}	
		u.user_min_sort(u.size_u);
		
		cout << "\nEnter 1 to play another game \nEnter 2 to exit\n";
		cin >> choice;
		cout << endl;
		while(1){
			if(choice==1)
			{
				u.print_score();
				break;
			}
			else if(choice==2){
				u.print_score();
				exit(1);
			}
			else{
				cout << "\n\t** Invalid Input **\n\nEnter Again: ";
				cin >> choice;
				cout << endl;
			}
		}
		
	
	}
	u.print_score();
	
	return 0;
}
