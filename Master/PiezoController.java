import java.io.*;
import java.net.*;

/** Connects to Mathias' Controller program. */
public final class PiezoController {

	Device dev;

	public PiezoController(String host, int port) throws UnknownHostException, IOException {
		dev = new Device("piezo", host, port);
	}

	/** Set start position for goto, scan2d.
	 * x=focus, y=left-right, z=upd-down, aux=extra channel, e.g. external magnet. */
	public void setStart(double x, double y, double z, double aux) throws IOException {
		dev.send("SET,START," + x + "," + y + "," + z + "," + aux);
		dev.receive();
	}

	/** Set increment vector for scan2d, outer (slow) scan loop.
	 * E.g.: 0.1, 0, 0, 0 slowly scans x, the focus.                      */
	public void setIInc(double x, double y, double z, double aux) throws IOException {
		dev.send("SET,IINC," + x + "," + y + "," + z + "," + aux);
		dev.receive();
	}

	/** Set increment vector for scan2d, inner (fast) scan loop.
	 * E.g.: 0, 0.1, 0, 0 quicly scans y, left-right.                     */
	public void setIJnc(double x, double y, double z, double aux) throws IOException {
		dev.send("SET,IINC," + x + "," + y + "," + z + "," + aux);
		dev.receive();
	}

	/** Set the number of pixels for the next scan2d. */
	public void setpixels(int nI, int nJ) throws IOException {
		dev.send("SET,PIXELS," + (float)(nI) + "," + (float)(nJ));
		dev.receive();
	}

	/** Set the settle time for the next scan2d, in ms (presumably). */
	public void	setTSettle(double ms) throws IOException {
		dev.send("SET,TSETTLE," + ms);
		dev.receive();
	}

	/** Start 2D scan with previously set parameters (setStart, setIInc, setJInc, setPixels, setTSettle). */
	public void scan2d() throws IOException {
		dev.send("SCAN_2D");
		for (;;){
			dev.receive();
 		}
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
}
