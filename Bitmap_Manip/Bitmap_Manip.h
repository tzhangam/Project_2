#ifndef B_MANIP
#define B_MANIP
#include <QtGui>
#define COL_NUMBER 10
#define ROW_NUMBER 20
/*
	Edit history:
	The specification file for class Bitmap_Manip. The class process all manipulations upon the central bitmap. 9-23-2016
	Add init&get for member bitmap. 9-23-2016
	Add row_is_full() and eliminate_row(). 9-25-2016
	Add down_shift_map() and print_map(). 9-25-2016
	Swap col and row. 9-25-2016
	Change return type of eliminate_full_row() to int, returning # of eliminated rows. 9-25-2016
	Add an argument for eliminate_full_row(). For it to eliminate all full rows beyond level r. 9-26-2016
	Add the same argument for down_shift_map(). 9-26-2016
	The return format of eliminate_full_row() is also rendering changes. 9-26-2016
	No need to change return format of eliminate_full_row(). Add merge_full() to utilize the current functions. 9-26-2016
*/
	class Bitmap_Manip{
	//Q_OBJECT
	public:
		Bitmap_Manip(int col=COL_NUMBER,int row=ROW_NUMBER);//Initialize the map with number of columns and rows.
		~Bitmap_Manip();

		void init_bitmap();//Initialize bitmap to all 0.
		int** get_bitmap();
		
		int merge_full();//Merge all the full rows in the map to void. Get total rows merged.
		
		bool row_is_full(int row);//row number here range from 1 to 20.
		int eliminate_full_row(int r);// eliminate neibouring full rows beyond level r, including level r. Bottom means r=rol_number=20
		void down_shift_map(int r,int d);//Down shift the map beyond level r, including level r(range from 1 to 20) by d rows.
		
		void print_map(); //For debug and testing use.
	private:
		int** bitmap;
		int col_number;
		int row_number;
	};
#endif