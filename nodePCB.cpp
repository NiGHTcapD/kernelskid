// LL struct
#include <iostream>
#include <string>
#include <sstream>
#include "kernelskid.h"
using namespace std;

#ifndef PC
#define PC
nodePCB *np = NULL;
#endif

/*
 *  ll=="linkedlist"
 */
void addP(nodePCB **primary, PCB *pcb){//same datatype as data-star
	nodePCB *ll = *primary;
	if (ll == NULL){
		np = new nodePCB;
		np->data = *pcb;
		np->next = NULL;
		*primary = np;
	}
	else if (ll->next == NULL){
		np = new nodePCB;
		np->data = *pcb;
		np->next = NULL;
		ll->next = np;
	}
	else{
		addP(&(ll->next), pcb);
	}
}

void removeP(nodePCB **primary, PCB *pcb){
	nodePCB *ll = *primary;
	if (ll == NULL){
		//return NULL;
	}
	else if (ll->data.ID == pcb->ID){
		nodePCB* temp = ll;
		*primary = ll->next;
		//return temp;
	}
	else if (ll->next != NULL){
		if (&(ll->next->data) == pcb){
			nodePCB* temp = ll->next;
			ll->next = ll->next->next;
			//return temp;
		}
	}
	else{
		return removeP(&(ll->next), pcb);
	}
}