import java.awt.event.*;
import java.awt.*;
import javax.swing.*;

public final class GUI {

	static final Color TOLEK_YELLOW = new Color(255, 255, 150); // typical STXM GUI color
	static final Color background = TOLEK_YELLOW;
	static final Color middleground = Color.LIGHT_GRAY;
	static final Color foreground = Color.BLACK;
	static final Color textBackground = Color.WHITE;
	static final String progname = "MOKA controller";

	static JLabel statusLabel = label(progname);
	static PiezoPanel piezo;

	static final int FRAME_W = 800, FRAME_H = 600; // initial window size


	public static void init()  {
		JFrame f = makeFrame();

		f.getContentPane().add(statusLabel, BorderLayout.SOUTH);

		piezo = new PiezoPanel(Main.piezo);
		f.getContentPane().add(piezo, BorderLayout.CENTER);

		update();

		f.pack();
		f.setVisible(true);
	}

	static void update() {
		piezo.update();
	}

	static JFrame makeFrame() {
		final JFrame f = new JFrame();
		f.setTitle(progname);
		f.setFocusable(true);
		f.setSize(FRAME_W, FRAME_H);
		f.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		f.setBackground(background);
		f.getContentPane().setLayout(new BorderLayout());
		return f;
	}

	static JLabel label(String text) {
		JLabel l = new JLabel(text);
		colorize(l);
		l.setOpaque(true);
		return l;
	}

	static JButton button(String text) {
		JButton b = new JButton(text);
		colorize(b);
		b.setBackground(middleground);
		b.setContentAreaFilled(false);
		b.setOpaque(true);
		return b;
	}

	static JPanel panel() {
		JPanel p = new JPanel();
		colorize(p);
		return p;
	}

	static JTextField textbox(String text) {
		JTextField f = new JTextField(text);
		colorize(f);
		f.setBackground(textBackground);
		return f;
	}


	static void colorize(JComponent c) {
		c.setBackground(background);
		c.setForeground(foreground);
		c.setOpaque(true);
	}

	static void log(String msg) {
		Main.debug(msg);
		statusLabel.setText(msg);
	}
}
