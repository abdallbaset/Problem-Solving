// Project_Stone_ Paper_scissors_Level_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
using namespace std;
enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinnere { Player1 = 1, Computer = 2, draw = 3 };
struct stRoundInfo
{
    short RoundNumber=0;
    enGameChoice ComputerChoice;
    enGameChoice Player1Choice;
    enWinnere Winner;
    string WinnerName="";
};
struct stGameResults
{
    short GameRounds=0;
    short Player1WinTims = 0;
    short ComputerWinTims = 0;
    short DrawTimes = 0;
    enWinnere GameWinner;
    string WinnerName="";
};
int Random(int From, int To)
{
    return rand() % (To - From + 1) + From;
}
enGameChoice GetComputerChoice()
{
    return (enGameChoice)Random(1,3);
}
enWinnere WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return enWinnere::draw;

    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Paper:
        return (RoundInfo.ComputerChoice == enGameChoice::Scissors) ? enWinnere::Computer : enWinnere::Player1;
            
    case enGameChoice::Scissors :
        return (RoundInfo.ComputerChoice == enGameChoice::Stone) ? enWinnere::Computer : enWinnere::Player1;

    case enGameChoice::Stone :
        return (RoundInfo.ComputerChoice == enGameChoice::Paper) ? enWinnere::Computer : enWinnere::Player1;
      
    }

}
enWinnere WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes) return enWinnere::Player1;
    else if (Player1WinTimes < ComputerWinTimes) return enWinnere::Computer;
    else  return enWinnere::draw;

}
string ChoiseName(enGameChoice Choise)
{
    string arrGameChoise[3] = { "Stone","Paper","Scissors" };
    return arrGameChoise[Choise - 1];
}
string WinnerName(enWinnere Winnere)
{
    string arrWinnereName[3] = { "Player1", "Computer", "No Winner (Draw)" };
    return arrWinnereName[Winnere - 1];
}
enGameChoice ReadPlayer1Choise()
{
    short Choise=1;
    do
    {
        cout << "Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
        cin >> Choise;

    } while (Choise < 1 || Choise > 3);

    return (enGameChoice)Choise;
}
short ReadHowManyRounds()
{
    short Round = 1;
    do
    {
        cout << "How Many Rounds 1 To 10 ?\n";
        cin >> Round;

    } while (Round <1 || Round > 10);
    return Round;
}
stGameResults FillGamerRsult(short GameRounds,short Player1WinTims, short ComputerWinTims, short DrawTimes)
{
    stGameResults GameResult;
    GameResult.GameRounds = GameRounds;
    GameResult.Player1WinTims = Player1WinTims;
    GameResult.ComputerWinTims = ComputerWinTims;
    GameResult.DrawTimes = DrawTimes;
    GameResult.GameWinner = WhoWonTheGame(Player1WinTims, ComputerWinTims);
    GameResult.WinnerName = WinnerName(GameResult.GameWinner);

    return GameResult;

}
string Tabs(short NumberOfTaps)
{
    string Tap = "";
    for (short i = 1; i < NumberOfTaps; i++)
    {

        Tap+="\t";
        cout << Tap;
    }
        return Tap;
}
void ShowFinalResultGame(stGameResults Result)
{
    cout << Tabs(2) << "-------------------------------------[Game Results]-------------------------------\n";
    cout << Tabs(2) << " Game Rounds        : " << Result.GameRounds << endl;
    cout << Tabs(2) << " Player1 won times  : " << Result.Player1WinTims << endl;
    cout << Tabs(2) << " Computer won times : " << Result.ComputerWinTims << endl;
    cout << Tabs(2) << " Draw times         : " << Result.DrawTimes << endl;
    cout << Tabs(2) << " Final Winner       : " << Result.WinnerName << endl;
    cout << Tabs(2) << "----------------------------------------------------------------------------------\n";
}
void getColorScreen(enWinnere Winner)
{
    switch (Winner)
    {
    case enWinnere::Player1:  system("color 2F"); break;
    case enWinnere::Computer: system("color 4F");
                              cout << "\a"; break;
    default:
         system("color 6F");

    }
}
void PrintRoundResults(stRoundInfo RoundInfo)
{
    getColorScreen(RoundInfo.Winner);
    cout << "\n________________________Round[" << RoundInfo.RoundNumber << "]________________________\n\n";
    cout << "Player1 Choice  :" << ChoiseName( RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice :" << ChoiseName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner    :[" << RoundInfo.WinnerName << "]\n" << endl;
    cout << "________________________________________________________\n"  << endl;;
}
void ShowGameOverScreen()
{
    cout << Tabs(2) <<"----------------------------------------------------------------------------------\n";
    cout << Tabs(2) <<"                                   +++Game Over+++ \n";
    cout << Tabs(2) <<"----------------------------------------------------------------------------------\n\n";
}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}
stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\n Round[" << GameRound << "] begins:"<<endl;
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choise();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinnere::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWinnere::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

    return FillGamerRsult(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}
void StartGame()
{
    char PlayAgin= 'y';
    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalResultGame(GameResults);
        cout <<endl<<Tabs(3)<<"Do you want to play again? (Y/N): ";
        cin >> PlayAgin;
    } while (PlayAgin == 'y' || PlayAgin == 'Y');
    
}
int main()

{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}


