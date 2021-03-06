import java.io.*;
import java.util.*;

/**
 * Class Proto implements the Mathias-2015 protocol for communicating over the network
 * device interface programs like HPInterface, RigolInterface, etc.
 * See send() and receive() for protocol details.
 * Mostly reverse-engineered from Mathia's C code.
 */
public final class Proto {

	// Return statusses in response header. Taken form Libraries/errors.h
	public static final int	FAILURE                 = -1;
	public static final int SUCCESS                 =  1;
	public static final int FINISHED                =  2;
	public static final int UNKNOWN_COMMAND         = -1;
	public static final int NOT_ENOUGH_PARAMETERS	= -2;
	public static final int HARDWARE_COMM_ERR       = -3;
	public static final int UNKNOWN_PARAMETER       = -4;

	// Maximum acceppted payload, avoid out-of-memory on malformed message.
	public static final int MAX_PAYLOAD       = 10000;

	// maps status numbers to human-readible information
	private static final HashMap<Integer, String> statusStr = new HashMap<Integer, String>();

	static {
		statusStr.put(FAILURE              , "FAILURE"              );
		statusStr.put(SUCCESS              , "SUCCESS"              );
		statusStr.put(FINISHED             , "FINISHED"             );
		statusStr.put(UNKNOWN_COMMAND      , "UNKNOWN_COMMAND"      );
		statusStr.put(NOT_ENOUGH_PARAMETERS, "NOT_ENOUGH_PARAMETERS");
		statusStr.put(HARDWARE_COMM_ERR    , "HARDWARE_COMM_ERR"    );
		statusStr.put(UNKNOWN_PARAMETER    , "UNKNOWN_PARAMETER"    );
	}


	/** Send a request string to out, e.g.: "MEAS", "SET,FREQ,1e9".
	    The request is sent as-is, in plaintext.
	    The request should not end with a newline.                  */
	public static void send(OutputStream out, String request) throws IOException {
		out.write(request.getBytes());
	}

	/** Read and parse a response to a prior request.
	    The response is sent in little-endian binary consisting of a number of 32-bit words.
		First word (int): status code: 1=OK, other=FAIL.
		Second word (int): length, in bytes of data payload (may be 0)
		Subsequent words, as many bytes as indicated by payload size:
		payload data which can be a string, floats or ints.         */
	public static byte[] receive(InputStream in) throws IOException {
		//Main.debugn("receive: ");
		// Parse the header
		byte[] hdr = new byte[8];
		readFull(in, hdr);
		int status = toIntOff(hdr, 0);
		int payload = toIntOff(hdr, 4);

		if(payload > MAX_PAYLOAD) {
			throw new IOException("too big payload: " + payload);
		}


		// Read the payload, even on error
		byte []data = new byte[payload];
		readFull(in, data);
		if(status > 0) {
			//Main.debug("OK");
			return data;
		} else {
			String info = statusStr.get(status);
			if(info  == null) {
				info = "unknown error";
			}
			throw new IOException("received status " + status + ": " + info);
		}
	}

	/** Convert a response to String. */
	static String toString(byte[] response) {
		return new String(response);
	}

	/** Convert a response to a float. */
	static float toFloat(byte[] response) {
		return Float.intBitsToFloat(toInt(response));
	}

	/** Convert a response to a float. */
	static float toFloatOff(byte[] response, int off) {
		return Float.intBitsToFloat(toIntOff(response, off));
	}

	/** Convert a response to int. */
	static int toInt(byte[] response) {
		Main.check(response.length == 4);
		return toIntOff(response, 0);
	}

	// read from in until data is full.
	private static void readFull(InputStream in, byte[] data) throws IOException {
		int N = data.length;
		int off = 0;
		while(off < N) {
			int read = in.read(data, off, N-off);
			if(read <= 0) {
				throw new IOException("read error");
			}
			off += read;
		}
	}

	// convert 4 bytes starting at offset off to int
	// assuming little endian encoding.
	private static int toIntOff(byte[] data, int off) {
		long b0 = (long)(data[off+0]) & 0xFF;
		long b1 = (long)(data[off+1]) & 0xFF;
		long b2 = (long)(data[off+2]) & 0xFF;
		long b3 = (long)(data[off+3]) & 0xFF;

		long v = (b0) | (b1 << 8) | (b2 << 16) | (b3 << 24);
		return (int)(v);
	}
}
