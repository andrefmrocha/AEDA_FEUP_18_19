/*
 * Restaurant.cpp
 *
 *  Created on: 17/11/2015
 *      Author: hlc
 */

#include "Restaurant.h"
#include <iostream>
using namespace std;

Restaurant::Restaurant() { }

Restaurant::Restaurant(vector< stack<Dish*> >* cl, queue<Dish*>* di, list<Dish*>* dr) {
	if(cl != NULL) clean = *cl;
	if(di != NULL) dirty = *di;
	if(dr != NULL) drying = *dr;
}

void Restaurant::addTable(unsigned int n_places) {
	tables.push_back(Table(n_places));
}

void Restaurant::addTable(Table& t) {
	tables.push_back(t);
}

const Table& Restaurant::getTable(vector<Table>::size_type idx) const {
	return tables[idx];
}

/**
 * Gets the clean dishes stack for a given collection and type.
 * If there is none, adds and returns an empty stack.
 */
stack<Dish*>& Restaurant::getCleanDishStack(string collection, TypeOfDish type) {

	for(vector< stack<Dish*> >::iterator it = clean.begin(); it != clean.end(); ++it) {
		if((*it).empty() || ((*it).top()->getCollection() == collection && (*it).top()->getType() == type)) {
			return *it;
		}
	}

	stack<Dish*> st;
	clean.push_back(st);
	return clean.back();
}

const queue<Dish*>& Restaurant::getDirty() const {
	return dirty;
}

const list<Dish*>& Restaurant::getDrying() const {
	return drying;
}

/**
 * Adds a number of dishes of a collection/type to the respective clean stack.
 */
void Restaurant::addDishes(unsigned int n, string collection, TypeOfDish type) {

	stack<Dish *> &dishes = Restaurant::getCleanDishStack(collection, type);

	for(unsigned int i = 0; i < n; i++)
	{
		Dish* d = new Dish(collection, type);
		dishes.push(new Dish(collection, type));
	}

}

/**
 * Washes a dish, getting if from the dirty queue and putting it in the wet list.
 * Returns the washed dish.
 */
Dish* Restaurant::washDish() {
	Dish* d;
	d = this->dirty.front();
	this->dirty.pop();
	this->drying.push_back(d);
	return d;
}

/**
 * Clears a table, placing all dishes that are on it in the dirty queue.
 */
void Restaurant::clearTable(vector<Table>::size_type idx) {

	vector<Dish *> dishes = this->tables[idx].clear();
	for(auto i: dishes)
	{
		this->dirty.push(i);
	}
}

/**
 * Stores in the respective clean stack all drying dishes of a given collection and type.
 */
void Restaurant::storeDryDishes(string collection, TypeOfDish type) {

	vector<Dish *> dishes;

	for(list<Dish *>::iterator it = this->drying.begin(); it != this->drying.end(); it++)
	{
		if((*it)->getCollection() == collection && (*it)->getType() == type)
		{
			list<Dish *>::iterator itAux = it;
			dishes.push_back(*it);
			itAux++;
			this->drying.erase(it);
			it = itAux;
		}
	}


	stack<Dish *> &dishesStack = Restaurant::getCleanDishStack(collection, type);
	for(auto i: dishes)
	{
		dishesStack.push(i);
	}
}

/**
 * Puts Plates of a given collection in a table.
 * Throws TableNotReadyException when the table is not empty.
 * Throws NotEnoughDishesException when there are not enough clean plates of the collection.
 */
void Restaurant::setupTable(vector<Table>::size_type idx, string collection) {

	TypeOfDish type = Plate;
	stack<Dish *> &dishesStack = Restaurant::getCleanDishStack(collection, type);
	if(this->tables.size() <= idx)
		return;

	if(!this->tables[idx].empty())
		throw(TableNotReadyException());
	if(this->tables[idx].size() > dishesStack.size())
		throw(NotEnoughDishesException());

	unsigned int no_plates = this->tables[idx].size();
	vector<Dish *> dishes;

	for(unsigned int i = 0; i < no_plates; i++)
	{
		dishes.push_back(dishesStack.top());
		dishesStack.pop();
	}

	this->tables[idx].putOn(dishes);
}

/**
 * Picks the dry dishes and groups them.
 * Returns the grouped dishes.
 */

bool compareDish(Dish * d1, Dish* d2)
{
	if(d1->getCollection() == d2->getCollection())
		return d1->getType() < d2->getType();
	return d1->getCollection() < d2->getCollection();
}
list<Dish*> Restaurant::pickupAndGroupDryDishes() {
	list<Dish*> dry_grouped = this->drying;
	this->drying.clear();

	dry_grouped.sort(compareDish);
	return dry_grouped;
}

/**
 * Stores grouped dishes in the respective clean stacks.
 * Returns the number of stacks that have been updated.
 */
int Restaurant::storeGroupedDishes(list<Dish*> grouped_dishes) {

	Dish * prev_dish;
	for(auto &i: this->clean)
	{
		for(auto &z: grouped_dishes)
		{
			if(z == i.top())
			{

			}
		}
	}

	return 0;
}

