#include <easyx.h>
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include <Mmsystem.h>
#pragma comment ( lib, "Winmm.lib" )

IMAGE bk, name, Plane[2], Plane12, bullet, bullet1, ene, pause, boom[2], lose, boss1, boss12, boss2, boss22, boss3, boss32, boss4, boss42, bossHP, HP, play, play1, freeze, blood, blood1, stop, next, grade[4], htp, rules;
char c;
MOUSEMSG m;
int g1 = 0, g2 = 0;
struct plane
{
    int blood = 5;
    int x;
    int y;
    boolean isDie;
    int fire = 1;
    boolean isFreeze = false;
}gamer[2];
plane enemy[60];
int distance(int x1, int y1, int x2, int y2)
{
    long int dis;
    dis = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    return dis;
}

struct value
{
    int x;
    int y = 0;
    int kind;
    boolean isDie = true;
}v[10];
void creatvalue() {
    for (int i = 0; i < 10; i++) {
        if (v[i].isDie) {
            v[i].y = 0;
            v[i].x = rand() % 600;
            v[i].kind = rand() % 2;
            v[i].isDie = false;
            break;
        }
    }
}
void movevalue() {
    for (int i = 0; i < 10; i++) {
        if (!v[i].isDie) {
            v[i].y += 10;
        }
        if (v[i].y >= 900)
            v[i].isDie = true;
    }
}
void drawvalue() {
    for (int i = 0; i < 10; i++) {
        if (!v[i].isDie) {
            if (v[i].kind == 0) {
                putimage(v[i].x, v[i].y, &blood1, SRCAND);
                putimage(v[i].x, v[i].y, &blood, SRCPAINT);
            }
            else {
                putimage(v[i].x, v[i].y, &bullet1, SRCAND);
                putimage(v[i].x, v[i].y, &bullet, SRCPAINT);
            }
        }
    }
}
void getvalue() {
    for (int i = 0; i < 10; i++) {
        if (!v[i].isDie) {
            if (distance(gamer[0].x + 30, gamer[0].y + 30, v[i].x + 15, v[i].y + 15) <= 45) {
                if (v[i].kind == 0) {
                    gamer[0].blood++;
                    v[i].isDie = true;
                }
                else {
                    gamer[0].fire++;
                    v[i].isDie = true;

                }
            }
            if (distance(gamer[1].x + 30, gamer[1].y + 30, v[i].x + 15, v[i].y + 15) <= 45) {
                if (v[i].kind == 0) {
                    gamer[0].blood++;
                    v[i].isDie = true;
                }
                else {
                    gamer[1].fire++;
                    v[i].isDie = true;

                }
            }

        }
    }
}

struct boss1
{
    int skillon = 20;
    int x = 220;
    int y = 50;
    int blood = 80;
    int skill = 0;
    boolean isDie = false;
}b1;
struct boss2
{
    int skillon = 20;
    int x = 240;
    int y = -60;
    int blood = 80;
    int skill = 0;
    boolean isDie = false;
}b2;
struct boss3
{
    int skillon = 20;
    int x = 240;
    int y = -60;
    int blood = 80;
    int skill = 0;
    boolean isDie = false;
}b3;
struct boss4
{
    int skillon = 20;
    int x = 240;
    int y = -60;
    int blood = 60;
    int skill = 0;
    boolean isDie = false;
}b4;


struct bullet
{
    int x;
    int y;
    boolean isDie;
}bb[200] = { 0 };
void plane_ini(plane* gamer, int x, int y)
{

    gamer[0].x = x;
    gamer[0].y = y;
    gamer[0].isDie;

    gamer[1].x = x;
    gamer[1].y = y;
    gamer[1].isDie;

}
void draw()
{
    putimage(0, 0, &bk);
    putimage(170, -20, &name);
    putimage(150, 200, &play1, SRCAND);
    putimage(150, 200, &play, SRCPAINT);
    putimage(150, 800, &rules);
    for (int i = 0; i < 4; i++)
        putimage(250, 320 + i * 120, grade + i);
}

void createbullet1()
{
    for (int i = 0; i < 200; i++)
    {
        if (bb[i].isDie && gamer[0].fire == 1)
        {
            bb[i].x = gamer[0].x + 15;
            bb[i].y = gamer[0].y;
            bb[i].isDie = false;
            break;
        }
        else if (bb[i].isDie && gamer[0].fire == 2) {
            bb[i].x = gamer[0].x;
            bb[i].y = gamer[0].y;
            bb[i].isDie = false;
            bb[i + 1].x = gamer[0].x + 30;
            bb[i + 1].y = gamer[0].y;
            bb[i + 1].isDie = false;
            break;
        }
        else if (bb[i].isDie && gamer[0].fire >= 3) {
            bb[i].x = gamer[0].x - 30;
            bb[i].y = gamer[0].y;
            bb[i].isDie = false;
            bb[i + 1].x = gamer[0].x + 60;
            bb[i + 1].y = gamer[0].y;
            bb[i + 1].isDie = false;
            bb[i + 2].x = gamer[0].x + 15;
            bb[i + 2].y = gamer[0].y;
            bb[i + 2].isDie = false;
            break;
        }
    }
}

void createbullet2()
{
    for (int i = 0; i < 200; i++)
    {
        if (bb[i].isDie && gamer[1].fire == 1)
        {
            bb[i].x = gamer[1].x + 15;
            bb[i].y = gamer[1].y;
            bb[i].isDie = false;
            break;
        }
        else if (bb[i].isDie && gamer[1].fire == 2) {
            bb[i].x = gamer[1].x;
            bb[i].y = gamer[1].y;
            bb[i].isDie = false;
            bb[i + 1].x = gamer[1].x + 30;
            bb[i + 1].y = gamer[1].y;
            bb[i + 1].isDie = false;
            break;
        }
        else if (bb[i].isDie && gamer[1].fire >= 3) {
            bb[i].x = gamer[1].x - 30;
            bb[i].y = gamer[1].y;
            bb[i].isDie = false;
            bb[i + 1].x = gamer[1].x + 60;
            bb[i + 1].y = gamer[1].y;
            bb[i + 1].isDie = false;
            bb[i + 2].x = gamer[1].x + 15;
            bb[i + 2].y = gamer[1].y;
            bb[i + 2].isDie = false;
            break;
        }
    }
}

void drawplane()
{
    FlushBatchDraw();
    cleardevice();
    putimage(0, 0, &bk);
    if (!gamer[0].isDie) {
        putimage(gamer[0].x, gamer[0].y, &Plane12, SRCAND);
        putimage(gamer[0].x, gamer[0].y, Plane + 0, SRCPAINT);
    }
    if (!gamer[1].isDie) {
        putimage(gamer[1].x, gamer[1].y, &Plane12, SRCAND);
        putimage(gamer[1].x, gamer[1].y, Plane + 0, SRCPAINT);
    }
    for (int i = 0; i < 200; i++)
    {
        if (!bb[i].isDie)
        {
            putimage(bb[i].x, bb[i].y, &bullet1, SRCAND);
            putimage(bb[i].x, bb[i].y, &bullet, SRCPAINT);
        }

    }
    for (int i = 0; i < 40; i++)
    {
        if (!enemy[i].isDie)
        {
            putimage(enemy[i].x, enemy[i].y, &ene);
        }

    }

    Sleep(50);

}

void  init()
{
    initgraph(600, 900);
    loadimage(&bk, "image/bk.png", 600, 900);
    loadimage(&name, "image/name.png", 260, 200),
        loadimage(Plane + 0, "image/plane1.png", 60, 60);
    loadimage(&Plane12, "image/plane12.png", 60, 60);
    loadimage(Plane + 1, "image/plane2.png", 60, 60);
    loadimage(boom + 0, "image/boom1.png", 60, 60);
    loadimage(boom + 1, "image/boom2.png", 30, 30);
    loadimage(grade + 0, "image/grade1.png", 100, 100);
    loadimage(grade + 1, "image/grade2.png", 100, 100);
    loadimage(grade + 2, "image/grade3.png", 100, 100);
    loadimage(grade + 3, "image/grade4.png", 100, 100);
    loadimage(&bullet, "image/bullet.png", 30, 30);
    loadimage(&bullet1, "image/bullet1.png", 30, 30);
    loadimage(&ene, "image/enemy.png", 30, 30);
    loadimage(&pause, "image/pause.png", 600, 200);
    loadimage(&lose, "image/lose.png", 600, 400);
    loadimage(&play, "image/play1.png", 300, 100);
    loadimage(&play1, "image/play2.png", 300, 100);
    loadimage(&rules, "image/rules.png", 300, 100);
    loadimage(&htp, "image/htp.png", 600, 360);
    loadimage(&next, "image/next.jpg", 600, 200);
    loadimage(&boss1, "image/boss1.png", 150, 150, 1);
    loadimage(&boss12, "image/boss12.png", 150, 150, 1);
    loadimage(&boss2, "image/boss2.png", 120, 120);
    loadimage(&boss22, "image/boss22.png", 120, 120);
    loadimage(&boss3, "image/boss3.png", 200, 200);
    loadimage(&boss4, "image/boss4.png", 120, 120);
    loadimage(&bossHP, "image/bossHP.png", 400, 30);
    loadimage(&HP, "image/HP.png", 30, 30);
    loadimage(&freeze, "image/freeze.png", 60, 60);
    loadimage(&blood, "image/blood1.png", 20, 30);
    loadimage(&blood1, "image/blood2.png", 20, 30);
    loadimage(&stop, "image/stop.png", 30, 30);
    mciSendString(_T("open music/bgm.mp3"), 0, 0, 0);
    for (int i = 0; i < 200; i++)
    {
        bb[i].isDie = true;
    }
    for (int i = 0; i < 20; i++)
    {
        enemy[i].isDie = true;
    }
    gamer[0].isDie = false;
    gamer[1].isDie = false;
    draw();
}
void drawblood(int blood)
{
    putimage(50, 20, &bossHP);
    for (int i = 0; i <= blood; i++) {
        putimage(50 + i * 6, 20, &HP);
    }
}
void drawgamerblood() {
    for (int i = 1; i <= gamer[0].blood; i++) {
        putimage(10 + i * 20, 870, &blood1, SRCAND);
        putimage(10 + i * 20, 870, &blood, SRCPAINT);
    }
}
void createmeny()
{
    for (int i = 0; i < 60; i++)
    {
        if (enemy[i].isDie)
        {
            enemy[i].x = rand() % getwidth();
            enemy[i].y = -10;
            enemy[i].isDie = false;
            break;
        }
    }
}
void creatbossemeny(int t)
{
    for (int i = 0; i < 60; i++)
    {
        if (enemy[i].isDie)
        {
            enemy[i].x = b1.x + t;
            enemy[i].y = b1.y + 30;
            enemy[i].isDie = false;
            break;
        }
    }
}

void ispause() {
    if (_kbhit())
        c = _getch();
    if (c == 27)
    {
        EndBatchDraw();
        putimage(0, 200, &pause);
        c = _getch();
        BeginBatchDraw();

    }
}
void moveplane()
{
    int speed = 20;
    if (!gamer[0].isFreeze) {
        if (GetAsyncKeyState(VK_UP))
        {
            gamer[0].y -= speed;
        }
        if (GetAsyncKeyState(VK_RIGHT) && gamer[0].x <= 555)
        {
            gamer[0].x += speed;
        }
        if (GetAsyncKeyState(VK_LEFT) && gamer[0].x >= -45)
        {
            gamer[0].x -= speed;
        }
        if (GetAsyncKeyState(VK_DOWN) && gamer[0].y < 850)
        {
            gamer[0].y += speed;
        }
        if (GetAsyncKeyState(VK_LBUTTON) && !gamer[0].isDie)
        {

            createbullet1();
        }
    }
    if (!gamer[1].isFreeze) {
        if (GetAsyncKeyState(VK_SPACE) && !gamer[1].isDie)
        {

            createbullet2();
        }
        if (GetAsyncKeyState(0x57))
        {
            gamer[1].y -= speed;
        }
        if (GetAsyncKeyState(0x44) && gamer[1].x <= 555)
        {
            gamer[1].x += speed;
        }
        if (GetAsyncKeyState(0x41) && gamer[1].x >= -45)
        {
            gamer[1].x -= speed;
        }
        if (GetAsyncKeyState(0x53) && gamer[1].y < 850)
        {
            gamer[1].y += speed;
        }
    }

    ispause();
}




void movebullet()
{
    for (int i = 0; i < 200; i++)
    {
        if (!bb[i].isDie)
            bb[i].y -= 50;
        if (bb[i].y <= 0)
        {
            bb[i].isDie = true;
        }
    }

}
void moveenemy()
{
    for (int i = 0; i < 60; i++)
    {
        if (!enemy[i].isDie)
            enemy[i].y += 15;
        if (enemy[i].y >= 900)
        {
            enemy[i].isDie = true;
        }
    }
}
void moveboss1()
{

    b1.y += 4;
    if (b1.y >= 1000)
    {
        b1.y = 0;
    }
}
void moveboss2() {
    b2.y += 30;
    if (b2.y >= 1000)
    {
        b2.y = 0;
    }

    if (rand() % 2 == 0) {
        b2.x += 30;
        if (b2.x > 540)
            b2.x = -60;
    }
    else {
        b2.x -= 30;
        if (b2.x < -60)
            b2.x = 540;
    }
}
int jump = 0;
void moveboss3() {

    b3.y += 5;

    if (jump % 15 == 0) {
        b3.y = rand() % 800;
        b3.x = rand() % 600 - 75;
    }
    if (b3.y >= 800)
    {
        b3.y = 0;
    }
    jump++;
}

void playingprogress()
{
    for (int i = 0; i < 60; i++)//绘画敌机
    {
        for (int j = 0; j < 20; j++)
        {
            if (distance(enemy[i].x + 15, enemy[i].y + 15, bb[j].x + 15, bb[j].y + 15) <= 25 && !enemy[i].isDie)
            {

                enemy[i].isDie = true;
                bb[j].isDie = true;
                if (enemy[i].y > 50)
                    putimage(enemy[i].x, enemy[i].y, boom + 1);
                break;
            }
        }
    }


    for (int i = 0; i < 60; i++) //绘画玩家
    {
        if (enemy[i].isDie == false) {

            if (distance(gamer[0].x + 30, gamer[0].y + 30, enemy[i].x + 15, enemy[i].y + 15) <= 45)
            {
                enemy[i].isDie = true;
                gamer[0].blood--;
                if (gamer[0].fire > 1)
                    gamer[0].fire = 1;
                if (gamer[0].blood <= 0) {
                    gamer[0].isDie = true;
                    if (g1 == 0) {
                        putimage(gamer[0].x, gamer[0].y, boom + 0);
                        g1 = 1;
                    }
                }
            }
            if (distance(gamer[1].x + 45, gamer[1].y + 45, enemy[i].x + 15, enemy[i].y + 15) <= 45)
            {
                gamer[0].blood--;
                enemy[i].isDie = true;
                if (gamer[1].fire > 1)
                    gamer[1].fire = 1;
                if (gamer[0].blood <= 0) {
                    gamer[1].isDie = true;
                    if (g1 == 0) {
                        putimage(gamer[1].x, gamer[1].y, boom + 0);
                        g1 = 1;
                    }
                }
            }
        }
    }
}

int main()
{
    int x = 0;
    int b = 0, t1;
    int t = 0;
    int grade = 0;
    init();
    while (grade == 0) {

        m = GetMouseMsg();
        switch (m.uMsg)
        {
        case WM_LBUTTONDOWN:
            if (m.x >= 0 && m.x <= 600 && m.y >= 200 && m.y <= 300)
                grade = 1;
            if (m.x >= 250 && m.x <= 350 && m.y >= 320 && m.y <= 440)
                grade = 1;
            if (m.x >= 250 && m.x <= 350 && m.y >= 440 && m.y <= 560)
                grade = 3;
            if (m.x >= 250 && m.x <= 350 && m.y >= 560 && m.y <= 680)
                grade = 5;
            if (m.x >= 250 && m.x <= 350 && m.y >= 680 && m.y <= 800)
                grade = 7;
            if (m.y >= 800 && m.y <= 900) {
                putimage(0, 100, &htp);
                while (true) {
                    if (_kbhit())
                        break;
                }
                cleardevice();
                draw();
            }

        }

    }
    plane_ini(&gamer[0], 400, 800);
    plane_ini(&gamer[1], 200, 800);

    mciSendString(_T("play music/bgm.mp3"), 0, 0, 0);
    while (true) {

        BeginBatchDraw();
        while (grade == 1)//第一关
        {

            moveplane();
            movebullet();
            moveenemy();
            movevalue();
            drawgamerblood();
            drawvalue();
            t1 = 8 - t / 200;//敌机生成
            if (x % t1 == 0)
            {
                createmeny();
            }
            if (x % 100 == 0)
                creatvalue();
            playingprogress();
            getvalue();
            if (distance(gamer[0].x + 45, gamer[0].y + 45, gamer[1].x + 45, gamer[1].y + 45) < 60) {
                if (g1 == 0 && g2 == 0)
                {
                    gamer[0].isDie = true;
                    gamer[1].isDie = true;
                }
            }
            if (gamer[0].isDie && gamer[1].isDie) {
                EndBatchDraw();
                putimage(0, 300, &lose);
                Sleep(5000);
                return 0;
            }

            Sleep(30);

            drawplane();
            x++;
            t++;
            if (t == 340)
                grade++;
        }
        x = 0, b = 0, t = 440;
        while (grade == 2)
        {
            moveplane();
            movebullet();
            moveenemy();
            moveboss1();
            drawblood(b1.blood);
            drawgamerblood();
            putimage(b1.x, b1.y, &boss12, SRCAND);
            putimage(b1.x, b1.y, &boss1, SRCPAINT);



            if (x % 20 == 0)
            {

                creatbossemeny(-150);
                creatbossemeny(270);
                creatbossemeny(170);
                creatbossemeny(-50);
                creatbossemeny(60);
            }
            if (x % 6 == 0)
            {
                createmeny();
            }
            playingprogress();


            for (int j = 0; j < 200; j++)
            {
                if (distance(b1.x + 75, b1.y + 75, bb[j].x + 15, bb[j].y + 15) <= 80 && !b1.isDie)
                {
                    if (!bb[j].isDie)
                    {
                        b1.blood--;
                        bb[j].isDie = true;

                        putimage(bb[j].x, bb[j].y, boom + 1);
                    }

                    break;
                }
            }

            if (b1.blood == 0)
            {


                b1.isDie = true;
                grade++;
            }
            if (distance(gamer[0].x + 45, gamer[0].y + 45, gamer[1].x + 45, gamer[1].y + 45) < 60) {
                if (g1 == 0 && g2 == 0)
                {
                    gamer[0].isDie = true;
                    gamer[1].isDie = true;
                }
            }
            if (distance(gamer[0].x + 30, gamer[0].y + 30, b1.x + 75, b1.y + 75) < 80) {
                gamer[0].isDie = true;
                if (g1 == 0) {
                    putimage(gamer[0].x, gamer[0].y, boom + 0);
                    g1 = 1;
                }
            }
            if (distance(gamer[1].x + 30, gamer[1].y + 30, b1.x + 75, b1.y + 75) < 80) {
                gamer[1].isDie = true;
                if (g2 == 0) {
                    putimage(gamer[1].x, gamer[1].y, boom + 0);
                    g2 = 1;
                }
            }
            if (gamer[0].isDie && gamer[1].isDie) {
                EndBatchDraw();
                putimage(0, 300, &lose);
                Sleep(5000);
                return 0;
            }


            Sleep(50);

            drawplane();


            drawblood(b1.blood);

            x++;
        }
        if (gamer[0].blood <= 5)
            gamer[0].blood = 5;
        gamer[0].isDie = gamer[1].isDie = false;
        g1 = g2 = 0;
        while (grade == 3) {
            EndBatchDraw();
            x = 0, b = 0, t = 440;
            putimage(0, 300, &next);
            BeginBatchDraw();
            m = GetMouseMsg();
            switch (m.uMsg)
            {
            case WM_LBUTTONDOWN:
                if (m.x >= 0 && m.x <= 600 && m.y >= 300 && m.y <= 500)

                    while (grade == 3)
                    {

                        moveplane();
                        movebullet();
                        moveenemy();
                        movevalue();
                        drawgamerblood();
                        drawvalue();
                        t1 = 8 - t / 200;//敌机生成
                        if (x % t1 == 0)
                        {
                            createmeny();
                        }
                        if (x % 150 == 0)
                            creatvalue();
                        playingprogress();
                        getvalue();
                        if (distance(gamer[0].x + 45, gamer[0].y + 45, gamer[1].x + 45, gamer[1].y + 45) < 60) {
                            if (g1 == 0 && g2 == 0)
                            {
                                gamer[0].isDie = true;
                                gamer[1].isDie = true;
                            }
                        }
                        if (gamer[0].isDie && gamer[1].isDie) {
                            EndBatchDraw();
                            putimage(0, 300, &lose);
                            Sleep(5000);
                            return 0;
                        }

                        Sleep(50);

                        drawplane();
                        x++;
                        t++;
                        if (t == 740)
                            grade++;
                    }
                while (grade == 4)
                {
                    moveplane();
                    movebullet();
                    moveenemy();
                    moveboss2();
                    drawgamerblood();
                    drawblood(b2.blood);
                    putimage(b2.x, b2.y, &boss22, SRCAND);
                    putimage(b2.x, b2.y, &boss2, SRCPAINT);

                    if (x % 2 == 0)
                        createmeny();

                    playingprogress();


                    for (int j = 0; j < 200; j++)
                    {
                        if (distance(b2.x + 60, b2.y + 60, bb[j].x + 15, bb[j].y + 15) <= 80 && !b2.isDie)
                        {
                            if (!bb[j].isDie)
                            {
                                b2.blood--;
                                bb[j].isDie = true;

                                putimage(bb[j].x, bb[j].y, boom + 1);
                            }

                            break;
                        }
                    }

                    if (b2.blood == 0)
                    {

                        EndBatchDraw();
                        b2.isDie = true;
                        grade++;
                    }
                    if (distance(gamer[0].x + 45, gamer[0].y + 45, gamer[1].x + 45, gamer[1].y + 45) < 60) {
                        if (g1 == 0 && g2 == 0)
                        {
                            gamer[0].isDie = true;
                            gamer[1].isDie = true;
                        }
                    }
                    if (distance(gamer[0].x + 30, gamer[0].y + 30, b2.x + 50, b2.y + 50) < 80) {
                        gamer[0].isDie = true;
                        if (g1 == 0) {
                            putimage(gamer[0].x, gamer[0].y, boom + 0);
                            g1 = 1;
                        }
                    }
                    if (distance(gamer[1].x + 30, gamer[1].y + 30, b2.x + 50, b2.y + 50) < 80) {
                        gamer[1].isDie = true;
                        if (g2 == 0) {
                            putimage(gamer[1].x, gamer[1].y, boom + 0);
                            g2 = 1;
                        }
                    }
                    if (gamer[0].isDie && gamer[1].isDie) {
                        EndBatchDraw();
                        putimage(0, 300, &lose);
                        Sleep(5000);
                        return 0;
                    }


                    Sleep(50);

                    drawplane();


                    drawblood(b2.blood);

                    x++;
                }
            }
        }
        if (gamer[0].blood <= 5)
            gamer[0].blood = 5;
        gamer[0].isDie = gamer[1].isDie = false;
        gamer[0].isFreeze = gamer[1].isFreeze = false;
        g1 = g2 = 0;
        while (grade == 5) {
            EndBatchDraw();
            x = 0, b = 0, t = 800;
            putimage(0, 300, &next);
            BeginBatchDraw();
            m = GetMouseMsg();
            switch (m.uMsg)
            {
            case WM_LBUTTONDOWN:
                if (m.x >= 0 && m.x <= 600 && m.y >= 300 && m.y <= 500)

                    while (grade == 5)//第三关
                    {

                        moveplane();
                        movebullet();
                        moveenemy();
                        movevalue();
                        drawgamerblood();
                        drawvalue();
                        t1 = 10 - t / 200;//敌机生成
                        if (x % t1 == 0)
                        {
                            createmeny();
                        }
                        if (x % 200 == 0)
                            creatvalue();
                        playingprogress();
                        getvalue();
                        if (distance(gamer[0].x + 45, gamer[0].y + 45, gamer[1].x + 45, gamer[1].y + 45) < 60) {
                            if (g1 == 0 && g2 == 0)
                            {
                                gamer[0].isDie = true;
                                gamer[1].isDie = true;
                            }
                        }
                        if (gamer[0].isDie && gamer[1].isDie) {
                            EndBatchDraw();
                            putimage(0, 300, &lose);
                            Sleep(5000);
                            return 0;
                        }

                        Sleep(50);

                        drawplane();
                        x++;
                        t++;
                        if (t == 1100)
                            grade++;
                    }
                while (grade == 6)
                {
                    moveplane();
                    movebullet();
                    moveenemy();
                    moveboss3();
                    drawgamerblood();
                    drawblood(b3.blood);
                    putimage(b3.x, b3.y, &boss32, SRCAND);
                    putimage(b3.x, b3.y, &boss3, SRCPAINT);
                    if (gamer[0].isFreeze && !gamer[0].isDie)
                        putimage(gamer[0].x, gamer[0].y, &freeze);
                    if (gamer[1].isFreeze && !gamer[1].isDie)
                        putimage(gamer[1].x, gamer[1].y, &freeze);



                    if (x % 4 == 0)
                        createmeny();

                    playingprogress();


                    for (int j = 0; j < 200; j++)
                    {
                        if (distance(b3.x + 75, b3.y + 75, bb[j].x + 15, bb[j].y + 15) <= 100 && !b3.isDie)
                        {
                            if (!bb[j].isDie)
                            {
                                b3.blood--;
                                bb[j].isDie = true;

                                putimage(bb[j].x, bb[j].y, boom + 1);
                            }

                            break;
                        }
                    }

                    if (b3.blood == 0)
                    {
                        EndBatchDraw();
                        b3.isDie = true;
                        grade++;
                    }
                    if (distance(gamer[0].x + 45, gamer[0].y + 45, gamer[1].x + 45, gamer[1].y + 45) < 120) {
                        if (gamer[0].isFreeze || gamer[1].isFreeze) {
                            gamer[0].isFreeze = false;
                            gamer[1].isFreeze = false;
                        }
                    }
                    if (distance(gamer[0].x + 45, gamer[0].y + 45, gamer[1].x + 45, gamer[1].y + 45) < 60) {
                        if (g1 == 0 && g2 == 0)
                        {
                            gamer[0].isDie = true;
                            gamer[1].isDie = true;
                        }

                    }

                    if (distance(gamer[0].x + 30, gamer[0].y + 30, b3.x + 100, b3.y + 100) < 130) {
                        if (!gamer[0].isFreeze)
                            gamer[0].isFreeze = true;

                    }
                    if (distance(gamer[1].x + 30, gamer[1].y + 30, b3.x + 100, b3.y + 100) < 130) {
                        if (!gamer[1].isFreeze)
                            gamer[1].isFreeze = true;


                    }
                    if (gamer[0].isDie && gamer[1].isDie || gamer[0].isDie && gamer[1].isFreeze || gamer[1].isDie && gamer[0].isFreeze || gamer[1].isFreeze && gamer[0].isFreeze) {
                        EndBatchDraw();
                        putimage(0, 300, &lose);
                        Sleep(5000);
                        return 0;
                    }
                    Sleep(50);
                    drawplane();


                    drawblood(b3.blood);

                    x++;
                }



            }
        }
        if (gamer[0].blood <= 5)
            gamer[0].blood = 5;
        gamer[0].isDie = gamer[1].isDie = false;
        g1 = g2 = 0;
        while (grade == 7) {
            EndBatchDraw();
            x = 0, b = 0, t = 0;
            putimage(0, 300, &next);
            BeginBatchDraw();
            m = GetMouseMsg();
            switch (m.uMsg)
            {
            case WM_LBUTTONDOWN:
                if (m.x >= 0 && m.x <= 600 && m.y >= 300 && m.y <= 500)
                    while (grade == 7)//第三关
                    {

                        moveplane();
                        movebullet();
                        moveenemy();
                        movevalue();
                        drawgamerblood();
                        drawvalue();
                        if (x % 2 == 0)
                        {
                            createmeny();
                        }
                        if (x % 200 == 0)
                            creatvalue();
                        playingprogress();
                        getvalue();
                        if (distance(gamer[0].x + 45, gamer[0].y + 45, gamer[1].x + 45, gamer[1].y + 45) < 60) {
                            if (g1 == 0 && g2 == 0)
                            {
                                gamer[0].isDie = true;
                                gamer[1].isDie = true;
                            }
                        }
                        if (gamer[0].isDie && gamer[1].isDie) {
                            EndBatchDraw();
                            putimage(0, 300, &lose);
                            Sleep(5000);
                            return 0;
                        }

                        Sleep(50);

                        drawplane();
                        x++;
                        t++;
                        if (t == 300)
                            grade++;
                    }
                b2.isDie = b3.isDie = false;
                while (grade == 8)
                {
                    moveplane();
                    movebullet();
                    moveenemy();
                    moveboss3();
                    if (!b3.isDie && !b2.isDie) {
                        moveboss2();
                        moveboss3();

                        putimage(b2.x, b2.y, &boss22, SRCAND);
                        putimage(b2.x, b2.y, &boss2, SRCPAINT);
                        putimage(b3.x, b3.y, &boss32, SRCAND);
                        putimage(b3.x, b3.y, &boss3, SRCPAINT);

                    }
                    else {
                        b2.x, b2.y, b3.x, b3.y = 0;
                    }

                    drawgamerblood();
                    drawblood(b4.blood);
                    putimage(b4.x, b4.y, &boss42, SRCAND);
                    putimage(b4.x, b4.y, &boss4, SRCPAINT);
                    if (gamer[0].isFreeze && !gamer[0].isDie)
                        putimage(gamer[0].x, gamer[0].y, &freeze);
                    if (gamer[1].isFreeze && !gamer[1].isDie)
                        putimage(gamer[1].x, gamer[1].y, &freeze);

                    if (x % 8 == 0)
                        createmeny();
                    if (b4.blood <= 30) {
                        b2.isDie, b3.isDie = true;
                        createmeny();
                    }

                    playingprogress();


                    for (int j = 0; j < 200; j++)
                    {
                        if (distance(b4.x + 60, b4.y + 60, bb[j].x + 15, bb[j].y + 15) <= 75)
                        {
                            if (!bb[j].isDie)
                            {
                                b4.blood--;
                                bb[j].isDie = true;

                                putimage(bb[j].x, bb[j].y, boom + 1);
                            }

                            break;
                        }
                    }
                    if (b4.blood <= 30) {
                        b2.isDie, b3.isDie = true;
                        createmeny();
                    }

                    if (b4.blood == 0)
                    {
                        EndBatchDraw();
                        b4.isDie = true;
                        grade++;
                    }
                    if (distance(gamer[0].x + 45, gamer[0].y + 45, gamer[1].x + 45, gamer[1].y + 45) < 120) {
                        if (gamer[0].isFreeze || gamer[1].isFreeze) {
                            gamer[0].isFreeze = false;
                            gamer[1].isFreeze = false;
                        }
                    }
                    if (distance(gamer[0].x + 45, gamer[0].y + 45, gamer[1].x + 45, gamer[1].y + 45) < 60) {
                        if (g1 == 0 && g2 == 0)
                        {
                            gamer[0].isDie = true;
                            gamer[1].isDie = true;
                        }

                    }

                    if (distance(gamer[0].x + 30, gamer[0].y + 30, b3.x + 100, b3.y + 100) < 130) {
                        if (!gamer[0].isFreeze)
                            gamer[0].isFreeze = true;

                    }
                    if (distance(gamer[1].x + 30, gamer[1].y + 30, b3.x + 100, b3.y + 100) < 130) {
                        if (!gamer[1].isFreeze)
                            gamer[1].isFreeze = true;
                    }
                    if (gamer[0].isDie && gamer[1].isDie || gamer[0].isDie && gamer[1].isFreeze || gamer[1].isDie && gamer[0].isFreeze || gamer[1].isFreeze && gamer[0].isFreeze) {
                        EndBatchDraw();
                        putimage(0, 300, &lose);
                        Sleep(5000);
                        return 0;
                    }

                    if (distance(gamer[0].x + 30, gamer[0].y + 30, b2.x + 50, b2.y + 50) < 80) {
                        gamer[0].isDie = true;
                        if (g1 == 0) {
                            putimage(gamer[0].x, gamer[0].y, boom + 0);
                            g1 = 1;
                        }
                    }
                    if (distance(gamer[1].x + 30, gamer[1].y + 30, b2.x + 50, b2.y + 50) < 80) {
                        gamer[1].isDie = true;
                        if (g2 == 0) {
                            putimage(gamer[1].x, gamer[1].y, boom + 0);
                            g2 = 1;
                        }
                    }


                    Sleep(50);
                    drawplane();

                    x++;
                }
            }
        }

    }
}


