import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

/** This is the GUI component for controlling the piezo stage and making images. */
public final class PiezoPanel extends JPanel implements Updater {

	PiezoController contr;    // The piezo controller program we talk to
	final double UNIT = 20.0; // piezo full range in micron

	ImageView viewer;                        // displays the image
	JTextField[] posbox = new JTextField[4]; // enter positions for x, y, z,aux
	JTextField pixX = new JTextField("20");  // number of pixels
	JTextField pixY = new JTextField("20");  // number of pixels
	JTextField strideX = new JTextField("5");// image size
	JTextField strideY = new JTextField("5");// image size
	JTextField settle = new JTextField("2"); // settle time
	JComboBox typeSel = new JComboBox(new String[] {"image (YZ)", "focus horiz. (YX)", "focus vert. (ZX)"});
	int scanI, scanJ;                        // scan directions (0=X, 1=Y, ...)
	JLabel pitch = GUI.label("-");           // pixel pitch

	static final String[]coordStr= {"x", "y", "z", "aux"};
	static final double SMALL_JOG = 1./1024.;
	static final double JOG = 32./1024.;
	static final int X = 0, Y=1, Z=2;

	/// Build GUI

	/** PiezoPanel for talking to specified controller. */
	public PiezoPanel(PiezoController contr) {
		this.contr = contr;

		setLayout(new BorderLayout());
		viewer = new ImageView();
		add(viewer, BorderLayout.CENTER);

		JPanel side = GUI.panel();
		side.setLayout(new BoxLayout(side, BoxLayout.Y_AXIS));
		side.setBorder(new TitledBorder("piezo"));
		side.add(buttonPanel());
		side.add(textPanel());
		side.add(scanPanel());

		add(side, BorderLayout.EAST);
		contr.viewer = this.viewer;
	}

	JPanel scanPanel() {
		JPanel p = GUI.panel();
		p.setLayout(new GridLayout(7, 2));

		GUI.colorize(typeSel);
		typeSel.setBackground(GUI.textBackground);
		typeSel.setOpaque(true);
		p.add(GUI.label("type"));
		p.add(typeSel);

		p.add(GUI.label("width (pix):"));
		p.add(pixX);
		p.add(GUI.label("height (pix):"));
		p.add(pixY);

		p.add(GUI.label("width (µm):"));
		p.add(strideX);
		p.add(GUI.label("height (µm):"));
		p.add(strideY);

		p.add(GUI.label("settle time"));
		p.add(settle);

		p.add(GUI.label("pixel pitch (µm):"));
		p.add(pitch);

		JPanel q = GUI.panel();
		JButton scan = GUI.button("scan");
		JButton abort = GUI.button("abort");
		abort.setBackground(Color.RED);
		abort.setForeground(Color.WHITE);
		q.add(scan);
		q.add(abort);

		scan.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Main.queue(new doScan());
			}
		});
		abort.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Main.piezo.dev.tryClose();
			}
		});

		JPanel root = GUI.panel();
		root.setLayout(new BoxLayout(root, BoxLayout.Y_AXIS));
		root.setBorder(new TitledBorder("scan"));
		root.add(p);
		root.add(q);

		return root;
	}

	JPanel buttonPanel() {
		JPanel p = new JPanel();
		p.setLayout(new GridLayout(5, 7, 5, 5));

		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(new JogButton("↑↑", 0, 0, JOG));
		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(new JogButton("↑↑", JOG, 0, 0));

		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(new JogButton("↑", 0, 0, SMALL_JOG));
		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(new JogButton("↑", SMALL_JOG, 0, 0));

		p.add(new JogButton("←←", 0, -JOG, 0));
		p.add(new JogButton("←", 0, -SMALL_JOG, 0));
		p.add(GUI.panel());
		p.add(new JogButton("→", 0, SMALL_JOG, 0));
		p.add(new JogButton("→→", 0, JOG, 0));
		p.add(GUI.panel());
		p.add(GUI.panel());

		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(new JogButton("↓", 0, 0, -SMALL_JOG));
		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(new JogButton("↓", -SMALL_JOG, 0, 0));

		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(new JogButton("↓↓", 0, 0, -JOG));
		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(new JogButton("↓↓", -JOG, 0, 0));

		p.setBackground(GUI.background);
		p.setOpaque(true);
		p.setPreferredSize(new Dimension(350, 250));
		return p;
	}

	JPanel textPanel() {
		for(int i=0; i<posbox.length; i++) {
			posbox[i] = GUI.textbox();
		}

		ActionListener a = new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				double x = atof(posbox[0].getText())/UNIT;
				double y = atof(posbox[1].getText())/UNIT;
				double z = atof(posbox[2].getText())/UNIT;
				double a = atof(posbox[3].getText())/UNIT;
				Main.queue(new doGoto(x, y, z, a));
			}
		};

		for(int i=0; i<posbox.length; i++) {
			posbox[i].addActionListener(a);
		}



		JPanel p = new JPanel();
		p.setLayout(new GridLayout(7, 2, 5, 5));

		p.add(GUI.panel());
		p.add(GUI.panel());

		p.add(GUI.label("y (horiz, µm):"));
		p.add(posbox[1]);
		p.add(GUI.label("z (vert, µm):"));
		p.add(posbox[2]);
		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(GUI.label("x (focus, µm):"));
		p.add(posbox[0]);
		p.add(GUI.label("aux:"));
		p.add(posbox[3]);

		p.setBackground(GUI.background);
		return p;
	}


	// read values from piezo and update textboxes, labels
	public void update() {
		posbox[0].setText("" + Main.piezo.posX*UNIT);
		posbox[1].setText("" + Main.piezo.posY*UNIT);
		posbox[2].setText("" + Main.piezo.posZ*UNIT);
		posbox[3].setText("" + Main.piezo.posAux);
		viewer.update();
	}



	class doScan implements Task {
		int w, h;
		double x, y, z, a;
		double startX, startY, startZ, startA;
		double xiinc, yiinc, ziinc, auxiinc;
		double xjinc, yjinc, zjinc, auxjinc;
		double tsettle;

		doScan() {


			x = atof(posbox[0].getText())/UNIT;
			y = atof(posbox[1].getText())/UNIT;
			z = atof(posbox[2].getText())/UNIT;
			a = atof(posbox[3].getText())/UNIT;

			startX = x;
			startY = y;
			startZ = z;
			startA = a;

			w = (int)(atof(pixX.getText()));
			h = (int)(atof(pixY.getText()));
			pixX.setText(""+w);
			pixY.setText(""+h);

			double iinc = atof(strideX.getText())/(w*UNIT);
			double jinc = atof(strideY.getText())/(h*UNIT);
			double i0, j0;
			pitch.setText( String.format("%.2f", (iinc*UNIT)) + " x " + String.format("%.2f", (jinc*UNIT)) );
			strideX.setText(""+(iinc*w*UNIT));
			strideY.setText(""+(jinc*h*UNIT));
			int type = typeSel.getSelectedIndex();
			switch (type) {
			default:
				throw new IllegalArgumentException("scan type " + type);
			case 0:  // image, YZ
				yiinc = iinc;
				zjinc = jinc;
				y -= (yiinc*w)/2.;
				z -= (zjinc*h)/2.;
				i0 = y;
				j0 = z;
				scanI = Y;
				scanJ = Z;
				break;
			case 1: // focus, XY
				xiinc = iinc;
				yjinc = jinc;
				x -= (xiinc*w)/2.;
				y -= (yjinc*h)/2.;
				i0 = x;
				j0 = y;
				scanI = X;
				scanJ = Y;
				break;
			case 2: // focus, ZX
				ziinc = iinc;
				xjinc = jinc;
				z -= (ziinc*w)/2.;
				x -= (xjinc*h)/2.;
				i0 = z;
				j0 = x;
				scanI = Z;
				scanJ = X;
				break;
			}
			viewer.dx = iinc*UNIT;
			viewer.dy = jinc*UNIT;
			viewer.x0 = i0*UNIT;
			viewer.y0 = j0*UNIT;

			tsettle = atof(settle.getText());
			settle.setText(""+tsettle);
		}
		public void run() throws Exception {
			Main.piezo.setStart(x, y, z, a);
			Main.piezo.goTo();
			Main.piezo.setpixels(w, h);
			Main.piezo.setIInc(xiinc, yiinc, ziinc, auxiinc);
			Main.piezo.setJInc(xjinc, yjinc, zjinc, auxjinc);
			Main.piezo.setTSettle(tsettle);
			Main.piezo.scan2d();
			Main.piezo.dev.connect(); // TODO: make sure controller doesn't drop connection
			Main.piezo.setStart(startX, startY, startZ, startA);
			Main.piezo.goTo();
		}
	}


	class doGoto implements Task {
		double x, y, z, a;
		doGoto(double x, double y, double z, double a) {
			this.x = x;
			this.y = y;
			this.z = z;
			this.a = a;
		}
		public void run() throws Exception {
			Main.piezo.setStart(x,y,z,a);
			Main.piezo.goTo();
			GUI.update();
		}
	}


	static double atof(String a) {
		double f = Double.parseDouble(a);
		return f;
	}


	class JogButton extends JButton implements ActionListener {
		double dx, dy, dz;
		JogButton(String label, double dx, double dy, double dz) {
			super(label);
			this.dx=dx;
			this.dy=dy;
			this.dz=dz;
			addActionListener(this);
			setContentAreaFilled(false); // less ugly, but only slightly
			setBackground(GUI.middleground);
			setForeground(GUI.foreground);
			setOpaque(true);
			setMargin(new Insets(0,0,0,0));
		}
		public void actionPerformed(ActionEvent e) {
			Main.queue(new doJog(dx, dy, dz));
		}
		private static final long serialVersionUID = 1; // sigh...
	}

	class doJog implements Task {
		double dx, dy, dz;
		doJog(double dx, double dy, double dz) {
			this.dx = dx;
			this.dy = dy;
			this.dz = dz;
		}
		public void run() throws Exception {
			Main.piezo.jog(dx, dy, dz);
			GUI.update();
		}
	}

	private static final long serialVersionUID = 1; // sigh...


	class ImageView extends JPanel implements MouseListener, MouseMotionListener, Updater {

		int chan = 0;
		ColorMap colormap = new ColorMap();
		double x0, y0, dx, dy; // center position and pixel stride, in µm, to display cursor position
		double mouseX, mouseY; // last mouse position, in µm
		JLabel coords;

		public ImageView() {
			GUI.colorize(this);
			setPreferredSize(new Dimension(512, 512));
			addMouseListener(this);
			addMouseMotionListener(this);
			setCursor (Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR));
		}

		public void mouseEntered(MouseEvent e) {}
		public void mouseExited(MouseEvent e) {}
		public void mousePressed(MouseEvent e) {}
		public void mouseReleased(MouseEvent e) {}
		public void mouseClicked(MouseEvent e) {
			if (e.getClickCount() == 2) {
				GUI.piezo.posbox[GUI.piezo.scanI].setText(fmt(mouseX));
				GUI.piezo.posbox[GUI.piezo.scanJ].setText(fmt(mouseY));
			}
		}
		public void mouseDragged(MouseEvent e) {}
		public void mouseMoved(MouseEvent e) {
			float[][][] image = contr.image;
			int W = getWidth();
			int H = getHeight();
			int i = e.getX();
			int j = (H-e.getY());
			int nJ = image[chan].length;
			int nI = image[chan][0].length;
			double I = (double)(i*nI)/W;
			double J = (double)(j*nJ)/H;
			mouseX = x0 + dx * I;
			mouseY = y0 + dy * J;

			if (coords != null) {
				coords.setText(fmt(mouseX) + ", " + fmt(mouseY) + " µm");

			}

		}

		public void update() {
			float[][][] image = contr.image;
			float[][] img = image[chan];

			float min = Float.MAX_VALUE;
			float max = Float.MIN_VALUE;

			for(int i=0; i<img.length; i++) {
				for(int j=0; j<img[i].length; j++) {
					float v = img[i][j];
					if(v<min) {
						min=v;
					}
					if(v>max) {
						max=v;
					}
				}
			}

			colormap.setRange(min, max);

			repaint();

		}

		public void paintComponent(Graphics g_) {

			Graphics2D g = (Graphics2D)(g_);
			int W = getWidth();
			int H = getHeight();

			// clear background
			g.setColor(Color.WHITE);
			g.fillRect(0, 0, W, H);


			float[][] img = contr.image[chan];
			int nI = img.length;
			int nJ = img[0].length;
			int sx = W / nJ + 1;
			int sy = H / nI + 1;

			for(int i=0; i<nI; i++) {
				for(int j=0; j<nJ; j++) {
					int x = (W*j)/nJ;
					int y = H-(H*i)/nI-sy;

					double v = (double)(img[i][j]);
					if(Double.isNaN(v)) {
						continue;
					}
					Color c = colormap.get(v);
					g.setColor(c);
					g.fillRect(x, y, sx, sy);
				}
			}
		}

		private static final long serialVersionUID = 1; // sigh...
	}


	static String fmt(double x) {
		return String.format("%.2f", x);
	}
}
