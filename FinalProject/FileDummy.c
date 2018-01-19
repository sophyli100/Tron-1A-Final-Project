#include "EV3_FileIO.c"

task main()
{
	TFileHandle fout;
	bool fileOkay = openWritePC(fout, "soundReadings.txt");

	writeFloatPC(fout, 3.5);
	closeFilePC(fout);


}
