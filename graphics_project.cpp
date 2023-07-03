#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h> // For delay function

void draw_car(int x, int y) {
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);


    // Draw the car body
    rectangle(x - 30, y - 10, x + 30, y + 10);
    rectangle(x - 20, y - 20, x + 20, y + 10);
    floodfill(x, y, YELLOW);

    // Draw the windows
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    rectangle(x - 15, y - 15, x - 5, y - 5);
    floodfill(x - 10, y - 10, BLUE);
    rectangle(x + 5, y - 15, x + 15, y - 5);
    floodfill(x + 10, y - 10, BLUE);

    // Draw the wheels
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    circle(x - 20, y + 20, 10);
    floodfill(x - 20, y + 20, BLACK);
    circle(x + 20, y + 20, 10);
    floodfill(x + 20, y + 20, BLACK);
}

void draw_road() {
    setcolor(WHITE);

    // Draw the road
    rectangle(0, 300, getmaxx(), getmaxy());

    // Draw the dividing lines on the road
    for (int i = 0; i <= getmaxx(); i += 20) {
        line(i, 400, i + 10, 400);
    }
}

void draw_buildings(int offset) {
    setcolor(LIGHTGRAY);
    setfillstyle(SOLID_FILL, LIGHTGRAY);

    // Draw the buildings
    rectangle(50 - offset, 100, 150 - offset, 300);
    floodfill(100 - offset, 200, LIGHTGRAY);
    rectangle(200 - offset, 150, 300 - offset, 300);
    floodfill(250 - offset, 250, LIGHTGRAY);
    rectangle(350 - offset, 200, 450 - offset, 300);
    floodfill(400 - offset, 250, LIGHTGRAY);
    rectangle(500 - offset, 100, 600 - offset, 300);
    floodfill(550 - offset, 200, LIGHTGRAY);

    // Draw the windows
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    for (int i = 60 - offset; i <= 140 - offset; i += 30) {
        rectangle(i, 120, i + 20, 160);
        floodfill(i + 10, 140, WHITE);
    }

    for (int i = 210 - offset; i <= 290 - offset; i += 30) {
        rectangle(i, 170, i + 20, 210);
        floodfill(i + 10, 190, WHITE);
    }

    for (int i = 360 - offset; i <= 440 - offset; i += 30) {
        rectangle(i, 220, i + 20, 260);
        floodfill(i + 10, 240, WHITE);
    }

    for (int i = 510 - offset; i <= 590 - offset; i += 30) {
        rectangle(i, 120, i + 20, 160);
        floodfill(i + 10, 140, WHITE);
    }
}

void draw_sky() {
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    rectangle(0, 0, getmaxx(), 300);
    floodfill(getmaxx() / 2, 150, BLUE);

    // Draw the sun
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    circle(100, 100, 50);
    floodfill(100, 100, YELLOW);

    // Draw the clouds
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);

    // Cloud 1
    ellipse(200, 80, 0, 360, 60, 30);
    floodfill(200, 80, WHITE);

    // Cloud 2
    ellipse(350, 120, 0, 360, 80, 40);
    floodfill(350, 120, WHITE);

    // Cloud 3
    ellipse(500, 90, 0, 360, 70, 35);
    floodfill(500, 90, WHITE);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    draw_sky();
    draw_road();

    int car_x = getmaxx() / 2; // Position the car in the center of the screen
    int car_y = 350;
    int building_offset = 0;

    // Create double buffers
    int buffer1 = 0;
    int buffer2 = 1;

    setactivepage(buffer1);

    while (!kbhit()) {
        // Clear the off-screen buffer
        cleardevice();

        draw_sky();
        draw_road();
        draw_buildings(building_offset);
        draw_car(car_x, car_y);

        // Swap buffers
        setvisualpage(buffer1);
        buffer1 = buffer1 ^ buffer2;
        buffer2 = buffer1 ^ buffer2;
        buffer1 = buffer1 ^ buffer2;
        setactivepage(buffer1);

        building_offset++;
        if (building_offset > getmaxx()) {
            building_offset = 0;
        }

        delay(50); // Delay for 50 milliseconds (adjust as needed for desired speed)
    }

    getch();
    closegraph();
    return 0;
}