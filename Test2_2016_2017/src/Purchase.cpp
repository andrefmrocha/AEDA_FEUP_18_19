/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"
#include<iostream>
using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {

	Article* ar = new Article(this->client, barCode);
	ar->setDeliverHome(deliverHome);
	ar->setPresent(present);
	return ar;

}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {

	if(this->bags.size() == 0)
	{
		stack<Article*> stack;
		stack.push(article);
		this->bags.push_back(stack);
		return;
	}
	std::list< std::stack<Article*> >::iterator  it= (--this->bags.end());
	if(it->size() >= this->BAG_SIZE)
	{
		stack<Article*> stack;
		stack.push(article);
		this->bags.push_back(stack);
	}
	else
	{
		it->push(article);
	}
}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {
	vector<Article*> presents;
	for(auto &i: this->bags)
	{
		vector<Article *> aux;
		while(!i.empty())
		{
			if(i.top()->getPresent())
			{
				presents.push_back(i.top());
				i.pop();
			}
			else
			{
				aux.push_back(i.top());
				i.pop();
			}
		}

		for(int z = aux.size()-1; z >= 0; z--)
		{
			i.push(aux[z]);
		}

	}
	return presents;

}

