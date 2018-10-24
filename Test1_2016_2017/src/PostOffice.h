/*
 * PostOffice.h
 */

#ifndef SRC_POSTOFFICE_H_
#define SRC_POSTOFFICE_H_

#include "Mail.h"
#include "Postman.h"
#include <vector>


class PostOffice {
	vector<Mail *> mailToSend;
	vector<Mail *> mailToDeliver;
	vector<Postman> postmen;
	string firstZipCode, lastZipCode;
public:
	PostOffice();
	PostOffice(string firstZCode, string lastZCode);
	void addMailToSend(Mail *m);
	void addMailToDeliver(Mail *m);
	void addPostman(const Postman &p);
	vector<Mail *> getMailToSend() const;
	vector<Mail *> getMailToDeliver() const;
	vector<Postman> getPostman() const;
	//-------
	vector<Mail *> removePostman(string name);
	vector<Mail *> endOfDay(unsigned int &balance);
	Postman addMailToPostman(Mail *m, string name);
};

template<class T>
unsigned int numberDifferent (const vector<T> & v1)
{
	vector<T> v2;
	for(auto i: v1)
	{
		bool flag = true;
		for(auto j: v2)
		{
			if(i == j)
			{
				flag = false;
			}
		}
		if(flag)
			v2.push_back(i);
	}
	return v2.size();
}

class  NoPostmanException{
	string name;
public:
	 NoPostmanException(string name)
	{
		 this->name = name;
	}
	 string getName(){return this->name;}

};

#endif /* SRC_POSTOFFICE_H_ */
