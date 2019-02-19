//===========================================
//              　  SNAKE GAME
//============================================


//============インクルードファイル==============
#include "function.h" 
//============================================



//---------------------------------------------
//                  メイン
//---------------------------------------------
int main(int argc,char *argv[]){

    //スクリーンを使うための準備
    initscr();              //cursesの領域確保
    noecho();               //キーを打っても出力されない
    nonl();                 //カーソルの動き高速化
    cbreak();               //入力した文字を即時利用可能にする
    wtimeout(stdscr,0);     //フレームベースな処理を可能にする
    keypad(stdscr,TRUE);    //十字キー有効
    curs_set(0);            //カーソルを見えなくする。

    
    //現在の時間で乱数調整
    srand((unsigned int)time(NULL)); 



    int ch;             //文字の取得につかう
    int x;              //座標
    int y;              
    int t;              //ゲームの流れをカウント
    int delay;          //ゲームの動作の速さを制御

    struct BODY *snake; 


    START:

    //初期設定
    snake = NULL;       
    x = 1;              
    y = 0;
    delay = 100000;
    t = 0;


    makeBody(&snake);   //頭を生成
    makeWalls();        //壁を生成


    while(1){

        makeFood(t);    //餌を生成


        usleep(delay);  //delayスリープすることでスネークの速さを調節   


        ch = getch();           //キーボードからの入力を取得
        switch(ch){             //入力によってスネークの進む向きを設定
            case KEY_LEFT : if(x !=  1)x = -1; y = 0; break;    
            case KEY_RIGHT: if(x != -1)x =  1; y = 0; break;
            case KEY_UP   : if(y !=  1)y = -1; x = 0; break;
            case KEY_DOWN : if(y != -1)y =  1; x = 0; break;
            default       : break; 
        }

        
        moveSnake(&snake,x,y);   //スネークの座標を変化させる

        move(snake->Y,snake->X); //カーソルを頭の座標に移動
        ch = inch();             //カーソル部分の文字を取得

        switch(ch){              
            case FOOD    :   makeBody(&snake);  break;   
            //スピードアップ     
            case POWER   :   delay -= 1000   ;  break;    
            case WALL    :   goto END;                     
            case BODYCHAR:   goto END;
            default      :   break;
        } 

        //スネークの体長をスクリーンに表示する
        mvprintw(WALL_ROW + 1 ,  1 ,  "LENGTH : %d m" ,getLength(snake));   


        //スネークの体長が増えるごとに１文字づつ表示される
        mvaddnstr(WALL_ROW + 6,  1 ,"oOoOo@ < Thank you for playing this Game!!! :)",getLength(snake)-1);   

        drawSnake(snake);   //スネークの体をスクリーンに表示する

        

        t++;                //１順をカウントする
    }


    END:

    
    printEnd(snake);        //終了画面を表示


    //ゲームを続けるか、辞めるかの選択
    do{
    mvprintw(WALL_ROW/2,(WALL_LINE/2)-9,"CONTINUE:c   QUIT:q");
        ch = getch();
        refresh();
        switch(ch){
            case 'c':  
                clear();
                freeBody(snake);
                goto START; 

            case 'q': break;
            default : break;
        }
    }while(ch != 'q');


    endwin();               //cursesの領域解放
    return 0;
}

