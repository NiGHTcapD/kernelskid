// LL struct
#include <iostream>
#include <string>
#include <sstream>
#include "nodemem.h"
using namespace std;

#ifndef noad
#define noad
nodemem *np = NULL;
#endif

/*
 *  ll=="linkedlist"
 */
void addN(nodemem **primary, int id){//same datatype as data-star
	nodemem *ll = *primary;
	if (ll == NULL){
		np = new nodemem;
		np->data = id;
		np->next = NULL;
		*primary = np;
	}
	else if (ll->next == NULL){
		np = new nodemem;
		np->data = id;
		np->next = NULL;
		ll->next = np;
	}
	else{
		addN(&(ll->next), id);
	}
}

void removeN(nodemem **primary, int id){
	nodemem *ll = *primary;
	if (ll == NULL){
		//do nothing
	}
	else if (ll->data == id){
		nodemem* temp = ll;
		*primary = ll->next;
	}
	else if (ll->next != NULL){
		if (ll->next->data == id){
			nodemem* temp = ll->next;
			ll->next = ll->next->next;
		}
	}
	else{
		return removeN(&(ll->next), id);
	}
}