import java.util.concurrent.*;

public final class Main {

	static boolean verbose = true;

	static PiezoController piezo;

	private static int QUEUE_LEN = 10;
	static private ArrayBlockingQueue<Task> requests = new ArrayBlockingQueue<Task>(QUEUE_LEN);	
	

	public static void main(String[] args) throws Exception {
		init();
		reconnect(); // if the initial connection fails, let's exit and troubleshoot.

		// main loop: receive requests from gui.
		for( ;; ){

			// run tasks untill error
			for(;;){
				Task t = null;
				try{
					t = Main.requests.take();
					Main.err("running: " + t.toString());
					t.run();
					Main.err("ready");
				}catch(Exception e){
					Main.err(t.toString() + ": " + e.toString());
					piezo.dev.tryClose();
					break;
				}
			}

			// re-connect
			boolean ok = false;
			while(!ok){
				try{
					reconnect();
					ok = true;
				}catch(Exception e){
					Main.err(e.toString() + ", retrying connection...");
					Thread.sleep(3000);
					ok = false;
				}
			}

		}

	}

	static void init(){
		//Rigol rigol = new Rigol("mona.ugent.be", 5005);
		//System.out.println("rigol id     : " + rigol.id() );
		//System.out.println("rigol measure: " + rigol.measure() + "V");

		//HP hp1 = new HP("hp1", "mona.ugent.be", 5003);
		//System.out.println("hp1 id: " + hp1.id() );
		

		piezo = new PiezoController("mona.ugent.be", 5000);

		GUI.init();	
		piezo.viewer = GUI.viewer;

	}

	static void reconnect() throws Exception{
		piezo.dev.connect();
	}

	static void run(Task t){
		//log("queue task " + t.toString());
		try{
		requests.put(t);
		}catch(InterruptedException e){
			debug(e.toString());
			System.exit(1);
		}
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

	static void err(String msg){
		debug(msg);
		GUI.log(msg);
	}

	static void check(boolean test) {
		if(test == false) {
			throw new IllegalArgumentException("assertion failed");
		}
	}
}
