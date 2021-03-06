import java.io.*;
import java.net.*;

/** Class Devices interfaces with a generic device over Mathias' networked protocol. */
class Device {

	String name;
	String host;
	int port;
	Socket socket;
	OutputStream out;
	InputStream in;

	// Make a device connection with given name (e.g.: "Rigol"),
	// connected to host:port.
	Device(String name, String host, int port) {
		this.name = name;
		this.host = host;
		this.port = port;
	}

	void connect() throws UnknownHostException , IOException {
		Main.debug(name + ": connecting to " + host + ":" + port);
		this.socket = new Socket(host, port);
		this.out = new PrintStream(socket.getOutputStream());
		this.in = socket.getInputStream();
		Main.debug(name + ": connected");
	}

	/** Send a request to the device, e.g. "MEAS". */
	void send(String msg) throws IOException {
		Main.debug("to " + name + ": " + msg);
		Proto.send(out, msg);
	}

	/** Receive the payload of the response, header stripped.
	 *  return null in case of an error. */
	byte[] receive() throws IOException {
		return Proto.receive(in);
	}

	void receiveOK() throws IOException {
		byte[] data = receive();
		if(data.length > 0) {
			throw new IOException("received unexpected data: " + data.length +  " bytes");
		}
	}

	/** Receive response and convert to String. */
	String receiveString() throws IOException {
		return Proto.toString(receive());
	}

	/** Receive response and convert to Float. */
	float receiveFloat() throws IOException {
		return Proto.toFloat(receive());
	}

	/** Close the network connection. */
	void close() throws IOException {
		Main.debugn(name + ": closing...");
		socket.close();
		Main.debug("OK");
	}

	/** Try to close network connection but do not panic on error. */
	void tryClose() {
		try {
			close();
		} catch(IOException err) {
			Main.debug(name + ": ignored error while closing connection: " + err.toString());
		}
	}

	/** Request and return device ID.
		Trims away trailing newline, if any. */
	String id() throws IOException {
		send("ID");
		String id = Proto.toString(receive());
		if (id.endsWith("\n")) {
			id = id.substring(0, id.length()-1);
		}
		return id;
	}
}
