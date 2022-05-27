#include "TXLib.h"
#include <fstream>
using namespace std;

struct Form
{
string question;
int right_answer;
string answer1;
string answer2;
string answer3;
string address;

};

bool Click(int y)
{
return(txMouseButtons() ==1 &&
txMouseX() > 600 &&
txMouseX() < 1150 &&
txMouseY() > y &&
txMouseY() < y+50);
}

void DrawAnswer(int y, string text)
{
txSelectFont ("Comic Sans MS",55);
txRectangle(600,y,1150,y+50);
txDrawText(600,y,1150,y+50, text.c_str());
}


string getPart(int *pos2, string str)
{
int pos1 = *pos2 +1;
*pos2 =str.find(",",pos1 +1);
string part = str.substr(pos1, *pos2 - pos1);
return part;
}

int main()
{
txCreateWindow (1920, 1080);

txTextCursor (false);
int n = 0;
int n_q = n+1;
int result = 0;

Form form_question;
Form form[100];
string str;
string PAGE = "test";


ifstream file("Вопрос ответ.txt");
while(file.good())
{
getline(file, str);
int pos2 = -1;
form[n].question = getPart(&pos2, str);
form[n].right_answer = atoi(getPart(&pos2, str).c_str());
form[n].answer1 = getPart(&pos2, str);
form[n].answer2 = getPart(&pos2, str);
form[n].answer3 = getPart(&pos2, str);
form[n].address = getPart(&pos2, str);
n++;
}
file.close();

while(n_q <= n)
{ /*
if (PAGE=="menu");
{
txBegin();
txSetColor(TX_WHITE, 5);
txSetFillColor(TX_BLACK);
txBitBlt(txDC(), 0, 0, 1920, 1080, BACKGROUNDMAIN);
//Кнопка
txRectangle (689, 488, 1069, 548);
txDrawText (689, 488, 1069, 548, "НАЧАТЬ");
txRectangle (689, 688, 1069, 748);
txDrawText (689, 688, 1069, 748, "ВЫХОД");
//Клик
if( txMouseX() >= 689 &&
txMouseY() >= 488 &&
txMouseX() <= 1069 &&
txMouseY() <= 548 &&
txMouseButtons () == 1)
{
PAGE = "test";
}

if(txMouseX() >= 689 &&
txMouseY() >= 688 &&
txMouseX() <= 1069 &&
txMouseY() <= 748 &&
txMouseButtons () == 1)
{
return 0;
}
txEnd();
}
*/
if(PAGE=="test")
{
txBegin();
txClear();
txSetFillColor (TX_BLACK);
txSetColor (TX_WHITE);
txSetFillColor (TX_BLACK);

form_question = form[n_q-1];

txSelectFont ("Comic Sans MS",70);



txRectangle(0,185,1920,250);
txDrawText(0,185,1920,250,form_question.question.c_str());
DrawAnswer(350, form_question.answer1);
DrawAnswer(450, form_question.answer2);
DrawAnswer(550, form_question.answer3);


//клик
if(Click(350))
{
while(txMouseButtons() == 1) txSleep(50);
n_q++;
if(form_question.right_answer == 1)
{
result++;
}
}
if(Click(450))
{
while(txMouseButtons() == 1) txSleep(50);
n_q++;
if(form_question.right_answer == 2)
{
result++;
}
}
if(Click(550))
{
while(txMouseButtons() == 1) txSleep(50);
n_q++;
if(form_question.right_answer == 3)
{
result++;
}
}
txEnd();
txSleep(100);
}


}
txSetFillColor(TX_BLACK);
txClear();
txDrawText(50,50,750,100,"Результат");
char stroka[10];
sprintf(stroka, "%d", result);
txDrawText(50,150,750,200,stroka);
if(result < 8) txDrawText(50,250,750,350,"Ты не Валера");
else txDrawText(50,250,750,350,"Ты Валера");

return 0;
}
