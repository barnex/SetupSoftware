import java.awt.*;
import java.awt.event.*;
import java.io.*;
import javax.swing.*;
import javax.swing.border.*;

public final class PiezoPanel extends JPanel{

	JTextField[] posbox = new JTextField[4]; // x,y,z,aux
	JTextField pixX = new JTextField("20");
	JTextField pixY = new JTextField("20");
	JTextField strideX = new JTextField("0.01");
	JTextField strideY = new JTextField("0.01");
	JTextField settle = new JTextField("5");
	JComboBox typeSel = new JComboBox(new String[]{"image (YZ)", "focus horiz. (YX)", "focus vert. (ZX)"});

	static final double SMALL_JOG = 1./1024.;
	static final double JOG = 32./1024.;

	public PiezoPanel(){
		setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
		GUI.colorize(this);
		setBorder(new TitledBorder("piezo"));

		add(buttonPanel());
		add(textPanel());
		add(scanPanel());
	}

	// read values from piezo and update textboxes, labels
	void update(){
		posbox[0].setText("" + Main.piezo.posX);
		posbox[1].setText("" + Main.piezo.posY);
		posbox[2].setText("" + Main.piezo.posZ);
		posbox[3].setText("" + Main.piezo.posAux);
	}

	JPanel scanPanel(){
		JPanel p = GUI.panel();
		p.setLayout(new GridLayout(6, 2));

		GUI.colorize(typeSel);
		typeSel.setBackground(GUI.textBackground);
		typeSel.setOpaque(true);
		p.add(GUI.label("type"));
		p.add(typeSel);

		p.add(GUI.label("width (pix):"));
		p.add(pixX);
		p.add(GUI.label("height (pix):"));
		p.add(pixY);

		p.add(GUI.label("stride w:"));
		p.add(strideX);
		p.add(GUI.label("stride h:"));
		p.add(strideY);

		p.add(GUI.label("settle time"));
		p.add(settle);


		JPanel q = GUI.panel();
		//q.setLayout(new BoxLayout(q, BoxLayout.Y_AXIS));
		JButton scan = GUI.button("scan");
		JButton abort = GUI.button("abort");
		abort.setBackground(Color.RED);
		abort.setForeground(Color.WHITE);
		q.add(scan);
		q.add(abort);

		scan.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				doScan();
			}
		});
		abort.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				doAbort();
			}
		});

		JPanel root = GUI.panel();
		root.setLayout(new BoxLayout(root, BoxLayout.Y_AXIS));
		root.setBorder(new TitledBorder("scan"));
		root.add(p);
		root.add(q);

		return root;
	}

	void doAbort(){
		try{	
			Main.piezo.abort();
		}catch(Exception err){ // TODO
			Main.log(err.toString());
		}
		
	}

	void doScan(){
		try{
			int w = (int)(atof(pixX.getText()));
			int h = (int)(atof(pixY.getText()));
			pixX.setText(""+w);
			pixY.setText(""+h);
			Main.piezo.setpixels(w, h);

			double iinc = atof(strideX.getText());
			double jinc = atof(strideY.getText());
			strideX.setText(""+iinc);
			strideY.setText(""+jinc);
			int type = typeSel.getSelectedIndex();

			double xiinc = 0., yiinc = 0., ziinc = 0.;
			double xjinc = 0., yjinc = 0., zjinc = 0.;

			switch (type){
				default: throw new IllegalArgumentException("scan type " + type);
				case 0:  // image, YZ
				yiinc = iinc;
				zjinc = jinc;
				break;
				case 1: // focus, XY
				xiinc = iinc;
				yjinc = jinc;
				break;
				case 2: // focus, ZX
				ziinc = iinc;
				xjinc = jinc;
				break;
			}
			double auxinc = 0.;
			Main.piezo.setIInc(xiinc, yiinc, ziinc, auxinc);
			Main.piezo.setIInc(xjinc, yjinc, zjinc, auxinc);

	
			double tsettle = atof(settle.getText());
			settle.setText(""+tsettle);
			Main.piezo.setTSettle(tsettle);

			Main.piezo.goTo();
			Main.piezo.scan2d();
		}catch(Exception err){ // TODO
			Main.log(err.toString());
		}
	}

	JPanel buttonPanel(){
		JPanel p = new JPanel();
		p.setLayout(new GridLayout(5, 7, 5, 5));
		
		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(new JogButton("↑↑", 0, 0, -JOG));
		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(new JogButton("↑↑", JOG, 0, 0));

		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(new JogButton("↑", 0, 0, -SMALL_JOG));
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
		p.add(new JogButton("↓", 0, 0, SMALL_JOG));
		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(new JogButton("↓", -SMALL_JOG, 0, 0));

		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(new JogButton("↓↓", 0, 0, JOG));
		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(new JogButton("↓↓", -JOG, 0, 0));

		p.setBackground(GUI.background);
		p.setOpaque(true);
		p.setPreferredSize(new Dimension(350, 250));
		return p;
	}

	JPanel textPanel(){
		for(int i=0; i<posbox.length; i++){
			posbox[i] = GUI.textbox();
		}	

		ActionListener a = new ActionListener(){
			public void actionPerformed(ActionEvent e){
				try{
					double x = atof(posbox[0].getText());
					double y = atof(posbox[1].getText());
					double z = atof(posbox[2].getText());
					double a = atof(posbox[3].getText());
					Main.piezo.setStart(x,y,z,a);
					Main.piezo.goTo();
					update();	
				}catch(Exception err){
					Main.log(err.toString()); // TODO;
				}
			}
		};

		for(int i=0; i<posbox.length; i++){
			posbox[i].addActionListener(a);
		}	



		JPanel p = new JPanel();
		p.setLayout(new GridLayout(7, 2, 5, 5));

		p.add(GUI.panel());
		p.add(GUI.panel());

		p.add(GUI.label("y (horiz):"));
		p.add(posbox[1]);
		p.add(GUI.label("z (vert):"));
		p.add(posbox[2]);
		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(GUI.label("x (focus):"));
		p.add(posbox[0]);
		p.add(GUI.label("aux:"));
		p.add(posbox[3]);

		p.setBackground(GUI.background);
		return p;
	}

	static double atof(String a){
		double f = Double.parseDouble(a);
		return f;
	}


	class JogButton extends JButton implements ActionListener{
		double dx, dy, dz;
		JogButton(String label, double dx, double dy, double dz){
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
		public void actionPerformed(ActionEvent e){
			try{
				Main.piezo.jog(dx, dy, dz);
				GUI.update();
			}catch(IOException err){
				GUI.log(err.toString());
			}
		}
		private static final long serialVersionUID = 1; // sigh...
	}	

	private static final long serialVersionUID = 1; // sigh...
}
