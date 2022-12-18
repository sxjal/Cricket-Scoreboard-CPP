#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
class cricket
{
	int batsman;
	int bowler;
	public :
	int wicket[12];
	int total[12];
	int maiden[12];
	int six[12],four[12];
	int bl_over[12];
	char stat[12];
	int extra[12];
	int ch,md;
	int tot_bl[12];
	char mode[12];
	char name_batsman[12][50];
	char name_bowler[12][50];
	int ovr;
	int tt_wck;
	int seq_over[12];
	int b_played[12];
	int team;
	int bl,ball,over,bat,bat2;

void name_ent(int x)
{
	ifstream bt,bw;
	if( x == 1 )
	{
		bt.open("team1~1.txt",ios :: in);
		bw.open("team2~1.txt",ios :: in);
	}
	else
	{
		bw.open("team1~1.txt",ios :: in);
		bt.open("team2~1.txt",ios :: in);
	}
	if(!bt || !bw)
	{
		cout<<"\n No file found";
	}
	bt.seekg(0);
	bw.seekg(0);
	char line[50];
	for(int i = 0 ; i < 12 ; i++)
	{
		bt.getline(line,50);
		strcpy(name_batsman[i],line);
		bw.getline(line,50);
		strcpy(name_bowler[i],line);
	}

	bt.close();
	bw.close();
}


void bowl()
{

	if( ch == 1 )
	{
		bowler = batsman;
		tot_bl[bl] += batsman;
		if(batsman == 0)
		{
			md = md + 1;
			if(ball == 5 && md == 6)
			{
				maiden[bl] = maiden[bl] + 1;
			}
		}
	}
	else if( ch == 2 )
	{
		wicket[bl] = wicket[bl]  + 1;
	}
	else if( ch == 3 )
	{
		extra[bl] == extra[bl] + 1;
	}
}

void batting()
{
int k;
while(1)
{
	cout<<"\n Enter 1 if the batsman has hit runs ";
	cout<<"\n Enter 2 if the batsman got out ";
	cout<<"\n Enter 3 if it was a wide ball ";
	cin>>ch;

	if( ch == 1 )
	{
		while(1)
		{
			cout<<"\nEnter Runs hit by batsman "<<bat + 1<<" :";
			cin>>batsman;

			if(( batsman >=0 &&  batsman <= 4) || ( batsman == 6 ))
			{
				break;
			}
			else
			{
				cout<<"\n invalid runs entered,please enter again.";
				continue;
			}
		}

		total[bat] = batsman;
		team = team + batsman;
		b_played[bat] += 1;
		bowl();
		if( batsman == 1 || batsman == 3)
		{
			for(k = 0; k <11 ; k++)
			{
				if( bat == k )
				{
					continue;
				}
				else if( stat[k] == 'n' )
				{
					bat2 = bat;
					bat = k;
					break;
				}
			}
		}
		else if( batsman == 4 || batsman == 6)
		{
			if(batsman == 4)
			{
				four[bat] += 1;
			}
			else if(batsman == 6)
			{
				six[bat] += 1;
			}
		}

	break;
	}

	else if( ch == 2 )
	{
		stat[bat] = 'o';
		tt_wck = tt_wck + 1;
		cout<<"\n Enter mode by which got out ";
		cout<<"\n Enter B is bowled. Enter c if got out by catch :";
		cin>>mode[bat];
		bowl();

		for(k = 0; k <11 ; k++)
		{
			if( bat == k )
			{
				continue;
			}
			else if( stat[k] == 'n' && bat2 != k)
			{
				bat = k;
				break;
			}
		}

		break;

	}

	else if( ch == 3 )
	{
		bowl();
		team = team + 1;
		extra[bl] = extra[bl] + 1;
		ball =  ball - 1;
		break;
	}
	else
	{
		cout<<"\n Invalid input,Try again  :";
		continue;
	}


}// End of while
if(ball == 5)
{
	ch   = bat;
	bat  =  bat2;
	bat2 = ch;
}

}// End of function

void det()
{
	int i = 0;
	int x = 0;
	cout<<"\n Enter the bowling sequence :";
	while(1)
	{
		cout<<"\n Enter for "<<i + 1<<" over :";
		cin>>seq_over[i];
		if( seq_over[i] ==  x)
		{
			cout<<"\n A bowler cannot throw two overs simultaneoulsy.";
			continue;
		}
		else
		{
			x = seq_over[i];
			i++;
		}
		if(i >= ovr)
		{
			break;
		}
	}
}

void score_board(int x,int e)
{
	if( x == 1 )
	{
		int a = 0 ;
		cout<<"\n ----------------------\n ";
		cout<<"\n Bowling stats : ";
		for(int i = 0 ; i<ovr ; i++)
		{
			a = seq_over[i] - 1;
			cout<<"\n --------------------------------------";
			cout<<"\n"<<name_bowler[a];
			cout<<"\n * Runs given : "<<tot_bl[a];
			cout<<"\n * Overs played : "<<bl_over[i];
			cout<<"\n * Maiden Overs : "<<maiden[a];
			cout<<"\n * Wickets taken : "<<wicket[a];
			cout<<"\n * Extras : "<<extra[a];
		}
	}

	else if( x == 2 )
	{
		cout<<"\n ----------------------\n ";
		cout<<"\n Batting stats : ";
		for(int i =0 ; i<11 ; i ++)
		{
			cout<<"\n --------------------------------------";
			cout<<"\n"<<name_batsman[i];
			cout<<"\n * Runs taken :"<<total[i];
			cout<<"\n * Balls played : "<<b_played[i];
			cout<<"\n * Status : ";
			if(stat[i] == 'n' )
			{
				cout<<"\n * Not out";
			}
			else
			{
				cout<<"\n * Out : "<<mode[i];
			}
			cout<<"\n * Boundaries - ";
			cout<<"\n * Sixes :"<<six[i];
			cout<<"\n * Fours :"<<four[i];
		}
		cout<<"\n * Total Runs : "<<team;
	}

	if( e == 1 )
	{
		cout<<"\n Team 2 needs "<<team + 1<<" runs to win in "<<ovr<<" overs.";
	}
	cout<<"\n End of Innings ";
}

void construct()
{
	for(int i = 0 ; i<12 ; i++)
	{
		wicket[i] = 0;
		maiden[i] = 0;
		tot_bl[i] = 0;
		total[i] = 0;
		extra[i] = 0;
		six[i] = 0;
		four[i] = 0;
		b_played[i] = 0;
		stat[i] = 'n';
		seq_over[i] = 0;
	}

	ball   = 0;
	tt_wck = 0;
	over   = 0;
	bat    = 0;
	team   = 0;
	ball   = 0;
	bl     = 0;
	bat2   = bat + 1;
}
};

void main()
{
	clrscr();
	cricket a;

	int e = 1;

	cout<<"\n Enter no of over : ";
	cin>>a.ovr;

	int tt[3] = {0};

while(1)
{
	a.construct();
	cout<<"\n Innings "<<e;
	a.name_ent(e);
	a.det();
	for( a.over = 0 ; a.over < a.ovr ; a.over++)
	{
		a.bl = a.seq_over[a.over] - 1;
		a.bl_over[a.bl] += 1;
		cout<<"\n ------------------------";
		cout<<"\n Enter stats for "<<a.over + 1<<" over :";
		for( a.ball = 0 ; a.ball < 6 ; a.ball++)
		{
			cout<<"\n For ball : "<<a.ball + 1;
			cout<<"\n Current Batsman : "<<a.name_batsman[a.bat];
			cout<<"\n Batsman non strick : "<<a.name_batsman[a.bat2];
			cout<<"\n Current Bowler : "<<a.name_bowler[a.bl];
			a.batting();
			tt[e] = a.team;
			if( e == 2 && (tt[e] > (tt[e-1] + 1)))
			{
				cout<<"\n Match Over.";
				goto ov;
			}
			if(a.tt_wck > 10)
			{
				cout<<"\n Inninngs Over,All out :";
				goto ov;
			}
		}
	}

	ov :
	getch();
	int b;
	while(1)
	{
		cout<<"\n For inning : "<<e;
		cout<<"\n Enter 1 if you want to print the score of bowling team else enter 2: ";
		cin>>b;
		a.score_board(b,e);
		getch();
		cout<<"\n Wanna see more ?";
		cout<<"\n Enter choice :";
		cin>>b;

		if(b == 1)
		{
			continue;
		}
		else
		{
			break;
		}
	}
	cout<<"\n ---------------------- ";
	if(e == 2)
	{
		if(tt[e-1]>tt[e])
		{
			cout<<"\n Team 1 won the match.";
		}
		else if(tt[e-1]<tt[e])
		{
			cout<<"\n Team 2 won the match.";
		}
		else
		{
			cout<<"\n Its a draw.";
		}
		break;
	}
	else
	{	e = 2;
		continue;
	}
}//end of while
getch();
}







