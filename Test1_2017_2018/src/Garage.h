/*
 * Garage.h
 *
 *  Created on: 24/10/2017
 *      Author: hlc
 */

#ifndef SRC_GARAGE_H_
#define SRC_GARAGE_H_

#include <vector>
#include <iostream>
#include<algorithm>
#include"Car.h"

class Garage {
	std::vector<Car *> vehicles;
	const unsigned int capacity;
public:
	Garage(int size);
	~Garage();
	std::vector<Car *> getVehicles() const;
	void setVehicles(std::vector<Car *> vehicles);
	int getCapacity() const;
	bool addVehicle(Car *vehicle);
	Car* removeVehicle(std::string brand, std::string model);
	float avgPrice(std::string brand) const;
	void sortVehicles();
};

class NoSuchVehicleException {
public:
	NoSuchVehicleException() { }
};

Garage::Garage(int size) : capacity(size) {
}

Garage::~Garage() {
	typename std::vector<Car *>::const_iterator it;
	for (it=vehicles.begin(); it!=vehicles.end(); it++) {
		delete *it;
	}
}


std::vector<Car *> Garage::getVehicles() const {
	return vehicles;
}


void Garage::setVehicles(std::vector<Car*> vehicles) {
	this->vehicles = vehicles;
}


int Garage::getCapacity() const {
	return capacity;
}

bool Garage::addVehicle(Car * vehicle)
{
	if(this->vehicles.size() >= this->capacity)
		return false;
	else
	{
		for(unsigned int i = 0; i < this->vehicles.size(); i++)
		{
			if(this->vehicles[i] == vehicle)
			{
				return false;
			}
		}
		this->vehicles.push_back(vehicle);
		return true;
	}
}

bool compareCars(Car * c1, Car * c2)
{
	if(c1->getBrand() == c2->getBrand())
	{
		return c1->getPrice() > c2->getPrice();
	}
	return c1->getBrand() < c2->getBrand();
}

void Garage::sortVehicles()
{
	std::cout << std::endl;
	std::sort(this->vehicles.begin(), this->vehicles.end(), compareCars);
}

Car* Garage::removeVehicle(std::string brand, std::string model)
{
	for(unsigned int i = 0; i < this->vehicles.size(); i++)
	{
		if(this->vehicles[i]->getBrand() == brand && this->vehicles[i]->getModel() == model)
		{
			Car * car= this->vehicles[i];
			this->vehicles.erase(this->vehicles.begin() + i);
			return car;
		}
	}
	throw(NoSuchVehicleException());
}

class NoSuchBrandException
{
	std::string brand;
public:
	NoSuchBrandException(std::string brand){
		this->brand = brand;
	};
	std::string getBrand(){
		return brand;
	}
};

float Garage::avgPrice(std::string brand) const
{
	float avg = 0;
	float counter = 0;
	for(auto i: this->vehicles)
	{
		if(i->getBrand() == brand)
		{
			avg+=i->getPrice();
			counter++;
		}
	}
	if(avg == 0)
	{
		throw(NoSuchBrandException(brand));
	}
	avg/=counter;
	return avg;
}


#endif /* SRC_GARAGE_H_ */
