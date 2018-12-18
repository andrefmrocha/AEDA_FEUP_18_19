/*
 * Cinema.cpp
 */
#include "Cinema.h"

Cinema::Cinema(string nm, unsigned d, unsigned nr): name(nm), distance(d),
		numberOfRooms(nr),timetable(FilmTime(0,NULL, 0))
{}

Cinema::Cinema(string nm, unsigned d, unsigned nr, list<string> ls): name(nm), distance(d),
		numberOfRooms(nr),services(ls), timetable(FilmTime(0,NULL,0))
{}

Cinema::~Cinema() { }

string Cinema::getName() const
{ return name; }

unsigned Cinema::getDistance() const
{ return distance; }

list<string> Cinema::getServices() const
{ return services; }

BST<FilmTime> Cinema::getTimetable() const
{ return timetable; }

void Cinema::addService(string service1)
{ services.push_back(service1); }

void Cinema::addFilmTime(const FilmTime &ft1)
{ timetable.insert(ft1); }


// TODO

bool Cinema::operator<(const Cinema & cr) const
{
	if(this->getDistance() == cr.getDistance())
		return this->getServices().size() < cr.getServices().size();
	return this->getDistance() > cr.getDistance();
}


//a1
Film *Cinema::filmAtHour(unsigned &h1) const {
	BSTItrIn<FilmTime> it(this->timetable);
	FilmTime prev(h1, NULL, 0);
	unsigned counter = 0;
	while(!it.isAtEnd())
	{
		counter ++;
		if(it.retrieve().getHour() == h1)
			return it.retrieve().getFilm();
		if(it.retrieve().getHour() > h1)
			break;
		prev = it.retrieve();
		it.advance();
	}
	if(counter <=1)
	{
		return NULL;
	}
	h1 = prev.getHour();
	return prev.getFilm();
}


//a2
bool Cinema::modifyHour(unsigned h1, unsigned room1, unsigned h2) {
	FilmTime mov(h1, NULL, 0);
	BSTItrIn<FilmTime> it(this->timetable);
	while(!it.isAtEnd())
	{
		if(it.retrieve().getRoomID() == room1 && it.retrieve().getHour() == h1)
		{
			mov = it.retrieve();
		}
		if(it.retrieve().getRoomID() == room1 && it.retrieve().getHour() == h2)
			return false;
		it.advance();
	}
	if(mov == FilmTime(h1, NULL, 0))
	{
		return false;
	}

	this->timetable.remove(mov);
	mov.setHour(h2);
	this->timetable.insert(mov);
	return true;;
}


//a3
unsigned Cinema::addFilm(Film *f1, unsigned h1) {

	bool found = false;

	for(unsigned id = 1 ; id<=numberOfRooms ; id++){
		found = false;

		BSTItrIn<FilmTime> it(timetable);
		while(!it.isAtEnd()){
			if (it.retrieve().getRoomID() == id && it.retrieve().getHour() == h1){
				found = true;
				break;
			}
			it.advance();
		}

		if(!found){
			timetable.insert(FilmTime(h1 , f1 ,id));
			return id;
		}
	}

	return 0;
}






