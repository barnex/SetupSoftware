#include "peakfind.h"

int getValue(int monaSock, double bandwidth, double *avgNoise, double *stdNoise, double *peakValue, double *fCenter)
{
    FILE * audioSpectrum = fopen("audio_spectrum.txt", "w");
    /*
     * Start the measurement
     */
    // Calculate the size of the FFT and send to MONA
    int fftsize = (int)(pow(2.0, ceil( log(48000.0/bandwidth)/log(2.0) )));
    int i = 0, widthSig = 0, widthRef = 0;
    double realBW = 1.0 / (double)(fftsize);
    widthSig  = (int)(0.2*fCenter[0]/realBW) + 10;
    widthRef = (int)(0.2*fCenter[1]/realBW) + 10;
    double *fRef, *fSig, *ReSig, *ReRef, *ImRef, *ImSig;

    fRef = malloc(sizeof(double) * widthRef);
    ReRef = malloc(sizeof(double) * widthRef);
    ImRef = malloc(sizeof(double) * widthRef);

    fSig = malloc(sizeof(double) * widthSig);
    ReSig = malloc(sizeof(double) * widthSig);
    ImSig = malloc(sizeof(double) * widthSig);

    char buffer[64];
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "%d,%f,%f,%f,%f", fftsize, 0.9*fCenter[0], 1.1*fCenter[0], 0.9*fCenter[1], 1.1*fCenter[1]);
    write(monaSock, buffer, 64);
	
    
    /*
     * Retrieve the data from MONA
     */
    memset(buffer, 0, sizeof(buffer)); 
    int nBytes = 0;
    nBytes = read(monaSock, buffer, 64);
    i = 0;
    int ref = 0;
    do
    {
	char *tmp = strtok( buffer, "\t" );
	if( !ref )
	{
	    if( i < fftsize && tmp != NULL )
	    {
		fSig[i] = atof(tmp);
	    }
	   tmp = strtok(NULL, "\t");
	    if( i < fftsize && tmp != NULL )
	    {
		ReSig[i] = atof(tmp);
	    }
    
	    tmp = strtok(NULL, "\t");
	    if( i < fftsize && tmp != NULL)
	    {
		ImSig[i] = atof(tmp);
	    }
	    fprintf(audioSpectrum, "%e\t%e\t%e\n", fSig[i], ReSig[i], ImSig[i]);
	    i++;
    
	}
	else
	{
	    if( i < fftsize && tmp != NULL )
	    {
		fRef[i] = atof(tmp);
	    }
	   tmp = strtok(NULL, "\t");
	    if( i < fftsize && tmp != NULL )
	    {
		ReRef[i] = atof(tmp);
	    }
    
	    tmp = strtok(NULL, "\t");
	    if( i < fftsize && tmp != NULL)
	    {
		ImRef[i] = atof(tmp);
	    }
	    fprintf(audioSpectrum, "%e\t%e\t%e\n", fRef[i], ReRef[i], ImRef[i]);
	    i++;
	}

	memset(buffer, 0, sizeof(buffer));
	nBytes = read(monaSock, buffer, 64);
	while( nBytes != 64)
	{
	    nBytes += read(monaSock, buffer + nBytes, sizeof(buffer) - nBytes);
	}
	
	printf("Buffer contents: %s\n", buffer);
	int found = (strstr(buffer, "EOL") != NULL);
	printf("found = %d\n", found);
	if( (ref == 0) && (strstr(buffer, "EOL") != NULL) )
	{
	    ref = 1;
	    i = 0;
	    printf("Detected EOL\n");
	    fprintf(audioSpectrum, "\n\n");
	}
    }while( strstr(buffer, "EOM") == NULL );
    printf("Detected EOM\n");
    fclose(audioSpectrum);
    //
    // Now go look for the peak at 10kHz
    //
    /*
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
    

    //
    // Now calculate noise parameters outside the band of interest
    //
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
    */
    return 0;
}
