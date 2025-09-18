// Banking System Version 1.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
enum enMainMenuOptions { ShowClientList = 1, Add_NewClient = 2, DeleteClient = 3, Update_ClientInfo = 4, FindClient = 5, Exit = 6 };
const string fileName = "clients.txt";
void ShowMainMenu();
void PrefromMainMenu(enMainMenuOptions ClientOption);
struct stClientInfo
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	float AccountBalance = 0.0;
	bool MarkClient = false;
};
short ReadMainMenuOptions(string Message)
{
	short NumberOfOption = 0;
	cout << Message;
	cin >> NumberOfOption;
	return NumberOfOption;
}
string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "Enter your Account Number : ";
	cin >> AccountNumber;
	return AccountNumber;
}

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
void PrintClientCard(stClientInfo ClientInfo)
{
	cout << "\nThe following are the client details :\n";
	cout << "--------------------------------------\n";
	cout << "Account Number:" << ClientInfo.AccountNumber << endl;
	cout << "PinCode       :" << ClientInfo.PinCode << endl;
	cout << "Name          :" << ClientInfo.Name << endl;
	cout << "Phone         :" << ClientInfo.Phone << endl;
	cout << "Account Balance :" << ClientInfo.AccountBalance << endl;
	cout << "--------------------------------------\n";

}
bool FindClientByAccountNumber(string AccountNumber, vector<stClientInfo>& vClients, stClientInfo& ClientInfo)
{

	for (stClientInfo& Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			ClientInfo = Client;
			return true;
		}

	}
	return false;
}
void SearchOnTheClient(vector<stClientInfo>& vClients)
{
	stClientInfo Client;
	string AccountNumber = ReadClientAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
	}
	else
	{
		cout << "Client with Account Number (" << AccountNumber << ") is Not found!\n\n";

	}
}
void ShowFindClientScreen(vector<stClientInfo>& vClients)
{
	cout << "------------------------------------------\n";
	cout << "           Find Clinet Screen \n";
	cout << "------------------------------------------\n\n";
	SearchOnTheClient(vClients);
}
void Header()
{
	cout << left << setw(90)
		<< "-----------------------------------------------------------------------------------------\n";
	cout << "|" << setw(16)
		<< " Account Number ";

	cout << "|" << setw(10)
		<< " Pin Code ";

	cout << "|" << setw(36)
		<< " Client Name ";

	cout << "|" << setw(10)
		<< "  Phone ";

	cout << "|" << setw(10)
		<< "  Balance "
		<< "|\n";

	cout << setw(90)
		<< "-----------------------------------------------------------------------------------------\n";
}
void ShowClient(stClientInfo ClientInfo)
{
	cout << left;
	cout << "|" << setw(16)
		<< ClientInfo.AccountNumber;

	cout << "|" << setw(10)
		<< ClientInfo.PinCode;

	cout << "|" << setw(36)
		<< ClientInfo.Name;

	cout << "|" << setw(10)
		<< ClientInfo.Phone;

	cout << "|" << setw(10)
		<< ClientInfo.AccountBalance
		<< "|\n";
	cout << "-----------------------------------------------------------------------------------------\n";

}
void showAllClientsScreen(vector<stClientInfo>& vClients)
{
	cout << "\t\t\t\tClient list " << (vClients.size()) << " clients(s)\n";
	Header();
	if (vClients.size() > 0)
	{

	   for (stClientInfo& Client : vClients)
	   {
		ShowClient(Client);
	    }

	}
	else
	{
		cout << "\t\t\t\t No Clients Available in the System!!\n";
	}

}
bool ClientExistsByAccountNumber(string FileName,string AccountNumber)
{

	stClientInfo ClientInfo;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	string line = "";
	if (MyFile.is_open())
	{
		while (getline(MyFile, line))
		{
			ClientInfo = ConvertLineDatatoRecord(line);
			if (ClientInfo.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
		}
	}
	MyFile.close();
	return false;
}
stClientInfo ReadNewClient(vector<stClientInfo>& vClients)
{
	stClientInfo ClientInfo;
	cout << "Enter Account Number :";
	getline(cin >> ws, ClientInfo.AccountNumber);
	while (ClientExistsByAccountNumber(fileName, ClientInfo.AccountNumber))
	{

		cout << "Client with [" << ClientInfo.AccountNumber << "] already exists, Enter another Account Number ? ";
		getline(cin >> ws, ClientInfo.AccountNumber);
	}
	cout << "Enter PinCode :";
	getline(cin, ClientInfo.PinCode);
	cout << "Enter Name :";
	getline(cin, ClientInfo.Name);
	cout << "Enter Phone :";
	getline(cin, ClientInfo.Phone);
	cout << "Enter Account Balance :";
	cin >> ClientInfo.AccountBalance;

	return ClientInfo;
}
void AddClientsToFile(string FileName, string dataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::app | ios::out);
	if (MyFile.is_open())
	{
		MyFile << dataLine << endl;
		MyFile.close();
	}
}
string ConvertRecordtoline(stClientInfo ClientInfo, string Sepertor = "#//#")
{
	string Line = "";
	Line += ClientInfo.AccountNumber + Sepertor;
	Line += ClientInfo.PinCode + Sepertor;
	Line += ClientInfo.Name + Sepertor;
	Line += ClientInfo.Phone + Sepertor;
	Line += to_string(ClientInfo.AccountBalance);

	return Line;
}
void AddNewClient(vector<stClientInfo>& vClients)
{
	stClientInfo ClientInfo = ReadNewClient(vClients);
	AddClientsToFile(fileName, ConvertRecordtoline(ClientInfo));
}
void AddNewClients(vector<stClientInfo>& vClients)
{
	char addMore = 'y';
	do {
		cout << "Add New Client:\n\n";
		AddNewClient(vClients);
		cout << "\nClient Added Successfuly,";
		cout << "Do you want to add more clients? (Y/N) => ";
		cin >> addMore;
		if (addMore == 'Y' || addMore == 'y')
			system("cls");

	} while (addMore == 'Y' || addMore == 'y');
	system("color 0F");
}
void showAddNewClients(vector<stClientInfo>& vClients)
{
	cout << "------------------------------------------\n";
	cout << "          Add New Clinets Screen \n";
	cout << "------------------------------------------\n\n";
	AddNewClients(vClients);
}
void ShowMainMenu()
{
	system("cls");
	cout << "-----------------------------------------------------\n";
	cout << "\t\tMain Menu Scree\n";
	cout << "-----------------------------------------------------\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Exit.\n";
	cout << "-----------------------------------------------------\n";
	PrefromMainMenu((enMainMenuOptions)ReadMainMenuOptions("Chose what do you want to do? [1 to 6]?"));
}
void Ends()
{
	system("cls");
	cout << "------------------------------------------\n";
	cout << "             Program Ends :-)\n";
	cout << "------------------------------------------\n";
}

void MarkClientByAccountNumber(string AccountNumber, vector<stClientInfo>& vClients)
{
	for (stClientInfo& client : vClients)
	{
		if (client.AccountNumber == AccountNumber)
		{
			client.MarkClient = true;
			break;
		}
	}
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
void DeleteClientByAccountNumber(string AccountNumber, vector<stClientInfo>& vClients)
{
	stClientInfo ClientInfo;
	char AreYouSure = 'y';

	if (FindClientByAccountNumber(AccountNumber, vClients, ClientInfo))
	{

		PrintClientCard(ClientInfo);

		cout << "\n\nAre You Sure Delete this client?(Y/N)=>";
		cin >> AreYouSure;
		if (AreYouSure == 'y' || AreYouSure == 'Y')
		{
			MarkClientByAccountNumber(AccountNumber, vClients);
			SaveClientInFile(fileName, vClients);
			cout << "\n\nclient deleted Successfuly \n";
			vClients = LoadClientDataFromFile(fileName);
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not found!\n\n";
	}
}
void ShowDeleteClientScreen(vector<stClientInfo> vClients)
{
	cout << "------------------------------------------\n";
	cout << "           Delete Clinet Screen \n";
	cout << "------------------------------------------\n\n";
	DeleteClientByAccountNumber(ReadClientAccountNumber(), vClients);
}
void UpdateClientInfo(stClientInfo& ClientInfo)
{
	cout << "\nEnter PinCode : ";
	getline(cin >> ws, ClientInfo.PinCode);
	cout << "Enter Name : ";
	getline(cin, ClientInfo.Name);
	cout << "Enter Phone : ";
	getline(cin, ClientInfo.Phone);
	cout << "Enter Account Balance : ";
	cin >> ClientInfo.AccountBalance;
}

void UpdateClientByAccountNumber(string AccountNumber, vector<stClientInfo>& vClients)
{
	stClientInfo ClientInfo;
	char AreYouSure = 'y';
	if (FindClientByAccountNumber(AccountNumber, vClients, ClientInfo))
	{
		PrintClientCard(ClientInfo);

		cout << "\n\nAre You Sure Want Update this client?(Y/N)=>";
		cin >> AreYouSure;
		if (AreYouSure == 'y' || AreYouSure == 'Y')
		{
			for (stClientInfo& client : vClients)
			{
				if (client.AccountNumber == AccountNumber)
				{
					UpdateClientInfo(client);
					break;
				}
			}
			SaveClientInFile(fileName, vClients);
			cout << "\n\nclient Update Successfuly \n";
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not found!\n\n";
	}
}
void ShowUpdateClientScreen(vector<stClientInfo>& vClients)
{
	cout << "------------------------------------------\n";
	cout << "         Update Clinet Info Screen \n";
	cout << "------------------------------------------\n\n";
	UpdateClientByAccountNumber(ReadClientAccountNumber(), vClients);
}

void GoMainScreen()
{
	cout << "\n Press any key to go back to Main Menu...";
	system("pause > nul");
	ShowMainMenu();
}

void PrefromMainMenu(enMainMenuOptions ClientOption)
{
	vector<stClientInfo> vClients = LoadClientDataFromFile(fileName);
	switch (ClientOption)
	{
	case enMainMenuOptions::Add_NewClient:
	{
		system("cls");
		showAddNewClients(vClients);
		GoMainScreen();
	}; break;
	case enMainMenuOptions::DeleteClient:
	{
		system("cls");
		ShowDeleteClientScreen(vClients);
		GoMainScreen();
	}; break;
	case enMainMenuOptions::Update_ClientInfo:
	{
		system("cls");
		ShowUpdateClientScreen(vClients);
		GoMainScreen();

	}; break;
	case enMainMenuOptions::ShowClientList:
	{
		system("cls");
		showAllClientsScreen(vClients);
		GoMainScreen();
	}; break;
	case enMainMenuOptions::FindClient:
	{
		system("cls");
		ShowFindClientScreen(vClients);
		GoMainScreen();
	}; break;
	case enMainMenuOptions::Exit:Ends(); break;
	default:
		cout << "This option Not Bounds the Option Menu :-(\n";
	}
}
int main()
{
	ShowMainMenu();
}
