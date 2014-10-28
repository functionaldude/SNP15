
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <pthread.h>
#include <string.h>
#include <math.h>

#define BALL "o"
#define PLAYER1 "\\"
#define PLAYER2 "|"
#define PLAYER3 "/"
#define COMPUTER1 "/"
#define COMPUTER2 "|"
#define COMPUTER3 "\\"
#define WIN_MSG "YOU WIN :)"
#define LOOSE_MSG "YOU LOOSE -.-"
#define DELAY 30000
#define INFO_HEIGHT 2
#define LOW_SPEED 0.1
#define MID_SPEED 0.5
#define HIGH_SPEED 1
#define MIN_TERM_HEIGHT 10
#define MIN_TERM_WIDTH 30

typedef enum
{NONE,QUIT,WIN,LOOSE} Result;

// Screen position
typedef struct
{
  unsigned x,y;
} Position;

// Ball position
typedef struct
{
  double x,y;
  double x_d,y_d;
} Ball;

static Ball ball = {.x_d = MID_SPEED, .y_d = MID_SPEED};
static Position player;
static Position computer;
static Position field_size;
static Position term_size;

WINDOW *info;
WINDOW *field;

static bool gameover = false;

void draw_window(WINDOW* screen, char* title, bool bottom) {
  int x, y, i;
  getmaxyx(screen, y, x);
  
  // corners
  mvwprintw(screen, 0, 0, "+");
  mvwprintw(screen, 0, x - 1, "+");
  
  // sides
  for (i = 1; i < (y - 1); i++) {
    mvwprintw(screen, i, 0, "|");
    mvwprintw(screen, i, x - 1, "|");
  }
  
  // top
  for (i = 1; i < (x - 1); i++) {
    mvwprintw(screen, 0, i, "-");
  }
  
  // bottom window
  if (bottom)
  {
    // bottom corners
    mvwprintw(screen, y - 1, 0, "+");
    mvwprintw(screen, y - 1, x - 1, "+");
    
    // bottom line
    for (i = 1; i < (x - 1); i++)
    {
      mvwprintw(screen, y - 1, i, "-");
    }
  }
  else
  {
    mvwprintw(screen, y-1, 0, "|");
    mvwprintw(screen, y-1, x - 1, "|");
  }
  
  // title
  i = (x- strlen(title)) / 2;
  mvwprintw(screen, 0, i, title);
}

void check_term_size()
{
  int x,y;
  char message[9];
  while (getmaxyx(stdscr, y, x) &&
         (y < MIN_TERM_HEIGHT ||
          x < MIN_TERM_WIDTH))
  {
    wclear(info);
    
    sprintf(message, "min: %dx%d",MIN_TERM_WIDTH, MIN_TERM_HEIGHT);
    draw_window(info,"Size", false);
    mvwprintw(info, 1, 1, message);
    wrefresh(info);
    
    getch();
  }
}

void handle_window_resizing()
{
  Position act_term_size;
  // stdscr is global variable from ncurses library for main screen
  getmaxyx(stdscr, act_term_size.y, act_term_size.x);

  if (act_term_size.y != term_size.y || act_term_size.x != term_size.x)
  {
    check_term_size();
    
    term_size.x = act_term_size.x;
    term_size.y = act_term_size.y;
    
    computer.x = term_size.x-2;
    
    wresize(info, INFO_HEIGHT, term_size.x);
    wresize(field, term_size.y - INFO_HEIGHT, term_size.x);
    
    wclear(stdscr);
  }
}

bool inside_borders(unsigned y)
{
  if (y-1 >= 1 && y+1 < field_size.y - 1)
    return true;
  return false;
}

void draw_player()
{
  mvwprintw(field,player.y-1,player.x,PLAYER1);
  mvwprintw(field,player.y,player.x,PLAYER2);
  mvwprintw(field,player.y+1,player.x,PLAYER3);
}

void draw_computer()
{
  mvwprintw(field,computer.y-1,computer.x,COMPUTER1);
  mvwprintw(field,computer.y,computer.x,COMPUTER2);
  mvwprintw(field,computer.y+1,computer.x,COMPUTER3);
}

double new_edge_speed(double speed)
{
  bool pos = speed > 0;
  
  if (abs(speed) == LOW_SPEED)
    speed = HIGH_SPEED;
  else if (abs(speed) == HIGH_SPEED)
    speed = LOW_SPEED;
  else
  {
    srand(time(NULL));
    if (rand() % 2)
      speed = HIGH_SPEED;
    else
      speed = LOW_SPEED;
  }
  
  if (pos)
    speed *= -1;
  
  return speed;
}

Ball next_move()
{
    Ball new_ball = ball;
    new_ball.x += new_ball.x_d;
    new_ball.y += new_ball.y_d;
    return new_ball;
}


/**
 * Runs the game.
 */
Result gameplay() {
  Result result = NONE;
  Ball new_ball;
  bool collision = false;
  int round = 2;
  char round_msg[28];
  
  while(!gameover)
  {
    handle_window_resizing();
    
    // react to player input
    
    if (// TODO: quit)
    {
      gameover = true;
      result = QUIT;
    }
    if (// TODO: pause)
      continue;
    
    if (//TODO: up && inside_borders(player.y + 1))
    {
      player.y++;
    }
    if (// TODO: down && inside_borders(player.y - 1))
    {
      player.y--;
    }
    
    // react to computer AI
    if (// TODO: up && inside_borders(computer.y + 1))
      computer.y++;
    if (// TODO: down && inside_borders(computer.y - 1))
      computer.y--;
    
    getmaxyx(field, field_size.y, field_size.x);

    // collision detection
    
    new_ball = next_move();
    int new_x = (int)new_ball.x;
    int new_y = (int)new_ball.y;
    
    // ball hits player or computer
    
    // left side
    if ((new_x == player.x && new_y == player.y - 1) ||
        (new_x == computer.x && new_y == computer.y - 1))
    {
        new_ball.y_d = new_edge_speed(new_ball.y_d);
        new_ball.x_d *= -1;
        collision = true;
        round++;
    }
    // middle
    else if ((new_x == player.x && new_y == player.y) ||
        (new_x == computer.x && new_y == computer.y))
    {
        int pos = new_ball.y_d > 0;
        new_ball.y_d = MID_SPEED;
        if(pos)
          new_ball.y_d *= -1;
        new_ball.x_d *= -1;
        collision = true;
        round++;
    }
    // right side
    else if ((new_x == player.x && new_y == player.y + 1) ||
        (new_x == computer.x && new_y == computer.y + 1))
    {
        new_ball.y_d = new_edge_speed(new_ball.y_d);
        new_ball.x_d *= -1;
        collision = true;
        round++;
    }
    // player failed
    else if (new_x <= player.x)
    {
      gameover = true;
      collision = true;
      result = LOOSE;
    }
    // computer failed
    else if(new_x >= computer.x)
    {
      gameover = true;
      collision = true;
      result = WIN;
    }
    // bottom and top borders
    else if (new_y >= field_size.y -1 ||
             new_y <= 0)
    {
      new_ball.y_d *= -1;
      collision = true;
    }
    
    // draw new window content

    wclear(info);
    wclear(field);
    
    draw_window(info,"Info", false);
    sprintf(round_msg, "round: %d - next: %s",round/2, round%2?"Player":"Computer");
    mvwprintw(info,1,2,round_msg);
    
    
    draw_window(field,"Pong", true);
    
    // only draw new position if no collision occured
    if (collision && !gameover)
      mvwprintw(field,ball.y,ball.x,BALL);
    else
      mvwprintw(field,new_ball.y,new_ball.x,BALL);
    
    draw_player();
    draw_computer();
    
    wrefresh(info);
    wrefresh(field);
    
    // set new ball position
    
    ball = new_ball;
    collision = false;
    
    usleep(DELAY);
  }
  
  return result;
}

/**
 * TODO: write user input method
 *
 * take user unput through getchar()
 * this method is BLOCKING
 * share user commands with gameplay
 * be threadsafe ;)
 * 
 * Mapping:
 * 'l': player up
 * 'j': player down
 * 'b': pause
 * 'q': quit
 *
 * ...also make sure this thread terminates when quitting
 */

/**
 * TODO: write ai-computer input method
 * share ai commands with gameplay
 * be threadsafe ;)
 *
 * You can use:
 *
 * while (!gameover)
 * {
 *   if (computer.y < ball.y && inside_borders(computer.y + 1))
 *   {
 *     // computer up
 *   }
 *   else if (computer.y > ball.y && inside_borders(computer.y - 1))
 *   {
 *     // computer down
 *   }
 *   else
 *   {
 *     // clear computer commands
 *   }
 *   usleep(DELAY);
 * }
 */

int main(int argc, char* argv[]) {
  Result result = NONE;
  
  // init ncurses
  initscr();
  noecho();
  curs_set(false);
  
  // init screen and windows
  getmaxyx(stdscr, term_size.y, term_size.x);
  
  info = newwin(INFO_HEIGHT, term_size.x, 0, 0);
  field = newwin(term_size.y - INFO_HEIGHT, term_size.x, INFO_HEIGHT, 0);
  
  check_term_size();
  
  // init player positions
  player.x = 1;
  player.y = term_size.y/2;
  computer.x = term_size.x-2;
  computer.y = term_size.y/2;
  ball.x = term_size.x/2;
  ball.y = term_size.y/2;
  
  // TODO: create user input and ai-computer threads
    
  // play the game
  result = gameplay();
  
  // print messages
  int pos_y = field_size.y/2;
  if (result == WIN)
  {
    int pos_x = (field_size.x-strlen(WIN_MSG))/2;
    mvwprintw(field,pos_y,pos_x,WIN_MSG);
  }
  else if (result == LOOSE)
  {
    int pos_x = (field_size.x-strlen(LOOSE_MSG))/2;
    mvwprintw(field,pos_y,pos_x,LOOSE_MSG);
  }
  
  wrefresh(info);
  wrefresh(field);
  
  // TODO: cleanup
  
  delwin(field);
  delwin(info);
  
  endwin();
  
  return err;
}
