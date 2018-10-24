/*
 * Postman.cpp
 */
#include "Postman.h"

unsigned int Postman::lastId = 0;

Postman::Postman(): id(0) {}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}


Postman::Postman(string name)
{
	this->name = name;
	this->id = ++this->lastId;
}

bool Postman::operator <(const Postman & p1) const
{
	vector<Mail *> v2;
	for(auto i: this->myMail)
	{
		bool flag = true;
		for(auto j: v2)
		{
			if(i->getZipCode() == j->getZipCode())
			{
				flag = false;
			}
		}
		if(flag)
			v2.push_back(i);
	}
	unsigned int places = v2.size();
	v2.clear();
	for(auto i: p1.getMail())
	{
		bool flag = true;
		for(auto j: v2)
		{
			if(i->getZipCode() == j->getZipCode())
			{
				flag = false;
			}
		}
		if(flag)
			v2.push_back(i);
	}
	return places < v2.size();
}

