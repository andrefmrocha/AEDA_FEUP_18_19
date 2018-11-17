/*
 * Doctor.cpp
 */

#include "Doctor.h"
#include<iostream>

Patient::Patient(unsigned codP, string mS): codeP(codP), medicalSpecialty(mS)
{}

string Patient::getMedicalSpecialty() const {
	return medicalSpecialty;
}

unsigned Patient::getCode() const {
	return codeP;
}

Doctor::Doctor(unsigned codM, string mS): codeM(codM), medicalSpecialty(mS)
{}


Doctor::Doctor(unsigned codM, string mS, queue<Patient> patients1): codeM(codM), medicalSpecialty(mS), patients(patients1)
{}

unsigned Doctor::getCode() const {
	return codeM;
}

string Doctor::getMedicalSpecialty() const {
	return medicalSpecialty;
}

queue<Patient> Doctor::getPatients() const {
	return patients;
}

void Doctor::addPatient(const Patient &p1) {
	patients.push(p1);
}

Patient Doctor::removeNextPatient() {
	if (!patients.empty()) {
		Patient p1 = patients.front();
		patients.pop();
		return p1;
	}
	else throw PatientInexistent();
}




void Doctor::moveToFront(unsigned codP1) {
	 queue<Patient> patient = this->patients;
	 string specialty;
	 for(int i = 0; i < this->patients.size(); i++)
	 {
		 if(patient.front().getCode() == codP1)
		 {
			 specialty = patient.front().getMedicalSpecialty();
			 break;
		 }
		 patient.pop();
	 }
	 if(specialty.empty())
	 {
		 return;
	 }
	 Patient pat(codP1,specialty);
	 queue<Patient> newPatient;
	 newPatient.push(pat);
	 while(this->patients.size() > 0)
	 {
		 if(this->patients.front().getCode() == codP1)
		 {
			 this->patients.pop();
			 continue;
		 }

		 newPatient.push(this->patients.front());
		 this->patients.pop();
	 }
	 this->patients = newPatient;
}

