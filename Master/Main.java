import java.io.*;
import java.net.*;

/*
	HP: ID; SET: FREQ, POW;
	Rigol: ID; MEAS;
 */

public final class Main {

	static final int STATUS_OK = 1;
	static boolean verbose = true;

	public static void main(String[] args) throws Exception {
		Rigol rigol = new Rigol("mona.ugent.be", 5005);
		System.out.println("rigol id     : " + rigol.id() );
		System.out.println("rigol measure: " + rigol.get() + "V");

		HP hp1 = new HP("hp1", "mona.ugent.be", 5003);
		System.out.println("hp1 id: " + hp1.id() );
	}


	static void log(String msg) {
		if (verbose){
			System.err.println(msg);
		}
	}
}

// Interfaces with a generic device over Mathias' networked protocol.
class Device {

	String name;
	Socket socket;
	PrintStream out;
	InputStream in;

	// Make a device connection with given name (e.g.: "Rigol"),
	// connected to host:port.
	Device(String name, String host, int port) throws UnknownHostException , IOException {
		this.name = name;
		Main.log(name + ": connecting to " + host + ":" + port);
		this.socket = new Socket(host, port);
		this.out = new PrintStream(socket.getOutputStream());
		this.in = socket.getInputStream();
		Main.log(name + ": connected");
	}

	void close() throws IOException {
		socket.close();
	}

	void send(String msg) {
		out.print(msg);
	}


	float readFloatResponse() throws IOException {
		byte[] data = readResponse();
		if(data.length != 4) {
			throw new IOException("readFloatResponse: got " + data.length + " bytes");
		}
		return toFloat(data, 0);

	}

	String readStringResponse() throws IOException {
		byte[] data = readResponse();
		return new String(data);
	}

	// read from in until data is full.
	void readFull(byte[] data) throws IOException {
		int N = data.length;
		int off = 0;
		while(off < N) {
			off += in.read(data, off, N-off);
		}
	}

	byte[] readResponse() throws IOException {
		byte[] hdr = new byte[8];
		readFull(hdr);

		int status = toInt(hdr, 0);
		int payload = toInt(hdr, 4);

		Main.log("response: status: " + status + " payload size: " + payload);

		if(payload > 0) {
			byte[] data = new byte[payload];
			readFull(data);
			return data;
		} else {
			return null;
		}
	}

	// convert 4 bytes starting at offset off to int
	// assuming little endian encoding.
	static int toInt(byte[] data, int off) {
		long b0 = (long)(data[off+0]) & 0xFF;
		long b1 = (long)(data[off+1]) & 0xFF;
		long b2 = (long)(data[off+2]) & 0xFF;
		long b3 = (long)(data[off+3]) & 0xFF;

		long v = (b0) | (b1 << 8) | (b2 << 16) | (b3 << 24);
		return (int)(v);
	}

	static float toFloat(byte[] data, int off) {
		return Float.intBitsToFloat(toInt(data, 0))	;
	}

	String id() throws IOException {
		send("ID");
		return readStringResponse();
	}

}

class Rigol {

	Device dev;

	Rigol(String host, int port) throws UnknownHostException , IOException {
		dev = new Device("rigol", host, port);
	}

	float get() throws IOException {
		dev.send("MEAS");
		return dev.readFloatResponse();
	}

	String id() throws IOException {
		return dev.id();
	}
}

class HP {

	Device dev;

	HP(String name, String host, int port) throws UnknownHostException , IOException {
		dev = new Device(name, host, port);
	}

	String id() throws IOException {
		return dev.id();
	}
}
