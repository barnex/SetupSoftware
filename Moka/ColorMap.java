import java.awt.Color;

public final class ColorMap {

	private Color[] map = new Color[512];
	private Interpolator ip;
	private double min;
	public double max;
	private Color a, b, c;

	public ColorMap() {
		this(1);
	}

	public ColorMap(double max) {
		this(max, Color.BLACK, Color.GRAY, Color.WHITE);
	}

	public ColorMap(double max, Color a, Color b, Color c) {
		this(-max, max, a, b, c);
	}

	public ColorMap(double min, double max, Color a, Color b, Color c) {
		setColorMap(min, max, a, b, c);
	}

	public void setColorMap(double min, double max, Color a, Color b, Color c) {
		this.a = a;
		this.b = b;
		this.c = c;
		this.min = min;
		this.max = max;
		ip = new Interpolator(min, 0, max, 511);
		for(int i = 0; i < 256; i++)
			map[i] = mix(a, b, i);
		for(int i = 256; i < 512; i++)
			map[i] = mix(b, c, i-256);
	}

	public void setValues(double min, double max) {
		setColorMap(min, max, a, b, c);
	}

	public void setColors(Color a, Color b, Color c) {
		setColorMap(min,max, a, b, c);
	}

	private Color mix(Color a, Color b, int i) {
		int rd = (255*a.getRed()   + (b.getRed()  -a.getRed())   * i) / 255;
		int gn = (255*a.getGreen() + (b.getGreen()-a.getGreen()) * i) / 255;
		int bl = (255*a.getBlue()  + (b.getBlue() -a.getBlue())  * i) / 255;
		return new Color(rd, gn, bl);
	}

	public Color get(double value) {
		int color = (int)ip.transf(value);
		if(color > 511)
			color = 511;
		else if(color < 0)
			color = 0;
		return map[color];
	}

	final class Interpolator {

		double a, b;

		Interpolator(double x1, double y1, double x2, double y2) {
			a = (y2-y1)/(x2-x1);
			b = y1-x1*(y2-y1)/(x2-x1);
		}

		double transf(double x) {
			return a*x+b;
		}
	}

}

