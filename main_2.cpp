#include <clocale>
#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
 
void print_gen(char gen_array[][101]);
bool keygen_array(char ch);
void move_left();
void move_right();
void move_down();
void move_up();
void cell_change();
void save(	std::ifstream& fin);
void open();
void game(char gen_array[][101]);
void f_open(std::ifstream& fin);
char gen_array[101][101];
std::ofstream fout;
std::ifstream fin;
int argc;
int x=1;
int y=1;
int row,col;
char str[512];
char *get;

int main(int argc, char* argv[])
{
	
	if(argc !=2)
	{
		std::cout<<"Usage: life <0th_gen.txt>" << std::endl;
		return -1;
	}
	
	
	
 	setlocale(LC_CTYPE, "");	
	initscr();
	curs_set(0);
	noecho();
	start_color();
	
	init_pair(1,COLOR_WHITE,COLOR_BLACK);
	init_pair(2,COLOR_RED,COLOR_BLACK);
	

	fin.open(argv[1]);
	f_open(fin);	


	char ch;
 
 	while (true)
	{	
		ch = getch();

		if (ch == 'q' || ch=='Q')
			break;
		if (ch == 'o' || ch=='0')
		{
		
		   clear();
		   printw("open file :");
          echo();
		  
          getstr(str);
		   argv[1]=str;

		   fin.open(argv[1]);
		   f_open(fin);
		}
		
		noecho();
		bool jud = keygen_array(ch);
	
	}

	endwin();
	getch();
	//endwin();
	fin.close();
	return 0;
}
 
bool keygen_array(char ch)
{
	switch(ch)
	{
		case 'h':	
       case 'H':
		y--;
		move_left();
		return true;

		case 'l':
       case 'L':
		y++;
		move_right();
		return true;

		case 'j': //down
       case 'J':
		x++;
		move_down();
		return true;
	
		case 'k' : //up
       case 'K' :
		x--;
		move_up();
		return true;
		
		case 't' : //change        
       case 'T':

		cell_change();
		return true;

		case 's' :
       case 'S':
		clear();
		echo();
		printw("Save file : ");
		save(fin);
		return true;
		
		case 'n':
		case 'N':
		game(gen_array);
		return true;
		
	}

}
void game(char gen_array[][101])
{

	int count[102][102] = {0};
	int cnt = 0;

		for (int i = 1; i <= row; i++)
		{
			for (int j = 1; j <= col; j++)
			{
				if (gen_array[i - 1][j - 1] == 79)
				{
					cnt++;
				}
				if (gen_array[i - 1][j] == 79)
				{
					cnt++;
				}
				if (gen_array[i - 1][j + 1] == 79)
				{
					cnt++;
				}
				if (gen_array[i][j - 1] == 79)
				{
					cnt++;
				}
				if (gen_array[i][j + 1] == 79)
				{
					cnt++;
				}
				if (gen_array[i + 1][j - 1] == 79)
				{
					cnt++;
				}
				if (gen_array[i + 1][j] == 79)
				{
					cnt++;
				}
				if (gen_array[i + 1][j + 1] == 79)
				{
					cnt++;
				}
				count[i][j] = cnt;
				cnt = 0;
			}
		}

		for (int i = 1; i <= row; i++) // X,0 바꾸기
		{
			for (int j = 1; j <= col; j++)
			{
				if (count[i][j] == 0)
				{
					if (gen_array[i][j] == 79)
					{
						gen_array[i][j] ==79;
					}
					if (gen_array[i][j] == 88)
					{
						gen_array[i][j] = 88;
					}
				}

				if (count[i][j] == 1)
				{
					if (gen_array[i][j] == 79)
					{
						gen_array[i][j] = 88;
					}
					else if (gen_array[i][j] == 88)
					{
						gen_array[i][j] = 88;
					}
				}
				if (count[i][j] == 2)
				{
					if (gen_array[i][j] == 79)
					{
						gen_array[i][j] = 79;
					}
					else if (gen_array[i][j] == 88)
					{
						gen_array[i][j] = 88;
					}
				}
				if (count[i][j] == 3)
				{
					if (gen_array[i][j] == 79)
					{
						gen_array[i][j] = 79;
					}
					else if (gen_array[i][j] == 88)
					{
						gen_array[i][j] = 79;
					}
				}

				if (count[i][j] >= 4)
				{
					if (gen_array[i][j] == 79)
					{
						gen_array[i][j] = 88;
					}
					else if (gen_array[i][j] == 88)
					{
						gen_array[i][j] = 88;
					}
				}

			}
		}

print_gen(gen_array);

}



void f_open(std::ifstream& fin)
{
	char a;
 
	fin>>row>>col;

	for(int i=1; i<=row; i++)
	{
		for(int j=1; j<=col; j++)
		{
			fin>>a;
			gen_array[i][j]=a;
		}
	}
	
	print_gen(gen_array);

}

void save(	std::ifstream& fin)
{
char str_[512];
getstr(str_);


fout.open(str_);
fout<<row<<" "<<col<<std::endl;

for(int i=1; i<=row; i++)
{
	for(int j=1; j<=col; j++)
	{
		fout<<gen_array[i][j];
	}
	fout<<"\n";
}
		
fout.close();

}
void cell_change()
{

	if(gen_array[x][y]=='X')
	{
		gen_array[x][y]='O';
		print_gen(gen_array);
	}
	else
	{
		gen_array[x][y]='X';
		print_gen(gen_array);
	}

	
}

void move_up()
{
	if(x>=1 && y>=1 && x<=row && y<=col)
	{
		print_gen(gen_array);
	}
	
	if(x==0)
	{
		x=1;
		print_gen(gen_array);
	}
}
void move_down()
{
	if(x>=1 && y>=1 && x<=row && y<=col)
	{
		print_gen(gen_array);	
	}
	
	if (x==row+1)
	{
		x=row;
		print_gen(gen_array);
	}
	
}
void move_right()
{
	if(x>=1 && y>=1 && x<=row && y<=col)
	{
		print_gen(gen_array);
	}
	if (y==col+1)
	{
		y=col;

		print_gen(gen_array);
	}
}

void move_left()
{
	if(x>=1 && y>=1 && x<=row && y<=col)
	{
		print_gen(gen_array);
	}
	
	if (y==0)
	{
		y=1;
		print_gen(gen_array);
	}
}
 
void print_gen(char gen_array[][101])
{
	clear();
	resize_term(300,500);
 
	attron(COLOR_PAIR(1));

	mvprintw(0,1,"\u002B");
	mvprintw(row+1,1,"\u002B");
	mvprintw(0,col*2+2,"\u002B");
	mvprintw(row+1,(col+1)*2,"\u002B");

	for(int i=2; i<=col*2+1; i++)
	{
		mvprintw(0,i,"\u002D");
		mvprintw(row+1,i,"\u002D");
	}

	for(int i=1; i<=row; i++)
	{
		mvprintw(i,1,"\u007C");
		mvprintw(i,(col+1)*2,"\u007C");
	}
	
	for(int i=1; i<=row; i++)
	{
		for(int j=1; j<=col; j++)
		{

			if(gen_array[i][j]== 'O')
				mvprintw(i,j*2,"\u2B1B");
			else
				mvprintw(i,j*2,"\u2B1C");
		}
	}
	
	attron(COLOR_PAIR(2));
	
	if(gen_array[x][y] == 'O')
		mvprintw(x,y*2,"\u2B1B");
	else
		mvprintw(x,y*2,"\u2B1C");
	attroff(COLOR_PAIR(2));
	refresh();

	//attroff(COLOR_PAIR(1));
	
	refresh();

}
