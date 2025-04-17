#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#define BALL_SYMBOL "O"
#define BORDER "#"
#define PADDLE "||"
#define NUM_BUMPERS 2
#define SLEEP_TIME 20000

struct Ball 
{
    int px, py, dx, dy;
};

struct Paddle 
{
    int px, py, length;
};

int main(void) 
{
    // initialization
    int hits = 0, misses = 0, best = 0, streak = 0, frame = 0;
    int score1 = 0, score2 = 0;
    int quit = 0, max_y, max_x;
    
    struct Ball ball;
    struct Paddle paddle1, paddle2;
    int bumper_y[NUM_BUMPERS] = {10, 15};
    int bumper_x = max_x / 2; // set this once before starting the loop

    system("clear");
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    nodelay(stdscr, 1);
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);  //paddle color
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); //ball color 
    init_pair(3, COLOR_GREEN, COLOR_BLACK); //border color 
    init_pair(4, COLOR_RED, COLOR_BLACK); //bumper  color 
    getmaxyx(stdscr, max_y, max_x);

    //paddle 1
    paddle1.length = 6;
    paddle1.py = (max_y / 2) - (paddle1.length / 2);
    paddle1.px = max_x - 3;

    //paddle 2
    paddle2.length = 6;
    paddle2.py = (max_y / 2) - (paddle2.length / 2);
    paddle2.px = 2; //left side of screen 

    // game logic
    while (!quit) 
    {
        // drawing
        getmaxyx(stdscr, max_y, max_x);
        clear();

        mvprintw(0, 0,"Hits: %d     Misses: %d     Streak: %d     Best: %d     Time: %d", hits, misses, streak, best, frame / 50);  // draw stats
        
        attron(COLOR_PAIR(3));
        for (int i = 0; i < max_x; i++)  // draw top borders
        { 
            mvprintw(1, i, BORDER);
            mvprintw(max_y - 1, i, BORDER);
        }
        for (int i = 1; i < max_y; i++) // draw side border
        {  
            mvprintw(i, 0, BORDER);
            mvprint(i, max_x -1, BORDER);
        }
        attroff(COLOR_PAIR(3));

        attron(COLOR_PAIR(1));
        for (int i = 0; i < paddle1.length; i++) 
        {
            mvprintw(paddle1.py + i, paddle1.px, PADDLE);  // draw paddle1
        }
        for (int i = 0; i < paddle2.length; i++) 
        {
            mvprintw(paddle2.py + i, paddle2.px, PADDLE);  // draw paddle2
        }
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(2));
        mvprintw(ball.py, ball.px, BALL_SYMBOL);  // draw ball
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(4)); //draw bumpers
        for (int i = 0; i < NUM_BUMPERS; i++) 
        {
            mvprintw(bumper_y[i], bumper_x, "X");
        }
        attroff(COLOR_PAIR(4));

        // ball collisions
        if ((ball.py + ball.dy) < 2 || (ball.py + ball.dy) > max_y - 2)
        {
            ball.dy *= -1;
        }
        
        if ((ball.px + ball.dx == paddle1.px + 2) && (ball.py + ball.dy >= paddle1.py) && (ball.py + ball.dy <= paddle1.py + paddle1.length)) 
        {
            ball.dx *= -1;
            score1++;
            streak++;
            if (streak > best)
            {
                best = streak;
            } 
        }
        
        if ((ball.px + ball.dx == paddle2.px) && (ball.py + ball.dy >= paddle2.py) && (ball.py + ball.dy <= paddle2.py + paddle2.length)) 
        {
            ball.dx *= -1;
            score2++;
            streak++;
            if (streak > best)
            {
                best = streak;
            } 
        }
        
        for (int i = 0; i < NUM_BUMPERS; i++) 
        {
            if ((ball.px + ball.dx == bumper_x) && (ball.py + ball.dy == bumper_y[i])) 
            {
                ball.dx *= -1;
                break;
            }
        }

        // ball out of bounds
        if (ball.px < 1) 
        {
            score2++; //point to p2
            streak = 0;
            ball.px = max_x / 2;
            ball.py = max_y / 2;
            ball.dx = (rand() & 1) ? 1 : -1;
            ball.dy = (rand() & 1) ? 1 : -1;
        } 
        else if (ball.px > max_x - 2) 
        {
            score1++; //point to p1
            streak = 0;
            ball.px = max_x / 2;
            ball.py = max_y / 2;
            ball.dx = (rand() & 1) ? 1 : -1;
            ball.dy = (rand() & 1) ? 1 : -1;
        }

        if (frame % 4 == 0) //move the ball
        {
            ball.py += ball.dy;
            ball.px += ball.dx;
        }

        // input
        switch (getch()) 
        {
            case 'i':  //paddle1 up 
                if (paddle1.py - 1 > 1) paddle1.py -= 1;
                break;

            case 'k': //paddle1 down
                if ((paddle1.py + paddle1.length) + 1 < max_y) paddle1.py += 1;
                break;
            
            case 'w': //paddle2 up
                if (paddle2.py - 1 > 1) paddle2.py -= 1;
                break;

            case 's': //paddle2 down
                if ((paddle2.py + paddle2.length) + 1 < max_y) paddle2.py += 1;
                break;
        
            case 'q':
                quit = 1;
                break;
        }
        frame++;
        usleep(SLEEP_TIME);
    }

    // exit
    endwin();
    system("clear");
    return 0;
}
