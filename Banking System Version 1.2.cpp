// Banking System Version 1.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

const string clientsFileName = "clients.txt";
const string fileUserName = "Users.txt";

enum enMainMenuOptions { ShowClientList = 1, Add_NewClient = 2, DeleteClient = 3, Update_ClientInfo = 4, FindClient = 5, Transactions = 6,
	ManageUser = 7, Logout = 8 };
enum enTransactionsMenuOptions { eDeposit = 1, eWithdraw = 2, eTotalBlances = 3, eMainMenue = 4 };
enum enManageUsersMenuOptions { eListUsers = 1, eAddUser = 2, eDeleteUser = 3, eUpdateUser = 4, FindUser = 5, MainMenu = 6 };
enum enMainMenuePermissions { pAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClientInfo = 8, pFindClient = 16, pTransactions = 32,
	pManageUser =64
};

struct stClientInfo
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	float AccountBalance = 0.0;
	bool MarkClient = false;
};

struct stUsers
{
	string UserName = "";
	string PassWord = "";
	short Permission = 0;
	bool MarkUser = false;
};
stUsers CurrentUser;
vector<stUsers> vUsers;
void ShowMainMenu();
void ShowTransactionsMenue(vector<stClientInfo>& vClients);
void ShowMangeUsersMenue();
void PrefromMainMenu(enMainMenuOptions ClientOption);
void PrefromTransactionsMenu(enTransactionsMenuOptions ClientOption, vector<stClientInfo>& vClients);
void PrefromManageUsersMenu(enManageUsersMenuOptions UserOption);
short ReadMenueOptions(string Message);
short ReadPermissionToSet();
stUsers ReadNewUser();
void AddNewUsers();
void showAddNewUsers();
bool LoadUserInfo(vector<stUsers>& vUsers, string UserName, string Password);
void Login();
void AddNewUser();
string ReadClientAccountNumber();
vector<string> SplitString(string String, string Delmt = "#//#");
stClientInfo ConvertLineToClientRecord(string LineData, string Sepertor = "#//#");
stUsers ConvertLineToUserRecord(string LineData, string Sepertor = "#//#");
vector<stClientInfo> LoadClientsDataFromFile(string FileName);
vector<stUsers> LoadUsersDataFromFile(string FileName);
void PrintClientCard(stClientInfo &ClientInfo);
void PrintUserCard(stUsers& User);
bool FindClientByAccountNumber(string AccountNumber, vector<stClientInfo>& vClients, stClientInfo& ClientInfo);
void SearchOnTheClient(vector<stClientInfo>& vClients);
void ShowFindClientScreen(vector<stClientInfo>& vClients);
void PrintClientsTableHeader();
void PrintUsersTableHeader();
void ShowDeleteUserScreen();
void DeleteUserByUserName(string UserName, vector<stUsers>& vUsers);
void ShowClient(stClientInfo ClientInfo);
void ShowUsers(stUsers &Users);
void ShowAccessDeniedMesssage();
void showAllClientsScreen(vector<stClientInfo>& vClients);
void showAllUsersScreen(vector<stUsers>& vUsers);
void ShowUpdateUserScreen();
void UpdateUserByUserName(string UserName, vector<stUsers>& vUsers);
bool ClientExistsByAccountNumber(string FileName, string AccountNumber);
bool FindUserByUserNameAndPassword(vector<stUsers>& vUsers, string UserName, string Password,stUsers &User);
bool FindUserByUserName(string UserName, vector<stUsers>& vUsers, stUsers& stUser);
bool CheakAccessPermission(enMainMenuePermissions Permission);
stClientInfo ReadNewClient(vector<stClientInfo>& vClients);
void AddDataLineToFile(string FileName, string dataLine);
string ConvertRecordtoline(stClientInfo ClientInfo, string Sepertor = "#//#");
string ConvertRecordtoline(stUsers User, string Sepertor = "#//#");
void AddNewClient(vector<stClientInfo>& vClients);
void AddNewClients(vector<stClientInfo>& vClients);
void showAddNewClients(vector<stClientInfo>& vClients);
void ShowFindUserScreen();
void SearchOnTheUser(vector<stUsers>& vUsers);
void MarkClientByAccountNumber(string AccountNumber, vector<stClientInfo>& vClients);
void MarkUserByUserName(string UserName, vector<stUsers>& vUsers);
void SaveClientInFile(string fileName, vector<stClientInfo>& vClients);
void SaveUserInFile(string fileName, vector<stUsers>& vUsers);
void DeleteClientByAccountNumber(string AccountNumber, vector<stClientInfo>& vClients);
void ShowDeleteClientScreen(vector<stClientInfo> &vClients);
void UpdateClientInfo(stClientInfo& ClientInfo);
void UpdateClientByAccountNumber(string AccountNumber, vector<stClientInfo>& vClients);
void ShowUpdateClientScreen(vector<stClientInfo>& vClients);
void GoBackMainMenu();
void GoBackTransactionsMenu(vector<stClientInfo>& vClients);
void GoBackManageUsersMenu();
void DepositBalanceToClientByAccountNumber(vector<stClientInfo>& vClients, string AccountNumber, double NumberofDeposit);
void DepositByAccountNumber(vector<stClientInfo>& vClients);
void ShowDepositScreen(vector<stClientInfo>& vClients);
void HeaderTotalBlances();
void ShowClientBlance(stClientInfo ClientInfo);
double TotalBlancesOfClients(const vector<stClientInfo>& vClients);
void showTotalBalancesOfScreen(vector<stClientInfo>& vClients);
void WithdrawBalanceFromClientByAccountNumber(vector<stClientInfo>& vClients, string AccountNumber, double NumberofWithdraw);
void WithdrawByAccountNumber(vector<stClientInfo>& vClients);
void ShowWithdrawScreen(vector<stClientInfo>& vClients);

int main()
{
	Login();
}

short ReadMenueOptions(string Message)
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
string ReadUserName()
{
	string UserName = "";
	cout << "Enter your User Name : ";
	cin >> UserName;
	return UserName;
}

vector<string> SplitString(string String, string Delmt )
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
stClientInfo ConvertLineToClientRecord(string LineData, string Sepertor )
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
stUsers ConvertLineToUserRecord(string LineData, string Sepertor )
{
	vector<string> vWord = SplitString(LineData, Sepertor);
	stUsers User;
	User.UserName = vWord[0];
	User.PassWord = vWord[1];
	User.Permission = stoi(vWord[2]);
	
	return User;
}

vector<stClientInfo> LoadClientsDataFromFile(string FileName)
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
			ClientInfo = ConvertLineToClientRecord(line);
			vClients.push_back(ClientInfo);
		}
		MyFile.close();
	}
	return vClients;
}
vector<stUsers> LoadUsersDataFromFile(string FileName)
{
	vector<stUsers>vUsers;
	stUsers Users;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	string line = "";
	if (MyFile.is_open())
	{
		while (getline(MyFile, line))
		{
			Users = ConvertLineToUserRecord(line);
			vUsers.push_back(Users);
		}
		MyFile.close();
	}
	return vUsers;
}
void PrintClientCard(stClientInfo &ClientInfo)
{
	cout << "\nThe following are the client details :\n";
	cout << "--------------------------------------\n";
	cout << "Account Number :" << ClientInfo.AccountNumber << endl;
	cout << "PinCode        :" << ClientInfo.PinCode << endl;
	cout << "Name           :" << ClientInfo.Name << endl;
	cout << "Phone          :" << ClientInfo.Phone << endl;
	cout << "Account Balance:" << ClientInfo.AccountBalance << endl;
	cout << "--------------------------------------\n";

}
void PrintUserCard(stUsers &User)
{
	cout << "\nThe following are the User details :\n";
	cout << "--------------------------------------\n";
	cout << "User Name :" << User.UserName << endl;
	cout << "PassWord  :" << User.PassWord << endl;
	cout << "Permission:" << User.Permission << endl;
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

bool FindUserByUserName(string UserName, vector<stUsers>& vUsers, stUsers &stUser)
{

	for (stUsers& User : vUsers)
	{
		if (User.UserName == UserName)
		{
			stUser = User;
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
	if (!CheakAccessPermission(enMainMenuePermissions::pFindClient))
	{
		ShowAccessDeniedMesssage();
		return;
	}

	cout << "------------------------------------------\n";
	cout << "\t  Find Clinet Screen \n";
	cout << "------------------------------------------\n\n";
	SearchOnTheClient(vClients);
}
void SearchOnTheUser(vector<stUsers>& vUsers)
{
	stUsers User;
	string UserName = ReadUserName();
	if (FindUserByUserName(UserName, vUsers, User))
	{
		PrintUserCard(User);
	}
	else
	{
		cout << "User with User Name (" << UserName << ") is Not found!\n\n";

	}
}
void ShowFindUserScreen()
{
	cout << "------------------------------------------\n";
	cout << "\t  Find User Screen \n";
	cout << "------------------------------------------\n\n";
	SearchOnTheUser(vUsers);
}
void PrintClientsTableHeader()
{
	cout << left 
		<< "-----------------------------------------------------------------------------------------\n";
	cout << "|" << setw(16)
		<< " Account Number ";

	cout << "|" << setw(10)
		<< " Pin Code ";

	cout << "|" << setw(36)
		<< " Client Name ";

	cout << "|" << setw(10)
		<< "  Phone ";

	cout << "|" << setw(10)
		<< "  Balance "
		<< "|\n";

	cout << "\n-----------------------------------------------------------------------------------------\n";
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
void PrintUsersTableHeader()
{
	cout << left 
		<< "-----------------------------------------------------------------------------------------\n";
	cout << "|" << setw(16)
		<< " User Name ";

	cout << "|" << setw(10)
		<< " PassWord ";

	cout << "|" << setw(36)
		<< " Permissions ";

	cout 
		<< "\n-----------------------------------------------------------------------------------------\n";
}
void ShowUsers(stUsers &Users)
{
	cout << left;
	cout << "|" << setw(16)
		<< Users.UserName;

	cout << "|" << setw(10)
		<< Users.PassWord;

	cout << "|" << setw(36)
		<< Users.Permission;

	cout << "\n-----------------------------------------------------------------------------------------\n";

}
void showAllClientsScreen(vector<stClientInfo>& vClients)
{
	if (!CheakAccessPermission(enMainMenuePermissions::pListClients))
	{
		ShowAccessDeniedMesssage();
		return;
	}

	cout << "\t\t\t\tClient list " << (vClients.size()) << " clients(s)\n";
	PrintClientsTableHeader();
	if (vClients.size() > 0)
	{

		for (stClientInfo& Client : vClients)
		{
			ShowClient(Client);
		}

	}
	else
	{
		cout << "\t\t\t\tNo Clients Available in the System!!\n";
	}

}
void showAllUsersScreen(vector<stUsers>& vUsers)
{
	cout << "\t\t\t\tUser list " << (vUsers.size()) << " Users(s)\n";
	PrintUsersTableHeader();
	if (vUsers.size() > 0)
	{

		for (stUsers& User : vUsers)
		{
			ShowUsers(User);
		}

	}
	else
	{
		cout << "\t\t\t\tNo Users Available in the System!!\n";
	}

}
bool ClientExistsByAccountNumber(string FileName, string AccountNumber)
{

	stClientInfo ClientInfo;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	string line = "";
	if (MyFile.is_open())
	{
		while (getline(MyFile, line))
		{
			ClientInfo = ConvertLineToClientRecord(line);
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
bool UserExistsByUserName(string FileName, string UserName)
{

	stUsers User;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	string line = "";
	if (MyFile.is_open())
	{
		while (getline(MyFile, line))
		{
			User = ConvertLineToUserRecord(line);
			if (User.UserName == UserName)
			{
				MyFile.close();
				return true;
			}
		}
	}
	MyFile.close();
	return false;
}
bool LoadUserInfo(vector<stUsers>& vUsers,string UserName, string Password)
{
	return (FindUserByUserNameAndPassword(vUsers, UserName,Password,CurrentUser));
}
bool FindUserByUserNameAndPassword(vector<stUsers> &vUsers,string UserName, string Password, stUsers &stUser)
{
		for(stUsers &User : vUsers)
		{
			if (User.UserName == UserName && User.PassWord == Password)
			{
				stUser = User;
				return true;
			}
		}
	
	return false;
}

stClientInfo ReadNewClient(vector<stClientInfo>& vClients)
{
	stClientInfo ClientInfo;
	cout << "Enter Account Number :";
	getline(cin >> ws, ClientInfo.AccountNumber);
	while (ClientExistsByAccountNumber(clientsFileName, ClientInfo.AccountNumber))
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
short ReadPermissionToSet()
{
	short Permission = 0;
	char Answer = 'n';
	cout << "Do you Want to give Full Access ? y/n ? ";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		return -1;
	}
	else
	{
		cout << "Do you went to give Access to:\n\n";
		cout << "Show Client List ? y/n ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission += enMainMenuePermissions::pListClients;
		}
		

		cout << "\nAdd New Client ? y/n ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission += enMainMenuePermissions::pAddNewClient;
		}
	

		cout << "\nDelete Client ? y/n ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission += enMainMenuePermissions::pDeleteClient;
		}
		else
		

		cout << "\nUpdate Client ? y/n ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission += enMainMenuePermissions::pUpdateClientInfo;
		}
	

		cout << "\nFind Client ? y/n ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission += enMainMenuePermissions::pFindClient;
		}
		

		cout << "\nTransactions ? y/n ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission += enMainMenuePermissions::pTransactions;
		}
		

		cout << "\nManage User ? y/n ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission += enMainMenuePermissions::pManageUser;
		}
	

	}
	return  Permission;
}
stUsers ReadNewUser()
{
	stUsers User;
	cout << "Enter User Name :";
	getline(cin >> ws, User.UserName);
	while (UserExistsByUserName(fileUserName, User.UserName))
	{

		cout << "User with [" << User.UserName << "] already exists, Enter another User Name ? ";
		getline(cin >> ws, User.UserName);
	}
	cout << "Enter PassWord :";
	getline(cin, User.PassWord);

	User.Permission = ReadPermissionToSet();

	return User;
}
void AddDataLineToFile(string FileName, string dataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::app | ios::out);
	if (MyFile.is_open())
	{
		MyFile << dataLine << endl;
		MyFile.close();
	}
}
string ConvertRecordtoline(stClientInfo ClientInfo, string Sepertor )
{
	string Line = "";
	Line += ClientInfo.AccountNumber + Sepertor;
	Line += ClientInfo.PinCode + Sepertor;
	Line += ClientInfo.Name + Sepertor;
	Line += ClientInfo.Phone + Sepertor;
	Line += to_string(ClientInfo.AccountBalance);

	return Line;
}
string ConvertRecordtoline(stUsers User, string Sepertor )
{
	string Line = "";
	Line += User.UserName + Sepertor;
	Line += User.PassWord + Sepertor;
	Line += to_string(User.Permission);

	return Line;
}
void AddNewClient(vector<stClientInfo>& vClients)
{
	stClientInfo ClientInfo = ReadNewClient(vClients);
	AddDataLineToFile(clientsFileName, ConvertRecordtoline(ClientInfo));
}
void AddNewUser()
{
	stUsers User = ReadNewUser();
	AddDataLineToFile(fileUserName, ConvertRecordtoline(User));
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
	
}
void showAddNewClients(vector<stClientInfo>& vClients)
{
	if (!CheakAccessPermission(enMainMenuePermissions::pAddNewClient))
	{
		ShowAccessDeniedMesssage();
		return;
	}

	cout << "------------------------------------------\n";
	cout << "\t  Add New Clinets Screen \n";
	cout << "------------------------------------------\n\n";
	AddNewClients(vClients);
}
void AddNewUsers()
{
	char addMore = 'y';
	do {
		cout << "Add New User:\n\n";
		AddNewUser();
		cout << "\nUser Added Successfuly,";
		cout << "Do you want to add more Users? (Y/N) => ";
		cin >> addMore;
		if (addMore == 'Y' || addMore == 'y')
			system("cls");

	} while (addMore == 'Y' || addMore == 'y');
	
}
void showAddNewUsers()
{
	cout << "------------------------------------------\n";
	cout << "\t  Add New Users Screen \n";
	cout << "------------------------------------------\n\n";
	AddNewUsers();
}
void ShowMainMenu()
{
	system("cls");
	cout << "-----------------------------------------------------\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "-----------------------------------------------------\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Tansactions.\n";
	cout << "\t[7] Mange User.\n";
	cout << "\t[8] Logout.\n";
	cout << "-----------------------------------------------------\n";
	PrefromMainMenu((enMainMenuOptions)ReadMenueOptions("Chose what do you want to do? [1 to 8]?"));
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
void MarkUserByUserName(string UserName, vector<stUsers>& vUsers)
{
	for (stUsers& User : vUsers)
	{
		if (User.UserName == UserName)
		{
			User.MarkUser = true;
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
void SaveUserInFile(string fileName, vector<stUsers>& vUsers)
{
	string LineData = "";
	fstream MyFile;
	MyFile.open(fileName, ios::out);
	if (MyFile.is_open())
	{
		for (stUsers & User : vUsers)
		{
			if (User.MarkUser == false)
			{
				LineData = ConvertRecordtoline(User);
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
			SaveClientInFile(clientsFileName, vClients);
			cout << "\n\nclient deleted Successfuly \n";
			vClients = LoadClientsDataFromFile(clientsFileName);
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not found!\n\n";
	}
}

void ShowDeleteClientScreen(vector<stClientInfo> &vClients)
{
	if (!CheakAccessPermission(enMainMenuePermissions::pDeleteClient))
	{
		ShowAccessDeniedMesssage();
		return;
	}

	cout << "------------------------------------------\n";
	cout << "\t  Delete Clinet Screen \n";
	cout << "------------------------------------------\n\n";
	DeleteClientByAccountNumber(ReadClientAccountNumber(), vClients);
}

void DeleteUserByUserName(string UserName, vector<stUsers>& vUsers)
{
	stUsers User;
	char AreYouSure = 'y';
	if (UserName == "admin")
	{
		cout << "\nYou Cannot Delete this User.\n\n";
		return;
	}
	if (FindUserByUserName(UserName, vUsers, User))
	{

		PrintUserCard(User);

		cout << "\n\nAre You Sure Delete this User?(Y/N)=>";
		cin >> AreYouSure;
		if (AreYouSure == 'y' || AreYouSure == 'Y')
		{
			MarkUserByUserName(UserName, vUsers);
			SaveUserInFile(fileUserName, vUsers);
			cout << "\n\nUser deleted Successfuly.\n";
			vUsers = LoadUsersDataFromFile(fileUserName);
		}
	}
	else
	{
		cout << "\nUser with User Name (" << UserName << ") is Not found!\n\n";
	}
}
void ShowDeleteUserScreen()
{
	cout << "------------------------------------------\n";
	cout << "\t  Delete User Screen \n";
	cout << "------------------------------------------\n\n";
	DeleteUserByUserName(ReadUserName(), vUsers);
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
void UpdateUserInfo(stUsers& UserInfo)
{
	cout << "\nEnter PassWord : ";
	getline(cin >> ws, UserInfo.PassWord);
	UserInfo.Permission = ReadPermissionToSet();
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
			SaveClientInFile(clientsFileName, vClients);
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
	if (!CheakAccessPermission(enMainMenuePermissions::pUpdateClientInfo))
	{
		ShowAccessDeniedMesssage();
		return;
	}

	cout << "------------------------------------------\n";
	cout << "\tUpdate Clinet Info Screen \n";
	cout << "------------------------------------------\n\n";
	UpdateClientByAccountNumber(ReadClientAccountNumber(), vClients);
}
void UpdateUserByUserName(string UserName, vector<stUsers>& vUsers)
{
	stUsers User;
	char AreYouSure = 'y';
	if (FindUserByUserName(UserName, vUsers, User))
	{
		PrintUserCard(User);

		cout << "\n\nAre You Sure Want Update this User?(Y/N)=>";
		cin >> AreYouSure;
		if (AreYouSure == 'y' || AreYouSure == 'Y')
		{
			for (stUsers& User : vUsers)
			{
				if (User.UserName == UserName)
				{
					UpdateUserInfo(User);
					break;
				}
			}
			SaveUserInFile(fileUserName, vUsers);
			cout <<"\n\nUser Update Successfuly\n";
		}
	}
	else
	{
		cout << "\nUser with User Name (" << UserName << ") is Not found!\n\n";
	}
}
void ShowUpdateUserScreen()
{
	cout << "------------------------------------------\n";
	cout << "\t  Update User Info Screen \n";
	cout << "------------------------------------------\n\n";
	UpdateUserByUserName(ReadUserName(), vUsers);
}

void GoBackMainMenu()
{
	cout << "\nPress any key to go back to Main Menu...";
	system("pause > nul");
	ShowMainMenu();
}
void GoBackTransactionsMenu(vector<stClientInfo>& vClients)
{
	cout << "\nPress any key to go back to Transactions Menu...";
	system("pause > nul");
	ShowTransactionsMenue(vClients);
}
void GoBackManageUsersMenu()
{
	cout << "\nPress any key to go back to Manage Users Menu...";
	system("pause > nul");
	ShowMangeUsersMenue();
}

void PrefromManageUsersMenu(enManageUsersMenuOptions UserOption)
{
	vUsers = LoadUsersDataFromFile(fileUserName);
	switch (UserOption)
	{
	case enManageUsersMenuOptions::eListUsers:
	{
		system("cls");
		showAllUsersScreen(vUsers);
		GoBackManageUsersMenu();
	}; break;
	case enManageUsersMenuOptions::eAddUser:
	{
		system("cls");
		showAddNewUsers();
		GoBackManageUsersMenu();
	}; break;
	case enManageUsersMenuOptions::eDeleteUser:
	{
		system("cls");
		ShowDeleteUserScreen();
		GoBackManageUsersMenu();

	}; break;
	case enManageUsersMenuOptions::eUpdateUser:
	{
		system("cls");
		ShowUpdateUserScreen();
		GoBackManageUsersMenu();

	}; break;
	case enManageUsersMenuOptions::FindUser:
	{
		system("cls");
		ShowFindUserScreen();
		GoBackManageUsersMenu();

	}; break;
	case enManageUsersMenuOptions::MainMenu:
	{
		ShowMainMenu();
	}; break;
	default:
		cout << "This option Not Bounds the Option Menu :-(\n";
	}
}
bool CheakAccessPermission(enMainMenuePermissions Permission)
{
	if(CurrentUser.Permission == enMainMenuePermissions::pAll) return true;

	return((CurrentUser.Permission & Permission) == Permission);
		
}
void ShowMangeUsersMenue()
{
	if (!CheakAccessPermission(enMainMenuePermissions::pManageUser))
	{
		 ShowAccessDeniedMesssage();
		 return;
	}


	system("cls");
	cout << "-----------------------------------------------------\n";
	cout << "\t\tManage Users Menue Screen\n";
	cout << "-----------------------------------------------------\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Manage.\n";
	cout << "-----------------------------------------------------\n";
	PrefromManageUsersMenu((enManageUsersMenuOptions)ReadMenueOptions("Chose what do you want to do? [1 to 6]?"));
}


void ShowTransactionsMenue(vector<stClientInfo>& vClients)
{
	if (!CheakAccessPermission(enMainMenuePermissions::pTransactions))
	{
		ShowAccessDeniedMesssage();
		return;
	}

	system("cls");
	cout << "-----------------------------------------------------\n";
	cout << "\t\tTransactions Menue Screen\n";
	cout << "-----------------------------------------------------\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Blances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "-----------------------------------------------------\n";
	PrefromTransactionsMenu((enTransactionsMenuOptions)ReadMenueOptions("Chose what do you want to do? [1 to 4]?"), vClients);
}


void DepositBalanceToClientByAccountNumber(vector<stClientInfo>& vClients, string AccountNumber, double NumberofDeposit)
{
	char AreYouSure = 'y';
	cout << "\nAre you sure you want to Prefrom this transaction? (Y/N) ?";
	cin >> AreYouSure;
	if (AreYouSure == 'Y' || AreYouSure == 'y')
	{

		for (stClientInfo& ClientInfo : vClients)
		{
			if (ClientInfo.AccountNumber == AccountNumber)
			{
				ClientInfo.AccountBalance += NumberofDeposit;
				cout << "\Deposit successful, new Blances is " << ClientInfo.AccountBalance << endl;
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
void DepositByAccountNumber(vector<stClientInfo>& vClients)
{
	stClientInfo Client;
	double NumberofDeposit = 0.0;
	string AccountNumber = ReadClientAccountNumber();
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "Client with Account Number (" << AccountNumber << ") is Not Exist!\n\n";
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClientCard(Client);
	cout << "\nPlase enter deposit amount? ";
	cin >> NumberofDeposit;
	DepositBalanceToClientByAccountNumber(vClients, AccountNumber, NumberofDeposit);



}
void ShowDepositScreen(vector<stClientInfo>& vClients)
{
	cout << "------------------------------------------\n";
	cout << "\t    Deposit Screen \n";
	cout << "------------------------------------------\n\n";
	DepositByAccountNumber(vClients);
}
void HeaderTotalBlances()
{
	cout << left << setw(90)
		<< "-----------------------------------------------------------------------------------------\n";
	cout << "|" << setw(24)
		<< " Account Number ";

	cout << "|" << setw(36)
		<< " Client Name ";

	cout << "|" << setw(25)
		<< " Balance "
		<< "|\n";

	cout << setw(90)
		<< "-----------------------------------------------------------------------------------------\n";
}
void ShowClientBlance(stClientInfo ClientInfo)
{
	cout << left;
	cout << "|" << setw(24)
		<< ClientInfo.AccountNumber;

	cout << "|" << setw(36)
		<< ClientInfo.Name;

	cout << "|" << setw(25)
		<< ClientInfo.AccountBalance
		<< "|\n";
	cout << "-----------------------------------------------------------------------------------------\n";

}
double TotalBlancesOfClients(const vector<stClientInfo>& vClients)
{
	double TotalBlances = 0.0;
	for (const stClientInfo& Client : vClients)
	{
		TotalBlances += Client.AccountBalance;
	}
	return TotalBlances;
}
void showTotalBalancesOfScreen(vector<stClientInfo>& vClients)
{
	cout << "\t\t\t\tClient list " << (vClients.size()) << " clients(s)\n";
	HeaderTotalBlances();
	if (vClients.size() > 0)
	{
		for (stClientInfo& Client : vClients)
		{
			ShowClientBlance(Client);
		}
		cout << "\n\t\t\t\tTotal Blances = " << TotalBlancesOfClients(vClients) << endl;
	}
	else
	{
		cout << "\t\t\t\tNo Clients Available in the System!!\n";
	}

}
void WithdrawBalanceFromClientByAccountNumber(vector<stClientInfo>& vClients, string AccountNumber, double NumberofWithdraw)
{
	char AreYouSure = 'y';
	for (stClientInfo& ClientInfo : vClients)
	{
		if (ClientInfo.AccountNumber == AccountNumber)
		{
			cout << "\nAre you sure you want to Prefrom this transaction? (Y/N) ?";
			cin >> AreYouSure;
			if (AreYouSure == 'Y' || AreYouSure == 'y')
			{
				ClientInfo.AccountBalance -= NumberofWithdraw;
				cout << "\nWithdraw successful, new Blances is " << ClientInfo.AccountBalance << endl;
				SaveClientInFile(clientsFileName, vClients);
				return;
			}
			else
			{
				cout << "\nThe Withdraw has been cancelled.\n";
			}

		}
	}
}
void WithdrawByAccountNumber(vector<stClientInfo>& vClients)
{
	stClientInfo Client;
	double Amount = 0.0;
	char AreYouSure = 'y';
	string AccountNumber = ReadClientAccountNumber();
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "Client with Account Number (" << AccountNumber << ") is Not Exist!\n\n";
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClientCard(Client);
	cout << "\nPlase enter Withdraw amount? ";
	cin >> Amount;
	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the blance? ,you Can Withdraw up to :" << Client.AccountBalance;
		cin >> Amount;
	}

	WithdrawBalanceFromClientByAccountNumber(vClients, AccountNumber, Amount);
}

void ShowWithdrawScreen(vector<stClientInfo>& vClients)
{
	cout << "------------------------------------------\n";
	cout << "\t   Withdraw Screen \n";
	cout << "------------------------------------------\n\n";
	WithdrawByAccountNumber(vClients);
}

void PrefromTransactionsMenu(enTransactionsMenuOptions ClientOption, vector<stClientInfo>& vClients)
{
	switch (ClientOption)
	{
	case enTransactionsMenuOptions::eDeposit:
	{
		system("cls");
		ShowDepositScreen(vClients);
		GoBackTransactionsMenu(vClients);
	}; break;
	case enTransactionsMenuOptions::eWithdraw:
	{
		system("cls");
		ShowWithdrawScreen(vClients);
		GoBackTransactionsMenu(vClients);
	}; break;
	case enTransactionsMenuOptions::eTotalBlances:
	{
		system("cls");
		showTotalBalancesOfScreen(vClients);
		GoBackTransactionsMenu(vClients);

	}; break;
	case enTransactionsMenuOptions::eMainMenue:
	{
		ShowMainMenu();
	}; break;
	default:
		cout << "This option Not Bounds the Option Menu :-(\n";
	}
}

void ShowAccessDeniedMesssage()
{
	system("cls");
	cout << "------------------------------------------\n";
	cout << "Access Denied,\n";
	cout << "You Dont Have Premission To Do this,\n";
	cout << "Please Conact Your Admin.\n";
	cout << "------------------------------------------\n\n\n\n";
	GoBackMainMenu();
}
void PrefromMainMenu(enMainMenuOptions ClientOption)
{
	vector<stClientInfo> vClients = LoadClientsDataFromFile(clientsFileName);
	
	switch (ClientOption)
	{
	case enMainMenuOptions::Add_NewClient:
	{
	system("cls");
	showAddNewClients(vClients);
	GoBackMainMenu();
		
	}; break;
	case enMainMenuOptions::DeleteClient:
	{
		system("cls");
		ShowDeleteClientScreen(vClients);
		GoBackMainMenu();
		
	}; break;
	case enMainMenuOptions::Update_ClientInfo:
	{
		system("cls");
		ShowUpdateClientScreen(vClients);
		GoBackMainMenu();
	
	}; break;
	case enMainMenuOptions::ShowClientList:
	{
		system("cls");
		showAllClientsScreen(vClients);
		GoBackMainMenu();
	}; break;
	case enMainMenuOptions::FindClient:
	{
		
		system("cls");
		ShowFindClientScreen(vClients);
		GoBackMainMenu();
		
	}; break;
	case enMainMenuOptions::Transactions:
	{
		system("cls");
		ShowTransactionsMenue(vClients);
		GoBackMainMenu();
	}; break;
	case enMainMenuOptions::ManageUser:
	{
		system("cls");
		ShowMangeUsersMenue();
		GoBackMainMenu();
	}; break;
	case enMainMenuOptions::Logout: Login(); break;
	default:
		cout << "This option Not Bounds the Option Menu :-(\n";
	}
}

void Login()
{
	bool LoginFaild = false;
    vUsers = LoadUsersDataFromFile(fileUserName);
	string UserName = "";
	string PassWord = "";
	
	do
	{
	  system("cls");
	  cout << "-----------------------------------------------\n";
	  cout << "\t\tLogin Screen\n";
	  cout << "-----------------------------------------------\n";
	  if (LoginFaild)
	  {
		  cout<<"Invlaid UserName/PassWord!\n";
	  }

		cout << "\nEnter UserName ? ";
		cin >> UserName;
		cout << "Enter PassWord ? ";
		cin >> PassWord;
			
		LoginFaild = !LoadUserInfo(vUsers, UserName, PassWord);

	} while (LoginFaild);
	ShowMainMenu();
}