#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//one square of the minesweeper board
typedef struct {
	int mine;
	bool visible;
	bool marked;
} minesq;

//minesweeper board
typedef struct {
	minesq* sqarray;
	int width;
	int rows;
	int mines;
} minebd;

//prototypes
minebd* minebd_dim (int width, int height, int mines);
void minebd_init (minebd* board);
void minebd_disp (minebd* board);

void minebd_set_sqmine (minebd* board, int x, int y, int value);
void minebd_set_sqvisible (minebd* board, int x, int y, bool value);
void minebd_set_sqmarked (minebd* board, int x, int y, bool value);
void minebd_setsq (minebd* board, int x, int y, minesq value);
int minebd_get_sqmine (minebd* board, int x, int y);
bool minebd_get_sqvisible (minebd* board, int x, int y);
bool minebd_get_sqmarked (minebd* board, int x, int y);
minesq minebd_getsq (minebd* board, int x, int y);

//main
int main () {
	minebd* board;
	board = minebd_dim(10,10,21);
	minebd_init(board);
	minebd_disp(board);
	return 0;
}

//create board
minebd* minebd_dim (int width, int height, int mines) {
	minebd* board;
	board = (minebd*) malloc(sizeof(minebd));
	board->sqarray = (minesq*) malloc(width*height*sizeof(minesq));
	board->width = width;
	board->rows = height;
	board->mines = mines;
	return board;
}

//initialize board
void minebd_init (minebd* board) {
	int i, j;
	int m = 0;
	srand(time(NULL));

	for (i=0;i<board->rows;i++) {
		for (j=0;j<board->width;j++) {
			minebd_set_sqmine(board,j,i,0);
			minebd_set_sqvisible(board,j,i,false);
			minebd_set_sqmarked(board,j,i,false);
		}
	}

	while (m<board->mines) {
		int x, y;
		x = rand() % board->width;
		y = rand() % board->rows;
		if (minebd_get_sqmine(board,x,y) != 9) {
			minebd_set_sqmine(board,x,y,9);
			m += 1;
		}
	}

	for (i=0;i<board->rows;i++) {
		for (j=0;j<board->width;j++) {
			if (minebd_get_sqmine(board,j,i) != 9) {
				int c = 0;
				if (minebd_get_sqmine(board,j+1	,i+1 ) == 9) {c += 1;}
				if (minebd_get_sqmine(board,j+1	,i	 ) == 9) {c += 1;}
				if (minebd_get_sqmine(board,j+1	,i-1 ) == 9) {c += 1;}
				if (minebd_get_sqmine(board,j-1	,i+1 ) == 9) {c += 1;}
				if (minebd_get_sqmine(board,j-1	,i	 ) == 9) {c += 1;}
				if (minebd_get_sqmine(board,j-1	,i-1 ) == 9) {c += 1;}
				if (minebd_get_sqmine(board,j	,i+1 ) == 9) {c += 1;}
				if (minebd_get_sqmine(board,j	,i-1 ) == 9) {c += 1;}
				minebd_set_sqmine(board,j,i,c);
			}
		}
	}
}

//display without fog
void minebd_disp (minebd* board) {
	int i, j;
	for (i=0;i<board->rows;i++) {
		for (j=0;j<board->width;j++) {
			printf("%d",minebd_get_sqmine(board,j,i));
		}
		printf("\n");
	}
}

//wrap board like array
void minebd_set_sqmine (minebd* board, int x, int y, int value) {
	board->sqarray[y*board->width+x].mine = value;
}

void minebd_set_sqvisible (minebd* board, int x, int y, bool value) {
	board->sqarray[y*board->width+x].visible = value;
}

void minebd_set_sqmarked (minebd* board, int x, int y, bool value) {
	board->sqarray[y*board->width+x].marked = value;
}

/*
void minebd_setsq (minebd* board, int x, int y, minesq value) {
	board->sqarray[y*board->width+x] = value;
}
*/

int minebd_get_sqmine (minebd* board, int x, int y) {
	return board->sqarray[y*board->width+x]->mine;
}

bool minebd_get_sqvisible (minebd* board, int x, int y) {
	return board->sqarray[y*board->width+x].visible;
}

bool minebd_get_sqmarked (minebd* board, int x, int y) {
	return board->sqarray[y*board->width+x].marked;
}

/*
minesq minebd_getsq (minebd* board, int x, int y) {
	return board->sqarray[y*board->width+x];
}
*/