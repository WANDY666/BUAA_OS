#include "pageReplace.h"
#include <iostream>
#define MAX_PHY_PAGE 64
#define MAX_PAGE 12
#define get_Page(x) (x >> MAX_PAGE)
#define INT_MAX (0x7fffffff)
#define INT_MIN (0x80000000)
using namespace std;

typedef struct Type
{
    int next;
    int last;
} Page;
int flags[get_Page(INT_MAX) + 1];
int page;
int index = 0;
int mmmm;
int flag;
int primary;
int base;

Page pages[MAX_PHY_PAGE];
Page *p;
int head = -1, tail = -1;
int ff = 1;
void pageReplace(long *physic_memery, long nwAdd) {
	if (ff) {
		static auto speedup = [](){ios::sync_with_stdio(false);cin.tie(nullptr);return nullptr;}();	
		ff = 0;
	}
    page = get_Page(nwAdd);
    flag = flags[page];
    if (flag > 0)
    {
        index = flag - 1;
        p = pages + index;
        if (p->last == -1)
        {
            return;
        }
        if (p->next != -1)
        {
            pages[p->next].last = p->last;
        } else
        {
            tail = p->last;
        }
        pages[p->last].next = p->next;
        pages[index].next = head;
        pages[head].last = index;
        head = index;
        pages[head].last = -1;
        return;
    }
    mmmm = INT_MIN;
    if (primary < 64)
    {
        index = primary++;
        if ((pages[index].next = head) != -1)
        {
            pages[head].last = index;
        } else
        {
            tail = index;
        }
        head = index;
        pages[index].last = -1;
    } else
    {
        index = tail;
        tail = pages[tail].last;
        pages[tail].next = -1;
        pages[index].next = head;
        pages[head].last = index;
        head = index;
        pages[head].last = -1;
    }
    flags[page] = index + 1;
    flags[physic_memery[index]] = 0;
    physic_memery[index] = page;
}
