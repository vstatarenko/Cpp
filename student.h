#include <string>
using namespace std;

class StudentList{
private:
	StudentList(const StudentList& other);
	void operator = (const StudentList& other);

	struct Student
	{
		string ID; 
		string	name;
		string 	address;
		float gpa;
		Student *next;
	};

	Student *head;

public:
	StudentList() { head = NULL; }
	~StudentList();

	void appendStudent(string ID, string name, string address, float gpa); //appends to the end
	void deleteStudent(string ID);
	void display() const;
	
	//friend string idGenerator(int len = 9);
};/**/

class StudentArr {
private:
	struct Student
	{
		string ID;
		string	name;
		string 	address;
		float gpa;
	};
	Student *arr = NULL;
	int numb_of_stud;

public:
	StudentArr() {}
	StudentArr(int numb_of_stud);
	~StudentArr();
	void display();
	friend string idGenerator(int len);
};