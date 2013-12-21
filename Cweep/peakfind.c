#include "peakfind.h"

int getValue(int monaSock, double bandwidth, double *avgNoise, double *stdNoise, double *peakValue, double fCenter)
{
    FILE * audioSpectrum = fopen("audio_spectrum.txt", "w");
    /*
     * Start the measurement
     */
    // Calculate the size of the FFT and send to MONA
    int fftsize = (int)(pow(2.0, ceil( log(48000.0/bandwidth)/log(2.0) )));
    int i = 0;
    double *f, *Re, *Im;
    f = malloc(sizeof(double) * fftsize);
    Re = malloc(sizeof(double) * fftsize);
    Im = malloc(sizeof(double) * fftsize);

    char buffer[64];
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "%d", fftsize);
    write(monaSock, buffer, 64);
	
    
    /*
     * Retrieve the data from MONA
     */
    memset(buffer, 0, sizeof(buffer)); 
    int nBytes = 0;
    nBytes = read(monaSock, buffer, 64);
    do
    {

	char *tmp = strtok( buffer, "\t" );
	if( i < fftsize && tmp != NULL )
	{
	    f[i] = atof(tmp);
	}
	tmp = strtok(NULL, "\t");
	if( i < fftsize && tmp != NULL )
	{
	    Re[i] = atof(tmp);
	}

	tmp = strtok(NULL, "\t");
	if( i < fftsize && tmp != NULL)
	{
	    Im[i] = atof(tmp);
	}
	fprintf(audioSpectrum, "%e\t%e\t%e\n", f[i], Re[i], Im[i]);
	i++;

	memset(buffer, 0, sizeof(buffer));
	nBytes = read(monaSock, buffer, 64);
	while( nBytes != 64)
	{
	    nBytes += read(monaSock, buffer + nBytes, sizeof(buffer) - nBytes);
	}
    }while( strpbrk(buffer, "EOM") == NULL );
    fclose(audioSpectrum);
    /*
     * Now go look for the peak at 10kHz
     */
    double spacing = f[1] - f[0];
    double tmp     = 0.0;
    *peakValue	   = 0.0;
    int startIndex = (fCenter - 50.0)/spacing;
    int stopIndex  = (fCenter + 50.0)/spacing;
    int peakIndex = 0;

    for( i = startIndex; i < stopIndex; i++ )
    {
	tmp = Re[i]*Re[i] + Im[i]*Im[i];
	if( tmp > *peakValue )
	{
	    *peakValue = tmp;
	    peakIndex = i;
	}
    }
    

    /*
     * Now calculate noise parameters outside the band of interest
     */
    startIndex = (fCenter+100.0)/spacing;
    stopIndex  = (fCenter+600.0)/spacing;

    *avgNoise = 0.0;
    *stdNoise = 0.0;
    for (i = startIndex; i < stopIndex; i++ )
    {
	*avgNoise += Re[i]*Re[i] + Im[i]*Im[i];
    }
    *avgNoise /= (double) (stopIndex-startIndex);

    for ( i = startIndex; i < stopIndex; i++ )
    {
	tmp = Re[i]*Re[i] + Im[i]*Im[i];
	*stdNoise += (tmp - *avgNoise) * (tmp - *avgNoise);
    }
    *stdNoise /= (double) (stopIndex - startIndex);
    *stdNoise = sqrt(*stdNoise);

    double threshold = *avgNoise + 10.0*(*stdNoise);
    if( Re[peakIndex-1]*Re[peakIndex-1] + Im[peakIndex-1]*Im[peakIndex-1] > threshold )
    {
	*peakValue += Re[peakIndex-1]*Re[peakIndex-1] + Im[peakIndex-1]*Im[peakIndex-1];
    }
    
    if( Re[peakIndex+1]*Re[peakIndex+1] + Im[peakIndex+1]*Im[peakIndex+1] > threshold )
    {
	*peakValue += Re[peakIndex+1]*Re[peakIndex+1] + Im[peakIndex+1]*Im[peakIndex+1];
    }

    return 0;
}
