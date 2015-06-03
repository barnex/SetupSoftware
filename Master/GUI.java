import java.awt.event.*;
import java.awt.*;
import javax.swing.*;
import javax.swing.border.*;

public final class GUI{

	static final Color background = new Color(255, 255, 150); // "Tolek Yellow"
	static final Color middleground = Color.LIGHT_GRAY;
	static final Color foreground = Color.BLACK;
	static final Color textBackground = Color.WHITE;

	static ImageView viewer = new ImageView();
	static JLabel statusLabel = label("MOKA controller");
	static PiezoPanel piezo;

	static final int FRAME_W = 800, FRAME_H = 600; // initial window size


	public static void init()  {
		JFrame f = makeFrame();

		f.getContentPane().add(viewer, BorderLayout.CENTER);

		f.getContentPane().add(statusLabel, BorderLayout.SOUTH);

		JPanel pp = new JPanel();
		pp.setBorder(new TitledBorder("piezo"));
		pp.setBackground(background);
		piezo = new PiezoPanel();
		pp.add(piezo);
		f.getContentPane().add(pp, BorderLayout.EAST);
		update();

		f.setVisible(true);
	}

	static void update(){
		piezo.update();
	}

	static JFrame makeFrame(){
		final JFrame f = new JFrame();
		f.setFocusable(true);
		f.setSize(FRAME_W, FRAME_H);
		f.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				f.dispose();
			}
		});
		f.setBackground(background);
		f.getContentPane().setLayout(new BorderLayout());
		return f;
	}

	static JLabel label(String text){
		JLabel l = new JLabel(text);
		colorize(l);
		l.setOpaque(true);
		return l;
	}

	static JPanel panel(){
		JPanel p = new JPanel();
		colorize(p);
		return p;
	}

	static JTextField textbox(){
		JTextField f = new JTextField();
		colorize(f);
		f.setBackground(textBackground);	
		return f;
	}


	static void colorize(JComponent c){
		c.setBackground(background);
		c.setForeground(foreground);
		c.setOpaque(true);
	}

	static void log(String msg){
		Main.log(msg);
		statusLabel.setText(msg);
	}
}
