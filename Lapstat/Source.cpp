#include<iostream>
#include<string> 
#include <time.h>
#include<stdlib.h>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;



void Divide_Cards();
bool Check(int competitor);
void Initialize();
bool Decision_Strategy(int competitor);
void Output();
void Shuffle();
int Loop();
int Start();
bool Draw_Card(int competitor,int mode);
void Shuffle();
string cards[52] = {"3S","4D","5S","3H","9D","6H","2H","6C","9C","KC","KD","10S","3C","3D","4S","10H","KH","10C","5H","8D","AD","9S","5D","6S","9H","QS","10D","JS","2D","JH","7H","8H","JC","AC","AS","QD","KS","2S","4H","4C","JD","2C","QH","AH","7C","7D","7S","QC","8S","5C","6D","8C"};
#define NUM_PLAYER 	6//including banker
#define NORMAL_MODE 2
#define BANKER_MODE 1
#define DEPOSIT 10
#define NUM_OF_TEST 1000
bool WINER_MODE = false;
string players[10][6];		//including banker
int current_cards=52;
int divided_cards=0;						// the number of current cards has been drawn
string current_card="";
long sum[10] ;
void test();
int count_turn=0,run;

int main()
{
	int i,j,winner;
	srand(time(NULL));

	
	for(i=0;i<10;++i)
		sum[i]=0;
	
	ofstream fout;
//	fout.open("Database4.txt",ios::app);
//	fout<<"		*********************************************************************		"<<endl<<endl<<endl;
//	fout<<"Test case: "<<NUM_OF_TEST<<endl<<endl;
	for(j=0;j<NUM_OF_TEST;++j){
	winner = Start();
	cout<<"Number test: "<<j+1<<endl;
	if(winner==-1)
		continue;
	for(i=0;i<NUM_PLAYER;++i)
		if(i==winner)
			sum[i]+=NUM_PLAYER*DEPOSIT - DEPOSIT;
		else sum[i]-= DEPOSIT;
	//	fout<<winner<<" has won"<<endl;

	}
	for(i=0;i<NUM_PLAYER;++i){
		cout<<"Player ";
		cout<<i;
		cout<<" has: ";
		cout<<sum[i]<<endl;
		fout<<"player "<<i<< " has won: "<<sum[i] <<endl; 
	}
//	fout.close();
	
	return 0;
}



//
//void test()
//{
//	ifstream fin;
//	fin.open("Database2.txt");
//	string temp;
//	int count=0;
//	while(!fin.eof())
//	{
//		getline(fin,temp);
//		if(temp=="0 has won")
//		{
//			while(!fin.eof())
//	{
//		if(temp=="0 has won"){
//			sum[0]+= NUM_PLAYER*DEPOSIT - DEPOSIT;
//			for(int i=0;i<NUM_PLAYER;++i)
//				if(i!=0)
//					sum[i]-=DEPOSIT;			
//		}
//		else if(temp=="1 has won"){
//			sum[1]+= NUM_PLAYER*DEPOSIT - DEPOSIT;
//			for(int i=0;i<NUM_PLAYER;++i)
//				if(i!=1)
//					sum[i]-=DEPOSIT;			
//		}
//		else if(temp=="2 has won"){
//			sum[2]+= NUM_PLAYER*DEPOSIT - DEPOSIT;
//			for(int i=0;i<NUM_PLAYER;++i)
//				if(i!=2)
//					sum[i]-=DEPOSIT;			
//		}
//		else if(temp=="3 has won"){
//			sum[3]+= NUM_PLAYER*DEPOSIT - DEPOSIT;
//			for(int i=0;i<NUM_PLAYER;++i)
//				if(i!=3)
//					sum[i]-=DEPOSIT;			
//		}
//		else if(temp=="4 has won"){
//			sum[4]+= NUM_PLAYER*DEPOSIT - DEPOSIT;
//			for(int i=0;i<NUM_PLAYER;++i)
//				if(i!=4)
//					sum[i]-=DEPOSIT;			
//		}
//		else if(temp=="5 has won"){
//			sum[5]+= NUM_PLAYER*DEPOSIT - DEPOSIT;
//			for(int i=0;i<NUM_PLAYER;++i)
//				if(i!=5)
//					sum[i]-=DEPOSIT;			
//		}
//		getline(fin,temp);
//		++count;
//		cout<<count<<endl;
//	}
//		}
//	}
//	
//	for(int i=0;i<NUM_PLAYER;++i)
//		cout<<"Player " << i<< ": "<<sum[i]<<endl;
//	
//
//}

void Output()
{
	for(int i=0;i<NUM_PLAYER;++i){
		for(int j=0;j<6;++j)
			cout<<players[i][j]<<" ";
		cout<<endl;
	}
}

void Initialize()							// Initialize before playing each time
{
	current_cards=52;
	divided_cards=0;
	current_card="";
	count_turn =0;

	WINER_MODE=false;
	for(int i=0;i<NUM_PLAYER;++i)
		for(int j=0;j<6;++j)
			players[i][j]="";
	
	//Shuffle();
	random_shuffle(&cards[0],&cards[52]);
//	cout<<"Cards have been shuffled!"<<endl;
	
	Divide_Cards();
//	cout<<"Cards have been divided for "<<NUM_PLAYER << " players"<<endl;
	//Output();
	cout<<endl;
}


//
//bool check(int competitor)
//{
//	int i,j,k,check=0;
//	for(i=0;i<6;++i){
//		for(j=0;j<6;++j)
//			if(players[competitor][i][0]==players[competitor][j][0])
//				++check;
//		if(check%2!=0) return false;
//		check=0;
//	} 
//	return true;
//}

bool Draw_Card(int competitor,int mode)						//performing drawing one card operation 
{
	int i,j,check=0;
	vector<int> v;

	if(mode == 2)						//NORMAL_MODE
	{
	for(i=0;i<5;++i){
			for(j=0;j<5;++j)
				if(players[competitor][i][0] != current_card[0] && players[competitor][i][0] == players[competitor][j][0])
					++check;
			if(check%2!=0)
				v.push_back(i);
			check=0;
		}
		if(v.size()==0){
			players[competitor][5]=current_card;
			WINER_MODE = true;
			return false;
		}
		else {
			//	srand(time(NULL));
				int random= rand() % v.size();
				int temp = v.at(random);
				swap(current_card,players[competitor][temp]);
				//players[competitor][temp] = current_card;
			return true;
		}

	}
	else if(mode == 1)					//BANKER_MODE			for banker only
	{
		for(i=0;i<6;++i){
			for(j=0;j<6;++j)
				if(players[competitor][i][0] == players[competitor][j][0])
					++check;
			if(check%2!=0)
				v.push_back(i);
			check=0;
		}
		if(v.size()==0)
		{
			WINER_MODE = true;
			return false;
		}
				int random= rand() % v.size();
			//	cout<<random<<endl;
				int temp = v.at(random);
				current_card = players[competitor][temp];
				swap(players[competitor][temp],players[competitor][5]);
				players[competitor][5] = "";
			return true;
	}
}


int Start()
{
	//cout<<"Start initializing!"<<endl;
	Initialize();
	//cout<<"Start playing!"<<endl;
	int result;
	result = Loop();
	if(result == -1) {
//	cout<<"The result is draw, so the winner is banker!"<<endl;
	return -1;
	}
	else {//cout<<"The winner is the competitor number "<<result<<endl;
		/*for(int i=0;i<6;++i)
			cout<<players[result][i]<<" ";
		cout<<endl;*/
		return result;
	}

}

int Loop()											// starting loop
{
	int j;
	Draw_Card(0,BANKER_MODE);
	//++count_turn;
	if(WINER_MODE) return 0;
	while(current_cards){
	for(run=0;run<NUM_PLAYER;++run){
		if(Decision_Strategy(run) == false){
			++count_turn;
			if(count_turn==NUM_PLAYER)
			{
			current_card = cards[divided_cards];
			++divided_cards;
			--current_cards;
			count_turn=0;
			}
			if(current_cards <= 0)
				return -1;
	
		}
		else count_turn=0;

		if(WINER_MODE) return run;
	}
	
	}

	return -1;
}


bool Decision_Strategy(int competitor)
{
	int i,j,check=0;
	
	for(i=0;i<5;++i)
		if(players[competitor][i][0]==current_card[0])
			++check;
	//cout<<check<<endl;
	if(check%2!=0)
	{
		Draw_Card(competitor,NORMAL_MODE);
		return true;
	}
	else return false;
}

void Divide_Cards()										// dividing cards for players
{
	for(int i=0;i<5;++i)
	{
		//for(int j=0;j<NUM_PLAYER;++j){
		for(int j=5;j>=0;--j){
			players[j][i]=cards[divided_cards];
			++divided_cards;
			--current_cards;
		}

	}
	players[0][5]= cards[divided_cards];
	++divided_cards;
	--current_cards;

}

//void Shuffle()
//{
//	int gap;
//	//srand(time(NULL));
//	
//	for(int i=0;i<100;++i){
//	gap= rand() % 52;
//	
//	//cout<<gap<<" ";
//	for(int j=0,k=51;j!=gap,k!=gap;++j,--k)
//		swap(cards[j],cards[k]);
//	
//	/*for(int i=0;i<52;++i)
//		cout<<cards[i]<<"  ";
//	cout<<endl;*/
//	}
//	
//}





