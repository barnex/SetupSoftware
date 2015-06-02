import java.awt.*;
import java.awt.event.*;
import java.io.*;
import javax.swing.*;

public final class PiezoPanel extends JPanel{

	static final double SMALL_JOG = 0.001;
	static final double JOG = 0.05;

	public PiezoPanel(){
		setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
		add(buttonPanel());
		add(textPanel());

		setBackground(GUI.background);
		setOpaque(true);
	}

	JPanel buttonPanel(){
		JPanel p = new JPanel();
		p.setLayout(new GridLayout(5, 7));
		
		p.add(padding());
		p.add(padding());
		p.add(new JogButton("↑↑", 0, 0, -JOG));
		p.add(padding());
		p.add(padding());
		p.add(padding());
		p.add(new JogButton("↑↑", JOG, 0, 0));

		p.add(padding());
		p.add(padding());
		p.add(new JogButton("↑", 0, 0, -SMALL_JOG));
		p.add(padding());
		p.add(padding());
		p.add(padding());
		p.add(new JogButton("↑", SMALL_JOG, 0, 0));

		p.add(new JogButton("←←", 0, -JOG, 0));
		p.add(new JogButton("←", 0, -SMALL_JOG, 0));
		p.add(padding());
		p.add(new JogButton("→", 0, SMALL_JOG, 0));
		p.add(new JogButton("→→", 0, JOG, 0));
		p.add(padding());
		p.add(padding());

		p.add(padding());
		p.add(padding());
		p.add(new JogButton("↓", 0, 0, SMALL_JOG));
		p.add(padding());
		p.add(padding());
		p.add(padding());
		p.add(new JogButton("↓", -SMALL_JOG, 0, 0));

		p.add(padding());
		p.add(padding());
		p.add(new JogButton("↓↓", 0, 0, JOG));
		p.add(padding());
		p.add(padding());
		p.add(padding());
		p.add(new JogButton("↓↓", -JOG, 0, 0));

		p.setBackground(GUI.background);
		p.setOpaque(true);
		p.setPreferredSize(new Dimension(350, 250));
		return p;
	}

	JPanel textPanel(){
		JPanel p = new JPanel();
		p.setLayout(new GridLayout(6, 2, 5, 5));

		p.add(padding());
		p.add(padding());

		p.add(label("y (horiz):"));
		p.add(new PiezoBox(0));
		p.add(label("z (vert):"));
		p.add(new PiezoBox(1));
		p.add(padding());
		p.add(padding());
		p.add(label("x (focus):"));
		p.add(new PiezoBox(2));

		p.setBackground(GUI.background);
		return p;
	}

	JLabel label(String text){
		JLabel l = new JLabel(text);
		l.setBackground(GUI.background);
		l.setForeground(GUI.foreground);
		return l;
	}

	JPanel padding(){
		JPanel p = new JPanel();
		p.setBackground(GUI.background);
		return p;
	}

	class PiezoBox extends JTextField{
		PiezoBox(int component){
			setBackground(GUI.background);
			setForeground(GUI.foreground);
		}
		private static final long serialVersionUID = 1; // sigh...
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
