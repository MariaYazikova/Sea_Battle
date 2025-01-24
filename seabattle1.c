#include<stdio.h>
#include <stdbool.h>
#define size 10

void print_field(int field[size][size]) //field output 
{
	printf("  ");
	for (int i = 0; i < size; i++) {
		printf("%d ", i);
	}
	printf("\n");
	for (int i = 0; i < size; i++) {
		printf("%d ", i);
		for (int j = 0; j < size; j++) {
			printf("%d ", field[i][j]);
		}
		printf("\n");
	}
	printf("\n");

}

bool empty_neighbors(int field[size][size], int str, int col, int sizeship, int direction) //checking for empty cells around the ship space and for ship space
{
	if (direction == 1) {
		for (int i = -1; i <= sizeship; i++) {
			for (int j = -1; j <= 1; j++) {
				int newstr = str + i;
				int newcol = col + j;
				if (newstr < 0 || newstr >= size || newcol < 0 || newcol >= size) {
					continue;
				}
				if (field[newstr][newcol] != 0) {
					return false;
				}
			}
		}
		return true;
	}
	else if (direction == 0) {
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= sizeship; j++) {
				int newstr = str + i;
				int newcol = col + j;
				if (newstr < 0 || newstr >= size || newcol < 0 || newcol >= size) {
					continue;
				}
				if (field[newstr][newcol] != 0) {
					return false;
				}
			}
		}
		return true;
	}
}

void place_ship(int field[size][size], int sizeship) //ship placement
{
	int str, col;
	printf("Enter the coordinates of a ship of size %d: ", sizeship);
	scanf_s("%d %d", &str, &col);
	getchar();
	if (str < 0 || str >= size || col < 0 || col >= size) {
		printf("You cannot set such coordinates. Try again.\n");
		place_ship(field, sizeship);
		return;
	}

	int dir;
	printf("Select the direction of the ship. 0 - horizontal, 1 - vertical: ");
	scanf_s("%d", &dir);
	getchar();
	if (dir != 0 && dir != 1) {
		printf("You cannot set such direction. Try again.\n");
		place_ship(field, sizeship);
		return;
	}

	if (!empty_neighbors(field, str, col, sizeship, dir)) {
		printf("Unable to place the ship. The neighbors are not empty. Try again.\n");
		place_ship(field, sizeship);
		return;
	}

	for (int i = 0; i < sizeship; i++) {
		if ((dir == 0 && col + i >= size) || (dir == 1 && str + i >= size)) {
			printf("Unable to place the ship. Try again.\n");
			place_ship(field, sizeship);
			return;
		}
		else {
			field[str + (dir == 0 ? 0 : i)][col + (dir == 1 ? 0 : i)] = 1;
		}
	}
}

bool shot(int opponent_field[size][size], int statistics_field[size][size], int str, int col) //making a shot
{
	if (str < 0 || str >= size || col < 0 || col >= size) {
		printf("You can't shoot here. Try again. \n");
		return false;
	}
	if (opponent_field[str][col] == 1) {
		printf("You hit the ship!\n");
		opponent_field[str][col] = 2;
		statistics_field[str][col] = 2;
	}
	else if (opponent_field[str][col] != 1) {
		printf("Miss.\n");
		statistics_field[str][col] = 1;
		return false;
	}
	return true;
}

bool winner(int field[size][size]) //checking for winner
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (field[i][j] == 1) {
				return false;
			}
		}
	}
	return true;
}

int main()
{
	int firfield[size][size] = { 0 };
	int secfield[size][size] = { 0 };
	int opponents_field_for_1[size][size] = { 0 };
	int opponents_field_for_2[size][size] = { 0 };

	printf("Welcome to sea battle! \n"
		"Rules for placing ships: \n"
		"You specify the coordinate of the first"
		"cell of the ship with two digits from 0 to 9 "
		"separated by a space, \nwhere the first digit"
		"is the row number, the second digit is the column number."
		"\nThen you set the direction. \nIf the ship's direction is horizontal"
		"- the first ship block is on the left, \n"
		"the remaining ones are automatically placed to the right. "
		"\nIf the ship's direction is vertical - the first ship block is on top, "
		"the remaining ones are automatically placed down. \nYou can place a ship only "
		"if all the cells around it and for it are free. \nYou cannot place a ship if "
		"it is out of bounds. \nGood game!");
	printf("\n\n");

	printf("Player 1 arrange the ships.\n");
	place_ship(firfield, 4); //fill the first field with ships
	print_field(firfield);
	place_ship(firfield, 3);
	print_field(firfield);
	place_ship(firfield, 3);
	print_field(firfield);
	place_ship(firfield, 2);
	print_field(firfield);
	place_ship(firfield, 2);
	print_field(firfield);
	place_ship(firfield, 2);
	print_field(firfield);
	place_ship(firfield, 1);
	print_field(firfield);
	place_ship(firfield, 1);
	print_field(firfield);
	place_ship(firfield, 1);
	print_field(firfield);
	place_ship(firfield, 1);
	printf("The field of player 1:\n");
	print_field(firfield);
	printf("The opponent's field:\n");
	print_field(opponents_field_for_1);

	printf("\n");

	printf("Player 2 arrange the ships.\n");
	place_ship(secfield, 4); //fill the second field with ships
	print_field(secfield);
	place_ship(secfield, 3);
	print_field(secfield);
	place_ship(secfield, 3);
	print_field(secfield);
	place_ship(secfield, 2);
	print_field(secfield);
	place_ship(secfield, 2);
	print_field(secfield);
	place_ship(secfield, 2);
	print_field(secfield);
	place_ship(secfield, 1);
	print_field(secfield);
	place_ship(secfield, 1);
	print_field(secfield);
	place_ship(secfield, 1);
	print_field(secfield);
	place_ship(secfield, 1);
	printf("The field of player 2:\n");
	print_field(secfield);
	printf("The opponent's field:\n");
	print_field(opponents_field_for_2);

	int currplayer = 1;

	while (1) {
		int str, col;
		printf("Player %d enter shot coordinates: ", currplayer);
		scanf_s("%d %d", &str, &col);
		if (shot(currplayer == 1 ? secfield : firfield, currplayer == 1 ? opponents_field_for_1 : opponents_field_for_2, str, col)) {
			print_field(currplayer == 1 ? opponents_field_for_1 : opponents_field_for_2);
			if (winner(currplayer == 1 ? secfield : firfield)) {
				printf("Player %d is winner!\n", currplayer);
				break;
			}
		}
		else {
			print_field(currplayer == 1 ? opponents_field_for_1 : opponents_field_for_2);
			currplayer = (currplayer == 1) ? 2 : 1;
		}
	}
	return 0;

}