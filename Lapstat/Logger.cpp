#include "Logger.h"
#include <sstream>

Logger::Logger(int num_of_player,int log_num)
{
	this->num_of_player = num_of_player;
	stringstream ss;
	ss << log_num;
	string str = ss.str();
	winlogname =  "winlog" + str + ".csv";
	winfout.open(winlogname);
	for (int i = 0; i < num_of_player; i++)
	{
		winfout << "Player ";
		winfout << i;
		if (i!=(num_of_player-1)) winfout << ",";
	}
	winfout << endl;
}


Logger::~Logger()
{
	winfout.close();
}

void Logger::MarkWinner(int winner)
{
	for (int i = 0; i < num_of_player; i++)
	{
		if (winner == i) winfout << "1";
		else winfout << "0";
		if (i != (num_of_player - 1)) winfout << ",";
	}
	winfout << endl;
}