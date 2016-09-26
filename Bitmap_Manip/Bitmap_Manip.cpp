#include "Bitmap_Manip.h"
#include <QtGui>
#include <iostream>
using namespace std;
/*
	Edit history:
	Add constructor and destructor, init and get for bitmap.
  Add row_is_full(), eliminate_full_row(). 9-25-2016
  Add print_map(). 9-25-2016
  Swap row with column. bitmap[row][col]. 9-25-2016
  Add an argument for eliminate_full_row(). 9-26-2016
  Add merge_full();
  Change all elimination functions' arguments to 1 based. 9-26-2016 
*/
Bitmap_Manip::Bitmap_Manip(int col,int row):col_number(col),row_number(row){
	init_bitmap();

  #if 1
  //The following code is for debug.
 for (int i=0;i<row_number;i++){
    for(int j=0;j<col_number;j++){
      bitmap[i][j]=(i+j)/7;}
    
  }

  bitmap[15][8]=bitmap[18][1]=bitmap[19][0]=0;
  #endif

}
void Bitmap_Manip::init_bitmap(){

  
    bitmap=new int*[row_number];

    for(int i=0;i<row_number;i++){
      bitmap[i]=new int[col_number]();
    }
}
bool Bitmap_Manip::row_is_full(int row){
  //row here is 1 based.
   for(int i=0;i<col_number;i++){
    if(get_bitmap()[row-1][i]==0)
      return false;
  }
  return true;
}

void Bitmap_Manip::down_shift_map(int r, int d){
  //Delete the d rows at the bottom.
  for(int i=1;i<=d;i++)
  {
    delete[] bitmap[r-i];
  }
  //Downshift the subarray pointers by d units. 
  for(int j=r-1;j>=d;j--)
  {
    bitmap[j]=bitmap[j-d];
  }
  //Create d new rows at the top.
  for(int k=d-1;k>=0;k--){
    bitmap[k]=new int[col_number]();
  }
}

#if 1
int Bitmap_Manip::eliminate_full_row(int r){

  int num_full_row=0;
  while(row_is_full(r-num_full_row)){
    num_full_row++;
  }

  down_shift_map(r,num_full_row);

  return num_full_row;
}
#endif
#if 1
int Bitmap_Manip::merge_full(){
  int cursor=row_number;
  int num=0;
  for(;cursor>0;cursor--){
    if(row_is_full(cursor)){
      num+=eliminate_full_row(cursor);
    }
  }
  return num;
}
#endif
int** Bitmap_Manip::get_bitmap(){
	return bitmap;
}
void Bitmap_Manip::print_map(){
  for(int i=0;i<row_number;i++)
    {
      for(int j=0;j<col_number;j++)
      {
        cout<<bitmap[i][j]<<" ";
      }
      cout<<endl;
    }
}
Bitmap_Manip::~Bitmap_Manip(){
for(int i=0;i<row_number;i++)
  delete bitmap[i];
delete[] bitmap;
}