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

void render_board();
void init_board();

// have a nine by nine array
// render the array upon each input as some series of symbols
// symbols to signify marked squares, background fill to signify cursor position
// upon using one of the arrow keys change cursor location in array
int main(int argc, char *argv[])
{
  int c; /* the character read*/
  Board *board_ptr = malloc(sizeof *board_ptr);

  init_board(board_ptr);

  // printf("%c", board_ptr->cells[0][0]);

  while ((c = getchar()) != EOF)
  {
    render_board(board_ptr);
  }

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
      board->cells[row][col].mark = X_MARK;
    }
  }
}
