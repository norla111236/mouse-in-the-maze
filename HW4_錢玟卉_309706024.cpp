//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HW4_錢玟卉_309706024.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define possible_direction 8
TForm1 *Form1;
int maze [20][20];				  //设置终点
int success = 0;
int m, n;
String str;
int p;
int top = -1;

struct offset{
	int dx;
	int dy;
};
//enum directions{N=1,NE=2,E=3,SE=4,S=5,SW=6,W=7,NW=8};
struct offset move[possible_direction];
struct position {   // Declare PERSON struct type
	int x;   // Declare member types
	int y;
	int dir;
	//directions dir;
};

struct position Stack[10000];
struct position step;

void push(struct position data){
	if(top < (m*p-1)) Stack[++top] = data;
}

struct position pop(){
	if(top >= -1) return Stack[top--];
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	FILE *fp;     // Define fp as a pointer pointing to some file (with data type FILE) in HD
	String out;
	int i, j;
	AnsiString infile;   // Use builder's string (AnsiString) to ease the conversion (into const char *)
	if (OpenDialog1->Execute())
	{
		infile = OpenDialog1->FileName;
		fp = fopen(infile.c_str(), "r+");
		//c_str函数的傳回值是 const char *, 即把AnsiString轉成const char *給fopen使用
		fscanf(fp, "%d %d", &m, &n);    // Read in two integers m & n
		Memo1->Lines->Add("(m, n)="+IntToStr(m)+", "+IntToStr(n));
		for (i=0; i<m; i++)    // Reda in m*n 0/1/2's into maze[][]
			for (j=0; j<n; j++)
				fscanf(fp, "%d", &maze[i][j]);
		fclose(fp);
		for (i=0; i<m; i++)      // Print out maze[][] in Memo1
		{   out = "";
			for (j=0; j<n; j++) out += "  "+IntToStr(maze[i][j]);
			Memo1->Lines->Add(out);
		}
		// Print out maze[][] in StringGrid1
		StringGrid1->RowCount = m;
		StringGrid1->ColCount = n;
		for (i=0; i<m; i++)
			for (j=0; j<n; j++)
				StringGrid1->Cells[j][i] = maze[i][j];
		}
		p = n-1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	int u, v, i, j;
	//struct position step;
	//struct position Stack[m*p];
	int mark[200][200];
	int maze_1[22][22];
	boolean found = false;
	for(int w=0;w<m+2;w++){
		maze_1[0][w]=2;
		maze_1[w][0]=2;
		maze_1[w][m+1]=2;
		maze_1[m+1][w]=2;
	}
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			maze_1[i+1][j+1]=maze[i][j];
		}
	}

	for (i = 0; i < m+2; i++) {
		for (j = 0; j < m+2; j++) {
			mark[i][j]=maze_1[i][j];
		}
	}


	/*
		String arra;
			for (i = 0; i < m+2; i++) {
				for (j = 0; j < m+2; j++) {
					arra+=IntToStr(maze_1[i][j])+"\t";
				}
				arra+="\r\n";
			}
			Form1->Memo1->Lines->Add(arra);
	*/
   /*
	move[0].dx = -1;   move[0].dy = 0;
	move[1].dx = -1;  move[1].dy = 1;
	move[2].dx = 0;    move[2].dy = 1;
	move[3].dx = 1;   move[3].dy = 1;
	move[4].dx = 1;    move[4].dy = 0;
	move[5].dx = 1;   move[5].dy = -1;
	move[6].dx = 0;    move[6].dy = -1;
	move[7].dx = -1;  move[7].dy = -1;
	*/

	move[0].dx = 0;    move[0].dy = 1;
	move[1].dx = 1;    move[1].dy = 0;
	move[2].dx = 0;    move[2].dy = -1;
	move[3].dx = -1;   move[3].dy = 0;

	Memo1->Lines->Add("m="+IntToStr(m)+" p="+IntToStr(p));
	// Memo1->Lines->Add(found);
	/*
	for (i=0; i<=m; i++)
	{   mark[i][n-1] = 2;
		maze[i][n-1] = 2;
	}
	for (j=0; j<=n; j++)
	{   mark[m-1][j] = 2;
		maze[m-1][j] = 2;
	}
	*/
	//for (i=0; i<=m; i++) { mark[i][0] = 1; mark[i][p+1] = 1; }
	//for (j=0; i<=p; i++) { mark[0][j] = 1; mark[m+1][j] = 1; }
	m = m+2;
	n = n+2;
	step.x = 1;
	step.y = 1;
	step.dir = 0;   // (i,j,dir)=(1,1,E)
	mark[1][1]=3;//起點設1
	push(step);
	while (top != -1)
	{    step = pop();
		 while ((step.dir <= 3) && (!found))
		{    u = step.x+move[step.dir].dx;
			 v = step.y+move[step.dir].dy;
			 int x = step.dir;
			Memo1->Lines->Add(".. (u,v,dir)="+
			IntToStr(u)+","+IntToStr(v)+","+IntToStr(x));
			Memo1->Lines->Add("...come:"+IntToStr(u)+","+
			IntToStr(v)+","+IntToStr(x));
		  // (u,v) = 自(i,j)欲嘗試的下一步座標
			if ((u == m-2) && (v == n-2))
			{  found = true; //成功找到出口，輸出路徑，可以停止
             mark[u][v]=3;
			 str = "("+IntToStr(u)+","+IntToStr(v)+")";
             StringGrid1->Cells[p][m] = "&";
			 str = "("+IntToStr(step.x)+","+IntToStr(step.y)+","+IntToStr(x)+")-->"+str;
             StringGrid1->Cells[step.y][step.x] = "->";
			 while (top != -1)
				{ step = pop();
				  int x = step.dir;
				  str = "("+IntToStr(step.x)+","+IntToStr(step.y)+","+IntToStr(x)+")-->"+str;
				  StringGrid1->Cells[step.y][step.x] = "->";
				}
             Memo1->Lines->Add(str);
			}
			else if ((maze_1[u][v]==0) && (mark[u][v]==0))
			 {  mark[u][v] = 3;
			   //	StringGrid1->Cells[v][u] = "*";
				step.dir = step.dir + 1;  //?
				push(step);
				step.x = u; step.y = v; step.dir = 0;
			 }
			else step.dir++;
	   }
	}
			String array;
			for (i = 0; i < m; i++) {
				for (j = 0; j < m; j++) {
					array+=IntToStr(mark[i][j])+"\t";
				}
				array+="\r\n";
			}
			Form1->Memo1->Lines->Add(array);

}
//---------------------------------------------------------------------------
