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
    int gdriver = DETECT, gmode;
    initgraph( & gdriver, & gmode, "C:\\TC\\BGI");
    int speed = 4, pexit, px, py, midx = getmaxx() / 2,
        midy = getmaxy() / 2, dir, flag = 1, i,
        pos = (getmaxx() / 2) - 2;
    float angle, xpix = getmaxx() / 2, ypix = getmaxy() - 9;
    stat p1 = {
        0,
        3
    };
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
    randomize();
    dir = random(2);
    if (dir == 1) {
        angle = M_PI / 3;
    } else {
        angle = (2 * M_PI) / 3;
    }
start:
    if (kbhit()) {
        i = getche();
        if (i == 97) {
            if (pos > 42) {
                p_left(pos);
                if (flag == 1)
                    xpix -= 5;
                bar(2, getmaxy() - 11, getmaxx() - 2, getmaxy() - 6);
            }
        } else if (i == 100) {
            if (pos < (getmaxx() - 42)) {
                p_rite(pos);
                if (flag == 1)
                    xpix += 5;
                bar(2, getmaxy() - 11, getmaxx() - 2, getmaxy() - 6);
            }
        } else if (i == 120)
            goto end;
        else if (i == 32)
            flag = 0;
        else if (i == 112) {
            settextstyle(0, 0, 6);
            settextjustify(1, 1);
            setcolor(8);
            outtextxy(midx, midy, "PAUSED");
            settextstyle(0, 0, 1);
            outtextxy(midx, midy + 30, "Press any key to continue.");
            settextjustify(2, 0);
            settextstyle(0, 0, 1);
            pexit = getche();
            if (pexit == 120)
                exit(0);
            bar(2, 20, getmaxx() - 2, getmaxy() - 6);
        } else if (i == 49)
            speed = 10;
        else if (i == 50)
            speed = 8;
        else if (i == 51)
            speed = 6;
        else if (i == 52)
            speed = 4;
        else if (i == 53)
            speed = 2;
    }
    setcolor(12);
    line(xpix - 2, ypix, xpix + 2, ypix);
    line(xpix - 2, ypix + 1, xpix + 2, ypix + 1);
    line(xpix - 2, ypix - 1, xpix + 2, ypix - 1);
    setcolor(0);
    setlinestyle(0, 0, 1);
    rectangle(xpix - 3, ypix - 3, xpix + 3, ypix + 3);
    setlinestyle(0, 0, 3);
    if (flag == 1)
        goto start;
    setcolor(15);
    xpix = xpix - (1 * cos(angle));
    ypix = ypix - (1 * sin(angle));
    delay(speed);
    if (getpixel(xpix, ypix - 5) == 8) {
        angle = 2 * M_PI - angle;
        sound(100 + random(400));
        delay(4);
        nosound();
        p1.pts = p1.pts + 50;
        bar(getmaxx() - 2, 13, getmaxx() - 121, 1);
        sprintf(points, "Points: %i", p1.pts);
        outtextxy(getmaxx() - 2, 13, points);
    }
    if (getpixel(xpix, ypix - 5) == 7) {
        angle = 2 * M_PI - angle;
        sound(100 + random(400));
        delay(4);
        nosound();
        p1.pts = p1.pts + 30;
        bar(getmaxx() - 2, 13, getmaxx() - 121, 1);
        sprintf(points, "Points: %i", p1.pts);
        outtextxy(getmaxx() - 2, 13, points);
    }
    if (getpixel(xpix, ypix - 5) == 15) {
        angle = 2 * M_PI - angle;
        sound(100 + random(400));
        delay(4);
        nosound();
        p1.pts = p1.pts + 10;
        bar(getmaxx() - 2, 13, getmaxx() - 121, 1);
        sprintf(points, "Points: %i", p1.pts);
        outtextxy(getmaxx() - 2, 13, points);
    }
    if (getpixel(xpix - 5, ypix) == 15) {
        angle = (angle + M_PI) / 2;
        sound(100 + random(400));
        delay(4);
        nosound();
    }
    if (getpixel(xpix + 5, ypix) == 15) {
        angle = 2 * angle - M_PI;
        sound(100 + random(400));
        delay(4);
        nosound();
    }
    if (getpixel((int) xpix, (int) ypix + 4) == 15) {
        angle = 2 * M_PI - angle;
        sound(100 + random(400));
        delay(4);
        nosound();
    } else if (ypix >= getmaxy() - 7) {
        if (p1.lvs > 0) {
            p1.lvs--;
            flag = 1;
            xpix = pos;
            ypix = getmaxy() - 9;
            bar(getmaxx() - 122, 13, getmaxx() - 182, 1);
            sprintf(lives, "Lives: %i", p1.lvs);
            outtextxy(getmaxx() - 122, 13, lives);
            settextjustify(1, 2);
            settextstyle(0, 0, 6);
            setcolor(8);
            sprintf(lives, "%i lives left", p1.lvs);
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
    int location, flag1 = 0;
    hs.open("highscore.txt", ios::in);
    while (hs) {
        hs.read((char * ) & temp, sizeof(temp));
        if (p1.pts >= temp.pts) {
            location = hs.tellp() - sizeof(temp);
            flag1 = 1;
        }
    }
    hs.close();
    if (flag1 != 1)
        cout << "No highscore. Better luck next time!\n ";
    else {
        cout << "Congratulations! New Highscore!";
        cout << "\nEnter your name: ";
        cin >> p1.name;
        hs1.open("highscore.txt", ios::out);
        hs1.seekp(location);
        hs1.write((char * ) & p1, sizeof(p1));
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