/*
 * Hospital.cpp
 */

#include "Hospital.h"
//
#include <algorithm>
#include <iostream>

Hospital::Hospital(unsigned trayC):trayCapacity(trayC)
{ }

void Hospital::addDoctor(const Doctor &d1) {
	doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
	return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
	letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
	return letterTray;
}



unsigned Hospital::numPatients(string medicalSpecialty) const
{
	unsigned number = 0;
	for(auto i: this->doctors)
	{
		if(i.getMedicalSpecialty() == medicalSpecialty)
			number += i.getPatients().size();
	}
	return number;
}

bool compare(Doctor d1, Doctor d2)
{
	if(d1.getPatients().size() == d2.getPatients().size())
	{
		if(d1.getMedicalSpecialty() == d2.getMedicalSpecialty())
			return d1.getCode() < d2.getCode();
		else
			return d1.getMedicalSpecialty() < d2.getMedicalSpecialty();
	}
	return d1.getPatients().size() < d2.getPatients().size();
}

void Hospital::sortDoctors() {
	this->doctors.sort(compare);
}



bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {
	int counter = 0;
	for(auto i: this->doctors)
	{
		if(i.getMedicalSpecialty() == medicalSpecialty1)
			counter++;
	}
	if(counter >= 3)
		return false;
	Doctor d1(codM1, medicalSpecialty1);
	this->doctors.push_back(d1);
	return true;
}



queue<Patient> Hospital::removeDoctor(unsigned codM1) {
	queue<Patient> patients;
	for(list<Doctor>::iterator it = this->doctors.begin(); it!=this->doctors.end(); it++)
	{
		if(it->getCode() == codM1)
		{
			patients = it->getPatients();
			this->doctors.erase(it);
			return patients;
		}
	}
	throw(DoctorInexistent());
}


bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {
	int size = 900;
	list<Doctor>::iterator it = this->doctors.end();
	for(list<Doctor>::iterator it2 = this->doctors.begin(); it2 != this->doctors.end(); it2++)
	{
		if(it2->getMedicalSpecialty() == medicalSpecialty1)
		{
			if(it2->getPatients().size() < size)
			{
				size = it2 ->getPatients().size();
				it = it2;
			}
		}
	}
	if(it == this->doctors.end())
		return false;
	Patient p1(cod1, medicalSpecialty1);
	it->addPatient(p1);
	return true;
}



void Hospital::processPatient(unsigned codM1) {
	Patient p1(codM1, "uhfhu");
	bool flag = true;
	for(auto& i: this->doctors)
	{
		if(i.getCode() == codM1)
		{
			flag = false;
			try
			{
				p1 = i.removeNextPatient();
			}
			catch(Doctor::PatientInexistent e)
			{
				return;
			}
		}
	}
	if(flag)
	{
		return;
	}
	flag = true;
	for(auto &i: this->letterTray)
	{
		if(i.size() < this->trayCapacity)
		{
			flag = false;
			i.push(p1);
			break;
		}
	}
	if(flag)
	{
		stack<Patient> tray;
		tray.push(p1);
		this->letterTray.push_back(tray);
	}

}


unsigned Hospital::removePatients(unsigned codP1) {
	unsigned counter = 0;
	for(list<stack<Patient> >::iterator it = this->letterTray.begin(); it != this->letterTray.end();)
	{
		if(it->top().getCode() == codP1)
		{
			counter++;
			it->pop();
			if(it->empty())
			{
				list<stack<Patient> >::iterator itAux = it;
				itAux++;
				this->letterTray.erase(it);
				it = itAux;
			}
			else
				it++;
		}
		else
			it++;
	}
	return counter;
}



