#pragma once
#include<stdexcept>
#include<algorithm>
using namespace std;

// Changes in checking elements in functions f, g and b, as well as changes in add.
template <typename T>
class List {
private:
	/* N - node, d - data, n - next, p - previous, h - head,
	t - tail, c - count, pn - prevNum, pv - prevNode. */
	struct N { T d; N* n = nullptr, * p = nullptr; N(T v) :d(v) {} };
	N* h = nullptr, * l = nullptr, * pv = nullptr; int count = 0, pn = -1;
	N* f(N* s, int j) {
		if (!s) return nullptr; 
		while (j-- && s->n) s = s->n; 
		return s;
	} // forward
	N* b(N* s, int j) {
		if (!s) return nullptr; 
		while (j-- && s->p) s = s->p; 
		return s;
	} // backward
	N* g(int i) { 
		if (!h) return nullptr;
		/*s - search start node, j - step count, hd - distance to i,
		ld - the same distance, but from the end. pd - distance from the last element */
		N* s = h; int j = 0, hd = i, ld = count - i - 1, pd = (pv) ? abs(pn - i) : INT_MAX;
		if (hd <= min(ld, pd));
		else if (ld < min(hd, pd)) { s = (!l) ? l : h, j = ld; }
		else { s = (!pv) ? pv : h, j = abs(pn - i); }
		return (j > pn) ? f(s, j) : b(s, j);
	}
public:
	void add(T v) {
		N* n = new N(v);
		if (!h || !l) { l = h = n; count++; return; }
		N* cur = h;
		while (cur) {
			if (cur->d == v) return;
			cur = cur->n;
		}
		l->n = n; n->p = l; l = n; count++;
	}
	void remove(const T& v) {
		N* cur = h; int x = 0;
		while (cur && cur->d != v) { 
			cur = cur->n;
			x++; 
		}
		if (!cur) return;
		if (cur->n) cur->n->p = cur->p;
		if (cur->p) cur->p->n = cur->n;
		h = cur == h ? h->n : h;
		if (h) h->p = nullptr;
		l = cur == l ? l->p : l; 
		if (l) l->n = nullptr;
		if (cur == pv) {
			pv = (cur->n) ? cur->n : cur->p;
			pn = (pv == cur->n) ? x : --x;
		}
		else { pn = (x < pn) ? --pn : pn; }
		delete cur;
		count--;
		if (count==0) { h = l = pv = nullptr; pn = -1; }
	}
	T& element(int x) { 
		N* n = g(x); pv = n; pn = x; 
		if (n) return n->d; 
		else { throw ("Invalid index"); } }
	bool contains(const T& v) { 
		if (h) { for (N* cur = h; cur != nullptr; cur = cur->n) { if (cur->d == v) return true; } }
		return false;
	}
	int size() { return count; }
	void clear() { 
		N* t = h;
		while (h->n) { t = h->n; delete h; h = t; }
		h = t = l = pv = nullptr; 
		count = 0; 
		pn = -1;
	}
};