#pragma once
#include<stdexcept>
#include<algorithm>
using namespace std;

template <typename T>
class List {
private:
	/* N - узел, d - данные, n - следующий, p - предыдущий, h - head,
		t - tail, c - count, pn - prevNum, pv - prevNode. */
	struct N { T d; N* n = nullptr, * p = nullptr; N(T v) :d(v) {} };
	N* h = nullptr, * l = nullptr, * pv = nullptr; int count = 0, pn = -1;
	N* f(N* s, int j) { while (j--)s = s->n; return s; } // forward
	N* b(N* s, int j) { while (j--)s = s->p; return s; } // backward
	N* g(int i) { 
		if (!h) return nullptr;
		/*s - узел начала поиска, j - счетчик шагов, hd - рассто€ние до i,
		ld - то же рассто€ние, но от конца. pd-рассто€ние от последнего элемента */
		N* s = h; int j = 0, hd = i, ld = count - i - 1, pd = (pv) ? abs(pn - i) : INT_MAX;
		if (hd <= min(ld, pd));
		else if (ld < min(hd, pd)) { s = l, j = ld;}
		else { s = pv, j = abs(pn - i); }
		return (j > pn) ? f(s, j) : b(s, j);
	}
public:
	void a(T v) {
		N* n = new N(v);
		if (!h) { l = h = n; count++; return; }
		N* cur = h;
		while (cur) {
			if (cur->d == v) return;
			cur = cur->n;
		}
		l->n = n; n->p = l; l = n; count++;
	}
	void r(const T& v) {
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
	T& e(int x) { N* n = g(x); pv = n; pn = x; if (n) return n->d; else { throw ("Invalid index"); } }
	bool con(const T& v) { 
		if (h) { for (N* cur = h; cur != nullptr; cur = cur->n) { if (cur->d == v) return true; } }
		return false;
	}
	int s() { return count; }
	void clear() { 
		N* t = h;
		while (h) { t = h->n; delete h; h = t; }
		h = t = l = pv = nullptr; count = 0; pn = -1;
	}
};