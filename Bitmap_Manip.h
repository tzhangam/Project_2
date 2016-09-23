#ifndef B_MANIP
#define B_MANIP
#include <QtGui>
#define COL_NUMBER =10
#define ROW_NUMBER =20
/*
	Edit history:
	The specification file for class Bitmap_Manip. The class process all manipulations upon the central bitmap. 9-23-2016
	Add init&get for member bitmap. 9-23-2016
*/
	class Bitmap_Manip{
	Q_OBJECT
	public:
		Bitmap_Manip(int col=COL_NUMBER,int row=ROW_NUMBER);
		~Bitmap_Manip();

		void init_bitmap();//Initialize bitmap to default value.
		int** get_bitmap();
	private:
		int** bitmap;
		int col_number;
		int row_number;
	};
#endif