#ifndef BITMAP_PRINTER
#define BITMAP_PRINTER
#include <QtGui>
#define IMAGE_FILE "background.bmp"
#define COL_NUMBER 10
#define ROW_NUMBER 20
 enum COLOR_SUBSCRIPT{GREEN=1,YELLOW,RED,CYAN,PURPLE,BLUE,SILVER};
/*
 Edit history:
 The class is created for converting a integer map into a visual colourful grid map. 9-21-2016
 Add drawAt() funtion. Draw a grid at specific x, y coordinate. 9-21-2016
 Add init_bitmap,set_bitmap.9-21-2016
 Remove bit_map member and related functions, this class in bound to receive message from Real_Gameboard. 9-22-2016
 Modify the parameter list of drawMap. Add function that initialize dimensions of grid network. 9-22-2016
 Modify parameter list of constructor. Add member fileName. 9-22-2016
 Add set function for background image. 9-22-2016
 Declared COLOR enum to be global. 9-22-2016
 Change class name to be Bitmap_Printer
 */
class Bitmap_Printer : public QWidget{
    Q_OBJECT
public:
  Bitmap_Printer(char* fN=IMAGE_FILE,int col=COL_NUMBER,int row=ROW_NUMBER);
  ~Bitmap_Printer();
  
 
 // void init_bitmap();//Allocate default memory to bit_map, initialize all entries to 0.
  //void set_bitmap(int** b_map);//Set current bit_map with b_map. This version does not accept b_map with non-standard size.
  void set_grid(int col,int row);//Set col_number,row_number,grid_length.
  void drawAt(QPainter& painter,int x, int y,int color);//Draw a particular grid using given painter.
  void drawMap(int** bit_map,int col,int row);//Reload the background image, draw the visual gameboard with given bit_map.
  void set_image(char* fN);
private:
  QImage background;
  QLabel label;

  char fileName[256];
  //int** bit_map;
  int col_number;//Total number of columns.
  int row_number;//Total number of rows.
  int grid_length;//Length of one side of the grid.
  const Qt::GlobalColor colorIs[8]={Qt::transparent,Qt::green,Qt::yellow,Qt::red,Qt::cyan,Qt::magenta,Qt::blue,Qt::lightGray};
 
};
#endif