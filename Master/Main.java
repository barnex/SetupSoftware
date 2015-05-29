import java.io.*;
import java.net.*;

/*
	HP: ID; SET: FREQ, POW;
	Rigol: ID; MEAS;
 */

public final class Main {

	static final int STATUS_OK = 1;

	public static void main(String[] args) throws Exception {
		RigolInterface rigol = RigolInterface.connect("mona.ugent.be", 5005);
		for(;;) {
			System.out.println("rigol: " + rigol.get() + " V");
		}
		//rigol.close();
	}

	static float readFloatResponse(InputStream in) throws IOException {
		byte[] data = readResponse(in);
		if(data.length != 4) {
			throw new IOException("readFloatResponse: got " + data.length + " bytes");
		}
		return toFloat(data, 0);

	}

	static byte[] readResponse(InputStream in) throws IOException {
		byte[] hdr = new byte[8];
		readFull(in, hdr);

		int status = toInt(hdr, 0);
		int payload = toInt(hdr, 4);

		log("response: status: " + status + " payload size: " + payload);

		if(payload > 0) {
			byte[] data = new byte[payload];
			readFull(in, data);
			return data;
		} else {
			return null;
		}


		//if(status != STATUS_OK) {
		//return null;
		//}

	}

	// read from in until data is full.
	static void readFull(InputStream in, byte[] data) throws IOException {
		int N = data.length;
		int off = 0;
		while(off < N) {
			off += in.read(data, off, N-off);
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

	static void log(String msg) {
		System.err.println(msg);
	}
}

class RigolInterface {

	Socket s;
	PrintStream out;
	InputStream in;

	static RigolInterface connect(String host, int port) throws UnknownHostException , IOException {
		RigolInterface i = new RigolInterface();
		Main.log("RigolInterface: connecting to " + host + ":" + port);
		i.s = new Socket(host, port);
		i.out = new PrintStream(i.s.getOutputStream());
		i.in = i.s.getInputStream();
		Main.log("RigolInterface: connected");
		return i;
	}

	float get() throws IOException {
		out.print("MEAS");
		return Main.readFloatResponse(in);
	}

	void close() throws IOException {
		s.close();
	}

}

