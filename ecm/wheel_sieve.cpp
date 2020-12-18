#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * Pretty bad wheel sieve
 * Lazy wheel sieve
 * Sets are represented using doubly linked lists, and lazily removes things as we come upon multiples
 * Not actually that fast :(
 * Maybe I can do a thing with a custom hashmap?
*/
typedef long long ll;

struct node {
	ll num;
	node *prev;
	node *next;
};
node * HEAD; // HEAD is actually the head, like the place where we put new things
node * TAIL; // we start from tail btw but it doesn't really matter

void node_insert(ll data) { // insert onto head
	node * newnode = (node*) malloc(sizeof(node));
	newnode->num = data;
	if (TAIL==NULL) { // if list is empty
		newnode->prev=newnode->next=NULL;
		TAIL=newnode;
		HEAD=newnode;
		return;
	}
	newnode->next=NULL;

	HEAD->next=newnode;
	newnode->prev=HEAD;
	HEAD=newnode;
}
void node_remove(node *toRemove) { // we remove the node itself so 
	// i'm pretty sure these are all the cases
	if (TAIL==toRemove) {
		TAIL=toRemove->next; // will be null either way sooo if it's the only thing in there it won't matter lmfao
	} else if (HEAD==toRemove) {
		HEAD=toRemove->prev;
		HEAD->next=NULL;
	} else {
		toRemove->prev->next=toRemove->next;
		toRemove->next->prev=toRemove->prev;      
	}
	free(toRemove);
}
void trav(node * start) {
	while (start!=NULL) {
		cout << start->num << " ";
		start=start->next;
	}
}
void rtrav(node * start) {
	while (start!=NULL) {
		cout << start->num << " ";
		start=start->prev;
	}
}

ll k,p,prod,BOUND,h;
unordered_set<ll> composite;
vector<ll> primes;
node * current;
node * temp;
int main() {
	node_insert(1);
	primes.push_back(2);
	auto it = composite.find(69);
	ll N = 100000000;
	k=1;
	p=3; // next prime to 'roll'
	prod=2; // current product of primes
	BOUND = N;
	bool overflow = false;
	while (p*p<=N) {
		if (!overflow) {
			if (prod*p>prod) {
				BOUND = min(N,prod*p);
			}
			else {
				BOUND = N;
				overflow=true;
			}
		}
		current = TAIL;
		if (!overflow) {
			while (current!=NULL) {
				while ((it=composite.find(current->num))!=composite.end()) {
					// number is composite
					composite.erase(it);
					temp = current->next;
					node_remove(current);
					current = temp;
				} 
				if (!overflow&&current->num+prod<BOUND) {
					// prod hasn't overflowed yet
					// if it has it's stupidly big so it doesn't matter
					// pretty obvious that this'll be sorted 
					node_insert(current->num+prod);
				} else {
					break;
				}
				current=current->next;
			}
		}
		current = TAIL->next;
		h=p;
		while (h*p<=BOUND&&current->next!=NULL) {
			current=current->next;
			h= current->num;
		} // when this finishes current is one too big

		if (current->prev!=NULL) current=current->prev;
		while (current!=NULL&&(current->num)>=1) {
			while ((it=composite.find(current->num))!=composite.end()) {
					// number is composite
					composite.erase(it);
				temp = current->prev;
				node_remove(current);
				current = temp;
			} 
			// then we put h*p into the 'bad' list. this will suck up a fuck ton of memory so we'll see how this goes
			if (current!=NULL) composite.insert(p*(current->num));
			else break;
			current=current->prev;
			
			
			
		}
		if (!overflow) {
			if (prod*p<prod) {
				overflow = true;
			} else {
				prod*=p;
			}
		}
		primes.push_back(p);

		current = TAIL->next;
		while (current!=NULL&&(it=composite.find(current->num))!=composite.end()) {
					// number is composite
			composite.erase(it);
			temp = current->next;
			node_remove(current);
			current = temp;

		} 
		p = current->num;
	}
	current = TAIL->next;
	while (current!=NULL) {
		while (current!=NULL&&composite.find(current->num)!=composite.end()) {
			// number is composite
			current=current->next;
		} 
		if (current==NULL) break;
		primes.push_back(current->num);
		current=current->next;
	}
	// for (ll num : primes) cout << num << " ";
	// cout << "\n";
	cout << primes.size() << "\n";

}
