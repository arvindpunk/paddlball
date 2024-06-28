#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <math.h>
#include <dos.h>
#include <stdlib.h>
#include <fstream.h>

#include "resource.h"

struct stat {
    int pts;
    int lvs;
    char name[12];
};

void main() {
    char points[15], lives[15];
    // initialize graphics library
    int gdriver = DETECT, gmode;
    initgraph( & gdriver, & gmode, "C:\\TC\\BGI");

    int speed = 4, 
        midx = getmaxx() / 2,
        midy = getmaxy() / 2, 
        dir, 
        is_ball_attached_to_paddle = 1,
        pos = (getmaxx() / 2) - 2;
    float angle, ball_x = getmaxx() / 2, ball_y = getmaxy() - 9;

    // initial plan was to have multiplayer support, lol
    stat player_1 = {
        0,
        3
    };

    // most likely the bounding box/edges
    setfillstyle(1, 0);
    setlinestyle(0, 0, 3);
    rectangle(0, 18, getmaxx(), getmaxy());
    setcolor(0);
    line(2, getmaxy(), getmaxx() - 2, getmaxy());
    setcolor(15);
    line(pos - 40, getmaxy() - 4, pos + 40, getmaxy() - 4);
    setcolor(15);
    line(2, 18, getmaxx() - 2, 18);
    setcolor(7);
    line(midx - 120, 18, midx + 120, 18);
    setcolor(8);
    line(midx - 40, 18, midx + 40, 18);
    setcolor(0);
    line(0, 16, getmaxx(), 16);

    settextjustify(2, 0);
    setcolor(15);
    outtextxy(getmaxx() - 2, 13, "Points: 0");
    outtextxy(getmaxx() - 122, 13, "Lives: 3");
death:
    // ball direction can launch either left or right
    randomize();
    dir = random(2);
    if (dir == 1) {
        angle = M_PI / 3;
    } else {
        angle = (2 * M_PI) / 3;
    }
start:
    if (kbhit()) {
        key_pressed = getche();
        if (key_pressed == 97) { // "a"
            if (pos > 42) {
                p_left(pos); // move and render paddle left
                if (is_ball_attached_to_paddle == 1)
                    ball_x -= 5;
                bar(2, getmaxy() - 11, getmaxx() - 2, getmaxy() - 6);
            }
        } else if (key_pressed == 100) { // "d"
            if (pos < (getmaxx() - 42)) {
                p_rite(pos); // move and render paddle right
                if (is_ball_attached_to_paddle == 1)
                    ball_x += 5;
                bar(2, getmaxy() - 11, getmaxx() - 2, getmaxy() - 6);
            }
        } else if (key_pressed == 120) // "x"
            goto end;
        else if (key_pressed == 32) // "space" (disconnect and launch ball from paddle)
            is_ball_attached_to_paddle = 0;
        else if (key_pressed == 112) { // "P" (pause menuy)
            settextstyle(0, 0, 6);
            settextjustify(1, 1);
            setcolor(8);
            outtextxy(midx, midy, "PAUSED");
            settextstyle(0, 0, 1);
            outtextxy(midx, midy + 30, "Press any key to continue.");
            settextjustify(2, 0);
            settextstyle(0, 0, 1);
            key_pressed = getche();
            if (key_pressed == 120) // "x"
                exit(0);
            bar(2, 20, getmaxx() - 2, getmaxy() - 6);
        } else if (key_pressed == 49) // "1" (slowest)
            speed = 10;
        else if (key_pressed == 50) // "2"
            speed = 8;
        else if (key_pressed == 51) // "3"
            speed = 6;
        else if (key_pressed == 52) // "4" (default)
            speed = 4;
        else if (key_pressed == 53) // "5" (fastest)
            speed = 2;
    }

    // ball border rendering:
    // Initially, each frame was blacked out and new frame with paddle+ball was rendered.
    // This was extremely slow and caused flickering.
    // This is an optimization technique to black out the parts around the ball (5x3 grid)
    setcolor(12);
    line(ball_x - 2, ball_y - 1, ball_x + 2, ball_y - 1);
    line(ball_x - 2, ball_y + 0, ball_x + 2, ball_y + 0);
    line(ball_x - 2, ball_y + 1, ball_x + 2, ball_y + 1);

    // ball rendering
    setcolor(0);
    setlinestyle(0, 0, 1);
    rectangle(ball_x - 3, ball_y - 3, ball_x + 3, ball_y + 3);
    setlinestyle(0, 0, 3);

    if (is_ball_attached_to_paddle == 1)
        goto start;
    setcolor(15);
    // ball movement logic
    ball_x = ball_x - (1 * cos(angle));
    ball_y = ball_y - (1 * sin(angle));
    delay(speed);
    // ball hits top bar, different color gives different score
    if (getpixel(ball_x, ball_y - 5) == 8) {
        angle = 2 * M_PI - angle;
        sound(100 + random(400));
        delay(4);
        nosound();
        player_1.pts = player_1.pts + 50;
        bar(getmaxx() - 2, 13, getmaxx() - 121, 1);
        sprintf(points, "Points: %i", player_1.pts);
        outtextxy(getmaxx() - 2, 13, points);
    }
    if (getpixel(ball_x, ball_y - 5) == 7) {
        angle = 2 * M_PI - angle;
        sound(100 + random(400));
        delay(4);
        nosound();
        player_1.pts = player_1.pts + 30;
        bar(getmaxx() - 2, 13, getmaxx() - 121, 1);
        sprintf(points, "Points: %i", player_1.pts);
        outtextxy(getmaxx() - 2, 13, points);
    }
    if (getpixel(ball_x, ball_y - 5) == 15) {
        angle = 2 * M_PI - angle;
        sound(100 + random(400));
        delay(4);
        nosound();
        player_1.pts = player_1.pts + 10;
        bar(getmaxx() - 2, 13, getmaxx() - 121, 1);
        sprintf(points, "Points: %i", player_1.pts);
        outtextxy(getmaxx() - 2, 13, points);
    }
    if (getpixel(ball_x - 5, ball_y) == 15) { // ball hit left wall
        angle = (angle + M_PI) / 2;
        sound(100 + random(400));
        delay(4);
        nosound();
    }
    if (getpixel(ball_x + 5, ball_y) == 15) { // ball hit right wall
        angle = 2 * angle - M_PI;
        sound(100 + random(400));
        delay(4);
        nosound();
    }
    if (getpixel((int) ball_x, (int) ball_y + 4) == 15) { // ball hits paddle
        angle = 2 * M_PI - angle;
        sound(100 + random(400));
        delay(4);
        nosound();
    } else if (ball_y >= getmaxy() - 7) { // ball misses paddle, player loses life/game over
        if (player_1.lvs > 0) {
            player_1.lvs--;
            is_ball_attached_to_paddle = 1;
            ball_x = pos;
            ball_y = getmaxy() - 9;
            bar(getmaxx() - 122, 13, getmaxx() - 182, 1);
            sprintf(lives, "Lives: %i", player_1.lvs);
            outtextxy(getmaxx() - 122, 13, lives);
            settextjustify(1, 2);
            settextstyle(0, 0, 6);
            setcolor(8);
            sprintf(lives, "%i lives left", player_1.lvs);
            outtextxy(midx, midy, lives);
            settextjustify(2, 0);
            settextstyle(0, 0, 1);
            setcolor(15);
            delay(1500);
            bar(2, 20, getmaxx() - 2, getmaxy() - 6);
            goto death;
        }
        settextstyle(0, 0, 4);
        settextjustify(0, 2);
        setcolor(8);
        moveto(getmaxx() / 2 - 150, getmaxy() / 2);
        outtext("GAME ");
        delay(1000);
        outtext("OVER.");
        delay(1000);
        getch();
        goto end;
    }
    goto start;
end:
    closegraph();
    fstream hs, hs1, hs2;
    stat temp;
    int location, is_highscore = 0;
    hs.open("highscore.txt", ios::in);
    while (hs) {
        hs.read((char * ) & temp, sizeof(temp));
        if (player_1.pts >= temp.pts) {
            location = hs.tellp() - sizeof(temp);
            is_highscore = 1;
        }
    }
    hs.close();
    if (is_highscore != 1)
        cout << "No highscore. Better luck next time!\n ";
    else {
        cout << "Congratulations! New Highscore!";
        cout << "\nEnter your name: ";
        cin >> player_1.name;
        hs1.open("highscore.txt", ios::out);
        hs1.seekp(location);
        hs1.write((char * ) & player_1, sizeof(player_1));
        hs1.close();
    }
    hs2.open("highscore.txt", ios::in);
    while (hs2) {
        hs2.read((char * ) & temp, sizeof(temp));
        cout << "Name : " << temp.name;
        cout << "\nPoints: " << temp.pts;
    }
    hs2.close();
    getch();
}