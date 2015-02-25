#pragma once
#include <fstream>
using namespace std;

/*

Log winner 
output: A csv file name winlog0.csv, winlog1.csv ...
Column name is number of player, from player 0 to num_of_player -1
Each row will be each match
if player win, 1, else 0

ex:
Player 0,Player 1,Player 2,Player 3,Player 4
0,0,0,1,0
0,0,1,0,0


player 3 win first match then player 2 win second match

*/

class Logger
{
private:
	//log winner for each round
	ofstream winfout;
	string winlogname;


	int num_of_player;
public:
	//num_of_player is number of player
	//log_num is name of log. 
	//ex: log_num=1, log will name log1.csv
	Logger(int num_of_player,int log_num);

	~Logger();

	void MarkWinner(int winner);//


};

