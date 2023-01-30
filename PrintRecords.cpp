#include <fstream>
#include <iomanip>
#include "PrintRecords.h"

using namespace std;
namespace samples
{
	Record ReadRecord(istream& stream, bool bPrompt) //istream은 입력 스트림
	{
		Record record;

		if (bPrompt)
		{
			cout << "Frist name: ";
		}
		stream >> record.FirstName; //스트림에서 이름 읽어오기

		if (bPrompt)
		{
			cout << "Last name: ";
		}
		stream >> record.LastName;

		if (bPrompt)
		{
			cout << "Student ID: ";
		}
		stream >> record.StudentID;

		if (bPrompt)
		{
			cout << "Score ";
		}
		stream >> record.Score;

		return record;
	}

	void DisplayRecords(fstream& fileStream)//파일 입력 및 출력은 fstream
	{
		fileStream.seekg(0); //읽기 포인터 이동, 처음부터 한줄씩 읽음

		string line;
		while (true)
		{
			getline(fileStream, line);

			if (fileStream.eof())
			{
				fileStream.clear();
				break;
			}
			cout << line << endl;
		}
	}

	void WriteFileRecord(fstream& outputStream, const Record& record)
	{
		outputStream.seekp(0, ios_base::end); //쓰는 포인터 맨 뒤로 옮기기

		outputStream << record.FirstName << " "
			<< record.LastName << " "
			<< record.StudentID << " "
			<< record.Score << endl;

		outputStream.flush();
	}

	void ManageRecordsExample()
	{
		cout << "Manage Records Example" << endl;

		fstream fileStream;
		fileStream.open("studentRecord.dat", ios_base::in | ios_base::out);

		bool bExit = false;
		while (!bExit)
		{
			char command = ' ';

			cout << "a: add" << endl
				<< "d: display" << endl
				<< "x: exit" << endl;

			cin >> command;
			cin.ignore(LLONG_MAX, '\n');

			switch (command)
			{
			case 'a':
			{
				Record record = ReadRecord(cin, true);
				WriteFileRecord(fileStream, record);
				break;
			}
			case 'd':
			{
				DisplayRecords(fileStream);
				break;
			}
			case 'x':
			{
				bExit = true;
				break;
			}
			default:
			{
				cout << "invalid input" << endl;
				break;
			}
			}
		}
		fileStream.close();
	}
}