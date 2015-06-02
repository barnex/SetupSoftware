
public final class Main {

	static boolean verbose = true;

	public static void main(String[] args) throws Exception {
		//Rigol rigol = new Rigol("mona.ugent.be", 5005);
		//System.out.println("rigol id     : " + rigol.id() );
		//System.out.println("rigol measure: " + rigol.measure() + "V");

		//HP hp1 = new HP("hp1", "mona.ugent.be", 5003);
		//System.out.println("hp1 id: " + hp1.id() );

		PiezoController piezo = new PiezoController("mona.ugent.be", 5000);
		System.out.println("piezo id: " + piezo.id() );
		piezo.setStart(0.1, 0.2, 0.3, 0.4);
		piezo.goTo();
		piezo.setIInc(0.008, 0, 0, 0);
		piezo.setIJnc(0, 0.008, 0, 0);
		piezo.setpixels(4, 3);
		piezo.setTSettle(5);
		piezo.goTo();
		piezo.scan2d();

		piezo.close();
		//piezo.abort();
		//piezo.scan2d();
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
