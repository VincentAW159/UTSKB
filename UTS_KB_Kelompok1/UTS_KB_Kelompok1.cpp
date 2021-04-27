#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

struct node
{
	int block[25];
	char* str;
	int pathcost;
	int valid;
	int totalcost;
	node* next;
};

void prepend(node* newnode, node* oldnode, int operator1, int size);
int goal(int* block, int sizee);
int notonqueue(int block[], int size);
node* bestnode();
void print(int* block, int size, int size2);
int apply(int* newstate, int* oldstate, int op);
node* newelement();
int op(char);
int to_char(int i, int size);
int heur1(int block[], int size);
int totalpathcost;

char rep[] = "dulr";
int notvalid31[4] = { 6, 0, 0, 2 };
int notvalid32[4] = { 7, 1, 3, 5 };
int notvalid33[4] = { 8, 2, 6, 8 };
int applyparam3[4] = { +3, -3, -1, +1 };
int notvalid41[4] = { 12, 0, 0, 3 };
int notvalid42[4] = { 13, 1, 4, 7};
int notvalid43[4] = { 14, 2, 8, 11 };
int notvalid44[4] = { 15, 3, 12, 15 };
int applyparam4[4] = { +4, -4, -1, +1 };
int notvalid51[4] = { 20, 0, 0, 4};
int notvalid52[4] = { 21, 1, 5, 9};
int notvalid53[4] = { 22, 2, 10, 14};
int notvalid54[4] = { 23, 3, 15, 19};
int notvalid55[4] = { 24, 4, 20, 24};
int applyparam5[4] = { +5, -5, -1, +1 };
int goal_block3[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int goal_block4[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
int goal_block5[25] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
int maxdepth;
node* top;

int heur1(int* block, int size) {
	int counter = 0;
	
	switch (size)
	{
	case 3:
		for (int i = 0; i < size; i++)
		{
			if (block[i] == goal_block3[i])
			{
				counter++;
			}
		}
		return counter;
		break;
	case 4:
		for (int i = 0; i < size; i++)
		{
			if (block[i] == goal_block4[i])
			{
				counter++;
			}
		}
		return counter;
		break;
	case 5:
		for (int i = 0; i < size; i++)
		{
			if (block[i] == goal_block5[i])
			{
				counter++;
			}
		}
		return counter;
		break;
	}
}

void prepend(node* newnode, node* oldnode, int op, int size)
{
	newnode->next = top;
	top = newnode;

	strcpy(newnode->str, oldnode->str);
	newnode->str[oldnode->pathcost] = rep[op];
	newnode->str[oldnode->pathcost + 1] = 0;

	newnode->pathcost = oldnode->pathcost + 1;
	newnode->totalcost = newnode->pathcost + heur1(newnode->block, size);
	if (newnode->totalcost < oldnode->totalcost) newnode->totalcost = oldnode->totalcost;
}

int goal(int* block, int size)
{
	int siz = size;
	if (size == 9)
	{
		int* g_block = goal_block3;

		for (int i = 0; i < siz; i++)
			if ((*(block++)) != (*(g_block++)))
				return 0;

		return 1;
	}
	else if (size == 16)
	{
		int* g_block = goal_block4;

		for (int i = 0; i < siz; i++)
			if ((*(block++)) != (*(g_block++)))
				return 0;

		return 1;
	}
	else if (size == 25)
	{
		int* g_block = goal_block5;

		for (int i = 0; i < siz; i++)
			if ((*(block++)) != (*(g_block++)))
				return 0;

		return 1;
	}
}

int notonqueue(int* block, int size)
{
	int i;
	node* t = top;

	while (t != NULL)
	{
		for (i = 0; i < size; i++)
			if (t->block[i] != block[i]) break;
		if (i == size) return 0;

		t = t->next;
	}
	return 1;
}

node* bestnode()
{
	node* t = top;
	int min_totalpathcost = 1000;

	node* nol = NULL;

	while (t != NULL)
	{
		if (t->valid == 1 && t->totalcost < min_totalpathcost)
		{
			min_totalpathcost = t->totalcost;
			nol = t;
		}
		t = t->next;
	}

	if (nol != NULL) nol->valid = 0;

	return nol;
}

int apply(int* newstate, int* oldstate, int op, int size)
{
	int j;
	int blank = 0;
	int siz = size * size;

	switch (size)
	{
	case 3:

		for (j = 0; j < siz; j++)
			if (oldstate[j] == siz) { blank = j; break; }

		if (blank == notvalid31[op] || blank == notvalid32[op] || blank == notvalid33[op])
			return -1;

		for (j = 0; j < siz; j++)
			newstate[j] = oldstate[j];

		newstate[blank] = newstate[blank + applyparam3[op]];
		newstate[blank + applyparam3[op]] = siz;

		return 1;
		break;
	case 4:
		for (j = 0; j < siz; j++)
			if (oldstate[j] == siz) { blank = j; break; }

		if (blank == notvalid41[op] || blank == notvalid42[op] || blank == notvalid43[op] || blank == notvalid44[op])
			return -1;

		for (j = 0; j < siz; j++)
			newstate[j] = oldstate[j];

		newstate[blank] = newstate[blank + applyparam4[op]];
		newstate[blank + applyparam4[op]] = siz;

		return 1;
		break;
	case 5:
		for (j = 0; j < siz; j++)
			if (oldstate[j] == siz) { blank = j; break; }

		if (blank == notvalid51[op] || blank == notvalid52[op] || blank == notvalid53[op] || blank == notvalid54[op] || blank == notvalid55[op])
			return -1;

		for (j = 0; j < siz; j++)
			newstate[j] = oldstate[j];

		newstate[blank] = newstate[blank + applyparam5[op]];
		newstate[blank + applyparam5[op]] = siz;

		return 1;
		break;
	}
}

node* newelement()
{
	node* t = new node;
	if (t == NULL) return NULL;
	t->valid = 1;
	t->str = new char[maxdepth + 1];
	if (t->str == NULL) return NULL;
	t->str[0] = 0;
	t->pathcost = t->totalcost = 0;
	t->next = NULL;
	return t;
}

void print(int* block, int siz, int sizori)
{
	int x = sizori;
	int y = sizori;
	int j = 0;
	cout << endl << "Initial State : " << endl;
	for (int i = 0; i < x; i++)
	{
		cout << "-------" << endl;
		while (j < y)
		{
			cout << "|" << to_char(block[j], sizori);
			j++;
		}
		cout << "|" << endl;
		y = y + x;

	}
}

int to_char(int i, int size)
{
	int sizexx = size * size;
	switch (size)
	{
	case 3:
		if (i >= 1 && i <= sizexx - 1) return i;
		if (i == sizexx) return 0;
		else { printf("ERROR in Program!"); return -1; }
		break;
	case 4:
		if (i >= 1 && i <= sizexx - 1) return i;
		if (i == sizexx) return 0;
		else { printf("ERROR in Program!"); return -1; }
		break;
	case 5:
		if (i >= 1 && i <= sizexx - 1) return i;
		if (i == sizexx) return 0;
		else { printf("ERROR in Program!"); return -1; }
		break;
	}
}

int op(char i)
{
	switch (i)
	{
	case 'd': return 0;
	case 'u': return 1;
	case 'l': return 2;
	case 'r': return 3;
	default: printf("ERROR!"); return -1;
	}
}

int main()
{
	int size, temp1, temp2;
	cout << "N Puzzle Game" << endl << "Masukkan Size Puzzle (N x N) [Ukuran Maksimal 5 x 5] : ";
	cin >> size;
	while (size > 5)
	{
		cout << "Ukuran diatas 5! " << endl << "Input Ulang : ";
		cin >> size;
	}
	temp1 = size * size;
	cout << "Masukkan state awal Puzzle !" << endl << "Penulisan dari kiri ke kanan lalu atas ke bawah" << endl << "0 menandakan kosong" << endl;

	int block[25];
	if (size == 3)
	{
		for (int i = 0; i < temp1; i++)
		{
			int chr;
			cin >> chr;
			if (chr == 0) block[i] = 9;
			else { block[i] = chr; }
		}
	}
		if (size == 4)
		{
		for (int i = 0; i < temp1; i++)
		{
			int chr;
			cin >> chr;
			if (chr == 0) block[i] = 16;
			else { block[i] = chr; }
		}
		}
		 if (size == 5)
	{
		for (int i = 0; i < temp1; i++)
		{
			int chr;
			cin >> chr;
			if (chr == 0) block[i] = 25;
			else { block[i] = chr; }
		}
	}

	cout << "Masukkan Goal State" << endl;

	for (int i = 0; i < temp1; i++)
	{
		if (size == 3)
		{
			int chr;
			cin >> chr;
			if (chr == 0) goal_block3[i] = 9; 
			else { goal_block3[i] = chr; }
		}
		else if (size == 4)
		{
			int chr;
			cin >> chr;
			if (chr == 0) goal_block3[i] = 16;
			else { goal_block3[i] = chr; }
		}
		else if (size == 5)
		{
			int chr;
			cin >> chr;
			if (chr == 0) goal_block3[i] = 25;
			else { goal_block3[i] = chr; }
		}

	}

	cout << "Masukkan depth : " << endl;
	cin >> maxdepth;

	top = newelement();
	for (int i = 0; i < temp1; i++)
		top->block[i] = block[i];
	top->totalcost = heur1(block, size);

	node* newnode = newelement();

	while (1)
	{
		node* node = bestnode();
		if (node == NULL) {
			cout << "Selesai." << endl;
			cout << "Tidak ada Solusi dengan depth : " << maxdepth << endl;
			break;
		}
		else if (goal(node->block, temp1)) {
			char chr[15];
			cout << "Selesai." << endl << "Menggunakan langkah paling sedikit : " << node->pathcost << endl;
			cout << "Tampilkan tampilan puzzle ? (Y/N)" << endl;
			cin >> chr;
			if (chr[0] == 'n' || chr[0] == 'N') {
				break;
			}

			int block2[25];
			for (int i = 0; i < node->pathcost; i++)
			{
				print(block, temp1, size);
				apply(block2, block, op(node->str[i]), size);
				for (int j = 0; j <= temp1 - 1; j++)
					block[j] = block2[j];
			}
			print(block, temp1, size);

			cout << endl << "Tampilan selesai." << endl;
			cout << node->str << endl;
			break;

		}

		if (node->totalcost > maxdepth) continue;

		for (int i = 0; i <= size; i++) {
			if (apply(newnode->block, node->block, i, size) == -1)
				continue;

			if (notonqueue(newnode->block, temp1)) {
				prepend(newnode, node, i, size);
				newnode = newelement();
				if (newnode == NULL) { cout << "ERROR. Tambahkan depth" << endl; return 1; }
			}
		}
	}
	return 0;
}
