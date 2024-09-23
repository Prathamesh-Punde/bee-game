#include <stdio.h>
#include <conio.h>
#include <graphics.h>

int score = 0;
int live = 1;

void start();
int logic(int bird_x, int bird_y, int pole_x[], int pole_y[], int gap[], int numPoles);
int main();

void drawBird(int *bird_x, int *bird_y) {
    setcolor(WHITE);
    circle(*bird_x, *bird_y, 10);
    setfillstyle(1, YELLOW);
    floodfill(*bird_x, *bird_y, WHITE);
    *bird_y += 7; // Simulate gravity
}

void drawPole(int width, int pole_x[], int pole_y[], int gap[], int numPoles) {
    for (int i = 0; i < numPoles; i++) {
        setcolor(3);
        rectangle(pole_x[i], 0, pole_x[i] + width, pole_y[i]);
        setfillstyle(4, 3);
        floodfill(pole_x[i] + 3, pole_y[i] - 2, 3);
        rectangle(pole_x[i], pole_y[i] + gap[i], pole_x[i] + width, getmaxy());
        floodfill(pole_x[i] + 3, pole_y[i] + gap[i] + 3, 3);
        pole_x[i] -= 18; // Move poles leftward
    }
}

void start() {
    int bird_x = 100;
    int bird_y = 300;
    int numPoles = 4; // Number of obstacles
    int pole_x[4] = {400, 600, 800, 1000};
    int pole_y[4] = {300, 250, 350, 280};
    int gap[4] = {75, 100, 90, 80};
    int width = 40;

    int gd = DETECT, gm;
    char driver[] = "C:\\Turboc3\\BGI"; // Update the path as necessary

    initgraph(&gd, &gm, driver);

    int ch;

    while (live == 1) {
        if (kbhit()) {
            ch = getch();
            if (ch == 32) { // Spacebar key (ASCII value 32) for flap
                bird_y -= 35; // Flap height
            }
        }

        if (logic(bird_x, bird_y, pole_x, pole_y, gap, numPoles) == 0) {
            cleardevice();
            setcolor(RED);
            settextstyle(4, HORIZ_DIR, 2);
            outtextxy(getmaxx() / 2 - 100, getmaxy() / 2 - 25, "Game Over");
            outtextxy(getmaxx() / 2 - 150, getmaxy() / 2 + 25, "Press 'y' to play again or any other key to exit.");
            ch = getch();
            if (ch == 'y') {
                live = 1;
                score = 0;
                bird_x = 100;
                bird_y = 300;
                for (int i = 0; i < numPoles; i++) {
                    pole_x[i] = 400 + i * 200;
                    pole_y[i] = rand() % 150 + 100;
                }
            } else {
                live = 0;
                break;
            }
        }

        score++;

        char str[100];
        sprintf(str, "Score: %d", score);
        outtextxy(getmaxx() - 100, 5, str);

        drawPole(width, pole_x, pole_y, gap, numPoles);
        drawBird(&bird_x, &bird_y);

        for (int i = 0; i < numPoles; i++) {
            if (pole_x[i] < 0) {
                pole_x[i] = getmaxx() + 300; // Move obstacles to the right edge
                pole_y[i] = rand() % 150 + 100;
            }
        }

        if (bird_y >= getmaxy()) {
            cleardevice();
            setcolor(RED);
            settextstyle(1, HORIZ_DIR, 1);
            outtextxy(getmaxx() / 2 - 100, getmaxy() / 2 - 25, "Game Over");
            outtextxy(getmaxx() / 2 - 150, getmaxy() / 2 + 25, "Press 'y' to play again or any other key to exit.");
            ch = getch();
            if (ch == 'y') {
                live = 1;
                score = 0;
                bird_x = 100;
                bird_y = 300;
                for (int i = 0; i < numPoles; i++) {
                    pole_x[i] = 400 + i * 200;
                    pole_y[i] = rand() % 150 + 100;
                }
            } else {
                live = 0;
                break;
            }
        }

        delay(90);
        cleardevice();
    }

    getch();
    closegraph();
    main();
}

int logic(int bird_x, int bird_y, int pole_x[], int pole_y[], int gap[], int numPoles) {
    for (int i = 0; i < numPoles; i++) {
        if (bird_x >= pole_x[i] && bird_x <= pole_x[i] + 40) {
            if (bird_y < pole_y[i] || bird_y > pole_y[i] + gap[i]) {
                return 0; // Collision detected
            }
        }
    }
    return 1; // No collision
}

int main() {
    start();
    return 0;
}
