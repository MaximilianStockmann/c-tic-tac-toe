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

void render_board(Board *board);
void init_board();
void update_cell(Board *board, int row, int col, char symbol);
void init_ncurses();
void move_cursor(int y, int x);
void move_cursor_up();
void move_cursor_down();
void move_cursor_left();
void move_cursor_right();
void handle_input(int ch, Board *board);
void print_banner();
void game_loop(Board *board);

// have a nine by nine array
// render the array upon each input as some series of symbols
// symbols to signify marked squares, background fill to signify cursor position
// upon using one of the arrow keys change cursor location in array
int main(int argc, char *argv[])
{
  init_ncurses();
  int c; /* the character read*/
  Board *board= malloc(sizeof *board);

  int a;
  int b;
  getyx(stdscr, a, b);

  move_cursor(0, COLS/2 - 1);
  addstr("Tic-Tac-Toe");

  init_board(board);

  // makes getch() non-blocking i.e. makes it so that it always gets a single character at a time, unbuffered

  game_loop(board);

  endwin();
  return EXIT_SUCCESS;
}

void game_loop(Board *board) {
  int ch;
     for (;;) {
          if ((ch = getch()) == ERR) {
              /* user hasn't responded
               ...
              */
          }
          else {
              handle_input(ch, board);
              /* user has pressed a key ch
               ...
              */
          }
     }
}

void render_board(Board *board) {
    int CURSOR_X;
    int CURSOR_Y;

    getyx(stdscr, CURSOR_Y, CURSOR_X);

    for (int row = 0; row <= 2; row++)
    {
      for (int col = 0; col <= 2; col++)
      {
        move_cursor(CURSOR_Y + col, CURSOR_X + row);
        addch(board->cells[row][col].mark);
      }
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

void handle_input(int ch, Board *board) {
    switch (ch) {
      case KEY_UP:
          move_cursor_up();
          break;
      case KEY_DOWN:
          move_cursor_down();
          break;
      case KEY_LEFT:
          move_cursor_left();
          break;
      case KEY_RIGHT:
          move_cursor_right();
          break;
      default:
          render_board(board);
  }
}

void init_ncurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
  nodelay(stdscr, TRUE);
}

void move_cursor(int y, int x) {
  move(y, x);
  refresh();
}

void move_cursor_up() {
  int CURSOR_Y;
  int CURSOR_X;
  getyx(stdscr, CURSOR_Y, CURSOR_X);

  move_cursor(CURSOR_Y - 1, CURSOR_X);
}

void move_cursor_down() {
  int CURSOR_Y;
  int CURSOR_X;
  getyx(stdscr, CURSOR_Y, CURSOR_X);

  move_cursor(CURSOR_Y + 1, CURSOR_X);
}

void move_cursor_left() {
  int CURSOR_Y;
  int CURSOR_X;
  getyx(stdscr, CURSOR_Y, CURSOR_X);

  move_cursor(CURSOR_Y, CURSOR_X - 1);
}

void move_cursor_right() {
  int CURSOR_Y;
  int CURSOR_X;
  getyx(stdscr, CURSOR_Y, CURSOR_X);

  move_cursor(CURSOR_Y, CURSOR_X + 1);
}
