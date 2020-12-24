#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<time.h>
#include<fstream.h>
#include<process.h>
#include<string.h>

static int csc=0;//static variable for counting 3 consecutive 6

//class for storing coordinates of circles where players will move
class Position
{
private:
int x,y;

public:
void setcoord(int x,int y){
this->x=x;
this->y=y;
}

void display(int b){
setcolor(15);
circle(x,y,10);
if(b==1){
setfillstyle(SOLID_FILL,RED);
floodfill(x,y,15);
}
if(b==2){
setfillstyle(SOLID_FILL,YELLOW);
floodfill(x,y,15);
}
if(b==3){
setfillstyle(SOLID_FILL,GREEN);
floodfill(x,y,15);
}
if(b==4){
setfillstyle(SOLID_FILL,BLUE);
floodfill(x,y,15);
}
}
};

//class for player with required properties
class Player{
private:
Position pos;//player has attribute of type class Position

public:
int posindex;
int status;
int homeway;

Player(){
status=0;
homeway=0;
}

void setposition(int pindex,Position p){
posindex=pindex;
pos=p;
}

void display(int b){
pos.display(b);
}

};

//create board interface before player gets displayed
void showboard(){
int i,x=0,y=465,d=6*31;
setbkcolor(15);
setcolor(8);

for(i=0; i<=y-x; i+=31){
line(x+i,x,x+i,y);
line(x,x+i,y,x+i);
}

setfillstyle(SOLID_FILL,RED);
int red[]={x,x,x+d,x,x+d,x+d,x+62,x+d,x+62,x+d+31,x+d,x+d+31,x+d,x+d,x+d+46,x+d+46,x+d,x+d+93,x+d,x+d+62,x+31,x+d+62,x+31,x+d,x,x+d,x,x};
fillpoly(14,red);

setfillstyle(SOLID_FILL,YELLOW);
int yellow[]={y,x,y,x+d,y-d,x+d,y-d,x+62,y-d-31,x+62,y-d-31,x+d,y-d,x+d,y-d-46,x+d+46,y-d-93,x+d,y-d-62,x+d,y-d-62,x+31,y-d,x+31,y-d,x,y,x};
fillpoly(14,yellow);

setfillstyle(SOLID_FILL,GREEN);
int green[]={y,y,y-d,y,y-d,y-d,y-62,y-d,y-62,y-d-31,y-d,y-d-31,y-d,y-d,y-d-46,y-d-46,y-d,y-d-93,y-d,y-d-62,y-31,y-d-62,y-31,y-d,y,y-d,y,y};
fillpoly(14,green);

setfillstyle(SOLID_FILL,BLUE);
int blue[]={x,y,x,y-d,x+d,y-d,x+d,y-62,x+d+31,y-62,x+d+31,y-d,x+d,y-d,x+d+46,y-d-46,x+d+93,y-d,x+d+62,y-d,x+d+62,y-31,x+d,y-31,x+d,y,x,y};
fillpoly(14,blue);

line(x+62,x+d+62,x+93,x+d+93);
line(x+93,x+d+62,x+62,x+d+93);

line(x+d,x+62,x+d+31,x+93);
line(x+d+31,x+62,x+d,x+93);

line(y-62,x+d,y-62-31,x+d+31);
line(y-62,x+d+31,y-62-31,x+d);

line(y-d,y-62,y-d-31,y-62-31);
line(y-d,y-62-31,y-d-31,y-62);
}


//save all the circle coordinates where player can move to an array of object of class Position
void initializecoords(Position p[]){
int x=0,y=465,d=6*31,h=0,i,j;
j=0;
for(i=0; i<6; i++){
p[j++].setcoord(x+15+h,x+d+15);
h+=31;
}
h=0;
for(i=0; i<6; i++){
p[j++].setcoord(x+d+15,x+d-15-h);
h+=31;
}
p[j++].setcoord(x+d+46,x+15);
h=0;
for(i=0; i<6; i++){
p[j++].setcoord(x+d+77,x+15+h);
h+=31;
}
h=0;
for(i=0; i<6; i++){
p[j++].setcoord(y-d+15+h,x+d+15);
h+=31;
}
p[j++].setcoord(y-15,x+d+46);
h=0;
for(i=0; i<6; i++){
p[j++].setcoord(y-15-h,y-d-15);
h+=31;
}
h=0;
for(i=0; i<6; i++){
p[j++].setcoord(y-d-15,y-d+15+h);
h+=31;
}
p[j++].setcoord(y-d-46,y-15);
h=0;
for(i=0; i<6; i++){
p[j++].setcoord(x+d+15,y-15-h);
h+=31;
}
h=0;
for(i=0; i<6; i++){
p[j++].setcoord(x+d-15-h,y-d-15);
h+=31;
}
p[j++].setcoord(x+15,y-d-46);
h=0;
for(i=0; i<6; i++){
p[j++].setcoord(x+46+h,x+d+46);
h+=31;
}
h=0;
for(i=0; i<6; i++){
p[j++].setcoord(x+d+46,x+46+h);
h+=31;
}
h=0;
for(i=0; i<6; i++){
p[j++].setcoord(y-46-h,x+d+46);
h+=31;
}
h=0;
for(i=0; i<6; i++){
p[j++].setcoord(x+d+46,y-46-h);
h+=31;
}
}


//save circle coordinates for initial position of player inside center of 4 big squares (i.e; before player is unlocked)
void initializecoords2(Position pi[]){
int x=0,y=465,d=6*31,i,j;
pi[0].setcoord(x+d/2,x+d/2);
pi[1].setcoord(y-d/2,x+d/2);
pi[2].setcoord(y-d/2,y-d/2);
pi[3].setcoord(x+d/2,y-d/2);
}


//initialize players to initial positions defined by above function and set status to 1 for players depending upon value of n(no. of players choosen in game)
void initializeplayer(Player red[],Player yellow[],Player green[],Player blue[],Position pi[],int n){
if(n==2){
red[0].setposition(-1,pi[0]);
yellow[0].setposition(-1,pi[1]);
red[0].status=1;
yellow[0].status=1;
}else if(n==3){
red[0].setposition(-1,pi[0]);
yellow[0].setposition(-1,pi[1]);
green[0].setposition(-1,pi[2]);
red[0].status=1;
yellow[0].status=1;
green[0].status=1;
}else{
red[0].setposition(-1,pi[0]);
yellow[0].setposition(-1,pi[1]);
green[0].setposition(-1,pi[2]);
blue[0].setposition(-1,pi[3]);
red[0].status=1;
yellow[0].status=1;
green[0].status=1;
blue[0].status=1;
}
}


//display all the players which are active
void displayplayer(Player red[],Player yellow[],Player green[],Player blue[]){
int i;
if(red[0].status==1){
red[0].display(1);
}
if(yellow[0].status==1){
yellow[0].display(2);
}
if(green[0].status==1){
green[0].display(3);
}
if(blue[0].status==1){
blue[0].display(4);
}
}

//main logic of rolling a dice for each player turn
void rolldice(Player red[], Player yellow[], Player green[], Player blue[], Position p[], Position pi[], int turn){
setcolor(8);
int x=0,y=465,i,j,k;
char *name;
csc=0;//consecutive six counter

if(turn==1){
name="Red";
}
if(turn==2){
name="Yellow";
}
if(turn==3){
name="Green";
}
if(turn==4){
name="Blue";
}

repeat://label for repeating turn if player gets 6
setcolor(8);
outtextxy(y+10,x+10,"Press Enter to roll...");
outtextxy(y+45,x+40,"Turn: ");
outtextxy(y+90,x+40,name);
outtextxy(y+10,y-10,"Press Esc to exit");
char ch;
while(1){
ch=getch();
if(ch==27 || ch==13)
break;
}
if(ch==27){//exit if player presses Escape key
exit(0);
}
if(ch==13){//execute if player presses Enter key
char roll[1];
time_t t;
srand((unsigned) time(&t));//for generating random number based on time
int n=rand()%6+1;
itoa(n,roll,10);

outtextxy(y+40,x+100,"You rolled:");
outtextxy(y+130,x+100,roll);

if(n==6 && csc==2){//reset player if it has encountered 2 sixes and again has got 6 while rolling(random number generated)
if(turn==1)
red[0].setposition(-1,pi[0]);
if(turn==2)
yellow[0].setposition(-1,pi[1]);
if(turn==3)
green[0].setposition(-1,pi[2]);
if(turn==4)
blue[0].setposition(-1,pi[3]);
delay(500);
cleardevice();
showboard();
displayplayer(red,yellow,green,blue);
}else{
if((turn==1 && red[0].posindex==-1)||(turn==2 && yellow[0].posindex==-1)||(turn==3 && green[0].posindex==-1)||(turn==4 && blue[0].posindex==-1)){//for initial 1 to unlock player
if(turn==1 && n==1){
red[0].posindex=1;
red[0].setposition(1,p[1]);
}
if(turn==2 && n==1){
yellow[0].posindex=14;
yellow[0].setposition(14,p[14]);
}
if(turn==3 && n==1){
green[0].posindex=28;
green[0].setposition(27,p[27]);
}
if(turn==4 && n==1){
blue[0].posindex=41;
blue[0].setposition(40,p[40]);
}
delay(500);
cleardevice();
showboard();
displayplayer(red,yellow,green,blue);
}
else{
if((turn==1&&red[0].homeway!=1)||(turn==1&&red[0].homeway==1&&red[0].posindex+n<=57)||(turn==2&&yellow[0].homeway!=1)||(turn==2&&yellow[0].homeway==1&&yellow[0].posindex+n<=63)||(turn==3&&green[0].homeway!=1)||(turn==3&&green[0].homeway==1&&green[0].posindex+n<=69)||(turn==4&&blue[0].homeway!=1)||(turn==4&&blue[0].homeway==1&&blue[0].posindex+n<=75)){//after player is unlocked
for(i=0; i<n; i++){
setcolor(8);
outtextxy(y+45,x+40,"Turn: ");
outtextxy(y+90,x+40,name);
outtextxy(y+40,x+100,"You rolled:");
outtextxy(y+130,x+100,roll);

if(turn==1){
int index=red[0].posindex;
red[0].setposition(index+1,p[index+1]);
if(index==51){
red[0].homeway=1;
}
if(index==56){
red[0].status=0;
delay(500);
cleardevice();
showboard();
displayplayer(red,yellow,green,blue);
return;
}
}
if(turn==2){
int index=yellow[0].posindex;
if(index==51){
index=-1;
}
if(index==12){
index=57;
yellow[0].homeway=1;
}
yellow[0].setposition(index+1,p[index+1]);
if(index==62){
yellow[0].status=0;
delay(500);
cleardevice();
showboard();
displayplayer(red,yellow,green,blue);
return;
}
}
if(turn==3){
int index=green[0].posindex;
if(index==51){
index=-1;
}
if(index==25){
index=63;
green[0].homeway=1;
}
green[0].setposition(index+1,p[index+1]);
if(index==68){
green[0].status=0;
delay(500);
cleardevice();
showboard();
displayplayer(red,yellow,green,blue);
return;
}
}
if(turn==4){
int index=blue[0].posindex;
if(index==51){
index=-1;
}
if(index==38){
index=69;
blue[0].homeway=1;
}
blue[0].setposition(index+1,p[index+1]);
if(index==74){
blue[0].status=0;
delay(500);
cleardevice();
showboard();
displayplayer(red,yellow,green,blue);
return;
}
}
delay(500);
cleardevice();
showboard();
displayplayer(red,yellow,green,blue);
}
}else{
delay(500);
cleardevice();
showboard();
displayplayer(red,yellow,green,blue);
}
}
int ri=red[0].posindex,yi=yellow[0].posindex,gi=green[0].posindex,bi=blue[0].posindex;//cut player if two player has same position
if(turn==1){
if(ri!=1&&ri!=9&&ri!=14&&ri!=22&&ri!=27&&ri!=35&&ri!=40&&ri!=48){
if(ri==yi){
yellow[0].setposition(-1,pi[1]);
yellow[0].homeway=0;
}
if(ri==gi){
green[0].setposition(-1,pi[2]);
green[0].homeway=0;
}
if(ri==bi){
blue[0].setposition(-1,pi[3]);
blue[0].homeway=0;
}
delay(500);
cleardevice();
showboard();
displayplayer(red,yellow,green,blue);
}
}
if(turn==2){
if(yi!=1&&yi!=9&&yi!=14&&yi!=22&&yi!=27&&yi!=35&&yi!=40&&yi!=48){
if(yi==ri){
red[0].setposition(-1,pi[0]);
red[0].homeway=0;
}
if(yi==gi){
green[0].setposition(-1,pi[2]);
green[0].homeway=0;
}
if(yi==bi){
blue[0].setposition(-1,pi[3]);
blue[0].homeway=0;
}
delay(500);
cleardevice();
showboard();
displayplayer(red,yellow,green,blue);
}
}
if(turn==3){
if(gi!=1&&gi!=9&&gi!=14&&gi!=22&&gi!=27&&gi!=35&&gi!=40&&gi!=48){
if(gi==ri){
red[0].setposition(-1,pi[0]);
red[0].homeway=0;
}
if(gi==yi){
yellow[0].setposition(-1,pi[1]);
yellow[0].homeway=0;
}
if(gi==bi){
blue[0].setposition(-1,pi[3]);
blue[0].homeway=0;
}
delay(500);
cleardevice();
showboard();
displayplayer(red,yellow,green,blue);
}
}
if(turn==4){
if(bi!=1&&bi!=9&&bi!=14&&bi!=22&&bi!=27&&bi!=35&&bi!=40&&bi!=48){
if(bi==ri){
red[0].setposition(-1,pi[0]);
red[0].homeway=0;
}
if(bi==yi){
yellow[0].setposition(-1,pi[1]);
yellow[0].homeway=0;
}
if(bi==gi){
green[0].setposition(-1,pi[2]);
green[0].homeway=0;
}
delay(500);
cleardevice();
showboard();
displayplayer(red,yellow,green,blue);
}
}

if(n==6){
csc++;
goto repeat;
}
}
}
}
int login()
{   char username[20];
    char password[20];
    char xuser[20];
    char xpass[20];
   // ofstream xFile;
    ifstream cFile;
   // xFile.open("login.txt");
    cFile.open("login.txt");
    // if(there are existing username and password in the file){
    //     the file will not be overwritten and continues off to a new line
    //}
  /* cout<<"Register"<<endl;
    cout<<"Username: ";
    cin>>username;
    cout<<"Password: ";
    cin>>password;
    xFile << username << endl;
    xFile << password << endl;
    clrscr();*/
    cout<<"Login"<<endl;
    cout<<"Username: ";
    cin>>username;
    cout<<"Password: ";
    cin>>password;
    cFile>>xuser;
    cFile>>xpass;
   // cout<<xuser;
   // cout<<xpass;
    if((stricmp(xuser,username))||(stricmp(xpass,password)))
      {
     return 0;
     }
     else
  return 1;
  cFile.close();
  //xFile.close();


}

//main function
void main(){
int a;
    clrscr();
    a=login();
   // cout<<a;
    if(a==1)
     {
int gd=DETECT,gm,x=0,y=465,i,j,k,n;
char ch;
initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

while(1){
cleardevice();
outtextxy(230,50,"***WELCOME TO LUDO***");
setcolor(BLUE);
rectangle(215,35,410,70);
setcolor(WHITE);
outtextxy(100,170,"*Enter number of players(2,3,4) & press Enter key to play*");
outtextxy(x+20,y-10,"Created By: GARV Chaplot and VAIBHAV Singhvi");
outtextxy(y+10,y-10,"Press Esc to exit");
outtextxy(310,200,"_");

outtextxy(290,290,"*Rules*");
outtextxy(240,310,"1 unlocks the player.");
outtextxy(240,330,"6 gives another turn.");
outtextxy(185,350,"3 consecutive 6 makes the player out.");
ch=getch();
if(ch==27){
exit(0);
}
if(ch==50||ch==51||ch==52){
if(ch==50){
outtextxy(310,190,"2");
n=2;
}
if(ch==51){
outtextxy(310,190,"3");
n=3;
}
if(ch==52){
outtextxy(310,190,"4");
n=4;
}
while(1){
ch=getch();
if(ch==13){
break;
}
if(ch==27){
exit(0);
}
}
break;
}
}
cleardevice();
showboard();
Position p[76];
Position pi[4];
initializecoords(p);
initializecoords2(pi);

Player red[1];
Player yellow[1];
Player green[1];
Player blue[1];
initializeplayer(red,yellow,green,blue,pi,n);
displayplayer(red,yellow,green,blue);

i=1;
while(1){
if((i==1 && red[0].status==1)||(i==2 && yellow[0].status==1)||(i==3 && green[0].status==1)||(i==4 && blue[0].status==1)){//execute rolldice for only active player
rolldice(red,yellow,green,blue,p,pi,i);
}
i++;
if(i==5)
i=1;
}
closegraph();
}

else
{
cout<<"sorry!!! wrong user name or password";
}
getch();
}









