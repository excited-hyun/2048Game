#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <termios.h>
#include <sys/time.h>
#include <unistd.h>

/* game over flag & board state */
int game_over, b[4][4];
FILE *fp;

void init(){
	int i, j;
	game_over = 0;
	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			b[i][j] = 0;
}


void rotate(int b[4][4]){
	int i, j;
	int a[4][4];
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			a[i][j] = b[3-j][i];
		}
	}

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			b[i][j] = a[i][j];
		}
	}	
}

int set_board(int dir, int b[4][4]){

	int i, j, k, l;
	int temp[4][4];
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			temp[i][j] = b[i][j];
		}
	}

	if(dir == 0)
	{
		for (k = 0; k < 3; k++)
		{
			for (i = 0; i < 4; i++)
			{
				for (j = 3; j > 0; j--)
				{
					if (b[i][j] == 0)
					{
						for (l = j; l > 0; l--)
						{
							b[i][l] = b[i][l - 1];
						}
						b[i][0] = 0;
					}
				}
			}
		}
		for (i = 0; i < 4; i++)
		{
			for (j = 3; j > 0; j--)
			{
				if (b[i][j] == b[i][j - 1])
				{
					b[i][j] = b[i][j] + b[i][j - 1];
					for (k = j - 1; k > 0; k--)
					{
						b[i][k] = b[i][k - 1];
					}
					b[i][0] = 0;
				}
			}
		}
	}
	else if(dir == 1)
	{
		for(i=0; i<dir; i++)
		{
			rotate(b);
		}
		for (k = 0; k<3; k++)
		{
			for (i = 0; i<4; i++)
			{
				for (j = 3; j>0; j--)
				{
					if (b[i][j] == 0)
					{
						for (l = j; l>0; l--)
						{
							b[i][l] = b[i][l - 1];
						}
						b[i][0] = 0;
					}
				}
			}
		}

		for (i = 0; i < 4; i++)
		{
			for (j = 3; j > 0; j--)
			{
				if (b[i][j] == b[i][j - 1])
				{
					b[i][j] = b[i][j] + b[i][j - 1];
					for (k = j - 1; k > 0; k--)
					{
						b[i][k] = b[i][k - 1];
					}
					b[i][0] = 0;
				}
			}
		}
		for(i=0; i<4-dir; i++)
		{
			rotate(b);
		}
	}
	else if(dir == 2)
	{
		for(i=0; i<dir; i++)
		{
			rotate(b);
		}
		for (k = 0; k<3; k++)
		{
			for (i = 0; i<4; i++)
			{
				for (j = 3; j>0; j--)
				{
					if (b[i][j] == 0)
					{
						for (l = j; l>0; l--)
						{
							b[i][l] = b[i][l - 1];
							
						}
						b[i][0] = 0;
					}
				}
			}
		}

		for (i = 0; i < 4; i++)
		{
			for (j = 3; j > 0; j--)
			{
				if (b[i][j] == b[i][j - 1])
				{
					b[i][j] = b[i][j] + b[i][j - 1];
					for (k = j - 1; k > 0; k--)
					{
						b[i][k] = b[i][k - 1];
					}
					b[i][0] = 0;
				}
			}
		}


		for(i=0; i<4-dir; i++)
		{
			rotate(b);
		}
	}
	else if(dir == 3)
	{
		for(i=0; i<dir; i++)
		{
			rotate(b);
		}
		for (k = 0; k<3; k++)
		{
			for (i = 0; i<4; i++)
			{
				for (j = 3; j>0; j--)
				{
					if (b[i][j] == 0)
					{
						for (l = j; l>0; l--)
						{
							b[i][l] = b[i][l - 1];
							
						}
						b[i][0] = 0;
					}
				}
			}
		}

		for (i = 0; i < 4; i++)
		{
			for (j = 3; j > 0; j--)
			{
				if (b[i][j] == b[i][j - 1])
				{
					b[i][j] = b[i][j] + b[i][j - 1];
					for (k = j - 1; k > 0; k--)
					{
						b[i][k] = b[i][k - 1];
					}
					b[i][0] = 0;
				}
			}
		}
	
		for(i=0; i<4-dir; i++)
		{
			rotate(b);
		}
	}
	
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			if(temp[i][j] != b[i][j])
			{
				return 1;
			}
		}
	}

	return 0;
}

int is_game_over(){
	int i, j, k=0, a = 0;
	int temp[4][4];
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			temp[i][j] = b[i][j];
		}
	}
	while(1)
	{
		if(k==4)
		{
			break;
		}
		a+=set_board(k, temp);
		k++;
	}
	if(a==0)
	{
		return 1;
	}
	
	/* if game over return 1, else then return 0 */
	return 0;
}

void draw_board(int tot, int command){
	int i, j, k, c[8][8], score;
	int total =0;
	/* console clear */
	system("clear");

	score = 0;
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			if(b[i][j] > score)
			{
				score = b[i][j];
			}
			total = total + b[i][j];
		}
	}
	if(tot != total)
	{
		printf("error\n");
	}

	
	/*user code*/
	/* calculate score & check sum of all block equasls variable tot */



	printf("    Score : %d\n", score);
	fprintf(fp, "%d %d\n", score, command);

	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			c[i][j] = 32;
			for(k=0; k<50; k++){
				if( b[i][j] == (1<<k) ){
					c[i][j] = 32 + (k%6);
					break;
				}
			}

		}
	}
	for(i=0; i<4; i++){
		for(j=0; j<4; j++)
			fprintf(fp, "%d ", b[i][j]);
		fprintf(fp, "\n");
	}

	for(i=0; i<4; i++){
		puts("");
		puts("");
		for(j=0; j<4; j++)
			printf("\033[%dm%5d\033[0m", c[i][j], b[i][j]);
		puts("");
		puts("");
	}
}

int make_two_or_four(){
	

	int per, n, i, j, areax, areay, sw=0;
	per = rand()%3;
	if(per == 1)
	{
		n = 4;
	}
	else
	{
		n=2;
	}
	for(i=0;i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			if(b[i][j] ==0)
			{
				sw=1;
			}
		}
	}
	if(sw==0)
	{
		return 0;
	}
	for(i=0; ;i++)
	{
		areax = rand()%4;
		areay = rand()%4;
		if(b[areax][areay] == 0)
		{
			b[areax][areay] = n;
			return n;
			break;
		}
	}
	/* if can not make two or four, then return 0 */
}


int getch(void)
{
	char   ch;
	int   error;
	static struct termios Otty, Ntty;

	fflush(stdout);
	tcgetattr(0, &Otty);
	Ntty = Otty;
	Ntty.c_iflag = 0;
	Ntty.c_oflag = 0;
	Ntty.c_lflag &= ~ICANON;
#if 1
	Ntty.c_lflag &= ~ECHO;
#else
	Ntty.c_lflag |= ECHO;
#endif
	Ntty.c_cc[VMIN] = 0;
	Ntty.c_cc[VTIME] = 1;

#if 1
#define FLAG TCSAFLUSH
#else
#define FLAG TCSANOW
#endif

	if (0 == (error = tcsetattr(0, FLAG, &Ntty)))
	{
		error = read(0, &ch, 1);
		error += tcsetattr(0, FLAG, &Otty);
	}

	return (error == 1 ? (int)ch : -1);
}


int GetCommand() {
	int ch = getch();

	switch (ch)
	{
	case 'd':
	case 'D': return 0;
	case 'w':
	case 'W': return 1;
	case 'a':
	case 'A': return 2;
	case 's':
	case 'S': return 3;
	default: return -1;
	}

	return -1;
}


int main() {
	int command = -1, i;
	fp = fopen("output.txt", "w");
	init();
	srand(time(NULL));

	int tot = 0;
	/* make init board */
	/* user code */
	for(i=0; i<2; i++)
	{
		tot = tot + make_two_or_four();
	}
	draw_board(tot, -1);

	
	do {
		command = GetCommand();

		if (command != -1) {
			if( set_board(command, b) ){

				/* user code */
				
				tot = tot+make_two_or_four();
				draw_board(tot, command);
				game_over = is_game_over();
			}
		}

	} while (!game_over);

	system("clear");
	printf("game over!\n");
	fclose( fp );
}
