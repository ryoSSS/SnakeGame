

//============インクルードファイル==============
#ifndef FUNCTION_H    //インクルードガード
#define FUNCTION_H
#include "curses.h"
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <unistd.h>
//============================================

//==================マクロ=====================
#define WALL_ROW  (LINES-10)     //壁の縦の長さ
#define WALL_LINE (COLS -5)      //壁の横の長さ
#define HEADCHAR '@'           //スネークの頭
#define BODYCHAR 'o'           //スネークの体
#define FOOD '#'               //餌
#define POWER 'P'              
#define WALL '*'                //壁
#define FILENAME "save.bin"
//=============================================


//スネークの体１節の構造体。これが繋がってスネーク全体となる。
struct BODY{
    int X;             //体がある座標
    int Y;   
    char   pattern;    //模様
    struct BODY *next; //リスト構造でスネークの体を制御する
};



//関数の仮定義
void makeWalls();                         //壁の作成
int  GetRandom(int);                       //0から引数までの範囲の乱数を返す
void freeBody(struct BODY *);             //スネークの確保したメモリ解放               
void makeBody(struct BODY**);             //スネークの体を一つ増やす  
void moveSnake(struct BODY**,int,int);    //スネークを動かす
int  getLength(struct BODY*);             //スネークの体長を返す
void drawSnake(struct BODY*);             //スネークの体全体を描画する 
void makeFood(int);                       //食べ物をフィールドに描画する
void writeFile(int *);                    //引数の値でファイルを上書き
void readFile(int *);                     //ファイルから読み込んだ値を引数のアドレスに渡す
void printEnd(struct BODY*);              //終了画面を表示する


#endif  //インクルードガード
