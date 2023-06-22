#include "head.h"

FILE* fp, * sp;
int cat = 0, r = 0, w_type = 0, a_type = 0, idx = 0, wallet = 10000, fight_count = 0;
double a_hp = 0.0, w_hp = 0.0;

struct mypo* mypo;
struct poketmon* wild;
struct mypo mypo_list[MAX] = { 0, };
struct poketmon poketmon_list[MAX] = { 0, };
struct fight_list fight_list[MAX] = { 0, };
struct stuff ball = { "몬스터볼",1000, 0 };
struct stuff potion = { "회복물약",2500, 0 };

void list() {
	fp = fopen("poketmon_list.txt", "r");

	char c[MAX], list[MAX], * token;
	int num = 0, enter;
	int i = 0;

	fgets(c, MAX, fp);
	while (feof(fp) == 0) {
		i = 0;
		fgets(list, MAX, fp);
		token = strtok(list, "|");
		while (token != NULL) {
			if (i == 0) {
				strcpy(poketmon_list[idx].name, token);
			}
			else if (i == 1) {
				strcpy(poketmon_list[idx].type, token);
			}
			else if (i == 2) {
				poketmon_list[idx].power = atoi(token);
			}
			else if (i == 3) {
				poketmon_list[idx].hp = atoi(token);
			}
			i++;
			token = strtok(NULL, "|");
		}
		idx++;
	}
}

void Main() {
	printf("\n====================\n"
		"\t\t포켓몬스터\n"
		"\tpress enter key to start\n");

	int enter = getchar();
	if (enter == '\n') {
		start();
	}
	else {
		printf("게임 종료");
		return;
	}
}

void start() {
	printf("====================\n"
		"\t1. 새로하기 2. 이어하기\n"
		">>");

	int n;
	scanf("%d", &n);
	if (n == 1) {
		remove(sp);
		list();
		choose();
	}
	else if (n == 2) { //미완 - load 함수에서 에러 발생
		list();
		load();
	}
}

void load() {
	FILE* rp = fopen("save.txt", "r");

	if (rp == NULL) {
		printf("save 파일이 존재하지 않습니다.\n");
		start();
	}
	else {
		char w[MAX], my_list[MAX], list[MAX];
		int money;
		char* rLine, * token1, * token2;
		int num = 0;
		while (feof(rp) == 0) {
			int l = 0;
			if (num == 0) {
				fgets(w, sizeof(w), rp);
				money = atoi(w);
				for (int u = 0; u < 3; u++) {
					fgets(my_list, MAX, rp);
					token1 = strtok(my_list, "|");
					if (u == 0) {
						for (int l = 0; l < 2; l++) {
							if (l == 0) {
								strcpy(ball.name, token1);
							}
							else if (l == 1) {
								ball.count = atoi(token1);
							}
						}
					}
					else if (u == 1) {
						for (int l = 0; l < 2; l++) {
							if (l == 0) {
								strcpy(potion.name, token1);
							}
							else if (l == 1) {
								potion.count = atoi(token1);
							}
						}
					}
					else if (u == 2) {
						for (int l = 0; l < 2; l++) {
							if (l == 0) {
								strcpy(mypo->name, token1); //에러
							}
							else if (l == 1) {
								strcpy(mypo->type, token1);
							}
							else if (l == 2) {
								mypo->power = atoi(token1);
							}
							else if (l == 3) {
								mypo->hp = atoi(token1);
							}
						}
					}
					token1 = strtok(NULL, "|");
				}
			}
			l = 0;

			fgets(list, MAX, rp);
			token2 = strtok(list, "|");
			while (token2 != NULL) {
				if (l == 0) {
					strcpy(fight_list[num].poketmon.name, token2);
				}
				else if (l == 1) {
					strcpy(fight_list[num].poketmon.type, token2);
				}
				else if (l == 2) {
					fight_list[num].poketmon.power = atoi(token2);
				}
				else if (l == 3) {
					fight_list[num].poketmon.hp = atoi(token2);
				}
				else if (l == 4) {
					strcpy(fight_list[num].status, token2);
				}
				l++;
				token2 = strtok(NULL, "|");
			}
			num++;
		}

		if (strcmp(fight_list[num - 1].status, "CATCH!") == 0) {
			final();
		}
		else if (strcmp(fight_list[0].poketmon.name, fight_list[num - 2].poketmon.name) == 0
			&& strcmp(fight_list[num - 2].status, "LOSE") == 0) {
			strcpy(wild->name, fight_list[num - 1].poketmon.name);
			strcpy(wild->type, fight_list[num - 1].poketmon.type);
			wild->power = fight_list[num - 1].poketmon.power;
			wild->hp = fight_list[num - 1].poketmon.hp;
			print_list(wild);
		}
		else {
			ready();
		}
	}
}

void choose() {
	srand(time(NULL));
	printf("====================\n"
		"\t어느 포켓몬을 고르시겠습니까?\n"
		"\t1. 파이리 2. 이상해씨 3. 꼬부기\n"
		">>");

	int n;
	scanf("%d", &n);
	if (n == 1) {
		strcpy(mypo_list[0].name, "파이리");
		strcpy(mypo_list[0].nickname, "파이리");
		strcpy(mypo_list[0].type, "불");
		mypo_list[0].power = rand() % 51 + 100;
		mypo_list[0].hp = rand() % 501 + 500;
		mypo = &mypo_list[0];
		a_hp = mypo->hp;
	}
	else if (n == 2) {
		strcpy(mypo_list[0].name, "이상해씨");
		strcpy(mypo_list[0].nickname, "이상해씨");
		strcpy(mypo_list[0].type, "풀");
		mypo_list[0].power = rand() % 51 + 100;
		mypo_list[0].hp = rand() % 501 + 500;
		mypo = &mypo_list[0];
		a_hp = mypo->hp;
	}
	else if (n == 3) {
		strcpy(mypo_list[0].name, "꼬부기");
		strcpy(mypo_list[0].nickname, "꼬부기");
		strcpy(mypo_list[0].type, "물");
		mypo_list[0].power = rand() % 51 + 100;
		mypo_list[0].hp = rand() % 501 + 500;
		mypo = &mypo_list[0];
		a_hp = mypo->hp;
	}
	ready();
}

void ready() {
	printf("====================\n"
		"\t여행을 떠나시겠습니까?\n"
		"\t1. 네   2. 아니오 ( 저장 여부 선택 )   3. 상점 가기 ( 몬스터볼과 회복 물약 사기 )\n"
		">>");

	int m;
	scanf("%d", &m);
	if (m == 3) {
		store();
	}
	else if (m == 2) {
		printf("저장하시겠습니까?(Y/N) : ");
		char answer = 'X';
		scanf(" %c", &answer);
		if (answer == 'Y') {
			save(mypo);
		}
		else if (answer == 'N') {
			ready();
		}
	}
	else {
		walk();
	}
}

void save(struct poketmon* mypo) {
	sp = fopen("save.txt", "w");

	if (sp == NULL) {
		perror("파일 열기 실패\n");
	}
	else {
		fprintf(sp, "%d\n", wallet);
		if (ball.count > 0) {
			fprintf(sp, "%s|%d\n", ball.name, ball.count);
		}
		if (potion.count > 0) {
			fprintf(sp, "%s|%d\n", potion.name, potion.count);
		}
		fprintf(sp, "%-6s|%-5s|%.1lf|%.1lf\n",
			mypo->name, mypo->type, mypo->power, mypo->hp);
		for (int i = 0; i < (fight_count * 2); i++) {
			if (fight_list[i].poketmon.name != NULL) {
				fprintf(sp, "%-6s|%-5s|%.1lf|%.1lf|%-6s\n",
					fight_list[i].poketmon.name, fight_list[i].poketmon.type,
					fight_list[i].poketmon.power, fight_list[i].poketmon.hp, fight_list[i].status);
			}
			else {
				fclose(sp);
				fclose(fp);
				exit(0);
			}
		}
		fclose(sp);
		fclose(fp);
		exit(0);
	}
}

void save_list(struct poketmon* po, char status[10]) {
	int i = 0;
	while (1) {
		if (fight_list[i].poketmon.name[0] == '\0') {
			strcpy(fight_list[i].poketmon.name, po->name);
			strcpy(fight_list[i].poketmon.type, po->type);
			fight_list[i].poketmon.power = po->power;
			fight_list[i].poketmon.hp = po->hp;
			strcpy(fight_list[i].status, status);
			break;
		}
		i++;
	}
}

void store() {
	printf("====================\n");
	printf("\t\t\t\t현재 소유 금액 : %d\n", wallet);
	printf("\t1.%s %d\n", ball.name, ball.price);
	printf("\t2.%s %d\n", potion.name, potion.price);

	while (1) {
		printf("\n\t어떤 아이템을 사시겠습니까? : ");
		int m, num;
		char answer = 'X';
		scanf("%d", &m);
		if (m == 0) {
			ready();
		}
		else {
			if (m == 1) {
				printf("수량 : ");
				scanf("%d", &num);
				printf("구매하시겠습니까? (Y or N) : ");
				scanf(" %c", &answer);
				if (answer == 'N') {
					continue;
				}
				else if (answer == 'Y') {
					if (cal(ball, num)) {
						printf("\t\t\t\t현재 소유 금액 : %d\n", wallet);
						printf("성공적으로 %s을 구매하였다.\n", ball.name);
						ball.count += num;
						continue;
					}
					printf("돈이 부족하여 살 수 없습니다.\n");
					continue;
				}
			}
			else if (m == 2) {
				printf("수량 :");
				scanf("%d", &num);
				printf("구매하시겠습니까? (Y or N) :");
				scanf(" %c", &answer);
				if (answer == 'N') {
					continue;
				}
				else if (answer == 'Y') {
					if (cal(potion, num)) {
						printf("\t\t\t\t현재 소유 금액 : %d\n", wallet);
						printf("성공적으로 %s을 구매하였다.\n", potion.name);
						potion.count += num;
						continue;
					}
					printf("돈이 부족하여 살 수 없습니다.\n");
					continue;
				}
			}
		}
	}
}

int cal(struct stuff st, int a) {
	int price = 0;
	price = st.price * a;
	if (price > wallet) {
		return 0;
	}
	wallet -= price;
	return 1;
}

void create() {
	wild = &poketmon_list[rand() % idx];
	wild->power = rand() % (200 - (int)wild->power + 1) + (int)wild->power;
	wild->hp = rand() % (1200 - (int)wild->hp + 1) + (int)wild->hp;
	w_hp = wild->hp;
}

void walk() {
	printf("====================\n"
		"\t길을 걷는중");
	for (int t = 0; t < rand() % 3 + 1; t++) {
		printf(" ...");
		Sleep(ONE_SECOND);
	}

	create();

	printf("\n====================\n"
		"\t야생의 포켓몬(%s)이 나타났다!", wild->name);
	appear(wild, mypo);
}

void appear(struct poketmon* wild, struct mypo* mypo) {
	printf("\n\t1. 공격 2. 도망치기 3. 가방 열기\n"
		">>");

	int n;
	scanf("%d", &n);

	switch (n) {
	case 1:
		fight(wild, mypo);
		break;
	case 2:
		run(wild);
		break;
	case 3:
		bag(wild);
	}
}

void fight(struct poketmon* wild, struct mypo* mypo) {
	compatibility(wild, mypo);
	int who = 1;
	while (1) {
		if (who == 1 && cat != 1) {
			if (w_type != 3 && a_type != 3) {
				if (w_type < a_type) {
					wild->hp -= (mypo->power) * 1.5;
					printf("효과는 굉장했다.\n\n");
				}
				else if (w_type > a_type) {
					wild->hp -= mypo->power;
					printf("효과가 별로인 듯 하다.\n\n");
				}
				else if (w_type == a_type) {
					wild->hp -= (mypo->power) * 0.5;
				}
			}
			else {
				wild->hp -= (mypo->power) * 0.5;
			}
		}
		if (wild->hp <= 0) {
			if (wild->hp == 0) {
				printf("앗! 포켓몬이 도망가버렸다...\n");
				fight_count++;
				save_list(mypo, "WIN");
				save_list(wild, "RUN AWAY");
				ready();
			}
			else {
				printf("포켓몬을 쓰러트렸다!\n");
				fight_count++;
				save_list(mypo, "WIN");
				save_list(wild, "LOSE");
				ready();
			}
		}
		printf("적(%s) : %.lf/%.lf\n", wild->name, wild->hp, w_hp);

		who *= -1;
		for (int t = 0; t < 1; t++) {
			printf("%s이(가) 공격 중...\n", wild->name);
			Sleep(ONE_SECOND);
		}

		if (who == -1) {
			if (w_type != 3 && a_type != 3) {
				if (w_type < a_type) {
					mypo->hp -= (wild->power) * 1.5;
				}
				else if (w_type > a_type) {
					mypo->hp -= wild->power;
				}
				else if (w_type == a_type) {
					mypo->hp -= (wild->power) * 0.5;
				}
			}
			else {
				mypo->hp -= (wild->power) * 0.5;
			}
		}
		cat = 0;
		if (mypo->hp <= 0) {
			printf("내 포켓몬이 쓰러졌다.\n");
			fight_count++;
			save_list(mypo, "LOSE");
			save_list(wild, "WIN");
			print_list(wild);
			break;
		}
		printf("나(%s) : %.lf/%.lf\n", mypo->name, mypo->hp, a_hp);
		break;
	}
	appear(wild, mypo);
}

void compatibility(struct poketmon* wild, struct mypo* mypo) {
	if ((strcmp(wild->type, "불") == 0)) {
		w_type = 0;
	}
	else if ((strcmp(wild->type, "물")) == 0) {
		w_type = 1;
	}
	else if ((strcmp(wild->type, "풀")) == 0) {
		w_type = 2;
	}
	else {
		w_type = 3;
	}

	if ((strcmp(mypo->type, "불")) == 0) {
		a_type = 0;
	}
	else if ((strcmp(mypo->type, "물")) == 0) {
		a_type = 1;
	}
	else if ((strcmp(mypo->type, "풀")) == 0) {
		a_type = 2;
	}
	else {
		a_type = 3;
	}
}

void run(struct poketmon* wild) {
	int per = 0;

	if (wild->hp < 300) {
		per = 90;
	}
	else if (wild->hp > 300 && wild->hp < 600) {
		per = 70;
	}
	else if (wild->hp > 600 && wild->hp < 1200) {
		per = 40;
	}
	else if (wild->hp == 1200) {
		per = 10;
	}

	if (per == 70) {
		printf("도망치기 성공!\n");
		ready();
	}
	else {
		printf("도망치기 실패..\n\n");
		cat = 1;
		fight(wild, mypo);
	}
}

void bag(struct poketmon* wild) {
	if (ball.count == 0 && potion.count == 0) {
		printf("가방이 비어있습니다.\n");
		appear(wild, mypo);
	}
	else {
		printf("====================\n");
		printf("1. %-6s x %d\n", ball.name, ball.count);
		printf("2. %-6s x %d\n\n", potion.name, potion.count);
		printf("어떤 아이템을 사용하시겠습니까? :");

		int num;
		scanf("%d", &num);
		if (num == 1) {
			if (ball.count == 0) {
				printf("몬스터볼을 사용할 수 없습니다.\n");
				bag(wild);
			}

			catch (wild);
			if (cat == 1) {
				fight(wild, mypo);
			}
			else {
				ready();
			}
		}
		else {
			if (potion.count == 0) {
				printf("회복물약을 사용할 수 없습니다.\n");
				bag(wild);
			}

			if (mypo->hp == a_hp) {
				printf("이미 충분한 체력을 소유하고 있습니다!\n");
				bag(wild);
			}
			else {
				potion.count--;
				mypo->hp += a_hp * 0.3;
				printf("%s의 체력이 회복되었습니다!"
					"\t%.lf/%.lf\n\n", mypo->name, mypo->hp, a_hp);
				save_list(mypo, "HEAL");
				cat = 1;
				fight(wild, mypo);
			}
		}
	}
}

void catch (struct poketmon* wild) {
	printf("가랏 몬스터볼!\n");
	for (int t = 0; t < 2; t++) {
		printf("!\n");
		Sleep(ONE_SECOND);
	}

	int per = 0;

	if (wild->hp > 600) {
		printf("체력을 더 깍아주세요..\n\n");
		cat = 1;
		return;
	}
	else if (wild->hp > 0 && wild->hp < 120) {
		per = 90;
	}
	else if (wild->hp > 120 && wild->hp < 360) {
		per = 60;
	}
	else if (wild->hp > 360 && wild->hp < 600) {
		per = 30;
	}
	ball.count--;


	if (per == 90) {
		wallet += 1000;
		printf("1000원을 획득했다!\n");
		printf("포켓몬을 잡았다! 이름을 입력해주세요 : ");
		if (r != 0) {
			add(wild);
		}
		else if (r == 0) {
			r += 1;
			add(wild);
		}
		final();
	}
	else if (per == 60 || per == 30) {
		printf("포켓몬이 몬스터볼을 빠져 나왔다.\n\n");
		cat = 1;
		return;
	}
}

void final() {
	if (r == 5) {
		char answer = 'X';
		printf("넌 이제 내꺼야! 여행을 더 떠나볼까?(Y/N) : ");
		scanf(" %c", &answer);
		if (answer == 'N') {
			exit(0);
		}
		else if (answer == 'Y') {
			for (int i = 1; i < r + 1; i++) {
				strcpy(mypo_list[i].name, "");
				strcpy(mypo_list[i].nickname, "");
				strcpy(mypo_list[i].type, "");
				mypo_list[i].power = 0;
				mypo_list[i].hp = 0;
			}
			r = 0;
			start();
		}
	}
}

void add(struct poketmon* wild) {
	char nick[10] = { 0, };
	scanf("%s", &nick);
	strcpy(mypo_list[r].nickname, nick);
	strcpy(mypo_list[r].name, wild->name);
	strcpy(mypo_list[r].type, wild->type);
	mypo_list[r].power = wild->power;
	mypo_list[r].hp = wild->hp;
	fight_count++;
	save_list(wild, "CATCH!");
}

void print_list(struct poketmon* wild) {
	printf("====================\n");
	int i = 0;
	struct mypo* pos_list[MAX] = { 0, };
	if (sizeof(mypo_list) / sizeof(struct mypo) > 0) {
		while (mypo_list[r].power != 0.0) {
			if (mypo_list[r].hp > 0) {
				pos_list[i] = &mypo_list[r];
				i++, r++;
			}
			else {
				r++;
			}
		}
	}

	if (pos_list[0]->name == NULL) {
		printf("눈 앞이 깜깜해졌다.\n"
			"====================\n"
			"보유하고 계신 모든 포켓몬이 체력을 회복하였습니다.\n");
		mypo->hp = a_hp;
		ready();
	}
	else {
		for (int e = 0; e < i; e++) {
			printf("%-3d %-5s %-5s %-2.1lf/%.1lf\n", e + 1, pos_list[e]->name, pos_list[e]->type,
				pos_list[e]->power, pos_list[e]->hp);
		}
		printf("\t어느 포켓몬을 내보내시겠습니까?\n"
			">>");
		int n;
		scanf("%d", &n);
		if (n == 0) {
			walk();
		}
		else {
			strcpy(mypo->name, pos_list[n - 1]->name);
			strcpy(mypo->nickname, pos_list[n - 1]->nickname);
			strcpy(mypo->type, pos_list[n - 1]->type);
			mypo->power = pos_list[n - 1]->power;
			mypo->hp = pos_list[n - 1]->hp;
			fight(wild, mypo);
		}
	}
}