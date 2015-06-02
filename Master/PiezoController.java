import java.io.*;
import java.net.*;

/** Connects to Mathias' Controller program. */
public final class PiezoController {

	Device dev;
	
	private double iincx, iincy, iincz, iincaux;  // outer scan increments
	private double jincx, jincy, jincz, jincaux;  // inner scan increments
	private int pixi, pixj;                       // # pixels to scan
	private double tsettle;                       // settle time per pixel (ms)
	private float[][][] image = new float[N_CHAN][pixi][pixj];  // last recored image

	public static final int N_CHAN = 8; // Number of recored channels.


	public PiezoController(String host, int port) throws UnknownHostException, IOException {
		dev = new Device("piezo", host, port);
	}

	/** Set start position for goto, scan2d.
	 * x=focus, y=left-right, z=upd-down, aux=extra channel, e.g. external magnet. */
	public void setStart(double x, double y, double z, double aux) throws IOException {
		dev.send("SET,START," + x + "," + y + "," + z + "," + aux);
		dev.receiveOK();
	}

	/** Set increment vector for scan2d, outer (slow) scan loop.
	 * E.g.: 0.1, 0, 0, 0 slowly scans x, the focus.                      */
	public void setIInc(double x, double y, double z, double aux) throws IOException {
		iincx = x;
		iincy = y;
		iincz = z;
		iincaux = aux;
		dev.send("SET,IINC," + x + "," + y + "," + z + "," + aux);
		dev.receiveOK();
	}

	/** Set increment vector for scan2d, inner (fast) scan loop.
	 * E.g.: 0, 0.1, 0, 0 quicly scans y, left-right.                     */
	public void setIJnc(double x, double y, double z, double aux) throws IOException {
		jincx = x;
		jincy = y;
		jincz = z;
		jincaux = aux;
		dev.send("SET,IINC," + x + "," + y + "," + z + "," + aux);
		dev.receiveOK();
	}

	/** Set the number of pixels for the next scan2d. */
	public void setpixels(int nI, int nJ) throws IOException {
		pixi = nI;
		pixj = nJ;
		dev.send("SET,PIXELS," + (float)(nI) + "," + (float)(nJ));
		dev.receiveOK();
	}

	/** Set the settle time for the next scan2d, in ms (presumably). */
	public void setTSettle(double ms) throws IOException {
		tsettle = ms;
		dev.send("SET,TSETTLE," + ms);
		dev.receiveOK();
	}

	/** Start 2D scan with previously set parameters (setStart, setIInc, setJInc, setPixels, setTSettle). */
	public void scan2d() throws IOException {

		Main.log(dev.name + ": start scan2d: " + pixi + " x " + pixj);
		image = new float[N_CHAN][pixi][pixj];
		
		dev.send("SCAN_2D");

		for (int i = 0; i<pixi; i++){
			for (int j = 0; j<pixj; j++){
				byte[] data = dev.receive();
				if(data.length != 4 * N_CHAN){
					throw new IOException("got bad scan data: " + data.length + " bytes");
				}
				for(int c = 0; c < N_CHAN; c++){
					image[c][i][j] = Proto.toFloatOff(data, 4*c);
				}
			}
 		}
		Main.log(dev.name + ": scan2d done");
		//for(int c = 0; c < N_CHAN; c++){
		//	for(int i=0; i<image[c].length; i++){
		//		for(int j=0; j<image[c][i].length; j++){
		//			System.out.print(image[c][i][j] + " ");
		//		}
		//		System.out.println();
		//	}
		//	System.out.println();
		//	System.out.println();
		//}
		
	}

	/** Move to position sent by setStart. */
	public void goTo() throws IOException {
		dev.send("GOTO");
		dev.receive();
	}

	/** Abort scan started by scan2d(). */
	public void abort() throws IOException {
		dev.send("ABORT");
		dev.receive();
	}

	/** Request and return device ID. */
	public String id() throws IOException {
		return dev.id();
	}

	public void close() throws IOException{
		dev.close();
	}
}
