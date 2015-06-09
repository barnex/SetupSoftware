import java.util.concurrent.*;

public final class Main {

	static boolean verbose = true;

	static PiezoController piezo;

	private static int QUEUE_LEN = 3;
	static private ArrayBlockingQueue<Task> requests = new ArrayBlockingQueue<Task>(QUEUE_LEN);


	public static void main(String[] args) throws Exception {
		init();
		connect(); // if the initial connection fails, let's exit and troubleshoot.
		disconnect();

		// main loop: receive requests from gui.
		for(;;) {
			Task t = null;
			try {
				t = Main.requests.take();
				Main.err("running: " + t.toString());
				connect();
				t.run();
				Main.err("ready");
			} catch(Exception e) {
				Main.err(t.toString() + ": " + e.toString());
				piezo.dev.tryClose();
				break;
			}
			disconnect();
		}

	}

	// Queue a Task to be executed in the main loop as soon as possible.
	// Called by the GUI to run scans without blocking the GUI responsiveness.
	static void queue(Task t) {
		try {
			requests.put(t);
		} catch(InterruptedException e) {
			debug(e.toString());
			System.exit(1);
		}
	}

	static void connect() throws Exception {
		piezo.dev.connect();
	}

	static void disconnect() throws Exception {
		piezo.dev.tryClose();
	}

	static void init() {
		piezo = new PiezoController("mona.ugent.be", 5000);
		GUI.init();
	}

	static void debug(String msg) {
		if (verbose) {
			System.err.println(msg);
		}
	}

	static void debugn(String msg) {
		if (verbose) {
			System.err.print(msg);
		}
	}

	static void err(String msg) {
		debug(msg);
		GUI.log(msg);
	}

	static void check(boolean test) {
		if(test == false) {
			throw new IllegalArgumentException("assertion failed");
		}
	}
}
