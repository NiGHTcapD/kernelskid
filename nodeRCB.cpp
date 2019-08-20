// LL struct
#include <iostream>
#include <string>
#include <sstream>
#include "kernelskid.h"
using namespace std;

#ifndef RC
#define RC
nodeRCB *np = NULL;
#endif

/*
 *  ll=="linkedlist"
 */
void addR(nodeRCB **primary, RCB *rcb){//same datatype as data-star
	nodeRCB *ll = *primary;
	if (ll == NULL){
		np = new nodeRCB;
		np->rcbee = *rcb;
		np->next = NULL;
		*primary = np;
	}
	else if ((*primary)->next == NULL){
		np = new nodeRCB;
		np->rcbee = *rcb;
		np->next = NULL;
		ll->next = np;
	}
	else{
		addR(&(ll->next), rcb);
	}
}

void removeR(nodeRCB **primary, RCB *rcb){
	nodeRCB *ll = *primary;
	if (ll == NULL){
		//return NULL;
	}
	else if (ll->rcbee.RID == rcb->RID){
		nodeRCB* temp = ll;
		*primary = ll->next;
		//return temp;
	}
	else if (ll->next != NULL){
		if (&(ll->next->rcbee) == rcb){
			nodeRCB* temp = ll->next;
			ll->next = ll->next->next;
			//return temp;
		}
	}
	else{ 
		return removeR(&(ll->next), rcb);
	}
}