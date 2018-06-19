#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <../queens.h>

int search_queen(Cell **table, int size, int i)
{
  int j = 0;
    for (; j < size; j++)
    {
      if(table[i][j].figure == 'Q')
      {
        break;
      }
    }
    return j;
}

int check_rows_and_cols(Cell **table, int size)
{
  int queens_in_row, queens_in_col;
  for (int i = 0; i < size; i++)
  {
    queens_in_col = 0;
    queens_in_row = 0;
    for (int j = 0; j < size; j++)
    {
      if(table[i][j].figure == 'Q') queens_in_row++;
      if(table[j][i].figure == 'Q') queens_in_col++;
      if(queens_in_row > 1 || queens_in_col > 1)
      {
        return 1;
        break;
      }
    }
  }
  if(queens_in_row < 2 && queens_in_col < 2) return 0;
}

/*
int check_diags(Cell **table, int size)
{
  int queens_on_diag1, queens_on_diag2;
  for (int i = 0; i < size; i++)
  {
    queens_on_diag1 = 0;
    queens_on_diag2 = 0;
    for (int j = 0 ; j < size - i; j++)
    {
      if (table[j][i + j].figure == 'Q') queens_on_diag1++;
      if (table[size - j - 1][i + j].figure == 'Q') queens_on_diag2++;
      if(queens_on_diag1 > 1 || queens_on_diag2 > 1)
      {
        return 1;
        break;
      }
    }
  }
  if(queens_on_diag1 < 2 && queens_on_diag2 < 2) return 0;

  for (int j = 1; j < size; j++)
  {
    queens_on_diag1 = 0;
    queens_on_diag2 = 0;
    for (int i = 0 ; i < size - j; i++)
    {
      if (table[j][i + j].figure == 'Q') queens_on_diag1++;
      if (table[size - j - 1][i + j].figure == 'Q') queens_on_diag2++;
      if(queens_on_diag1 > 1 || queens_on_diag2 > 1)
      {
        return 1;
        break;
      }
    }
  }
  if(queens_on_diag1 < 2 && queens_on_diag2 < 2) return 0;
}*/

int check_diags(Cell **table, int size, int i, int j)
{
  int q_on_diag = 0;
  int a_x = i - 1;
  int a_y = j - 1;
  int b_x = i - 1;
  int b_y = j + 1;
  int c_x = i + 1;
  int c_y = j - 1;
  int d_x = i + 1;
  int d_y = j + 1;
  while(a_x >= 0 && a_y >= 0)
  {
    if(table[a_x][a_y].figure == 'Q')
    {
      q_on_diag++;
    }
    a_x--;
    a_y--;
  }

  while(b_x >= 0 && b_y <= (size-1))
  {
    if(table[b_x][b_y].figure == 'Q')
    {
      q_on_diag++;
    }
    b_x--;
    b_y++;
  }

  while(c_x <= (size-1) && c_y >= 0)
  {
    if(table[c_x][c_y].figure == 'Q')
    {
      q_on_diag++;
    }
    c_x++;
    c_y--;
  }

  while(d_x <= (size-1) && d_y <= (size-1))
  {
    if(table[d_x][d_y].figure == 'Q')
    {
      q_on_diag++;
    }
    d_x++;
    d_y++;
  }

  if(q_on_diag > 0) return 1;
  else return 0;
}

//void place_queens(Cell **table, int size)
//{
//   printf(search_queen(**table, size));
//}


int main()
  {
    int n = 8;

    int q_pos[n][2];
    int i_1st = 0, j_1st = 0;


     Cell **table;
  table = malloc(n * sizeof(Cell*));
  for (int i = 0; i < n; i++)
    table[i] = malloc(n * sizeof(Cell));
  table[0][3].figure = 'Q';


  for(; i_1st < n; i_1st++)
  {
    j_1st = search_queen(table, n, i_1st);
    if(j_1st > 0)
    {
      q_pos[0][0]=i_1st;
      q_pos[0][1]=j_1st;
      break;
  }
  }
  //printf("%d %d", q_pos[0][0], q_pos[0][1]);
  int q_count = 1;
  int i, j;
  int err_count = 0;
  while(q_count < n)
  {
    int errr = 1;

    if(q_pos[q_count-1][1] < (n-2))
    {
      i = q_pos[q_count-1][0] + 1;
      j = q_pos[q_count-1][1] + 2;
    }
    else
    {
      i = q_pos[q_count-1][0] + 1;
      j = 0;
    }

    while(errr > 0)
    {
      table[i][j].figure = 'Q';
      int a = check_rows_and_cols(table, n);
      int b = check_diags(table, n, i, j);
      printf("%d %d \n", a, b);

      //Print table
       int x = 0;
       int y = 0;
       while(y < n)
       {
       x = 0;
       while(x < n)
       {
         if(table[x][y].figure != 'Q')
       {
         table[x][y].figure = 'E';
       }
       printf("%c ", table[x][y]);
       x++;
       }
       printf("\n");
       y++;
       }

      if(a < 1 && b < 1)
      {
        q_pos[q_count][0] = i;
        q_pos[q_count][1] = j;
        q_count++;
        errr = 0;
      }
      else
      {
        errr++;
        table[i][j].figure = 'E';
        if(j < (n-1))
          j++;
        else
          j = 0;
      }
      if(errr == (n+1))
      {
        err_count++;
        q_count--;
        errr = 1;
        i = q_pos[q_count][0];
        j = q_pos[q_count][1];
        table[i][j].figure = 'E';
        if(err_count > (n-1))
        {
          q_count--;
          errr = 1;
          i = q_pos[q_count][0];
          j = q_pos[q_count][1];
          table[i][j].figure = 'E';
          if(err_count > (2*n-1))
          {
            q_count--;
            errr = 1;
            i = q_pos[q_count][0];
            j = q_pos[q_count][1];
            table[i][j].figure = 'E';
            if(err_count > (3*n-1))
            {
              q_count--;
              errr = 1;
              i = q_pos[q_count][0];
              j = q_pos[q_count][1];
              table[i][j].figure = 'E';
            }
          }
        }
        j++;
      }
    }
  }
//  int x = 0;
//  int y = 0;
//  while(y < n)
//  {
//    x = 0;
//    while(x < n)
//    {
//      if(table[x][y].figure != 'Q')
//      {
//        table[x][y].figure = 'E';
//      }
//      printf("%c ", table[x][y]);
//      x++;
//    }
//    printf("\n");
//    y++;
//  }

  int m = 0;
  while(m < n)
  {
    printf("\n %d %d \n", q_pos[m][0], q_pos[m][1]);
    m++;
  }
}
