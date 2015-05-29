import java.io.*;
import java.net.*;

/** Connects to Mathias' Controller program. */
public final class PiezoController {

	Device dev;

	public PiezoController(String host, int port) throws UnknownHostException, IOException {
		dev = new Device("piezo", host, port);
	}

	public String id() throws IOException {
		return dev.id();
	}
}
