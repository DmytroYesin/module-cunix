#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <queens.h>

int search(Cell **table, int size, int i)
{
  int j = 0;
    for (; j < size; j++)
    {
      if(table[i][j].figure == 'Q')
      {
        return (j);
        break;
      }
    }
    return j;
}

int ch_rows_and_cols(Cell **table, int size)
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
  return 0;
}

int ch_diags(Cell **table, int size, int i, int j)
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

void place_queens(Cell **table, int size)
  {
    int n = size;
    int q_pos[n][2];
    int i_1st = 0, j_1st = 0;

  for(; i_1st < n; i_1st++)
  {
    j_1st = search(table, n, i_1st);
    if(j_1st > 0)
    {
      q_pos[0][0]=i_1st;
      q_pos[0][1]=j_1st;
      break;
  }
  }
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
      int a = ch_rows_and_cols(table, n);
      int b = ch_diags(table, n, i, j);
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
          int k = err_count / n;
          while(k > 0)
          {
            q_count--;
            errr = 1;
            i = q_pos[q_count][0];
            j = q_pos[q_count][1];
            table[i][j].figure = 'E';
            k--;
          }
        }
        j++;
      }
    }
  }
}

