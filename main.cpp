#include <bits/stdc++.h>
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <unistd.h>
using namespace std;
mt19937 rd;
long speed=100;
long wMax=164,hMax=42,score,x,y,ht,Count,foodx,foody;
char snake;
queue<pair<long,long> > qu;
pair<long,long> dir[]={{0,-1},{-1,0},{0,1},{1,0}};
vector<pair<long,long> > luu;
bool visited[200][50];
string Banner[]={
    "  #### ",
    " #     ",
    "  #    ",
    "    #  ",
    " ####  ",

    "#     # ",
    "# #   # ",
    "#  #  # ",
    "#   # # ",
    "#     # ",

    "    #    ",
    "   # #   ",
    "  #   #  ",
    " # # # # ",
    "#       #",

    " #   # ",
    " #  #  ",
    " # #   ",
    " #  #  ",
    " #   # ",

    " # # #",
    " #    ",
    " # # #",
    " #    ",
    " # # #"
};
HWND WINAPI GetConsoleWindowNT(void)
{
    //declare function pointer type
    typedef HWND WINAPI(*GetConsoleWindowT)(void);
    //declare one such function pointer
    GetConsoleWindowT GetConsoleWindow;
    //get a handle on kernel32.dll
    HMODULE hk32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
    //assign procedure address to function pointer
    GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32Lib
    ,TEXT("GetConsoleWindow"));
    //check if the function pointer is valid
    //since the function is undocumented
    if(GetConsoleWindow == NULL){
        return NULL;
    }
    //call the undocumented function
    return GetConsoleWindow();
}
void SetWindowSize(SHORT width, SHORT height) {
    HWND hWnd=GetConsoleWindowNT();
    MoveWindow(hWnd,0,0,1220,750,TRUE);
}
void GOTO(SHORT posX, SHORT posY)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

	SetConsoleCursorPosition(hStdout, Position);
}
void HideCursor(){
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &ConCurInf);
}
void ShowScrollbar(BOOL Show)
{
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, Show);
}
long random(long l,long r) {
    return rd()%(r-l+1)+l;
}
void border() {
    for(long i=0;i<=wMax;i++) {
        GOTO(i,0);cout<<'#';
    }
    for(long i=1;i<hMax;i++) {
        GOTO(0,i);cout<<'#';
        GOTO(3*wMax/4,i);cout<<'#';
        GOTO(wMax,i);cout<<'#';
    }
    for(long i=0;i<=wMax;i++) {
        GOTO(i,hMax);cout<<'#';
    }
}
void banner() {
    for(long i=0;i<5;i++) {
        GOTO(3*wMax/4+1,i+5);
        for(long j=0;j<5;j++) cout<<Banner[j*5+i];
    }
    GOTO(3*wMax/4+5,15);
    cout<<"SCORE: ";
    for(long i=3*wMax/4+1;i<wMax;i+=2) {
        GOTO(i,20);cout<<'#';
    }
    GOTO(3*wMax/4+5,23);cout<<"Press W to go up, S to go down";
    GOTO(3*wMax/4+5,25);cout<<"A to go left, D to go right";
    GOTO(3*wMax/4+5,27);cout<<"When you lose, press R to replay";

}
void init() {
    while (qu.size()) qu.pop();
    memset(visited,0,sizeof visited);
    snake=char(1);
    for(long i=1;i<3*wMax/4;i++) {
        for(long j=1;j<hMax;j++) luu.push_back(make_pair(i,j));
    }
    Count=luu.size();
}
long pos(long x) {
    //Find a place where food can be placed
    for(long i=0;i<luu.size();i++) {
        if (!visited[luu[i].first][luu[i].second]) x--;
        if (x==0) return i;
    }
}
void game() {
    score=0;
    long tmp=pos(random(1,Count));
    foodx=luu[tmp].first;
    foody=luu[tmp].second;
    GOTO(foodx,foody);cout<<'*';

    x=random(3,3*wMax/5-3);
    y=random(3,hMax-3);
    GOTO(x,y);cout<<snake;
    visited[x][y]=1;
    qu.push(make_pair(x,y));
    Count--;
    char c=getch();
    if (c=='a') ht=1;else
        if (c=='s') ht=2;else
            if (c=='d') ht=3;else ht=0;
    while (true) {
        if (kbhit()) {
            c=getch();
            if (c=='a'&&ht%2==0) ht=1;
            if (c=='s'&&ht%2==1) ht=2;
            if (c=='d'&&ht%2==0) ht=3;
            if (c=='w'&&ht%2==1) ht=0;
        }
        x=x+dir[ht].first;
        y=y+dir[ht].second;
        if (x<1||y<1||x>=3*wMax/4||y>=hMax||visited[x][y]) {
            return;
        }
        GOTO(x,y);cout<<snake;
        visited[x][y]=1;
        qu.push(make_pair(x,y));
        if (x!=foodx||y!=foody) {
            GOTO(qu.front().first,qu.front().second);cout<<' ';
            visited[qu.front().first][qu.front().second]=0;
            qu.pop();
        } else {
            score++;
            GOTO(3*wMax/4+5,15);
            cout<<"SCORE: "<<score;
            tmp=pos(random(1,Count));
            foodx=luu[tmp].first;
            foody=luu[tmp].second;
            GOTO(foodx,foody);cout<<'*';
            Count--;
        }
        Sleep(speed);
    }
}
int main() {
    SetWindowSize(164,43);
    ShowScrollbar(0);
    HideCursor();
    SetConsoleTitle("snake");
    init();
    border();
    banner();
    game();
    while (true) {
        while (true) {
            if (kbhit()) {
                char c=getch();
                if (c=='r') break;
            }
        }
        system("cls");
        init();
        border();
        banner();
        game();
    }
    /*while (true) {
        if (kbhit()) {
            char c=getch();
            cout<<c<<'\n';
            sleep(2);
        }

    }*/
}
