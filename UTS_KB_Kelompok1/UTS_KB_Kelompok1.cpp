#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

struct node
{
	int block[9];
	char* str;
	int pathcost;
	int valid;
	int totalcost;
	node* next;
};

int heur(int block[]);
void prepend(node* newnode, node* oldnode, int operator1);
int goal(int* block);
int notonqueue(int block[]);
node* bestnode();
void print(int* block);
int apply(int* newstate, int* oldstate, int op);
node* newelement();
int op(char);
char to_char(int i);
int totalpathcost;

char rep[] = "dulr";
int notvalid1[4] = { 6, 0, 0, 2 };
int notvalid2[4] = { 7, 1, 3, 5 };
int notvalid3[4] = { 8, 2, 6, 8 };
int applyparam[4] = { +3, -3, -1, +1 };
int goal_block[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
int maxdepth;
node* top;

int heur(int* block)
{
	int nol = 0;

	for (int i = 0; i < 9; i++)
	{
		nol += abs((i / 3) - (block[i] / 3));
		nol += abs((i % 3) - (block[i] % 3));
	}
	return nol;
}

void prepend(node* newnode, node* oldnode, int op)
{
	newnode->next = top;
	top = newnode;

	strcpy(newnode->str,oldnode->str);
	newnode->str[oldnode->pathcost] = rep[op];
	newnode->str[oldnode->pathcost + 1] = 0;

	newnode->pathcost = oldnode->pathcost + 1;
	newnode->totalcost = newnode->pathcost + heur(newnode->block);
	if (newnode->totalcost < oldnode->totalcost) newnode->totalcost = oldnode->totalcost;
}

int goal(int* block)
{
	int* g_block = goal_block;

	for (int i = 0; i < 9; i++)
		if ((*(block++)) != (*(g_block++)))
			return 0;

	return 1;
}

int notonqueue(int* block)
{
	int i;
	node* t = top;

	while (t != NULL)
	{
		for (i = 0; i < 9; i++)
			if (t->block[i] != block[i]) break;
		if (i == 9) return 0;

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

int apply(int* newstate, int* oldstate, int op)
{
	int j;
	int blank;

	for (j = 0; j < 9; j++)
		if (oldstate[j] == 8) { blank = j; break; }

	if (blank == notvalid1[op] || blank == notvalid2[op] || blank == notvalid3[op])
		return -1;

	for (j = 0; j < 9; j++)
		newstate[j] = oldstate[j];

	newstate[blank] = newstate[blank + applyparam[op]];
	newstate[blank + applyparam[op]] = 8;

	return 1;
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

void print(int* block)
{
	cout << endl;
	cout << "-------";
	cout << endl << "|" << to_char(block[0]) << "|" << to_char(block[1]) << "|" << to_char(block[2]) << "|" << endl;
	cout << "-------";
	cout << endl << "|" << to_char(block[3]) << "|" << to_char(block[4]) << "|" << to_char(block[5]) << "|" << endl;
	cout << "-------";
	cout << endl << "|" << to_char(block[6]) << "|" << to_char(block[7]) << "|" << to_char(block[8]) << "|" << endl;
	cout << "-------";

}

char to_char(int i)
{
	if (i >= 0 && i <= 7) return i + '1';
	else if (i == 8) return 'x';
	else { cout << "Program ERROR" << endl; return -1; }

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
	int block[9];

	cout << "8 Puzzle Game" << endl;

	cout << "Masukkan state awal Puzzle !" << endl << "Penulisan dari kiri ke kanan lalu atas ke bawah" << endl << "x menandakan kosong" << endl;


	int i = 0;
	while (i < 9)
	{
		char chr;
		cin >> chr;
		if (chr == 32) continue;
		if (chr == 'x') block[i] = 8;
		else if (chr >= '1' && chr <= '9') block[i] = chr - '1';
		else { cout << "Invalid Input" << endl; return 1; }
		i++;
	}

	cout << "Masukkan Goal State" << endl;

	i = 0;
	while (i < 9)
	{
		char chr;
		cin >> chr;
		if (chr == 32) continue;
		if (chr == 'x') goal_block[i] = 8;
		else if (chr >= '1' && chr <= '9') goal_block[i] = chr - '1';
		else { cout << "Invalid Input" << endl; return 1; }
		i++;
	}

	cout << "Masukkan depth (maximal 40 depth)" << endl;
	cin >> maxdepth;

	top = newelement();
	for (i = 0; i < 9; i++)
		top->block[i] = block[i];
	top->totalcost = heur(block);

	node* newnode = newelement();

	while (1)
	{
		node* node = bestnode();
		if (node == NULL) {
			cout << "Selesai." << endl;
			cout << "Tidak ada Solusi dengan depth : " << maxdepth << endl;
			break;
		}
		else if (goal(node->block)) {
			char chr[15];
			cout << "Selesai." << endl << "Menggunakan langkah paling sedikit : " << node->pathcost << endl;
			cout << "Tampilkan tampilan puzzle ? (Y/N)" << endl;
			cin >> chr;
			if (chr[0] == 'n' || chr[0] == 'N') {
				break;
			}

			int block2[9];
			for (i = 0; i < node->pathcost; i++)
			{
				print(block);
				apply(block2, block, op(node->str[i]));
				for (int j = 0; j <= 8; j++)
					block[j] = block2[j];
			}
			print(block);

			cout << endl << "Tampilan selesai." << endl;
			cout << node->str << endl;
			break;

		}

		if (node->totalcost > maxdepth) continue;

		for (i = 0; i <= 3; i++) {
			if (apply(newnode->block, node->block, i) == -1)
				continue;

			if (notonqueue(newnode->block)) {
				prepend(newnode, node, i);
				newnode = newelement();
				if (newnode == NULL) { cout << "ERROR. Tambahkan depth" << endl; return 1; }
			}
		}

	}
	return 0;
}