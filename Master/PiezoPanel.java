import java.awt.*;
import java.awt.event.*;
import java.io.*;
import javax.swing.*;

public final class PiezoPanel extends JPanel{

	static final double SMALL_JOG = 0.001;
	static final double JOG = 0.05;

	public PiezoPanel(){
		setLayout(new GridLayout(5, 7));
		
		add(padding());
		add(padding());
		add(new JogButton("↑↑", 0, 0, -JOG));
		add(padding());
		add(padding());
		add(padding());
		add(new JogButton("↑↑", JOG, 0, 0));

		add(padding());
		add(padding());
		add(new JogButton("↑", 0, 0, -SMALL_JOG));
		add(padding());
		add(padding());
		add(padding());
		add(new JogButton("↑", SMALL_JOG, 0, 0));

		add(new JogButton("←←", 0, -JOG, 0));
		add(new JogButton("←", 0, -SMALL_JOG, 0));
		add(padding());
		add(new JogButton("→", 0, SMALL_JOG, 0));
		add(new JogButton("→→", 0, JOG, 0));
		add(padding());
		add(padding());

		add(padding());
		add(padding());
		add(new JogButton("↓", 0, 0, SMALL_JOG));
		add(padding());
		add(padding());
		add(padding());
		add(new JogButton("↓", -SMALL_JOG, 0, 0));

		add(padding());
		add(padding());
		add(new JogButton("↓↓", 0, 0, JOG));
		add(padding());
		add(padding());
		add(padding());
		add(new JogButton("↓↓", -JOG, 0, 0));

		setBackground(GUI.background);
		setOpaque(true);
		setPreferredSize(new Dimension(350, 250));
	}

	JPanel padding(){
		JPanel p = new JPanel();
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
