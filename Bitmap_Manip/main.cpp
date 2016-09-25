
#include "Bitmap_Manip.h"
//#include <QtGui>
#include <iostream>
using namespace std;
/*
 Edit History:
      This is the temporary program driver. 9-21-2016
 */
int main(int argc, char* argv[]){
  //QApplication app(argc, argv);
  Bitmap_Manip manip;
  manip.print_map();
  cout<<manip.eliminate_full_row()<<"Rows to be eliminated. "<<endl;
  cout<<" "<<endl;
  manip.print_map();

  //manip.init_bitmap();


  //return app.exec();
}