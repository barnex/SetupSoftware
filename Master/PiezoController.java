import java.io.*;
import java.net.*;

/** Connects to Mathias' Controller program. */
public final class PiezoController {

	Device dev;
	
	double posX = 0.5, posY = 0.5, posZ = 0.5, posAux; // last position, dimensionless: 0..1
	int nX, nY;                                        // # pixels to scan
	private float[][][] image = new float[N_CHAN][nY][nX];     // last recored image

	public static final int N_CHAN = 8; // Number of recored channels.

	ImageView viewer = null;


	public PiezoController(String host, int port) throws UnknownHostException, IOException {
		dev = new Device("piezo", host, port);
	}

	/** Set start position for goto, scan2d. Dimensionless numbers between 0 and 1 for full scan range.
	 * x=focus, y=left-right, z=upd-down, aux=extra channel, e.g. external magnet. */
	public void setStart(double x, double y, double z, double aux) throws IOException {
		posX = x;
		posY = y;
		posZ = z;
		posAux = aux;
		dev.send("SET,START," + x + "," + y + "," + z + "," + aux);
		dev.receiveOK();
	}

	/** Set increment vector for scan2d, outer (slow) scan loop.
	 * E.g.: 0.1, 0, 0, 0 slowly scans x, the focus.                      */
	public void setIInc(double x, double y, double z, double aux) throws IOException {
		//iincx = x;
		//iincy = y;
		//iincz = z;
		//iincaux = aux;
		dev.send("SET,IINC," + x + "," + y + "," + z + "," + aux);
		dev.receiveOK();
	}

	/** Set increment vector for scan2d, inner (fast) scan loop.
	 * E.g.: 0, 0.1, 0, 0 quicly scans y, left-right.                     */
	public void setIJnc(double x, double y, double z, double aux) throws IOException {
		//jincx = x;
		//jincy = y;
		//jincz = z;
		//jincaux = aux;
		dev.send("SET,JINC," + x + "," + y + "," + z + "," + aux);
		dev.receiveOK();
	}

	/** Set the number of pixels for the next scan2d. */
	public void setpixels(int nX, int nY) throws IOException {
		this.nX = nX;
		this.nY = nY;
		dev.send("SET,PIXELS," + (float)(nX) + "," + (float)(nY));
		dev.receiveOK();
	}

	/** Set the settle time for the next scan2d, in ms (presumably). */
	public void setTSettle(double ms) throws IOException {
		//tsettle = ms;
		dev.send("SET,TSETTLE," + ms);
		dev.receiveOK();
	}

	/** Convenience method to make relative movment. */
	public void jog(double dx, double dy,double  dz) throws IOException{
		posX += dx;
		posY += dy;
		posZ += dz;
		if(posX > 1){posX = 1;}
		if(posY > 1){posY = 1;}
		if(posZ > 1){posZ = 1;}
		if(posX < 0){posX = 0;}
		if(posY < 0){posY = 0;}
		if(posZ < 0){posZ = 0;}
		setStart(posX, posY, posZ, posAux);	
		goTo();
	}

	/** Start 2D scan with previously set parameters (setStart, setIInc, setJInc, setPixels, setTSettle). */
	public void scan2d() throws IOException {

		Main.log(dev.name + ": start scan2d: " + nX + " x " + nY);

   		// init new image buffer with NaN's 
		image = new float[N_CHAN][nY][nX];
		for(int c = 0; c < N_CHAN; c++){
			for(int y=0; y<nY; y++){
				for(int x=0; x<nX; x++){
					image[c][y][x] = (float)(0./0.);  
				}
			}	
		}
		
		// Start scan
		dev.send("SCAN_2D");

		// recieve data: for each pixel: one response packet with 8 floats payload (8 ADC channels).
		for (int y = 0; y<nY; y++){
			for (int x = 0; x<nX; x++){
				byte[] data = dev.receive();
				if(data.length != 4 * N_CHAN){
					throw new IOException("got bad scan data: " + data.length + " bytes");
				}
				for(int c = 0; c < N_CHAN; c++){
					image[c][y][x] = Proto.toFloatOff(data, 4*c);
				}
				if(viewer != null){
					viewer.display(image);
				}
			}
 		}
		Main.log(dev.name + ": scan2d done");
	}

	/** Move to position sent by setStart. */
	public void goTo() throws IOException {
		dev.send("GOTO");
		dev.receiveOK();
	}

	/** Abort scan started by scan2d(). */
	public void abort() throws IOException {
		dev.send("ABORT");
		dev.receiveOK();
	}

	/** Request and return device ID. */
	public String id() throws IOException {
		return dev.id();
	}

	public void close() throws IOException{
		dev.close();
	}
}
