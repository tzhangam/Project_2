
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
  cout<<manip.merge_full()<<"Rows to be eliminated. "<<endl;
 // manip.down_shift_map(13,5);
  cout<<" "<<endl;
  manip.print_map();

  //manip.init_bitmap();


  //return app.exec();
}