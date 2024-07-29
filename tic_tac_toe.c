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
void move_cursor(Screen_Position *scrpos, int x, int y);
void move_cursor_up(Screen_Position *scrpos);
void move_cursor_down(Screen_Position *scrpos);
void move_cursor_left(Screen_Position *scrpos);
void move_cursor_right(Screen_Position *scrpos);
void handle_input(int ch, Screen_Position *scrpos, Board *board_ptr);

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
              handle_input(ch, scrpos, board_ptr);
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

void handle_input(int ch, Screen_Position *scrpos, Board *board_ptr) {
    switch (ch) {
      case KEY_UP:
          move_cursor_up(scrpos);
          break;
      case KEY_DOWN:
          move_cursor_down(scrpos);
          break;
      case KEY_LEFT:
          move_cursor_left(scrpos);
          break;
      case KEY_RIGHT:
          move_cursor_right(scrpos);
          break;
      default:
          move_cursor(scrpos, 0, 0); 
  }
}

void init_ncurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
}

void move_cursor(Screen_Position *scrpos, int y, int x) {
  scrpos->x = x;
  scrpos->y = y;
  move(scrpos->y, scrpos->x);
  refresh();
}

void move_cursor_up(Screen_Position *scrpos) {
  scrpos->y = scrpos->y - 1;
  move(scrpos->y, scrpos->x);
  refresh();
}

void move_cursor_down(Screen_Position *scrpos) {
  scrpos->y = scrpos->y + 1;
  move(scrpos->y, scrpos->x);
  refresh();
}

void move_cursor_left(Screen_Position *scrpos) {
  scrpos->x = scrpos->x - 1;
  move(scrpos->y, scrpos->x);
  refresh();
}

void move_cursor_right(Screen_Position *scrpos) {
  scrpos->x = scrpos->x + 1;
  move(scrpos->y, scrpos->x);
  refresh();
}
