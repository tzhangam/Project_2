#include "Bitmap_Printer.h"
#include <QtGui>
#include <iostream>
using namespace std;
/*Edit history:
 * This is the implementation file for class Bitmap_Printer. 9-21-2016
 * Add constructor and destructor.
 * Add drawAt(),drawMap,init_bitmap,set_bitmap function.
 * Remove painter member. Initiate a instant painter whenever needed.
 * Remove bit_map related functions. 9-22-2016
 * Modify drawMap parameter list. Implement set_grid 9-22-2016
 * Modify parameter list of constructor. 9-22-2016    
 * Implement set_image. 9-22-2016
 * Pure bit_map visualizor is tested. 9-22-2016
 * Change class name. 9-22-2016
 * This line is for GitHub try out. 9-23-2016
 */
int min(int x,int y){
  if(x<=y)
    return x;
  else
    return y;
}
Bitmap_Printer::Bitmap_Printer(char* fN,int col,int row){ 
  //Set up image and grids.
  bzero(fileName,256);
  strcpy(fileName,fN);
  set_image(fileName);
  set_grid(col,row);
  
  #if 0
  //The following code is for debug.
   int** temp;
 temp=new int*[col_number];
  for (size_t i=0;i<col_number;i++){
    temp[i]=new int[row_number];
    for(size_t j=0;j<row_number;j++){
      temp[i][j]=(i+j)/7;}
    
  }
  
   drawMap(temp,col_number,row_number);
  delete[] temp;
#endif

  label.setPixmap(QPixmap::fromImage(background));
  label.show();

}

/*
void Bitmap_Printer::init_bitmap(){
  
    bit_map=new int*[col_number];
    
    for(int i=0;i<col_number;i++){
      bit_map[i]=new int[row_number];
    }
    
    for(int i=0;i<col_number;i++)
      for(int j=0;j<row_number;j++)
      {bit_map[i][j]=0;
	
      }
  
}
void Bitmap_Printer::set_bitmap(int** b_map){
  
  delete[] bit_map;
  init_bitmap();
  
  for(size_t i=0;i<col_number;i++)
    for(size_t j=0;j<row_number;j++)
      bit_map[i][j]=b_map[i][j];
}
*/
void Bitmap_Printer::drawAt(QPainter& painter,int x,int y,int color){
  
  painter.setPen(Qt::black);
  painter.setBrush(colorIs[color]); 
  painter.drawRect(x*grid_length,y*grid_length,grid_length,grid_length);

}
void Bitmap_Printer::drawMap(int** bit_map,int col, int row){
   //Reset drawing configuration.
  set_image(fileName);
  set_grid(col,row);
  QPainter painter(&background);
  
  //Draw the bit_map.
  for(int i=0;i<col;i++){
    for(int j=0;j<row;j++){
      drawAt(painter,i,j,bit_map[i][j]);
    }
  }
  
}
void Bitmap_Printer::set_grid(int col,int row){
  
  col_number=col;
  row_number=row;
  grid_length=min(background.width()/col_number,background.height()/row_number);
  
}
void Bitmap_Printer::set_image(char* fN){
    background.load(fN);
}
Bitmap_Printer::~Bitmap_Printer(){
  
  }