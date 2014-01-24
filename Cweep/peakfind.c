#include "peakfind.h"

int getValue(int monaSock, double bandwidth, double *measurements, double *fCenter)
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
	
	int found = (strstr(buffer, "EOL") != NULL);
	if( (ref == 0) && (strstr(buffer, "EOL") != NULL) )
	{
	    ref = 1;
	    widthSig = i;
	    i = 0;
	    fprintf(audioSpectrum, "\n\n");
	}
    }while( strstr(buffer, "EOM") == NULL );
    widthRef = i;
    fclose(audioSpectrum);

    // Firstly, analyse the reference spectrum, i.e. find the maximum magnitude
    double max = 0.0;
    int refPeakIndex = 0;
    i = 0;
    double tmp = 0;
    for( i = 0; i < widthRef; i++ )
    {
	if( tmp < (ReRef[i]*ReRef[i] + ImRef[i]*ImRef[i]) )
	{
	    tmp = ReRef[i]*ReRef[i] + ImRef[i]*ImRef[i];
	    refPeakIndex = i;
	}
    }

    // Now analyse the signal spectrum
    tmp = 0.0;
    int sigPeakIndex = 0;
    i = 0;
    for( i = 0; i < widthSig; i++ )
    {
	if( tmp < (ReSig[i]*ReSig[i] + ImSig[i]*ImSig[i]) )
	{
	    tmp = (ReSig[i]*ReSig[i] + ImSig[i]*ImSig[i]) ;
	    sigPeakIndex = i;
	}
    }

    //
    // Now calculate noise parameters outside the band of interest
    //
    measurements[0] = 0.0;
    int start = 0, stop = widthSig;
    if( sigPeakIndex > widthSig/2 )
    {
	stop = (int) ((double)widthSig * 0.375);
    }
    else
    {
	start = (int) ((double)widthSig * 0.625);
    }

    i = 0;
    double mag;
    for( i = start; i < stop; i++ )
    {
	measurements[0] += ImSig[i]*ImSig[i] + ReSig[i]*ReSig[i];
    }
	
    (measurements[0]) /= (double) stop;

    (measurements[1]) = 0.0;	
    for( i = start; i < stop; i++ )
    {
	mag = ReSig[i] * ReSig[i] + ImSig[i]*ImSig[i];
	(measurements[1]) += (mag - (measurements[0])) * (mag - (measurements[0]));
    }
    (measurements[1]) /= (double) stop;
    (measurements[1]) = sqrt( (measurements[1]) );

    // Save the magnitude and phase of the energy in the largest peak in the spectrum
    (measurements[2]) = ReSig[sigPeakIndex]*ReSig[sigPeakIndex] + ImSig[sigPeakIndex]*ImSig[sigPeakIndex];
    (measurements[3]) = atan( ReSig[sigPeakIndex] / ImSig[sigPeakIndex] );

    // Now look if there is energy in the adjacent bins next to the main peak
    double threshold = (measurements[0]) + 10.0*((measurements[1]));
    double magLowerSidePeak = ReSig[sigPeakIndex-1]*ReSig[sigPeakIndex-1] + ImSig[sigPeakIndex-1] * ImSig[sigPeakIndex-1];
    if( magLowerSidePeak > threshold )
    {
	(measurements[2]) += magLowerSidePeak;
    }

    double magUpperSidePeak = ReSig[sigPeakIndex+1]*ReSig[sigPeakIndex+1] + ImSig[sigPeakIndex+1] * ImSig[sigPeakIndex+1];
    if( magUpperSidePeak > threshold )
    {
	(measurements[2]) += magUpperSidePeak;
    }

    // Also save magnitude and phase of the reference
    (measurements[4]) = ReRef[refPeakIndex]*ReRef[refPeakIndex] + ImRef[refPeakIndex]*ImRef[refPeakIndex];
    (measurements[5]) = atan(ReRef[refPeakIndex]/ImRef[refPeakIndex]);
    
    return 0;
}
