#pragma once
#include <iomanip>
#include "clsBankClient.h"
#include  "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;
class clsTotalBalanceScreen:protected clsScreen
{
private:
	static void _PrintClientRecordBalanceLine(clsBankClient ClientInfo)
{
	cout << left;
	cout << "|" << setw(24)
		<< ClientInfo.AccountNumber;

	cout << "|" << setw(36)
		<< ClientInfo.FullName;

	cout << "|" << setw(25)
		<< ClientInfo.AccountBalance
		<< "|\n";
	cout << "-----------------------------------------------------------------------------------------\n";

}
	static void _HeaderTotalBlances()
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
public:
	static void ShowTotalBalancesScreen()
{
	vector<clsBankClient>vClients = clsBankClient::GetClientsList();
	if (vClients.size() > 0)
	{
		string Title = "    Total Balances Screen";
		string SubTitle = "    \t  Client list " + to_string(vClients.size()) + " clients(s)";
		_DrawScreenHeader(Title, SubTitle);
		_HeaderTotalBlances();
		for (clsBankClient& Client : vClients)
		{
			_PrintClientRecordBalanceLine(Client);
		}
		float TotalBalances = clsBankClient::GetTotalBlances();
		cout << "\n\t\t\t\tTotal Blances = " << TotalBalances << endl;
		cout << "\n\t\t(" << clsUtil::NumberToText(TotalBalances)<<")" << endl;
	}
	else
	{
		cout << "\t\t\t\tNo Clients Available in the System!!\n";
	}

}
};

