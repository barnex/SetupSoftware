import java.awt.*;
import java.awt.event.*;
import java.io.*;
import javax.swing.*;

public final class PiezoPanel extends JPanel{

	JTextField[] posbox = new JTextField[4]; // x,y,z,aux

	static final double SMALL_JOG = 1./1024.;
	static final double JOG = 32./1024.;

	public PiezoPanel(){
		setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
		GUI.colorize(this);

		add(buttonPanel());
		add(textPanel());
	}

	// read values from piezo and update textboxes, labels
	void update(){
		posbox[0].setText("" + Main.piezo.posX);
		posbox[1].setText("" + Main.piezo.posY);
		posbox[2].setText("" + Main.piezo.posZ);
		posbox[3].setText("" + Main.piezo.posAux);
	}

	JPanel buttonPanel(){
		JPanel p = new JPanel();
		p.setLayout(new GridLayout(5, 7));
		
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
