/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>
#include<iostream>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name)
{
	vector<Mail *> mail;
	for(unsigned int i = 0; i < this->postmen.size(); i++)
	{
		if(this->postmen[i].getName() == name)
		{
			mail = this->postmen[i].getMail();
			this->postmen.erase(this->postmen.begin() + i);
			return mail;
		}
	}
	return mail;
}

vector<Mail *> PostOffice::endOfDay(unsigned int & balance)
{
	balance = 0;
	vector<Mail *> nackMail;
	this->mailToDeliver.clear();
	for(auto &i: this->mailToSend)
	{
		balance+=i->getPrice();
		if(this->firstZipCode<= i->getZipCode() && this->lastZipCode >= i->getZipCode())
		{
			this->mailToDeliver.push_back(i);
		}
		else
		{
			nackMail.push_back(i);
		}
	}
	this->mailToSend.clear();
	return nackMail;
}

Postman PostOffice::addMailToPostman(Mail *m, string name)
{
	for(auto i: this->postmen)
	{
		if(i.getName() == name)
		{
			i.addMail(m);
			return i;
		}
	}
	throw(NoPostmanException(name));
}


