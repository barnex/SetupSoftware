import java.awt.Color;

public final class ColorMap {

	private static Color[] map = new Color[256];
	double gamma = 2.2;
	double min;
	double max;

	static {
		for(int i=0; i<256; i++) {
			map[i] = new Color(i, i, i);
		}
	}

	public void setRange(double min, double max) {
		this.min=min;
		this.max=max;
	}

	public Color get(double value) {
		double x1 = min;
		double y1 = 0;
		double x2 = max;
		double y2 = 1;

		double a = (y2-y1)/(x2-x1);
		double b = y1-x1*(y2-y1)/(x2-x1);
		value = a*value + b;

		value = Math.pow(value, 1./gamma);

		value *= 255;

		if(value < 0) {
			value = 0;
		}
		if(value > 255) {
			value = 255;
		}
		return map[(int)(value)];
	}
}

