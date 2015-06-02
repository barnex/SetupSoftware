
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public final class PiezoPanel extends JPanel{

	static final double SMALL_JOG = 0.001;
	static final double JOG = 0.05;

	public PiezoPanel(){
		setLayout(new GridLayout(5, 7));
		
		add(new JPanel());
		add(new JPanel());
		add(new JogButton("↑↑", 0, 0, JOG));
		add(new JPanel());
		add(new JPanel());
		add(new JPanel());
		add(new JogButton("↑↑", JOG, 0, 0));

		add(new JPanel());
		add(new JPanel());
		add(new JogButton("↑", 0, 0, SMALL_JOG));
		add(new JPanel());
		add(new JPanel());
		add(new JPanel());
		add(new JogButton("↑", SMALL_JOG, 0, 0));

		add(new JogButton("←←", 0, 0, JOG));
		add(new JogButton("←", 0, 0, SMALL_JOG));
		add(new JPanel());
		add(new JogButton("→", 0, 0, SMALL_JOG));
		add(new JogButton("→→", 0, 0, JOG));
		add(new JPanel());
		add(new JPanel());

		add(new JPanel());
		add(new JPanel());
		add(new JogButton("↓", 0, 0, -SMALL_JOG));
		add(new JPanel());
		add(new JPanel());
		add(new JPanel());
		add(new JogButton("↓", -SMALL_JOG, 0, 0));

		add(new JPanel());
		add(new JPanel());
		add(new JogButton("↓↓", 0, 0, -JOG));
		add(new JPanel());
		add(new JPanel());
		add(new JPanel());
		add(new JogButton("↓↓", -JOG, 0, 0));



	}

	class JogButton extends JButton implements ActionListener{
		double dx, dy, dz;
		JogButton(String label, double dx, double dy, double dz){
			super(label);
			this.dx=dx;
			this.dy=dy;
			this.dz=dz;
			addActionListener(this);
		}
		public void actionPerformed(ActionEvent e){
			Main.log("click");
		}
		private static final long serialVersionUID = 1; // sigh...
	}	

	private static final long serialVersionUID = 1; // sigh...
}
