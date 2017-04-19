#include "student.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <time.h>

using namespace std;


string idGenerator(int len = 9);

string idGenerator(int len)
{
	string numbset = "0123456789";
	int numbsetLen = numbset.length();
	string id = "A";
	srand(time(NULL));
	for (int i = 1; i < len; i++)
		id.push_back(numbset[rand() % numbsetLen]);
	return id;

}

void StudentList::appendStudent(string ID, string name, string address, float gpa) 
{
	Student *node = new Student;
	node->ID = ID;
	node->name = name;
	node->address = address;
	node->gpa = gpa;
	node->next = NULL;

	if (head == NULL){
		head = node;
		return;
	}

	Student *iter = head;
	while (iter -> next)
		iter = iter->next;
	iter->next = node;

}

void StudentList::display() const
{
	Student *iter = head;
	while(iter){
		cout << "student's ID " << iter->ID << " student's Name "
		    << iter->name << " student's address " << iter->address <<
		    " student's gpa " << iter->gpa << endl;
		iter = iter->next;
	}
}

void StudentList::deleteStudent(string ID)
{
	Student *iter = head;
	Student *prev = NULL;
	if (head == NULL)
		return;
	if (head->ID == ID) {
		iter = head->next;
		delete head;
		head = iter;
		return;
	}

	while (iter != NULL && iter->ID != ID)
	{
		prev = iter;
		iter = iter->next;
	}
	if (iter) {
		prev->next = iter->next;
		delete iter;
	}
}

StudentList::~StudentList()
{
	Student *iter = head;
	Student *next_student = NULL;

	while (iter != NULL)
	{
		next_student = iter->next;
		delete iter;
		iter = next_student;
	}
}

StudentArr::StudentArr(int numb_of_stud)
{
	this->numb_of_stud = numb_of_stud;
	arr = new Student[numb_of_stud];
	for (int i = 0; i < numb_of_stud; i++)
	{
		arr[i].ID = idGenerator();
	}
}

StudentArr::~StudentArr()
{
	delete[] arr;
}

void StudentArr::display()
{
	for (int i = 0; i < numb_of_stud; i++) {
		cout << i << " stud's id " << arr[i].ID << endl;
	}
}
