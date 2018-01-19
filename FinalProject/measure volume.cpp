// MEASURE VOLUME FUNCTION

void measureVolume(ofstream & fout, int & numSound)
{
	int numReadings = 0;
	int sum = 0;

	collectReadings(numReadings);
	outputAvg(numreadings, sum, fout);
	numSound ++;
}
