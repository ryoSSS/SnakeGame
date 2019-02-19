
//============インクルード=====================
#include "function.h"
//============================================


//--------------------------------------------
//              壁を生成する
//---------------------------------------------
void makeWalls(){

    int l,c; 

    for(l = 0; l <= WALL_ROW ; l++){
        mvaddch(l,0,WALL);
        mvaddch(l,WALL_LINE,WALL);
    }

    for(c = 0;c <= WALL_LINE ; c++){
        mvaddch(0,c,WALL);
        mvaddch(WALL_ROW,c,WALL);
    }

    mvprintw(WALL_ROW+3 ,  1 ,  "%c : GROW SNAKE" ,  FOOD);
    mvprintw(WALL_ROW+4 ,  1 ,  "%c : SPEED UP"   ,  POWER);
}


//---------------------------------------------
//                乱数を返す
//---------------------------------------------
int GetRandom(int st){
    return (  rand() % (st-2)  ) +1;
}


//---------------------------------------------
//          スネークのメモリを解放する
//---------------------------------------------
void freeBody(struct BODY *body){
    struct BODY *p = body;

    while(p != NULL){
        p = body->next; 
        free(body);
        body = p;
    }
} 


//---------------------------------------------
//           スネークの体１節を生成する
//---------------------------------------------
void makeBody(struct BODY **body){
   
    struct BODY *new;
    static struct BODY *ptr;
    new = (struct BODY *)malloc(sizeof(struct BODY)); 
    if(*body == NULL){
        *body = new;
        new -> X = 1;
        new -> Y = 1;
        new -> pattern = HEADCHAR;
        ptr = *body;
    }else{
        ptr->next = new;   
        new -> X = ptr->X;
        new -> Y = ptr->Y;
        new -> pattern = BODYCHAR; 
        ptr = new;
    }

    new -> next = NULL;
}


//---------------------------------------------
//              スネークの座標を変える
//----------------------------------------------
void moveSnake(struct BODY **body,int x,int y){
    int preX,preY;
    struct BODY *ptr;
    ptr = *body;

    preX = ptr->X;
    preY = ptr->Y;
    ptr -> X = preX + x;
    ptr -> Y = preY + y;

    while(ptr->next != NULL){
        ptr = ptr->next;
        x = preX;
        y = preY;
        preX = ptr->X;
        preY = ptr->Y;
        ptr->X = x;
        ptr->Y = y;
    }
     mvaddch(preY,preX,' '); 
}


//---------------------------------------------
//                餌を生成する
//---------------------------------------------
void makeFood(int t){
    
    if(t%20 == 0){
        mvaddch(GetRandom(WALL_ROW),GetRandom(WALL_LINE),FOOD);
    }
    if(t%50 == 0 && t != 0){
        mvaddch(GetRandom(WALL_ROW),GetRandom(WALL_LINE),POWER);    
    }

    
    refresh();
}


//---------------------------------------------
//         　　スネークの体長を返す
//---------------------------------------------
int getLength(struct BODY *snake){

    int length = 1;

    while(snake->next != NULL){
        length++;
        snake = snake->next;
    }

    return length;
}

//---------------------------------------------
//         スネークをスクリーンに表示する
//---------------------------------------------
void drawSnake(struct BODY *body){
        
    do{
        mvaddch(body->Y,body->X,body->pattern);
        body = body -> next;
    }while(body != NULL);

    refresh();
}


//---------------------------------------------
//             　ファイル書き込み
//---------------------------------------------
void writeFile(int *length){
    FILE *fp;

    if((fp = fopen(FILENAME,"wb")) == NULL)
        printf("\file not open\n");
    else{
        fwrite(length,sizeof(int),1,fp);
        fclose(fp);
    }
}


//----------------------------------------------
//            　   ファイル読み出し
//----------------------------------------------
void readFile(int *length){

    FILE *fp;

    if((fp = fopen(FILENAME,"rb")) == NULL){
        length = 0;
    }
    else{
        fread(length,sizeof(int),1,fp);
        fclose(fp);
    }
}


//---------------------------------------------
//                  終了画面
//---------------------------------------------
void printEnd(struct BODY *snake){

    clear();

    int length = getLength(snake);

    mvprintw(WALL_ROW/2,(WALL_LINE/2)-13,"YOUR SNAKE LENGTH  %d (m)",length);
    refresh();
    sleep(5);

    clear();

    int bestlength = 0;
    readFile(&bestlength);
    
    if( bestlength < length ){
        mvprintw(WALL_ROW/2,(WALL_LINE/2)-13,"!!! BREAK BEST LECORD !!!",length);
        mvprintw((WALL_ROW/2)+2,(WALL_LINE/2)-7,"%d (m) -> %d (m)",bestlength,length);
        refresh();
        sleep(5);
        writeFile(&length);
    }else{
        mvprintw(WALL_ROW/2,(WALL_LINE/2)-9,"NOT LECORD UPDATE");
        mvprintw((WALL_ROW/2)+2,(WALL_LINE/2)-9,"BEST LECORD %d (m)",bestlength);
        refresh();
        sleep(5);
    }

    clear();
}
