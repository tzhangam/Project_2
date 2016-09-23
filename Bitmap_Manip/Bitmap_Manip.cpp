#include "Bitmap_Manip.h"
#include <QtGui>
/*
	Edit history:
	Add constructor and destructor, init and get for bitmap.
*/
Bitmap_Manip::Bitmap_Manip(int col,int row):col_number(col),row_numer(row){
	init_bitmap();
}
void Bitmap_Manip::init_bitmap(){

  
    bitmap=new int*[col_number];
    
    for(int i=0;i<col_number;i++){
      bitmap[i]=new int[row_numer];
    }
    
    for(int i=0;i<col_number;i++)
      for(int j=0;j<row_numer;j++)
      bitmap[i][j]=0;
      
  
}
int** Bitmap_Manip::get_bitmap(){
	return bitmap;
}
Bitmap_Manip::~Bitmap_Manip(){
delete[] bitmap;
}