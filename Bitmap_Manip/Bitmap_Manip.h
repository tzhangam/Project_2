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
*/
	class Bitmap_Manip{
	//Q_OBJECT
	public:
		Bitmap_Manip(int col=COL_NUMBER,int row=ROW_NUMBER);//Initialize the map with number of columns and rows.
		~Bitmap_Manip();

		void init_bitmap();//Initialize bitmap to all 0.
		int** get_bitmap();
		bool row_is_full(int row);//row number is 0 based.
		int eliminate_full_row();
		void down_shift_map(int d);//Down shift the whole map by d rows.
		void print_map(); //For debug and testing use.
	private:
		int** bitmap;
		int col_number;
		int row_number;
	};
#endif