#include <iostream>
#include <string>
#include <sstream>

#include "kernelskid.h"
using namespace std;

extern void addN(nodemem**, int);
extern void addO(othres**, int);
extern void addP(nodePCB**, PCB*);
extern void addR(nodeRCB**, RCB*);
extern void removeN(nodemem**, int);
extern void removeO(othres**, int);
extern void removeP(nodePCB**, PCB*);
extern void removeR(nodeRCB**, RCB*);

nodePCB* prior[NUMLEV];
PCB* curpro = NULL; //currentprocess;

nodeRCB* all = NULL;


RCB* Get_RCB(int RID){
	if (all == NULL){
		return NULL;
	}
	else if (all->rcbee.RID == RID){
		return &(all->rcbee);
	}
	else{
		nodeRCB* fornow = all;
		while (fornow->next != NULL){
			if (fornow->next->rcbee.RID == RID){
				nodeRCB* temp = fornow->next;
				return &(temp->rcbee);
			}
			else{ fornow = fornow->next; }
		}
		return NULL;
	}
}
void insert(othres** hold, RCB* putin){
	addO(hold, putin->RID);
}
void remove(nodeRCB** aReL, RCB* getout){
	removeR(aReL, getout);
}
void insert(nodePCB** hold, PCB* putin){
	addP(hold, putin);
}
void remove(othres** aReL, RCB* getout){
	removeO(aReL, getout->RID);
}
void remove(nodePCB** aReL, PCB* getout){//make sure the node is destroyed? 
	removeP(aReL, getout);
}
void insert(nodeRCB** hold, RCB* putin){
	addR(hold, putin);
}

void Create(int pid, int prilev){
	if (prilev >= NUMLEV){cout << "Not enough priority levels." << endl;}
	else{	
		struct Status *statusc = (struct Status *) malloc(sizeof(struct Status));
		memset(statusc, 0, sizeof(struct Status));
		string str = "ready";
		statusc->Type = str;
		statusc->List = NULL;

		struct CreationJTree *treec = (struct CreationJTree *) malloc(sizeof(struct CreationJTree));
		memset(treec, 0, sizeof(struct CreationJTree));
		treec->Child = pid == 0 ? 0 : curpro->ID;
		treec->Parent = 0;

		struct PCB *pcb = (struct PCB *) malloc(sizeof(struct PCB));
		memset(pcb, 0, sizeof(struct PCB));
		pcb->ID = pid;
		pcb->memory = NULL; // *memll;
		pcb->other_resources = NULL; // orll;
		pcb->status = *statusc;
		pcb->creationJTree = *treec;
		pcb->priority = prilev;

		if (prior[prilev] == NULL){
			struct nodePCB *pcbll = (struct nodePCB *) malloc(sizeof(struct nodePCB));
			memset(pcbll, 0, sizeof(struct nodePCB));
			pcbll->data = *pcb;
			pcbll->next = NULL;

			prior[prilev] = pcbll;
		}
		else{
			insert(&prior[prilev], pcb);
		}
	}
}


void preempt(nodePCB* nuu, PCB* old){
	if (old != NULL) {
		old->status.Type = "ready";
	}
	nuu->data.status.Type = "running";
	curpro = &(nuu->data);
	cout << "Process " << curpro->ID << " is now running." << endl;
}
void Scheduler() {
	nodePCB* p = NULL;
	p = prior[0];
	for (int ex = NUMLEV - 1; ex>0; ex--) {//p=(some function to look through all p for high pri)//find highest priority process p
		if (prior[ex] != NULL){
			p = prior[ex];
			break;
		}
	}
	if (curpro == NULL || curpro->priority < p->data.priority || curpro->status.Type != "running"){
		preempt(p, curpro);
	}
}

void Request(int RID) {
	RCB* r = Get_RCB(RID);
	if (r->status == "free") {
		r->status = "allocated";
		insert(&(curpro->other_resources), r);//RCB* into othres*
	}
	else {
		bool alreadyhere = false;
		if (curpro->other_resources == NULL){/*do nothing*/ }
		else if (curpro->other_resources->othRID == RID){
			alreadyhere = true;
		}
		else{
			othres* fornow = curpro->other_resources;
			while (fornow->next != NULL){
				if (fornow->next->othRID == RID){alreadyhere = true;}
				else{fornow = fornow->next;}
			}
		}
		if (alreadyhere == false){
			curpro->status.Type = "blocked";
			insert(&(curpro->status.List), r);
			remove(&(prior[curpro->priority]), curpro);//PCB* out of nodeRCB*
			insert(&(r->waiting_list), curpro);//PCB* into nodePCB*
		}
		else{ cout << "That process already has or is waiting on that resource." << endl; }
	}
	Scheduler();
}

void Release(int RID) {
	RCB* r = Get_RCB(RID);
	remove(&(curpro->other_resources), r);//RCB* out of othres*
	if (r->waiting_list == NULL){ r->status = "free"; }
	else {
		PCB* pcbee = &(r->waiting_list->data);
		remove(&(r->waiting_list), pcbee);//PCB* out of nodePCB*
		pcbee->status.Type = "ready";
		remove(&(pcbee->status.List), r);
		insert(&prior[pcbee->priority], pcbee);//PCB* into nodeRCB*
	}
	Scheduler();
}
void Destroy(int pid){
	//search for the pid. if pid not found, output error and return; delete PCB with pid, and all of its contents too.
	if (curpro->ID == pid){
		int ex = curpro->priority;
		if (prior[ex]->data.ID == pid){
			nodePCB* temp = prior[ex];
			prior[ex] = prior[ex]->next;

			while (temp->data.other_resources != NULL){
				Release(temp->data.other_resources->othRID);
			}
			delete temp;
			curpro = NULL;
		}
		else{
			nodePCB* fornow = prior[ex];
			while (fornow->next != NULL){
				if (fornow->next->data.ID == pid){
					nodePCB* temp = fornow->next;
					fornow->next = fornow->next->next;

					while (temp->data.other_resources != NULL){
						Release(temp->data.other_resources->othRID);
					}
					delete temp;
					curpro = NULL;
				}
				else{ fornow = fornow->next; }
			}
		}
	}
	else{
		for (int ex = NUMLEV - 1; ex >= 0; ex--){
			if (prior[ex] == NULL){
				//do nothing
			}
			else if (prior[ex]->data.ID == pid){
				//delete it, and close its gap
				nodePCB* temp = prior[ex];
				prior[ex] = prior[ex]->next;

				curpro = &(temp->data);
				while (temp->data.other_resources != NULL){
					Release(temp->data.other_resources->othRID);
					curpro = &(temp->data);
				}
				delete temp;
			}
			else{
				nodePCB* fornow = prior[ex];
				while (fornow->next != NULL){
					if (fornow->next->data.ID == pid){
						nodePCB* temp = fornow->next;
						fornow->next = fornow->next->next;

						curpro = &(temp->data);
						while (temp->data.other_resources != NULL){
							Release(temp->data.other_resources->othRID);
							curpro = &(temp->data);
						}
						delete temp;
					}
					else{ fornow = fornow->next; }
				}
			}
		}//I guess it doesn't exist.
	}
}

void user(){
	string want;
	int id;
	int prilvl;
	while (want != "quit"){
		cout << "input command: ";
		cin >> want;
		if (want == "cr" || want == "create" || want == "Cr" || want == "Create"){
			cout << "Give it a numerical ID. ";
			cin >> id;
			cout << "Give it a priority level (0-4). ";
			cin >> prilvl;
			Create(id, prilvl);
			Scheduler();
		}
		else if (want == "rq" || want == "req" || want == "request" || want == "quest"){
			cout << "Which resource (1-10)? ";
			cin >> id;
			Request(id);
		}
		else if (want == "rl" || want == "rel" || want == "release" || want == "lease"){
			cout << "Which resource in use? ";
			cin >> id;
			Release(id);
		}
		else if (want == "ds" || want == "des" || want == "destroy" || want == "troy"){
			cout << "Which process to go? ";
			cin >> id;
			Destroy(id);
			Scheduler();
		}
		else if (want == "quit"){
			//break;
		}
		else {
			cout << "invalid input" << endl;
		}
	}
}

int main(){
	//make an init PCB at element 0
	Create(0, 0);
	curpro = &(prior[0]->data);

	struct RCB *some1 = (struct RCB *) malloc(sizeof(struct RCB));
	memset(some1, 0, sizeof(struct RCB));
	some1->RID = 1;
	some1->status = "free";
	some1->waiting_list = NULL;
	struct nodeRCB *all1 = (struct nodeRCB *) malloc(sizeof(struct nodeRCB));
	memset(all1, 0, sizeof(struct nodeRCB));
	all1->rcbee = *some1;
	all1->next = NULL;

	all = all1;
	for (int wy = 2; wy <= 10; wy++){
		struct RCB *some = (struct RCB *) malloc(sizeof(struct RCB));
		memset(some, 0, sizeof(struct RCB));
		some->RID = wy;
		some->status = "free";
		some->waiting_list = NULL;
		insert(&all, some);
	}
	user();
}