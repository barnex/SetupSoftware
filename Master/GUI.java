import java.awt.event.*;
import java.awt.*;
import javax.swing.*;

public final class GUI{

	static ImageView viewer = new ImageView();
	static JLabel statusLabel = new JLabel();

	static final int FRAME_W = 800, FRAME_H = 600; // initial window size

	static Color background = Color.DARK_GRAY;
	static Color middleground = Color.GRAY;
	static Color foreground = Color.WHITE;

	public static void init()  {
		final JFrame f = new JFrame();
		f.setFocusable(true);
		f.setSize(FRAME_W, FRAME_H);
		f.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				f.dispose();
			}
		});

		f.setBackground(background);
		f.setForeground(foreground);

		viewer.setBackground(background);

		statusLabel.setOpaque(true);
		statusLabel.setBackground(background);
		statusLabel.setForeground(foreground);
		f.getContentPane().setBackground(background);
		f.getContentPane().setLayout(new BorderLayout());
		f.getContentPane().add(viewer, BorderLayout.CENTER);
		f.getContentPane().add(statusLabel, BorderLayout.SOUTH);

		JPanel pp = new JPanel();
		pp.setBackground(background);
		pp.add(new PiezoPanel());
		f.getContentPane().add(pp, BorderLayout.EAST);

		f.setVisible(true);
	}

	static void log(String msg){
		Main.log(msg);
		statusLabel.setText(msg);
	}
}
