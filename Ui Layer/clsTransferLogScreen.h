#pragma once
#include <iomanip>
#include  "clsScreen.h"
#include  "clsBankClient.h"
using namespace std;
class clsTransferLogScreen:protected clsScreen
{
private:
	static void _PrintLoginRegisterRecordLine(clsBankClient::stTransferLogRecord TransferlogRegister)
	{
		cout << left;
		cout << "|" << setw(20)
			<< TransferlogRegister.DateTime;

		cout << "|" << setw(15)
			<< TransferlogRegister.SourceAccountNumber;

		cout << "|" << setw(15)
			<< TransferlogRegister.DestinationAccountNumber;

		cout << "|" << setw(10)
			<< TransferlogRegister.AmountTransfer;
			

		cout << "|" << setw(10)
			<< TransferlogRegister.SourceBalanceAfter;
		

		cout << "|" << setw(10)
			<< TransferlogRegister.DestinationBalanceAfter;
			

		cout << "|" << setw(15)
			<< TransferlogRegister.UserName<<"|";
			
	}
	static void _HeaderTransferLogRegisterList()
	{
		cout << left
			<< "-------------------------------------------------------------------------------------------------------\n";
		cout << "|" << setw(20)
			<< "Date/Time ";

		cout << "|" << setw(15)
			<< "S.Account ";

		cout << "|" << setw(15)
			<< "D.Account ";

		cout << "|" << setw(10)
			<< "Amount ";
			

		cout << "|" << setw(10)
			<< "S.Balance ";


			cout << "|" << setw(10)
			<< "D.Balance ";
			

			cout << "|" << setw(15)
				<< "User Name      |";

		cout << "\n-------------------------------------------------------------------------------------------------------\n";
	}
public:
	static void ShowTransferLogScreen()
	{
		vector<clsBankClient::stTransferLogRecord>vTransferLoginRegisters = clsBankClient::GetTransferLogRegister();
		if (vTransferLoginRegisters.size() > 0)
		{
			string Title = "    Transfer Log Screen";
			string SubTitle = "    \t\t" + to_string(vTransferLoginRegisters.size()) + " Records(s)";
			_DrawScreenHeader(Title, SubTitle);
			_HeaderTransferLogRegisterList();
			for (clsBankClient::stTransferLogRecord& Record : vTransferLoginRegisters)
			{
				_PrintLoginRegisterRecordLine(Record);
				cout << "\n-------------------------------------------------------------------------------------------------------\n";
			}

		}
		else
		{
			cout << "\t\t\t\t\tNo Transfer Log Register Available in the System :-(\n";
		}
	}
};

