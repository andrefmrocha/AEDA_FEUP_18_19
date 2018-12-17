/*
 * FEUPConsulting.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "FEUPConsulting.h"

FEUPConsulting::FEUPConsulting(): expertizes(Expertize("", 0)) {
}

FEUPConsulting::FEUPConsulting(vector<Project*> projects): expertizes(Expertize("", 0)) {
	this->projects = projects;
}

void FEUPConsulting::addProjects(vector<Project*> projects) {
	this->projects = projects;
}

vector<Project*> FEUPConsulting::getProjects() const{
	return this->projects;
}


// get the expertize objet with the given name, including all students with the corresponding skills
Expertize FEUPConsulting::getExpertize(string name, unsigned cost) {
	Expertize itemNotFound("", 0);
	Expertize expertize(name, cost);
	Expertize search = expertizes.find(expertize);

	return search;
}


void FEUPConsulting::addProject(Project* project) {
	//TODO
	Expertize itemNotFound("", 0);
	Expertize expertize(project->getExpertize(), project->getCost());
	Expertize search = expertizes.find(expertize);

	if(search == itemNotFound) {
		this->expertizes.insert(expertize);
	}

	projects.push_back(project);
}

BST<Expertize> FEUPConsulting::getExpertizes() const {
	return this->expertizes;
}

void FEUPConsulting::addNewExpertize(const Expertize & expertize1) {
	this->expertizes.insert(expertize1);
}

vector<StudentPtr> FEUPConsulting::getStudents() const {
	vector<StudentPtr> ptrs;
	HashTabStudentPtr::const_iterator it1 = this->students.begin();
	HashTabStudentPtr::const_iterator it2 = this->students.end();
	for(; it1 != it2; it1++) {
			ptrs.push_back(*it1); //We can make it a bit more complex by considering only records with a condition!
	}
	return ptrs;
}

void FEUPConsulting::setStudents(vector<StudentPtr>& newStudents) {
	for(int i = 0; i < newStudents.size(); i++) students.insert(newStudents[i]);
}

priority_queue<Student> FEUPConsulting::getActiveStudents() const {
	return activeStudents;
}
void FEUPConsulting::setActiveStudents(priority_queue<Student>& students) {
	activeStudents = students;
}


//
// TODO: Part I   - BST
//

void FEUPConsulting::addAvailability(Student* student, string expertizeAvailable, unsigned cost) {
	BSTItrIn<Expertize> it(this->expertizes);
	Expertize exp(expertizeAvailable, cost);
	while(!it.isAtEnd())
	{
		if(exp == it.retrieve())
		{
			exp = it.retrieve();
			this->expertizes.remove(it.retrieve());
		}
		it.advance();
	}
	exp.addConsultant(student);
	this->expertizes.insert(exp);
}

vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;
	BSTItrIn<Expertize> it(this->expertizes);
	Expertize exp(project->getExpertize(), project->getCost());
	while(!it.isAtEnd())
	{
		if(exp == it.retrieve())
		{
			for(auto i: it.retrieve().getConsultants())
			{
				if(i->getCurrentProject().size() == 0)
					temp.push_back(i);
			}

		}
		it.advance();
	}
	return temp;

}


bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {
	vector<Student *> students = this->getCandidateStudents(project);
	if(project->getConsultant() != NULL)
		return false;
	for(auto i: students)
	{
		if(i->getName() == student->getName() && i->getEMail() == student->getEMail() && i->getCurrentProject().size()==0)
		{
			student->addProject(project->getTitle());
			project->setConsultant(student);
			return true;
		}
	}
	return false;

}

//
// TODO: Part II  - Hash Table
//

void FEUPConsulting::addStudent(Student* student) {
	students.insert(student);

}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
	this->students.erase(student);
	student->setEMail(newEMail);
	this->addStudent(student);
}


//
// TODO: Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
	for(const auto &i: candidates)
	{
		if(i.getPastProjects().size() >= min)
		{
			this->activeStudents.push(i);
		}
	}
}


int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {
	int max = -1;
	int counter = 1;
	if(this->activeStudents.empty())
		return 0;
	priority_queue<Student> copy = this->activeStudents;
	Student st = copy.top();
	copy.pop();
	if(st.getPastProjects().size() == copy.top().getPastProjects().size())
	{
		return 0;
	}
	else
	{
		studentMaximus = st;
		if(st.getPastProjects().size() == 0)
		{
			return 0;
		}
		while(!copy.empty())
		{
			Student stu = copy.top();
			copy.pop();
			counter++;
		}
	}
	return counter;
//	vector<Student> students;
//	while(!copy.empty())
//	{
//		Student st = copy.top();
//		copy.pop();
//		cout << st.getPastProjects().size() << " " << max <<endl;
//		if(st.getPastProjects().size() >= max)
//		{
//			cout << "Meias" << endl;
//			students.push_back(st);
//			max = st.getPastProjects().size();
//		}
//		if(st.getPastProjects().size() > 0)
//		{
//			counter++;
//		}
//
//	}
//	if(students.size() == 0)
//		return 0;
//	if(students[students.size() - 1].getPastProjects().size() == students[students.size() - 2].getPastProjects().size())
//	{
//		return 0;
//	}
//	studentMaximus = students[students.size() - 1];
//	return counter;

}





















