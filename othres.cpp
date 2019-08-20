// LL struct
#include <iostream>
#include <string>
#include <sstream>
#include "othres.h"
using namespace std;

#ifndef others
#define others
othres *np = NULL;
#endif

void addO(othres **primary, int resID){//same datatype as data-star
	othres *ll = *primary;//*ll=="linkedlist"
	if (ll == NULL){
		np = new othres;
		np->othRID = resID;
		np->next = NULL;
		*primary = np;
	}
	else if (ll->next == NULL){
		np = new othres;
		np->othRID = resID;
		np->next = NULL;
		ll->next = np;
	}
	else{
		addO(&(ll->next), resID);
	}
}

void removeO(othres **primary, int resID){
	othres *ll = *primary;
	if (ll == NULL){
		//return NULL;
	}
	else if (ll->othRID == resID){
		othres* temp = ll;
		*primary = ll->next;
		//return temp;
	}
	else if (ll->next != NULL){
		if (ll->next->othRID == resID){
			othres* temp = ll->next;
			ll->next = ll->next->next;
			//return temp;
		}
	}
	else{
		return removeO(&(ll->next), resID);
	}
}