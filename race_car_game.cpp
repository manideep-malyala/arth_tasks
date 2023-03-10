#include <iostream>
#include <conio.h>
#include <dos.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[6][11] = {
    {'*', ' ', ' ', '*', '_', '_', '_', '_', '_', ' ', ' '},
    {'/', '±', '±', '\\', '_', '_', '_', '_', '_', '\\', ' '},
    {'|', '±', '±', '|', ' ', '_', '_', '_', ' ', ' ', '|'},
    {'\\', '_', '_', '/', ' ', ' ', ' ', ' ', ' ', ' ', '/'},
    {' ', ' ', ' ', ' ', '\\', '_', '_', '_', '/', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};

int carPos = WIN_WIDTH / 2;
int score = 0;

void gotoxy(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size)
{
    if (size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}
void drawBorder()
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            gotoxy(0 + j, i);
            cout << "±";
            gotoxy(WIN_WIDTH - j, i);
            cout << "±";
        }
    }
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        gotoxy(SCREEN_WIDTH, i);
        cout << "±";
    }
}
void genEnemy(int ind)
{
    enemyX[ind] = 17 + rand() % (33);
}
void drawEnemy(int ind)
{
    if (enemyFlag[ind])
    {
        gotoxy(enemyX[ind], enemyY[ind]);
        cout << "\033[1;31m"
             << "@@@@"
             << "\033[0m";

        gotoxy(enemyX[ind], enemyY[ind] + 1);
        cout << "\033[1;32m"
             << " ## "
             << "\033[0m";

        gotoxy(enemyX[ind], enemyY[ind] + 2);
        cout << "\033[1;33m"
             << "@@@@"
             << "\033[0m";

        gotoxy(enemyX[ind], enemyY[ind] + 3);
        cout << "\033[1;34m"
             << " ** "
             << "\033[0m";
    }
}

void eraseEnemy(int ind)
{
    if (enemyFlag[ind] == true)
    {
        gotoxy(enemyX[ind], enemyY[ind]);
        cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 1);
        cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 2);
        cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 3);
        cout << "    ";
    }
}
void resetEnemy(int ind)
{
    eraseEnemy(ind);
    enemyY[ind] = 1;
    genEnemy(ind);
}

void drawCar()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoxy(j + carPos, i + 22);
            cout << car[i][j];
        }
    }
}
void eraseCar()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoxy(j + carPos, i + 22);
            cout << " ";
        }
    }
}

int collision()
{
    if (enemyY[0] + 4 >= 23)
    {
        if (enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9)
        {
            return 1;
        }
    }
    return 0;
}
void gameover(string name, int score)
{
    system("cls");
    cout << endl;
    cout << "\033[1;31m\t\t--------------------------\033[0m" << endl;
    cout << "\033[1;33m\t\t-------- GAME OVER -------\033[0m" << endl;
    cout << "\033[1;31m\t\t--------------------------\033[0m" << endl
         << endl;
    cout << "\033[1;32m\t\tHi, " << name << "\n\t\tYour Score Is : " << score << "\033[0m" << endl;

    string feedback;
    if (score < 30)
    {
        feedback = "\n\n\033[1;31m\t\tYou Can Do Better Than That!\033[0m\n";
    }
    else if (score >= 30 && score < 50)
    {
        feedback = "\n\n\033[1;33m\t\tNice Try, Keep Practicing!\033[0m\n";
    }
    else if (score >= 50 && score < 100)
    {
        feedback = "\n\n\033[1;32m\t\tGreat Job, You're Getting Better!\033[0m\n";
    }
    else
    {
        feedback = "\n\n\033[1;35m\t\tYou're A Pro at This, Amazing Job!\033[0m\n";
    }
    cout << feedback;
    cout << "\n\033[1;34m\t        PRESS Any KEY To \033[1;32mGo BACK to MENU\033[0m";
    getch();
}

void updateScore()
{
    gotoxy(WIN_WIDTH + 7, 5);
    cout << "Score: " << score << endl;
}

void instructions()
{
    system("cls");
    cout << endl;
    cout << "\033[1;33m+----------------------------------------------------+\033[0m" << endl; // yellow border
    cout << "\033[1;33m|                      INSTRUCTIONS                  |\033[0m" << endl; // yellow border and text
    cout << "\033[1;33m+----------------------------------------------------+\033[0m" << endl; // yellow border
    cout << "\033[1;36m|                                                    |\033[0m" << endl; // cyan border

    // Centered text with a maximum of 100 characters per line and additional spacing
    cout << "\033[1;32m|          AVOID CARS BY MOVING LEFT OR RIGHT        |\033[0m\n";

    cout << "\033[1;36m|                                                    |\033[0m" << endl; // cyan border

    // Centered text with a maximum of 100 characters per line and additional spacing
    cout << "\n\033[1;35m|                PRESS 'A' TO MOVE LEFT              |\033[0m\n";
    cout << "\033[1;35m|                PRESS 'D' TO MOVE RIGHT             |\033[0m\n";

    cout << "\033[1;36m|                                                    |\033[0m" << endl; // cyan border

    // Centered text with a maximum of 100 characters per line and additional spacing
    cout << "\n\033[1;31m|                PRESS 'ESCAPE' TO EXIT              |\033[0m\n";

    cout << "\033[1;36m|                                                    |\033[0m" << endl; // cyan border

    // Centered text with a maximum of 100 characters per line and additional spacing
    cout << "\n\033[1;34m|         PRESS ANY KEY TO GO BACK TO THE MENU       |\033[0m\n";

    cout << "\033[1;36m|                                                    |\033[0m" << endl; // cyan border
    cout << "\033[1;33m+----------------------------------------------------+\033[0m" << endl; // yellow border

    getch();
}

void play()
{
    carPos = -1 + WIN_WIDTH / 2;
    score = 0;
    enemyFlag[0] = 1;
    enemyFlag[1] = 0;
    enemyY[0] = enemyY[1] = 1;
    system("cls");
    drawBorder();
    updateScore();
    genEnemy(0);
    genEnemy(1);

    gotoxy(WIN_WIDTH + 7, 2);
    cout << "\033[1;33mRACE CAR GAME\033[0m";

    gotoxy(WIN_WIDTH + 7, 12);
    cout << "\033[1;33mCONTROLS\033[0m";

    gotoxy(WIN_WIDTH + 7, 14);
    cout << "\033[1;32mA Key - LEFT\033[0m";
    gotoxy(WIN_WIDTH + 7, 15);
    cout << "\033[1;32mD Key - RIGHT\033[0m";

    string name;
    gotoxy(18, 7);
    cout << "\033[1;32mEnter Your Name : \033[0m";

    cin >> name;
    gotoxy(18, 7);
    cout << "                               ";

    gotoxy(WIN_WIDTH + 6, 4);
    cout << " Player : " << name << endl;
    gotoxy(18, 5);
    cout << "\033[1;33m       Press Any Key To Start\033[0m";

    getch();
    gotoxy(18, 5);
    cout << "                              ";

    while (1)
    {
        if (kbhit())
        {
            char ch = getch();
            if (ch == 'a' || ch == 'A')
            {
                if (carPos > 18)
                    carPos -= 4;
            }
            if (ch == 'd' || ch == 'D')
            {
                if (carPos < 50)
                    carPos += 4;
            }
            if (ch == 27)
            {
                break;
            }
        }

        drawCar();
        drawEnemy(0);
        drawEnemy(1);
        if (collision() == 1)
        {
            gameover(name, score);
            return;
        }
        Sleep(50);
        eraseCar();
        eraseEnemy(0);
        eraseEnemy(1);

        if (enemyY[0] == 10)
            if (enemyFlag[1] == 0)
                enemyFlag[1] = 1;

        if (enemyFlag[0] == 1)
            enemyY[0] += 1;

        if (enemyFlag[1] == 1)
            enemyY[1] += 1;

        if (enemyY[0] > SCREEN_HEIGHT - 4)
        {
            resetEnemy(0);
            score++;
            updateScore();
        }
        if (enemyY[1] > SCREEN_HEIGHT - 4)
        {
            resetEnemy(1);
            score++;
            updateScore();
        }
    }
}

int main()
{
    setcursor(0, 0);
    srand((unsigned)time(NULL));
    do
    {
        system("cls");

        cout << endl;
        cout << "\033[1;34m"
             << "=================================================="
             << "\033[0m" << endl; // blue border
        cout << "\033[1;34m"
             << "#                 RACE CAR GAME                  #"
             << "\033[0m" << endl; // blue border and text
        cout << "\033[1;34m"
             << "=================================================="
             << "\033[0m" << endl
             << endl; // blue border
        cout << "\033[1;32m"
             << "                   1. START GAME                  "
             << "\033[0m" << endl
             << endl; // green text
        cout << "\033[1;32m"
             << "                   2. INSTRUCTIONS                "
             << "\033[0m" << endl
             << endl; // green text
        cout << "\033[1;32m"
             << "                   3. QUIT                        "
             << "\033[0m" << endl
             << endl; // green text
        cout << "\033[1;36m"
             << "                  SELECT OPTION :                "
             << "\033[0m" << endl
             << endl;
        ; // cyan text and border
        cout << "\033[1;36m"
             << "=================================================="
             << "\033[0m" << endl; // cyan border

        char op = getche();

        if (op == '1')
            play();
        else if (op == '2')
            instructions();
        else if (op == '3')
            exit(0);

    } while (1);

    return 0;
}
