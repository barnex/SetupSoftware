import java.awt.*;
import java.awt.event.*;
import java.io.*;
import javax.swing.*;

public final class PiezoPanel extends JPanel{

	JTextField xbox, ybox, zbox;

	static final double SMALL_JOG = 1./1024.;
	static final double JOG = 32./1024.;

	public PiezoPanel(){
		setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
		GUI.colorize(this);
		add(buttonPanel());
		add(textPanel());
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

		xbox = GUI.textbox();
		ybox = GUI.textbox();
		zbox = GUI.textbox();


		JPanel p = new JPanel();
		p.setLayout(new GridLayout(6, 2, 5, 5));

		p.add(GUI.panel());
		p.add(GUI.panel());

		p.add(GUI.label("y (horiz):"));
		p.add(ybox);
		p.add(GUI.label("z (vert):"));
		p.add(zbox);
		p.add(GUI.panel());
		p.add(GUI.panel());
		p.add(GUI.label("x (focus):"));
		p.add(xbox);

		p.setBackground(GUI.background);
		return p;
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
			}catch(IOException err){
				GUI.log(err.toString());
			}
		}
		private static final long serialVersionUID = 1; // sigh...
	}	

	private static final long serialVersionUID = 1; // sigh...
}
