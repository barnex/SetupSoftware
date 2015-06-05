import java.util.concurrent.*;

public final class Main {

	static boolean verbose = true;

	static PiezoController piezo;

	static final int N_THREADS = 1;
	static ArrayBlockingQueue<Runnable> requests = new ArrayBlockingQueue<Runnable>(N_THREADS);	
	

	public static void main(String[] args) throws Exception {
		//Rigol rigol = new Rigol("mona.ugent.be", 5005);
		//System.out.println("rigol id     : " + rigol.id() );
		//System.out.println("rigol measure: " + rigol.measure() + "V");

		//HP hp1 = new HP("hp1", "mona.ugent.be", 5003);
		//System.out.println("hp1 id: " + hp1.id() );
		


		piezo = new PiezoController("mona.ugent.be", 5000);
		piezo.setStart(0.5, 0.5, 0.5, 0);
		piezo.goTo();

		GUI.init();	
		piezo.viewer = GUI.viewer;

		for(int i=0; i<N_THREADS; i++){
			new Thread(new Worker()).start();
		}
	}


	static void log(String msg) {
		if (verbose) {
			System.err.println(msg);
		}
	}

	static void logn(String msg) {
		if (verbose) {
			System.err.print(msg);
		}
	}

	static void check(boolean test) {
		if(test == false) {
			throw new IllegalArgumentException("assertion failed");
		}
	}
}
