#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>   /* ����Windowsƽ̨����������ַ��������Ժͻس�ȷ�ϵ�getch()���� */
#include <windows.h> /* ����Windowsƽ̨������趨������λ�ôﵽ�������ܵĺ��� */ 

#define R 4
#define C 4

typedef struct _Position *PtrToPosition;
typedef struct _Position{
	int Row, Col;
}Position;

//int game_num[R][C] = {{2,2,2,2},{2,4,2,4},{2,0,2,0},{0,2,0,2}};//���������� 
int game_num[R][C] = {0};
int game_over = 0, if_need_add_num=0; 
int currentScore = 0, bestScore = 0;
int i, j;//ʹ��̫Ƶ��������Ϊȫ�ֱ��� 

void start_game(void);
void init_game(void); //��ʼ��game_num�������������������Ϊ��ʼֵ 
void check_game(void);//�����Ϸ�Ƿ��ܼ���
void LeadSpace(int space);
void play_again(void);
void game_isover(void);
void game_quit(void);
void draw_gameover(void);
void draw_interface(void);
void move_left(void);
void move_right(void);
void move_up(void);
void move_down(void);
void RandomNumer(void);

int main(void)
{
	start_game();
	
	return 0;
} 

void start_game(void){		
	char cmd;
	
	init_game();//��ʼ��game_num�������������������Ϊ��ʼֵ 
	
	while(1){
		if( if_need_add_num )
		     RandomNumer();
		if_need_add_num=0;
		draw_interface();
		check_game();
		if( game_over == 1 ) //�����Ϸ�Ƿ��ܼ��� 
		    draw_gameover();
		T:cmd = getch();	    
	
		if( game_over == 1 ){//һ����Ϸ����ֹ 		    
			switch(cmd){
				//ָ����� 
			    case 'Y':
			    case 'y':
				    play_again();break;
			    case 'N':
			    case 'n':			
			        game_isover();break;
			    case -32://�������ɨ���룬���ֽڣ����ֽ����������� 
			    	break;
			    default:
			    	printf("Unkown keys\n"); goto T;
			}
			if( game_over ) break;
		}
		else{
			switch(cmd){
			    //�ֶ���ֹ��Ϸ			
			    case 'Q': 
			    case 'q':
				    game_quit();break; 
			    //������� 
			    case 'A':
			    case 'a':
			    case 75:
				    move_left();break; 
			    case 'D':
			    case 'd':
			    case 77:
				    move_right();break; 
			    case 'W':
			    case 'w':
			    case 72:
				    move_up();break; 
			    case 'S':
			    case 's':
			    case 80:
				    move_down();break; 
				case -32:
					break;
				default:
			    	printf("Other keys"); goto T;
		    }			
		} 						
	}
}

int Random(int max){
	return rand() % max;
}

//2��4���ָ��ʣ�2:1 
int GetRandNum(){
	if( Random(6) <=3 )
		return 2;
	else
	    return 4;
}

void init_game(void){	
	srand((int)time(NULL));
	
	for( i=0; i<R; i++)
	    for( j=0; j<C; j++)
	        game_num[i][j] = 0;
	        
	game_over = 0;
	bestScore = currentScore;
	currentScore = 0;
	
	Position num1, num2;	
	int randRow, randRowCol, randNum1, randNum2;
	num1.Row = Random(R); num1.Col = Random(C);
	num2.Row = Random(R);
	while( (num2.Col = Random(C)) == num1.Col && num2.Row == num2.Row );//��֤num1��num2������ͬһ��λ�� 
	
	game_num[num1.Row][num1.Col] = GetRandNum();
	game_num[num2.Row][num2.Col] = GetRandNum();
}

void check_game(void){	   
	int i, j;
    for ( i = 0; i < R; i++){
        for ( j = 0; j < C-1; j++){
        	//���п�λ 
        	if( game_num[i][j] == 0 || game_num[i][j+1] == 0 || game_num[j][i] == 0 || game_num[j+1][i] == 0 ) {
        		game_over = 0;
        		return;
			}
            /* ���������Ƚϰ��ŵ�����Ԫ���Ƿ���ȣ������������Ϸ������ */
            if (game_num[i][j] == game_num[i][j+1] || game_num[j][i] == game_num[j+1][i]){
                game_over = 0;
                return;
            }
        }
    }
    game_over = 1;
}

void play_again(void){
	system("cls");
	init_game();
}

void game_isover(void){
	system("cls");
	printf("\n\n\n");
	LeadSpace(15);
	printf("Game is over!\n");
	LeadSpace(15);
	printf("The Best Score is %d!\n", bestScore);
}

void game_quit(void){
	game_over = 1; 
}

void draw_gameover(void){
//	system("cls");
	printf("\n\n\n");
	LeadSpace(10);
	printf("Game is over! Are you want to play again?\n");
	LeadSpace(15);
	printf("Press Y to Yes, or press N to No\n");
}

void LeadSpace(int space){
	int k;
	for( k=0; k<space; k++)
		printf(" ");
}

void draw_interface(void){
	COORD pos = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    
	int blank = 20;//�����е�ǰ�ÿհ� 
//	system("cls");
	printf("\n\n\n");
	LeadSpace(10);
	printf("Game: 2048    The Best Score: %d    The Current Score: %d\n", bestScore, currentScore); 
	LeadSpace(blank);
	printf("�������������Щ����������Щ����������Щ�����������\n");
	
	int i, j;
	for( i=0; i<R; i++){
		LeadSpace(blank);	
	    printf("��");		
		for( j=0; j<C; j++){
			if( game_num[i][j] == 0 )
			    printf("     ��");
			else
			    printf("%5d��", game_num[i][j]); 
		}
		printf("\n");
		LeadSpace(blank);
		if( i < R-1 ){
			printf("�������������੤���������੤���������੤����������\n");
		}		    		    
		else{
			printf("�������������ة����������ة����������ة�����������\n"); 
		}		    
	}	  
	LeadSpace(blank+5);
	printf("W��  A��  ��D  ��S\n"); 
}

void RandomNumer(void){
	srand((int)time(NULL));
	
	int i, j, k=0, num, index;
	Position p[R*C];
	num = GetRandNum();//��ȡ����� 
	for( i=0; i<R; i++)
		for( j=0; j<C; j++)
		    if( game_num[i][j] == 0 ){//�ռ����п�λ 
		    	p[k].Row = i; p[k].Col = j;
		    	k++;
			}   
	index = Random(k);//�����λ 
	game_num[p[index].Row][p[index].Col] = num;	    
} 

void merge_help(int num[], int n){
	int i, j=0;
	for( i=0; i<n; i++)
		if( num[i] == 0 ){//�����治Ϊ0����ǰ�ƣ�����Ϊ0��λ�� 
			for( j=i+1; j<n; j++)
				if( num[j] != 0 ){
					if_need_add_num |= 1;
					break;
				}
				    
			if( i<n && j<n ){
				num[i] = num[j];
			    num[j] = 0;			    
			} 		
		}
} 

void merge(int num[], int n){	
	//��������ǰ 
    merge_help(num, n);	
	//�ϲ����֣����ܻ��ٴγ��ֿո�
	int i; 
	for( i=0; i<n-1; i++){
		if( num[i] == num[i+1] ){
			currentScore += num[i+1];//���ֱ�׼ 
			num[i] += num[i+1];
			num[i+1] = 0;
			if( num[i+1] != 0 )//0+0����ϲ� 
			    if_need_add_num |= 1;//��ⷢ���ϲ� 
    	}
	}
	//�ٴ�������ǰ	    
	merge_help(num, n);
} 

void move_left(void){
	int i;
    for( i=0; i<R; i++)
    	merge(game_num[i], C);	     
}
void move_right(void){
	int i, j, k, num[C];
	for( i=0; i<R; i++){
		k=0;
		//�Ƚ����鷴�� ���ٺϲ�����������¸�ֵ 
		for( j=C-1; j>=0; j--)
			num[k++] = game_num[i][j];
		merge(num, k);
		k=0;
		for( j=C-1; j>=0; j--)
			game_num[i][j] = num[k++];
	}
}
void move_up(void){
	int i, j, k, num[R];
	for( i=0; i<C; i++){
		k=0;
		//�Ƚ����鷴�� ���ٺϲ�����������¸�ֵ 
		for( j=0; j<R; j++)
			num[k++] = game_num[j][i];
		merge(num, k);
		k=0;
		for( j=0; j<R; j++)
			game_num[j][i] = num[k++];
	}
}

void move_down(void){
	int i, j, k, num[R];
	for( i=0; i<C; i++){
		k=0;
		//�Ƚ����鷴�� ���ٺϲ�����������¸�ֵ 
		for( j=R-1; j>=0; j--)
			num[k++] = game_num[j][i];
        merge(num, k);
		k=0;
		for( j=R-1; j>=0; j--)
			game_num[j][i] = num[k++];
	} 
}
