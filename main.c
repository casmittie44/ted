#include "editor.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void set_input_mode();
void reset_input_mode();

struct termios tattr;
struct termios saved_attributes;

int main(int argc, char** argv) {
  // Set up the input mode
  set_input_mode();

  // Set up the buffer and get things going
  puts("Welcome to ted. Press Ctrl + D to exit.");
  buffer* b = buffer_construct();
  edit_buffer(b);
  buffer_destruct(b);

  // Reset the input mode, so we don't ruin life for everyone
  reset_input_mode();
  return 0;
}

/*********************************************************************
 *This function sets the input mode of the terminal to a non-canonical
 *mode to allow us to edit and handle control sequences.
 *********************************************************************/
void set_input_mode (void)
{
  struct termios tattr;

  /* Make sure stdin is a terminal. */
  if (!isatty (STDIN_FILENO))
    {
      fprintf (stderr, "Not a terminal.\n");
      exit (EXIT_FAILURE);
    }

  /* Save the terminal attributes so we can restore them later. */
  tcgetattr (STDIN_FILENO, &saved_attributes);
  atexit (reset_input_mode);

  /* Set the funny terminal modes. */
  tcgetattr (STDIN_FILENO, &tattr);
  tattr.c_lflag &= ~(ICANON); /* Clear ICANON */
  tattr.c_cc[VMIN] = 1;
  tattr.c_cc[VTIME] = 0;
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

/****************************************************************
 *This function restores the original settings to the STD_IN
 ***************************************************************/
void reset_input_mode (void)
{
  tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}
