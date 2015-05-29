import java.io.*;
import java.net.*;

/** Class HP connects to Mathias' HPInterface program. */
class HP {

	Device dev;

	public HP(String name, String host, int port) throws UnknownHostException , IOException {
		dev = new Device(name, host, port);
	}

	/** Set the frequency, in Hz. */
	public void setFreq(double hz) throws IOException {
		dev.send("SET,FREQ,"+hz);
	}

	/** Set the power, in dBm */
	public void setPow(double dBm) throws IOException {
		dev.send("SET,POW,"+dBm);
	}

	/** Request and return the device ID. */
	public String id() throws IOException {
		return dev.id();
	}
}
