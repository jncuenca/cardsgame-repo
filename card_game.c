#include <stdio.h>
#include <time.h>
#include <windows.h>

#if defined(_WIN32) || defined(__MSDOS__)
   #define SPADE   "\x06"
   #define CLUB    "\x05"
   #define HEART   "\x03"
   #define DIAMOND "\x04"
#else
   #define SPADE   "\xE2\x99\xA0"
   #define CLUB    "\xE2\x99\xA3"
   #define HEART   "\xE2\x99\xA5"
   #define DIAMOND "\xE2\x99\xA6"
#endif

typedef struct card{
	int number;
	int type;
	int color; // 0 for black / 1 for red
	int state; // 0 for disabled y 1 for enable
}Card;

void generate_cards(Card cards[]);
void messing_up_cards(Card cards[], Card unordered_cards[]);
void main_game(Card unordered_cards[], int points[10], int n_game);
void order_machine_4elem(Card machine[6], int option);
void order_machine_2elem(Card machine[2], int option);
void order_elems_machine(Card machine[6], int start, int end, int option);
void battles_1v1(Card player[], Card machine[], int points[10], int size, int turn);
int mosquetero_battle(Card player[6], Card machine[6], int points[10]);
int is_poker(Card cards[6]);
void print_main_header(int turn, int n_game);
void print_points_header();
int color(int num);

int main(){
	srand(time(NULL));
	Card cards[52];
	generate_cards(cards);
	Card unordered_cards[52];
	int points[10]={0,0,0,0,0,0,0,0,0,0};
	int n_game = 0, op=1;
	
	do{
		messing_up_cards(cards, unordered_cards);
		n_game++;
		main_game(unordered_cards, points, n_game);	
		printf("-----------------------------------------------------------\n");
		printf("Do you wanna keep playing?\n 1. YES\n 0. NO\n");
		printf("-----------------------------------------------------------\n");
		printf("Enter option: ");
		scanf("%d", &op);
		system("cls");
	}while(op == 1);
	
	printf("-----------------------------------------------------------\n");
	printf(" %s%s BATTLE %s%s Game Finished!\n", DIAMOND, DIAMOND, DIAMOND, DIAMOND);
	printf("-----------------------------------------------------------\n");
	printf("\n	- Number of games: %d\n", n_game);
	color(14);
	printf("	- Player point: %d\n", points[0]);
	color(11);
	printf("	- Machine point: %d\n\n", points[1]);
	color(15);
		
	printf("-----------------------------------------------------------\n");
	if (points[0] == points[1]){
		color(7);
		printf("	BATTLE TIED WITH %d POINTS!\n", points[0]);
	}else if(points[0] > points[1]){
		color(3);
		printf("	YOU WON BY %d POINTS!\n", (points[0] - points[1]));
	}else{
		color(12);
		printf("	YOU LOST BY %d POINTS!\n", (points[1] - points[0]));
	}
	color(15);
	printf("-----------------------------------------------------------\n");
	
	printf("\n<Enter> to continue...");
	getchar();
	getchar();
	
	return 0;
}

// 15 for white -- 12 for red -- 3 for green
int color(int num){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),num);
	return 0;
}

void print_main_header(int turn, int n_game){
	printf("-----------------------------------------------------------\n");
	printf(" %s%s BATTLE %s%s Game number %d - Turn %d\n", DIAMOND, DIAMOND, DIAMOND, DIAMOND, n_game, turn);
	printf("-----------------------------------------------------------\n");
}

void print_points_header(){
	printf("\n-----------------------------------------------------------\n");
	printf(" POINTS\n");
	printf("-----------------------------------------------------------\n");
}

//generate 52 ordered cards
void generate_cards(Card cards[]){
	int i, j, c=0;
	for(i = 1; i < 5; i++){
		for(j = 1; j < 14; j++){
			Card C;
			C.number = j;
			C.type = i;
			C.state = 1;
			if(i % 2 == 0)
				C.color = 1;
			else
				C.color = 0;
			cards[c] = C;
			c++;
		}	
	}	
}

//Get unordered cards
void messing_up_cards(Card cards[], Card unordered_cards[]){
	int i, pos;
	pos = rand()%52;
	
	for(i = 0; i < 52; i++){
		while(cards[pos].state == 0){
			pos = rand()%52;
		}
		unordered_cards[i] = cards[pos];
		cards[pos].state = 0;
	}
	
	//reset 1 to card's state
	for(i = 0; i < 52; i++){
		cards[i].state = 1;
	}
}

//Main game
void main_game(Card unordered_cards[], int points[10], int n_game){
	color(15);
	int i, e, k, aux = 0, aux_2 = 6, cont, option, turn=1, resul_check=0;
	int n1, n2, n3, n4, n5, n6;
	char types[][10] = {CLUB, HEART, SPADE, DIAMOND};
	char numbers[][5] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	
	//deal 6 cards each/ 4 times
	Card player[6], ordered_player[6], machine[6];
	for(e = 0; e < 4; e++){
		cont = 0;
		for(i = aux; i < aux_2; i++){
			player[cont] = unordered_cards[i];
			machine[cont] = unordered_cards[i+6];
			cont++;
		}
		aux += 12, aux_2 += 12;
		
		print_main_header(turn, n_game);
		
		color(14);
		printf("Player cards\n");
		for(k = 0; k < 6; k++){
			if(player[k].color == 1) color(12);
			else color(15);
			printf("|%s%s|	", numbers[player[k].number - 1], types[player[k].type - 1]);		
		}
		color(15);
		printf("\n(1)	(2)	(3)	(4)	(5)	(6)\n");
		
		//ordering player's card
		printf("\nOrder the cards, separate the positions by commas: ");
		scanf("%d, %d, %d, %d, %d, %d", &n1, &n2, &n3, &n4, &n5, &n6);
		ordered_player[0] = player[n1-1], ordered_player[1] = player[n2-1], ordered_player[2] = player[n3-1];
		ordered_player[3] = player[n4-1], ordered_player[4] = player[n5-1], ordered_player[5] = player[n6-1];
		
		system("cls");
		print_main_header(turn, n_game);	
		
		color(14);	
		printf("Player cards\n");
		for(k = 0; k < 6; k++){
			if(ordered_player[k].color == 1)color(12);
			else color(15);
			printf("|%s%s|	", numbers[ordered_player[k].number - 1], types[ordered_player[k].type - 1]);		
		}
		color(15);
		printf("\n(1)	(2)	(3)	(4)	(5)	(6)\n");
		
		color(11);
		printf("\n\nMachine cards - ");
		//ordening machine's card
		option = 1 + rand()%2;
		order_machine_4elem(machine, option);
		for(k = 0; k < 6; k++){
			if(machine[k].color == 1) color(12);
			else color(15);
			printf("|%s%s|	", numbers[machine[k].number - 1], types[machine[k].type - 1]);		
		}
		color(15);
		printf("\n(1)	(2)	(3)	(4)	(5)	(6)\n");
		
		//start the battle
		resul_check = mosquetero_battle(ordered_player, machine, points);
		if(resul_check == 0){
			battles_1v1(ordered_player, machine, points, 6, turn);
		}
	
		print_points_header();
	
		color(14);
		printf("PLAYER %s Normal:%d Hero:%d Squire:%d Mosquetero:%d TOTAL: %d\n", DIAMOND, points[2], points[4], points[6], points[8], points[0]);
		color(11);
		printf("MACHINE %s Normal:%d Hero:%d Squire:%d Mosquetero:%d TOTAL: %d\n", DIAMOND, points[3], points[5], points[7], points[9], points[1]);
		color(15);
		
		printf("\n<Enter> to continue...");
		getchar();
		getchar();
		system("cls");
		
		turn++;
	}
	
	//deal 2 cards each/ last time
	Card player_l[2], ordered_player_l[2], machine_l[2];
	cont = 0;
	for(i = 48; i < 50 ; i++){
		player_l[cont] = unordered_cards[i];
		machine_l[cont] = unordered_cards[i+2];
		cont++;
	}
	
	print_main_header(turn, n_game);
	
	color(14);
	printf("Player cards \n");
	for(k = 0; k < 2; k++){
		if(player_l[k].color == 1) color(12);
		else color(15);
		
		printf("|%s%s|	", numbers[player_l[k].number - 1], types[player_l[k].type - 1]);		
	}
	color(15);
	printf("\n(1)	(2)\n");
	
	//ordering player's card
	printf("\nOrder the cards, separate the positions by commas(2 elems): ");
	scanf("%d, %d", &n1, &n2);
	ordered_player_l[0] = player_l[n1-1], ordered_player_l[1] = player_l[n2-1];
	system("cls");
	
	print_main_header(turn, n_game);
	
	color(14);
	printf("Player cards\n");
	for(k = 0; k < 2; k++){
		if(ordered_player_l[k].color == 1) color(12);
		else color(15);
		
		printf("|%s%s|	", numbers[ordered_player_l[k].number - 1], types[ordered_player_l[k].type - 1]);		
	}
	color(15);
	printf("\n(1)	(2)\n");
	
	color(11);
	printf("\n\nMachine cards - ");
	
	//ordering machine's card
	option = 1 + rand()%2;
	order_machine_2elem(machine_l, option);
	for(k = 0; k < 2; k++){
		if(machine_l[k].color == 1) color(12);
		else color(15);
		printf("|%s%s|	", numbers[machine_l[k].number - 1], types[machine_l[k].type - 1]);		
	}
	color(15);
	printf("\n(1)	(2)\n");

	//Last battle
	battles_1v1(ordered_player_l, machine_l, points, 2, turn);

	print_points_header();
	
	color(14);
	printf("PLAYER %s Normal:%d Hero:%d Squire:%d Mosquetero:%d TOTAL: %d\n", DIAMOND, points[2], points[4], points[6], points[8], points[0]);
	color(11);
	printf("MACHINE %s Normal:%d Hero:%d Squire:%d Mosquetero:%d TOTAL: %d\n", DIAMOND, points[3], points[5], points[7], points[9], points[1]);
	color(15);	
	
	printf("\n<Enter> to continue...");
	getchar();
	getchar();
	system("cls");
}

//order card for 4 elements
void order_machine_4elem(Card machine[6], int option){
	int i, e;
	Card elem;
	for (i = 0; i < 6; i++){
		if(machine[i].color == 0){
			if (i == 5) break;	
			for( e = (i+1); e < 6; e++){
				if (machine[e].color == 1){
					elem = machine[i];
					machine[i] = machine[e];
					machine[e] = elem;
				}
			}
		}
	}
	
	int start_r, end_r=-1, start_n=0, end_n=5;
	for (i = 0; i < 6; i++){
		if (machine[i].color == 1){
			start_r=0;
			end_r++;
			start_n = end_r + 1;
		}
	}
	
	if (end_r > 0)
		order_elems_machine(machine, start_r, end_r+1, option);	
	if (end_r <4)
		order_elems_machine(machine, start_n, end_n+1, option);	
		
	if(option == 1)
		printf("First red, from lowest to highest with respect to number\n");
	else
		printf("First red, from lowest to highest with respect to type\n");
}

//order cards for 2 elements
void order_machine_2elem(Card machine_l[2], int option){
	Card elem;
	if(machine_l[0].color != machine_l[1].color){
		if(machine_l[0].color == 0){
			elem = machine_l[0];
			machine_l[0] = machine_l[1];
			machine_l[1] = elem;
		}	
	}else{
		order_elems_machine(machine_l, 0, 2, option);	
	}
	
	if(option == 1)
		printf("First red, from lowest to highest with respect to number\n");
	else
		printf("First red, from lowest to highest with respect to type\n");
}

//order cards with respect to (number or type)
void order_elems_machine(Card machine[6], int start, int end, int option){
	int i, j;
	Card temp;
	if (option == 1){
		for (i = start+1; i < end; i++){
			for (j = start; j < end-1; j++){
				if (machine[j].number > machine[j+1].number){
					temp = machine[j];
					machine[j] = machine[j+1];
					machine[j+1] = temp;
				}
			}
		}
	}else{
		for (i = start+1; i < end; i++){
			for (j = start; j < end-1; j++){
				if (machine[j].type > machine[j+1].type){
					temp = machine[j];
					machine[j] = machine[j+1];
					machine[j+1] = temp;
				}
			}
		}	
	}
}

int mosquetero_battle(Card player[6], Card machine[6], int points[10]){
	int check_player = is_poker(player);
	int check_machine = is_poker(machine);
	
	if(check_player == 0 && check_machine == 0)
		return 0;
	
	if(check_player != 0 && check_machine != 0){
		if(check_player == 1 || check_machine == 1){
			if(check_player == 1){
				points[0] += 8;
				points[8] += 8;
			}else{
				points[1] += 8;
				points[9] += 8;	
			}	
		}else{
			if(check_player > check_machine){
				points[0] += 8;
				points[8] += 8;	
			}else{
				points[1] += 8;	
				points[9] += 8;		
			}	
		}			
	}else{
		if (check_player != 0){
			points[0] += 8;
			points[8] += 8;
		}else{
			points[1] += 8;
			points[9] += 8;	
		}
	}
	
	return 1;
}

int is_poker(Card cards[6]){
	int i, e , cont = 1, number=0;
	Card elem;
	for(i = 0; i < 3; i++){
		elem = cards[i];
		for(e = i+1; e < 6; e++){
			if(elem.number == cards[e].number){
				cont++;	
				number = elem.number;
			}
		}	
		if(cont == 4) break;
		else cont=1;
	}
	if(cont == 4) return number;
	else return 0;
}

void battles_1v1(Card player[], Card machine[], int points[10], int size, int turn){
	int i;
	for(i = 0; i < size; i++){
		if(player[i].number == machine[i].number){	
			if(player[i].color != machine[i].color){
				if(turn % 2 == 0){
					if(player[i].color == 1){
						points[0] += 2;
						points[4] += 2;
					}else{
						points[1] += 2;
						points[5] += 2;
					}
				}else{
					if(player[i].color == 0){
						points[0] += 2;
						points[4] += 2;
					}else{
						points[1] += 2;
						points[5] += 2;
					}
				}
			}
		}else{
			if(player[i].number == 1 && machine[i].number == 13){
				points[0] += 3;
				points[6] += 3;
			}else{
				if(machine[i].number == 1 && player[i].number == 13){
					points[1] += 3;
					points[7] += 3;
				}else{
					if(player[i].number > machine[i].number){
						points[0]++;
						points[2]++;
					}else{
						points[1]++;
						points[3]++;
					}
				}
			}	
		}
	}
}
