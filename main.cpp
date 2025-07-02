#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SDL2/SDL.h>
#include <cstdio>
#include <ctime>
#include <string>
#define FPS 60
#define LEFT -1
#define RIGHT 1
#define END 12
#define START -12
void display();
void ChangBGcolor();
void reshape(int, int);
void timer(int);
void drawpolygon(int, int, int);
void keyboard(int, int, int);
void movepolygon();
void generate_random();

float pos_x = 0, pos_y = 15;
int dir = 0, random_side, score = 0;

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(800, 80);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Geometry Game");

    generate_random();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutSpecialFunc(keyboard);
    glutMainLoop();

    return 0;
}

void showMessage(std::string scr) {
    const SDL_MessageBoxButtonData buttons[] = {{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Okay" /* flags, buttonid, text */ }};
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL, /* window */
        "Game Over", /* title */
        scr.c_str(), /* message */
        1, /* button quantity */
        buttons, /* buttons */
        NULL /* colorScheme */
    };

    SDL_ShowMessageBox(&messageboxdata, NULL);
}

void exit_() {
    showMessage("Your Score: " + std::to_string(score));
    exit(0);
}

void generate_random() {
    srand(time(0));
    random_side = 3 + rand() % 5;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawpolygon(3, -12, -7);
    drawpolygon(4, -6, -7);
    drawpolygon(5, 0, -7);
    drawpolygon(6, 6, -7);
    drawpolygon(7, 12, -7);
    movepolygon();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-15, 15, -15, 15);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, timer, 0);
    if(pos_y >= -8.0)
        pos_y -= 0.15;
    else {
        pos_y = 10.0;
        switch(random_side) {
        case 3 :
            if(pos_x == -12) score++;
            else exit_();
            break;
        case 4 :
            if(pos_x == -6) score++;
            else exit_();
            break;
        case 5 :
            if(pos_x == -0) score++;
            else exit_();
            break;
        case 6 :
            if(pos_x == 6) score++;
            else exit_();
            break;
        case 7 :
            if(pos_x == 12) score++;
            else exit_();
            break;
        }
        pos_x = 0;
        generate_random();
    }
}

void drawpolygon(int side, int x, int y) {
    glBegin(GL_POLYGON);
    switch(side) {
    case 3 :
        glVertex2f(x, y);
        glVertex2f(x+1.73, y-1.5);
        glVertex2f(x-1.73, y-1.5);
        break;
    case 4 :
        glVertex2f(x-1, y);
        glVertex2f(x-1, y-2);
        glVertex2f(x+1, y-2);
        glVertex2f(x+1, y);
        break;
    case 5 :
        glVertex2f(x, y);
        glVertex2f(x-1.18, y-0.41);
        glVertex2f(x-1.18, y-1.23);
        glVertex2f(x+1.18, y-1.23);
        glVertex2f(x+1.18, y-0.41);
        break;
    case 6 :
        glVertex2f(x, y);
        glVertex2f(x-1.18, y-0.41);
        glVertex2f(x-1.18, y-1.23);
        glVertex2f(x, y-1.64);
        glVertex2f(x+1.18, y-1.23);
        glVertex2f(x+1.18, y-0.41);
        break;
    case 7 :
        glVertex2f(x, y);
        glVertex2f(x-1.18, y-0.41);
        glVertex2f(x-1.38, y-1.23);
        glVertex2f(x-1.18, y-1.84);
        glVertex2f(x+1.18, y-1.84);
        glVertex2f(x+1.38, y-1.23);
        glVertex2f(x+1.18, y-0.41);
        break;
    }
    glEnd();
}

void keyboard(int key, int, int) {
    switch(key) {
    case GLUT_KEY_LEFT :
        dir = -1;
        break;
    case GLUT_KEY_RIGHT :
        dir = 1;
        break;
    }
}

void movepolygon() {
    if(dir == LEFT) pos_x = (pos_x == START ? END : pos_x + LEFT * 6), dir = 0;
    else if(dir == RIGHT) pos_x = (pos_x == END ? START : pos_x + RIGHT * 6), dir = 0;
    drawpolygon(random_side, pos_x, pos_y);
}
