#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const char* DIVIDER = "-------------------------------------------------------------------------";

int myAtoi(const char* str)
{
	int result = 0;

	for (unsigned int i = 0; str[i] != '\0'; ++i)
	{
		if ('0' <= str[i] && str[i] <= '9')
		{
			result = result * 10 + str[i] - '0';
		}
	}

	return result;
}

// Utils
int findStudentById(vector<string> studentIds, string id);
int findLectureByCode(vector<string> lectureCodes, string code);
void deleteElement(vector<string>& v, int index);

// File read
void readStudentFile(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes);
void readLectureFile(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits);

// File write
void writeStudentFile(const vector<string>& studentIds, const vector<string>& passwords, const vector<string>& names, const vector<int>& credits, const vector<vector<string>>& appliedLectureCodes);
void writeLectureFile(const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, const vector<int>& limits);

// Get user input
string getInputId();
string getInputPassword();

// Login
int studentLogin(const vector<string>& studentIds, const vector<string>& passwords);
bool adminLogin();
int login(const vector<string>& studentIds, const vector<string>& passwords);

// Common
void printLectures(const vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, const vector<int>& limits, const int& user = -100);

// Admin
void addStudent(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes);
void addLecture(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits);
void deleteLecture(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits, vector<int>& credits, vector<vector<string>>& appliedLectureCodes);
int runAdmin(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits);

// User
void printStudent(const vector<string>& studentIds, const vector<string>& names, const vector<int>& credits, const int& user);
void applyLecture(const vector<string>& studentIds, const vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, vector<int>& limits, const int& user);
void disapplyLecture(const vector<string>& studentIds, const vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, vector<int>& limits, const int& user);
void changePassword(vector<string>& passwords, const int& user);
int runStudent(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits, int user);

int main() {
	int user = -1; //user index
	int status = -1;

	// Student Info
	vector<string> studentIds;
	vector<string> passwords;
	vector<string> names;
	vector<int> credits;
	vector<vector<string>> appliedLectureCodes;

	// Lecture Info
	vector<string> lectureCodes;
	vector<string> lectureNames;
	vector<int> lectureCredits;
	vector<int> limits;

	// Read from files
	readStudentFile(studentIds, passwords, names, credits, appliedLectureCodes);
	readLectureFile(lectureCodes, lectureNames, lectureCredits, limits);

	// Login phase
	while (status == -1) {
		user = login(studentIds, passwords);
		if (user == -999) { // Login fail
			break;
		}
		else if (user == -1) { // Exit command
			break;
		}
		else if (user == -100) { // Admin login success
			status = runAdmin(studentIds, passwords, names, credits, appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits);
		}
		else { // Student login success
			status = runStudent(studentIds, passwords, names, credits, appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
		}
	}
	// Write to files
	writeStudentFile(studentIds, passwords, names, credits, appliedLectureCodes);
	writeLectureFile(lectureCodes, lectureNames, lectureCredits, limits);
	return 0;
}
int findStudentById(vector<string> studentIds, string id) {
	for (unsigned i = 0; i < studentIds.size(); i++) {
		if (studentIds[i] == id)
			return i;
	}
	return -1;
}
int findLectureByCode(vector<string> lectureCodes, string code) {
	for (unsigned i = 0; i < lectureCodes.size(); i++) {
		if (lectureCodes[i] == code)
			return i;
	}
	return -1;
}
void deleteElement(vector<string>& v, int index) {
	v.erase(v.begin() + index);
}
void deleteElement(vector<int>& v, int index) {
	v.erase(v.begin() + index);
}
void readStudentFile(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes) {
	ifstream studentFile("students.txt");

	char fileInput;
	string vectorInput;
	string trash;
	unsigned int parseTurn = 0;
	unsigned int studentTurn = 0;
	while (!studentFile.eof())
	{
		studentFile.get(fileInput);
		// std::cout << "char: " << fileInput << std::endl;

		if (studentFile.fail())
		{
			studentFile.clear();
			studentFile >> trash;
		}
		else
		{
			if (fileInput != '\t' && fileInput != '\n')
			{
				vectorInput.push_back(fileInput);
			}
			else 
			{
				switch (parseTurn)
				{
				case 0:		studentIds.push_back(vectorInput);
							appliedLectureCodes.push_back(vector<string>());
							break;
				case 1:		passwords.push_back(vectorInput);
							break;
				case 2:		names.push_back(vectorInput);
							break;
				case 3:		credits.push_back(myAtoi(vectorInput.c_str()));
							break;
				case 4:		appliedLectureCodes[studentTurn].push_back(vectorInput);
							--parseTurn;
							break;
				default:	
							break;
				}

				vectorInput.clear();
				if (fileInput == '\t')
				{
					++parseTurn;
				}
				else
				{
					++studentTurn;
					parseTurn = 0;
				}
			}
		}
	}

	studentFile.close();
}
void readLectureFile(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits) {
	ifstream lectureFile("lectures.txt");

	char fileInput;
	string vectorInput;
	string trash;
	unsigned int parseTurn = 0;
	unsigned int lectureTurn = 0;
	while (!lectureFile.eof())
	{
		lectureFile.get(fileInput);

		if (lectureFile.fail())
		{
			lectureFile.clear();
			lectureFile >> trash;
		}
		else
		{
			if (fileInput != '\t' && fileInput != '\n')
			{
				vectorInput.push_back(fileInput);
			}
			else 
			{
				switch (parseTurn)
				{
				case 0:		lectureCodes.push_back(vectorInput);
							break;
				case 1:		lectureNames.push_back(vectorInput);
							break;
				case 2:		lectureCredits.push_back(myAtoi(vectorInput.c_str()));
							break;
				case 3:		limits.push_back(myAtoi(vectorInput.c_str()));
							break;
				default:	break;
				}

				vectorInput.clear();
				if (fileInput == '\t')
				{
					++parseTurn;
				}
				else
				{
					++lectureTurn;
					parseTurn = 0;
				}
			}
		}
	}

	lectureFile.close();
}

void writeStudentFile(const vector<string>& studentIds, const vector<string>& passwords, const vector<string>& names, const vector<int>& credits, const vector<vector<string>>& appliedLectureCodes) {
	/* 구현 */
	std::ofstream studentFile("students.txt", std::ofstream::out | std::ofstream::trunc);

	for (unsigned int user = 0; user < studentIds.size(); ++user)
	{
		studentFile << studentIds[user] << "\t" << passwords[user] << "\t" << names[user] << "\t" << credits[user];
		for (unsigned int lecture = 0; lecture < appliedLectureCodes[user].size(); ++lecture)
		{
			studentFile << "\t" << appliedLectureCodes[user][lecture];
		}
		studentFile << std::endl;
	}

	studentFile.close();
}
void writeLectureFile(const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, const vector<int>& limits) {
	/* 구현 */
	std::ofstream lectureFile("lectures.txt", std::ofstream::out | std::ofstream::trunc);

	for (unsigned int lecture = 0; lecture < lectureCodes.size(); ++lecture)
	{
		lectureFile << lectureCodes[lecture] << "\t" << lectureNames[lecture] << "\t" << lectureCredits[lecture] << "\t" << limits[lecture] << std::endl;
	}

	lectureFile.close();
}
string getInputId() {
	/* 구현 */
	std::string userId;
	std::string trash;
	while (!cin.eof())
	{
		std::cout << "아이디: ";
		cin >> userId;
		if (cin.fail())
		{
			cin.clear();
			cin >> trash;
		}
		else
		{
			break;
		}
	}

	return userId;
}
string getInputPassword() {
	/* 구현 */
	std::string userPassword;
	std::string trash;
	while (!cin.eof())
	{
		std::cout << "비밀번호: ";
		cin >> userPassword;
		if (cin.fail())
		{
			cin.clear();
			cin >> trash;
		}
		else
		{
			break;
		}
	}

	return userPassword;
}

int studentLogin(const vector<string>& studentIds, const vector<string>& passwords) {
	int idIndex = -1;
	bool bIsCorrectPassword = false;
	std::string userId = getInputId();
	std::string userPassword = getInputPassword();

	idIndex = findStudentById(studentIds, userId);
	bIsCorrectPassword = (passwords[idIndex] == userPassword);

	if (idIndex == -1 || !bIsCorrectPassword)
	{
		return -1;
	}

	return idIndex;
}

bool adminLogin() {
	bool bIsAdminId = false;
	bool bIsAdminPassword = false;

	std::string userId = getInputId();
	std::string userPassword = getInputPassword();

	bIsAdminId = (userId == "admin");
	bIsAdminPassword = (userPassword == "admin");

	return (bIsAdminId && bIsAdminPassword);
}

int login(const vector<string>& studentIds, const vector<string>& passwords) {
	std::cout << DIVIDER << std::endl;
	std::cout << "1. 학생 로그인" << std::endl;
	std::cout << "2. 관리자 로그인" << std::endl;
	std::cout << "3. 종료" << std::endl;
	std::cout << DIVIDER << std::endl;

	bool bAdminLoginSuccess = false;
	char userInput = '\0';
	int userIndex = -1;
	std::string trash;
	unsigned int loginCount = 3;
	while (!cin.eof() && loginCount > 0)
	{
		cin >> userInput;

		if (cin.fail())
		{
			cin.clear();
			cin >> trash;
		}
		else
		{
			switch (userInput)
			{
			case '1':		while (loginCount > 0)
							{
								userIndex = studentLogin(studentIds, passwords);
								if (userIndex == -1)
								{
									--loginCount;
									std::cout << "로그인 " << 3 - loginCount << "회 실패 (3회 실패 시 종료)" << std::endl;
								}
								else
								{
									return userIndex;
								}
							}
							break;
			case '2':		while (loginCount > 0)
							{
								bAdminLoginSuccess = adminLogin();
								if (!bAdminLoginSuccess)
								{
									--loginCount;
									std::cout << "로그인 " << 3 - loginCount << "회 실패 (3회 실패 시 종료)" << std::endl;
								}
								else
								{
									return -100;
								}
							}
							break;
			case '0':		break;
			default:		break;
			}

			return -999;
		}
	}

	return -999;
}

void printLectures(const vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, const vector<int>& limits, const int& user) {
	/* 구현 */
	std::cout << DIVIDER << std::endl;
	unsigned int maxLectureName = 0;
	unsigned int maxLectureCode = 0;

	std::cout << "과목코드\t강의명\t\t학점\t수강가능인원" << std::endl;
	if (user == -100)
	{
		for (unsigned int lecture = 0; lecture < lectureNames.size(); ++lecture)
		{
			if (lectureNames[maxLectureName].size() < lectureNames[lecture].size())
			{
				maxLectureName = lecture;
			}

			if (lectureCodes[maxLectureCode].size() < lectureCodes[lecture].size())
			{
				maxLectureCode = lecture;
			}
		}

		for (unsigned int lecture = 0; lecture < lectureCodes.size(); ++lecture)
		{
			std::cout << lectureCodes[lecture] << "\t" << lectureNames[lecture];

			for (unsigned int i = 0; i < ((lectureNames[maxLectureName].size() / 3) - (lectureNames[lecture].size() / 3)) + (lectureCodes[maxLectureCode].size() / 3) - (lectureCodes[lecture].size() / 3); i += 4)
			{
				std::cout << "\t";
			}
			std::cout << lectureCredits[lecture] << "\t" << limits[lecture] << std::endl;
		}
	}
	else
	{
		for (unsigned int lecture = 0; lecture < appliedLectureCodes[user].size(); ++lecture)
		{
			int lectureIndex = findLectureByCode(lectureCodes, appliedLectureCodes[user][lecture]);
			if (lectureNames[maxLectureName].size() < lectureNames[lectureIndex].size())
			{
				maxLectureName = lectureIndex;
			}

			if (lectureCodes[maxLectureCode].size() < lectureCodes[lectureIndex].size())
			{
				maxLectureCode = lectureIndex;
			}
		}

		for (unsigned int lecture = 0; lecture < appliedLectureCodes[user].size(); ++lecture)
		{
			int lectureIndex = findLectureByCode(lectureCodes, appliedLectureCodes[user][lecture]);
			std::cout << lectureCodes[lectureIndex] << "\t" << lectureNames[lectureIndex];

			for (unsigned int i = 0; i < ((lectureNames[maxLectureName].size() / 3) - (lectureNames[lectureIndex].size() / 3)) + (lectureCodes[maxLectureCode].size() / 3) - (lectureCodes[lectureIndex].size() / 3); i += 4)
			{
				std::cout << "\t";
			}
			std::cout << lectureCredits[lectureIndex] << "\t" << limits[lectureIndex] << std::endl;
		}
	}
	std::cout << DIVIDER << std::endl;
}
void addStudent(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes) {
	/* 구현 */
	std::cout << DIVIDER << std::endl;

	std::string trash;
	std::string newId;
	while (!cin.eof())
	{
		std::cout << "학번: ";
		cin >> newId;

		if (cin.fail())
		{
			cin.clear();
			cin >> trash;
		}
		else
		{
			break;
		}
	}

	std::string newPassword;
	while (!cin.eof())
	{
		std::cout << "비밀번호: ";
		cin >> newPassword;

		if (cin.fail())
		{
			cin.clear();
			cin >> trash;
		}
		else
		{
			break;
		}
	}

	std::string newName;
	while (!cin.eof())
	{
		std::cout << "학생 이름: ";
		cin >> newName;

		if (cin.fail())
		{
			cin.clear();
			cin >> trash;
		}
		else
		{
			break;
		}
	}
	std::cout << DIVIDER << std::endl;

	if (findStudentById(studentIds, newId) != -1)
	{
		std::cout << "이미 존재하는 학번입니다." << std::endl;
	}
	else
	{
		studentIds.push_back(newId);
		passwords.push_back(newPassword);
		names.push_back(newName);
		credits.push_back(18);
		appliedLectureCodes.push_back(std::vector<std::string>());
		std::cout << "성공적으로 등록되었습니다." << std::endl;
	}
}
void addLecture(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits) {
	/* 구현 */
	std::cout << DIVIDER << std::endl;

	std::string trash;
	std::string newCode;
	while (!cin.eof())
	{
		std::cout << "과목코드: ";
		cin >> newCode;

		if (cin.fail())
		{
			cin.clear();
			cin >> trash;
		}
		else
		{
			break;
		}
	}

	std::string newName;
	while (!cin.eof())
	{
		std::cout << "과목명: ";
		cin >> newName;

		if (cin.fail())
		{
			cin.clear();
			cin >> trash;
		}
		else
		{
			break;
		}
	}

	std::string newCredit;
	while (!cin.eof())
	{
		std::cout << "학점: ";
		cin >> newCredit;

		if (cin.fail())
		{
			cin.clear();
			cin >> trash;
		}
		else
		{
			if (myAtoi(newCredit.c_str()) != -1)
			{
				break;
			}
		}
	}
	
	std::string newLimit;
	while (!cin.eof())
	{
		std::cout << "수강인원: ";
		cin >> newLimit;

		if (cin.fail())
		{
			cin.clear();
			cin >> trash;
		}
		else
		{
			if (myAtoi(newLimit.c_str()) != -1)
			{
				break;
			}
		}
	}
	std::cout << DIVIDER << std::endl;
	
	if (findLectureByCode(lectureCodes, newCode) != -1)
	{
		std::cout << "이미 존재하는 과목코드 입니다." << std::endl;
	}
	else
	{
		lectureCodes.push_back(newCode);
		lectureNames.push_back(newName);
		lectureCredits.push_back(myAtoi(newCredit.c_str()));
		limits.push_back(myAtoi(newLimit.c_str()));
		std::cout << "성공적으로 강의가 개설되었습니다." << std::endl;
	}
}
void deleteLecture(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits, vector<int>& credits, vector<vector<string>>& appliedLectureCodes) {
	/* 구현 */
	/* 내부 호출 함수: printLectures*/
	printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits);

	std::string userInput;
	std::string trash;
	while (!cin.eof())
	{
		std::cout << "삭제할 강의코드 (0: 뒤로가기) >> ";
		std::cin >> userInput;

		if (cin.fail())
		{
			cin.clear();
			cin >> trash;
		}
		else
		{
			if (userInput == "0")
			{
				return;
			}
			else
			{
				int lectureToDelete = findLectureByCode(lectureCodes, userInput);
				if (lectureToDelete == -1)
				{
					std::cout << "일치하는 코드가 없습니다." << std::endl;
					return;
				}

				std::cout << "성공적으로 강의가 폐쇄되었습니다." << std::endl;
				for (unsigned int users = 0; users < appliedLectureCodes.size(); ++users)
				{
					for (unsigned int lectures = 0; lectures < appliedLectureCodes[users].size(); ++lectures)
					{
						if (appliedLectureCodes[users][lectures] == lectureCodes[lectureToDelete])
						{
							deleteElement(appliedLectureCodes[users], lectures);
							credits[users] += lectureCredits[lectureToDelete];
							break;
						}
					}
				}

				deleteElement(lectureCodes, lectureToDelete);
				deleteElement(lectureNames, lectureToDelete);
				deleteElement(lectureCredits, lectureToDelete);
				deleteElement(limits, lectureToDelete);
				return;
			}
		}
	}
}
int runAdmin(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits) {
	/* 구현 */
	/* 내부 호출 함수: addStudent, addLecture, deleteLecture*/
	while (true)
	{
		std::cout << DIVIDER << std::endl;
		std::cout << "1. 학생 추가" << std::endl;
		std::cout << "2. 강의 개설" << std::endl;
		std::cout << "3. 강의 삭제" << std::endl;
		std::cout << "4. 로그아웃" << std::endl;
		std::cout << "0. 종료" << std::endl;
		std::cout << DIVIDER << std::endl;

		char userInput = '\0';
		std::string trash;
		while (!cin.eof())
		{
			cin >> userInput;

			if (cin.fail())
			{
				cin.clear();
				cin >> trash;
			}
			else
			{
				switch (userInput)
				{
				case '1':		addStudent(studentIds, passwords, names, credits, appliedLectureCodes);
								break;
				case '2':		addLecture(lectureCodes, lectureNames, lectureCredits, limits);
								break;
				case '3':		deleteLecture(lectureCodes, lectureNames, lectureCredits, limits, credits, appliedLectureCodes);
								break;
				case '4':		return -1;
								break;
				case '0':		return 1;
								break;
				default:		break;
				}

				std::cout << "계속하려면 아무 키나 누르십시오..." << std::endl;
				while (!cin.eof())
				{
					cin >> trash;

					if (cin.fail())
					{
						cin.clear();
						cin >> trash;
					}
					else
					{
						break;
					}
				}
				cin.clear();
				break;
			}
		}
	}
}
void printStudent(const vector<string>& studentIds, const vector<string>& names, const vector<int>& credits, const int& user) {
	/* 구현 */
	std::cout << DIVIDER << std::endl;
	std::cout << "학번: " << studentIds[user] << "\t이름: " << names[user] << "\t수강가능학점: " << credits[user] << std::endl;
	std::cout << DIVIDER << std::endl;
}
void applyLecture(const vector<string>& studentIds, const vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, vector<int>& limits, const int& user) {
	/* 구현 */
	/* 내부 호출 함수: printStudent, printLectures*/
	printStudent(studentIds, names, credits, user);
	printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits);

	int lectureToApply = -1;
	std::string userInput;
	std::string trash;
	while (!cin.eof())
	{
		std::cout << "신청할 과목 코드(0: 뒤로가기) >> ";
		cin >> userInput;

		if (cin.fail())
		{
			cin.clear();
			cin >> trash;
		}
		else
		{
			if (userInput == "0")
			{
				return;
			}

			lectureToApply = findLectureByCode(lectureCodes, userInput);
			if (lectureToApply != -1)
			{
				break;
			}
		}
		
	}

	bool bHasSameLecture = false;
	if (limits[lectureToApply] <= 0)
	{
		std::cout << "수강정원이 꽉 찼습니다." << std::endl;
	}
	else if (credits[user] < lectureCredits[lectureToApply])
	{
		std::cout << "수강가능학점이 부족합니다." << std::endl;
	}
	else if (findLectureByCode(appliedLectureCodes[user], userInput) != -1)
	{
		std::cout << "이미 해당 과목을 신청했습니다." << std::endl;
	}
	else
	{
		for (unsigned int i = 0; i < appliedLectureCodes[user].size(); ++i)
		{
			if (lectureNames[lectureToApply] == lectureNames[findLectureByCode(lectureCodes, appliedLectureCodes[user][i])])
			{
				std::cout << "이미 동일명의 과목을 신청했습니다." << std::endl;
				bHasSameLecture = true;
			}
		}

		if (!bHasSameLecture)
		{
			appliedLectureCodes[user].push_back(lectureCodes[lectureToApply]);
			credits[user] -= lectureCredits[lectureToApply];
			--limits[lectureToApply];
			std::cout << "[" << lectureCodes[lectureToApply] << "] " << lectureNames[lectureToApply] << "(을)를 성공적으로 신청하였습니다." << std::endl;
		}
	}
}
void disapplyLecture(const vector<string>& studentIds, const vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, vector<int>& limits, const int& user) {
	/* 구현 */
	/* 내부 호출 함수: printStudent, printLectures*/
	printStudent(studentIds, names, credits, user);
	printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);

	int lectureToDisapply = -1;
	std::string userInput;
	std::string trash;
	while (!cin.eof())
	{
		std::cout << "철회할 과목 코드(0: 뒤로가기) >> ";
		cin >> userInput;

		if (cin.fail())
		{
			cin.clear();
			cin >> trash;
		}
		else
		{
			if (userInput == "0")
			{
				return;
			}

			lectureToDisapply = findLectureByCode(lectureCodes, userInput);
			if (lectureToDisapply != -1)
			{
				break;
			}
		}
		
	}

	if (findLectureByCode(appliedLectureCodes[user], userInput) != -1)
	{
		deleteElement(appliedLectureCodes[user], findLectureByCode(appliedLectureCodes[user], userInput));
		credits[user] += lectureCredits[lectureToDisapply];
		++limits[lectureToDisapply];	
		std::cout << "[" << lectureCodes[lectureToDisapply] << "] " << lectureNames[lectureToDisapply] << "(을)를 철회하였습니다." << std::endl;
	}
	else
	{
		std::cout << "과목 코드가 올바르지 않습니다." << std::endl;
	}
}
void changePassword(vector<string>& passwords, const int& user) {
	/* 구현 */
	std::cout << DIVIDER << std::endl;
	std::cout << "본인 확인을 위해 비밀번호를 한 번 더 입력해주세요." << std::endl;

	int passwordIndex = -1;
	std::string userPassword = getInputPassword();
	passwordIndex = findStudentById(passwords, userPassword);

	std::cout << DIVIDER << std::endl;
	
	if (passwordIndex == user)
	{
		std::cout << "새로 설정할 비밀번호를 입력하세요." << std::endl;
		passwords[user] = getInputPassword();
		std::cout << "변경되었습니다." << std::endl;
		std::cout << DIVIDER << std::endl;
	}
	else
	{
		std::cout << "비밀번호가 일치하지 않습니다." << std::endl;
	}
}

int runStudent(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits, int user) {
	/* 구현 */
	/* 내부 호출 함수: applyLecture, printStudent, printLectures, disapplyLecture, changePassword*/
	while (true)
	{
		std::cout << DIVIDER << std::endl;
		std::cout << "1. 수강 신청" << std::endl;
		std::cout << "2. 수강 현황" << std::endl;
		std::cout << "3. 수강 철회" << std::endl;
		std::cout << "4. 비밀번호 변경" << std::endl;
		std::cout << "5. 로그아웃" << std::endl;
		std::cout << "0. 종료" << std::endl;
		std::cout << DIVIDER << std::endl;

		char userInput = '\0';
		std::string trash;
		while (!cin.eof())
		{
			cin >> userInput;

			if (cin.fail())
			{
				cin.clear();
				cin >> trash;
			}
			else
			{
				switch (userInput)
				{
				case '1':		applyLecture(studentIds, names, credits, appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
								break;
				case '2':		printStudent(studentIds, names, credits, user);
								printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
								break;
				case '3':		disapplyLecture(studentIds, names, credits, appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
								break;
				case '4':		changePassword(passwords, user);
								break;
				case '5':		return -1;
								break;
				case '0':		return 1;
								break;
				default:		break;
				}

				std::cout << "계속하려면 아무 키나 누르십시오..." << std::endl;
				while (!cin.eof())
				{
					cin >> trash;

					if (cin.fail())
					{
						cin.clear();
						cin >> trash;
					}
					else
					{
						break;
					}
				}

				cin.clear();
				break;
			}
		}
	}
}