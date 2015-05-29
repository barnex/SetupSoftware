import java.io.*;
import java.net.*;

/** Connects to the RigolInterface program. */
public final class Rigol {

	Device dev;

	Rigol(String host, int port) throws UnknownHostException , IOException {
		dev = new Device("rigol", host, port);
	}

	/** Measure and return voltage, in volts. */
	float measure() throws IOException {
		dev.send("MEAS");
		return dev.receiveFloat();
	}

	/** Request and return the device ID. */
	String id() throws IOException {
		return dev.id();
	}
}
