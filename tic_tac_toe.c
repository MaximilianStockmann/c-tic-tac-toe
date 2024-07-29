#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>

#define X_MARK 88
#define O_MARK 79

typedef struct {
  int mark; /* can be x or o */
  int cursor; /* can be 1 or 0 */
} Cell;

typedef struct {
  Cell cells[3][3];
} Board;

typedef struct {
  int x;
  int y;
} Screen_Position;

void render_board();
void init_board();
void update_cell(Board *board, int row, int col, char symbol);
void init_ncurses();
void move_cursor(int x, int y);

// have a nine by nine array
// render the array upon each input as some series of symbols
// symbols to signify marked squares, background fill to signify cursor position
// upon using one of the arrow keys change cursor location in array
int main(int argc, char *argv[])
{
  init_ncurses();
  int c; /* the character read*/
  Board *board_ptr = malloc(sizeof *board_ptr);
  Screen_Position *scrpos = malloc(sizeof *scrpos);

  scrpos->x = 0;
  scrpos->y = 0;
  init_board(board_ptr);

  // printf("%c", board_ptr->cells[0][0]);

  nodelay(stdscr, TRUE);
  int ch;
     for (;;) {
          if ((ch = getch()) == ERR) {
              /* user hasn't responded
               ...
              */
          }
          else {
              scrpos->x += 1;
              scrpos->y += 1;
              move_cursor(scrpos->x,scrpos->y);
              /* user has pressed a key ch
               ...
              */
          }
     }

  endwin();
  return EXIT_SUCCESS;
}

void render_board(Board *board) {
    for (int row = 0; row <= 2; row++)
    {
      for (int col = 0; col <= 2; col++)
      {
        putchar(board->cells[row][col].mark);
      }
      putchar(10); // LF
      clear();
    }
    refresh();
}

void init_board(Board *board) {
  for (int row = 0; row <= 2; row++) {
    for (int col = 0; col <= 2; col++) {
      update_cell(board, row, col, O_MARK);
    }
  }
}

void update_cell(Board *board, int row, int col, char symbol) {
  if (symbol == X_MARK || symbol == O_MARK) {
    board->cells[row][col].mark = symbol;
  } else {
    printf("%s\n", "Not a valid symbol");
  }
}

void init_ncurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
}

void move_cursor(int x, int y) {
  move(x, y);
  refresh();
}
