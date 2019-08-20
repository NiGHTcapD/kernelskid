#include "nodemem.h"
#include "othres.h"
#include "nodeRCB.h"
#ifndef WT
#define WT
using namespace std;
#define NUMLEV 5

struct nodeRCB;
struct Status {
	string Type;
	struct nodeRCB* List;
};
struct CreationJTree {
	int Parent;
	int Child;
};
struct PCB {
	int ID;
	struct nodemem* memory;
	struct othres* other_resources;
	struct Status status;
	struct CreationJTree creationJTree;
	int priority;
};

struct nodePCB
{
	struct PCB data;
	nodePCB *next;
};

struct RCB {
	int RID;
	string status;
	struct nodePCB* waiting_list;
};
#endif