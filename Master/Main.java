import java.io.*;
import java.net.*;

/*
	HP: ID; SET: FREQ, POW;
	Rigol: ID; MEAS;
 */

public final class Main {

	public static void main(String[] args) throws Exception {
		Socket s = new Socket("mona.ugent.be", 5005);
		PrintStream out = new PrintStream(s.getOutputStream());
		InputStream in = s.getInputStream();

		out.println("MEAS");

		byte[] hdr = new byte[8];
		readFull(in, hdr);
		int status = toInt(hdr, 0);
		int payload = toInt(hdr, 4);

		System.out.println("status: " + status+ ", payload: " + payload);

		if(payload > 0) {
			byte[] data = new byte[payload];
			readFull(in, data);
			System.out.println(Float.intBitsToFloat(toInt(data, 0)));
		}

		s.close();
	}

	//float readOneFloat(IntputStream in){
	//
	//}

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

}
