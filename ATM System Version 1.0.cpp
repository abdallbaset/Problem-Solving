// ATM System Version 1.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
enum enAtmMainMenuOptions {QuickWithraw = 1, NormalWithdraw = 2, Deposit = 3, CheckBalance = 4, Logout = 5};
const string clientsFileName = "clients.txt";
void Login();
void ShowAtmMainMenu();
short ReadMenueOptions(string Message);
void showQuickWithrawScreen();
void ShowNormalWithdrawScreen();

struct stClientInfo
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	float AccountBalance = 0.0;
	bool MarkClient = false;
};
stClientInfo CurrentClient;
vector<stClientInfo> vClientInfo;

vector<string> SplitString(string String, string Delmt = "#//#")
{
	vector<string> vWord;
	string sWord = "";
	short pos = 0;
	while ((pos = String.find(Delmt)) != string::npos)
	{
		sWord = String.substr(0, pos);

		if (sWord != "") vWord.push_back(sWord);

		String.erase(0, pos + Delmt.length());
	}

	if (String != "") vWord.push_back(String);

	return vWord;
}
stClientInfo ConvertLineDatatoRecord(string LineData, string Sepertor = "#//#")
{
	vector<string> vWord = SplitString(LineData, Sepertor);
	stClientInfo ClientInfo;
	ClientInfo.AccountNumber = vWord[0];
	ClientInfo.PinCode = vWord[1];
	ClientInfo.Name = vWord[2];
	ClientInfo.Phone = vWord[3];
	ClientInfo.AccountBalance = stof(vWord[4]);

	return ClientInfo;
}
vector<stClientInfo> LoadClientDataFromFile(string FileName)
{
	vector<stClientInfo>vClients;
	stClientInfo ClientInfo;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	string line = "";
	if (MyFile.is_open())
	{
		while (getline(MyFile, line))
		{
			ClientInfo = ConvertLineDatatoRecord(line);
			vClients.push_back(ClientInfo);
		}
		MyFile.close();
	}
	return vClients;
}
bool FindClientByAccountNumber( vector<stClientInfo>& vClients, string AccountNumber, string PinCode, stClientInfo& ClientInfo)
{

	for (stClientInfo& Client : vClients)
	{
		if ((Client.AccountNumber == AccountNumber) && (Client.PinCode == PinCode))
		{
			ClientInfo = Client;
			return true;
		}

	}
	return false;
}
bool LoadUserInfo(vector<stClientInfo>& vClientInfo, string AccountNumber, string PinCode)
{
	return (FindClientByAccountNumber(vClientInfo, AccountNumber, PinCode, CurrentClient));
}
void GoBackMainMenu()
{
	cout << "\nPress any key to go back to Main Menu...";
	system("pause > nul");
	ShowAtmMainMenu();	
}
void GetBalance()
{
	cout << "Your Balance is :" << CurrentClient.AccountBalance << endl;
}
void showCheckBalanceScreen()
{
	cout << "-----------------------------------------------------\n";
	cout << "\t\tCheck Balance Screen\n";
	cout << "-----------------------------------------------------\n";
	GetBalance();
}
string ConvertRecordtoline(stClientInfo ClientInfo, string Sepertor="#//#")
{
	string Line = "";
	Line += ClientInfo.AccountNumber + Sepertor;
	Line += ClientInfo.PinCode + Sepertor;
	Line += ClientInfo.Name + Sepertor;
	Line += ClientInfo.Phone + Sepertor;
	Line += to_string(ClientInfo.AccountBalance);

	return Line;
}
void SaveClientInFile(string fileName, vector<stClientInfo>& vClients)
{
	string LineData = "";
	fstream MyFile;
	MyFile.open(fileName, ios::out);
	if (MyFile.is_open())
	{
		for (stClientInfo& client : vClients)
		{
			if (client.MarkClient == false)
			{
				LineData = ConvertRecordtoline(client);
				MyFile << LineData << endl;

			}
		}
		MyFile.close();
	}
}

void WithdrawBalanceFromClientByAccountNumber(vector<stClientInfo>& vClients, string AccountNumber, int NumberofWithdraw)
{
	char AreYouSure = 'y';
	for (stClientInfo& Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			cout << "\nAre you sure you want to Prefrom this transaction? (Y/N) ?";
			cin >> AreYouSure;
			if (AreYouSure == 'Y' || AreYouSure == 'y')
			{
				Client.AccountBalance -= NumberofWithdraw;
				cout << "\nWithdraw successful, new Blances is " << Client.AccountBalance << endl;
				SaveClientInFile(clientsFileName, vClients);
				return;
			}
			else
			{
				cout << "\nThe Withdraw has been cancelled.\n";
				return;
			}

		}
	}
}
int ReadWithdrawAmount()
{
	int Amount = 0;
	do
	{
		cout << "\nPlase enter an amount Multiple of 5’s? ";
		cin >> Amount;
	} while ((Amount % 5 != 0));

	return Amount;
}

short GetQuickWithdrawAmount(short QuickWithdrawOption)
{
	switch (QuickWithdrawOption)
	{
      	case 1: return 20;
	    case 2: return 50;
	    case 3: return 100;
      	case 4: return 200;
	    case 5: return 400;
   	    case 6: return 600;
	    case 7: return 800;
	    case 8: return 1000;
	  default:
	  {
		cout << "This option Not Bounds the Option Menu :-(\n";
		return 0;
	  }
	}
}
void PrefromQuickWithdraw(short QuickWithdrawOption)
{
	if (QuickWithdrawOption == 9)
		return;
	short WithDrawBalance = GetQuickWithdrawAmount(QuickWithdrawOption);
	if (WithDrawBalance > CurrentClient.AccountBalance)
	{
		cout << "\nAmount Exceeds your blance,Make Another Choice ,Press anyKey to Continue....";
		system("pause > nul");
		showQuickWithrawScreen();
		return;
	}
	WithdrawBalanceFromClientByAccountNumber(vClientInfo, CurrentClient.AccountNumber, WithDrawBalance);
	CurrentClient.AccountBalance -= WithDrawBalance;
}
void showQuickWithrawScreen()
{
	system("cls");
	cout << "-----------------------------------------------------\n";
	cout << "\t\tQuick Withraw Screen\n";
	cout << "-----------------------------------------------------\n";
	cout << "\t[1] 20  \t[2] 50\n";
	cout << "\t[3] 100 \t[4] 200\n";
	cout << "\t[5] 400 \t[6] 600\n";
	cout << "\t[7] 800 \t[8] 1000\n";
	cout << "\t[9] Exit\n";
	cout << "-----------------------------------------------------\n";
	GetBalance();
	PrefromQuickWithdraw(ReadMenueOptions("Chose what to Withraw  from[1] to [9]? "));
}
void DepositBalanceToClientByAccountNumber(vector<stClientInfo>& vClients, string AccountNumber, double DepositAmount)
{
	char AreYouSure = 'y';
	cout << "\nAre you sure you want to Prefrom this transaction? (Y/N) ?";
	cin >> AreYouSure;
	if (AreYouSure == 'Y' || AreYouSure == 'y')
	{

		for (stClientInfo& Client : vClients)
		{
			if (Client.AccountNumber == AccountNumber)
			{
				Client.AccountBalance += DepositAmount;
				cout << "\Deposit successful, new Blances is " << Client.AccountBalance << endl;
				SaveClientInFile(clientsFileName, vClients);
				return;
			}
		}

	}
	else
	{
		cout << "\nThe deposit has been cancelled.\n";
	}

}
void PrefromNormalWithdraw()
{
	int WithDrawBalance = ReadWithdrawAmount();
	if (WithDrawBalance > CurrentClient.AccountBalance)
	{
		cout << "\nAmount Exceeds your blance,Make Another Choice ,Press anyKey to Continue....";
		system("pause > nul");
		ShowNormalWithdrawScreen();
		return;
	}
	WithdrawBalanceFromClientByAccountNumber(vClientInfo, CurrentClient.AccountNumber, WithDrawBalance);
	CurrentClient.AccountBalance -= WithDrawBalance;
}
void ShowNormalWithdrawScreen()
{
	system("cls");
	cout << "-----------------------------------------------------\n";
	cout << "\t\tNormal Withdraw Screen\n";
	cout << "-----------------------------------------------------\n";
	PrefromNormalWithdraw();
}
double ReadDepositAmount(string Maseeage)
{
	double DepositAmount = 0;
	do {
	cout << Maseeage;
	cin >> DepositAmount;

	} while (DepositAmount <= 0);
	return DepositAmount;
}
void PrefromDeposit()
{
	double DepositAmount = ReadDepositAmount("Enter a positive Deposit Amount? ");

	DepositBalanceToClientByAccountNumber(vClientInfo, CurrentClient.AccountNumber, DepositAmount);
	CurrentClient.AccountBalance += DepositAmount;
}
void ShowDepositScreen()
{
	cout << "-----------------------------------------------------\n";
	cout << "\t\t    Deposit Screen\n";
	cout << "-----------------------------------------------------\n";
	PrefromDeposit();
}
void PrefromMainMenu(enAtmMainMenuOptions ClientOption)
{
	switch (ClientOption)
	{
	case enAtmMainMenuOptions::QuickWithraw:
	{
		system("cls");
		showQuickWithrawScreen();
		GoBackMainMenu();

	}; break;
	case enAtmMainMenuOptions::NormalWithdraw:
	{
		system("cls");
		ShowNormalWithdrawScreen();
		GoBackMainMenu();

	}; break;
	case enAtmMainMenuOptions::Deposit:
	{
		system("cls");
		ShowDepositScreen();
		GoBackMainMenu();

	}; break;
	case enAtmMainMenuOptions::CheckBalance:
	{
		system("cls");
		showCheckBalanceScreen();
		GoBackMainMenu();
	}; break;
	
	case enAtmMainMenuOptions::Logout: Login(); break;
	default:
		cout << "This option Not Bounds the Option Menu :-(\n";
	}
}
short ReadMenueOptions(string Message)
{
	short NumberOfOption = 0;
	cout << Message;
	cin >> NumberOfOption;
	return NumberOfOption;
}

void ShowAtmMainMenu()
{
	system("cls");
	cout << "-----------------------------------------------------\n";
	cout << "\t\tATM Main Menue Screen\n";
	cout << "-----------------------------------------------------\n";
	cout << "\t[1] Quick Withraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "-----------------------------------------------------\n";
	PrefromMainMenu((enAtmMainMenuOptions)ReadMenueOptions("Chose what do you want to do? [1 to 5]?"));
}

void Login()
{
	bool LoginFaild = false;
	vClientInfo = LoadClientDataFromFile(clientsFileName);
	string AccountNumber = "";
	string PinCode = "";

	do
	{
		system("cls");
		cout << "-----------------------------------------------\n";
		cout << "\t\tLogin Screen\n";
		cout << "-----------------------------------------------\n";
		if (LoginFaild)
		{
			cout << "Invlaid AccountNumber/PinCode!\n";
		}

		cout << "\nEnter AccountNumber ? ";
		cin >> AccountNumber;
		cout << "Enter Pin? ";
		cin >> PinCode;

		LoginFaild = !LoadUserInfo(vClientInfo, AccountNumber, PinCode);

	} while (LoginFaild);

  	ShowAtmMainMenu();
}
int main()
{
	Login();
}


