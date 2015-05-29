import java.io.*;
import java.net.*;

/** Connects to the RigolInterface program. */
public final class Rigol {

	Device dev;

	public Rigol(String host, int port) throws UnknownHostException , IOException {
		dev = new Device("rigol", host, port);
	}

	/** Measure and return voltage, in volts. */
	public float measure() throws IOException {
		dev.send("MEAS");
		return dev.receiveFloat();
	}

	/** Request and return the device ID. */
	public String id() throws IOException {
		return dev.id();
	}
}
