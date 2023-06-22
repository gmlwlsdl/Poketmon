#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100
#define ONE_SECOND 1000

typedef struct poketmon {
	char name[10];
	char type[10];
	double power;
	double hp;
};

typedef struct mypo {
	char name[10];
	char nickname[10];
	char type[10];
	double power;
	double hp;
};

typedef struct stuff {
	char name[9];
	int price;
	int count;
};

typedef struct fight_list {
	struct poketmon poketmon;
	char status[10];
};

void Main();
void list();
void start();
void load();
void choose();
void ready();
void save(struct poketmon* mypo);
void save_list(struct poketmon* po, char status[10]);
void store();
int cal(struct stuff st, int a);
void create();
void walk();
void appear(struct poketmon* wild, struct mypo* mypo);
void fight(struct poketmon* wild, struct mypo* mypo);
void compatibility(struct poketmon* wild, struct mypo* mypo);
void run(struct poketmon* wild);
void bag(struct poketmon* wild);
void catch (struct poketmon* wild);
void final();
void add(struct poketmon* wild);
void print_list(struct poketmon* wild);