import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public final class ImageView extends JPanel implements MouseListener, MouseMotionListener{

	int chan = 0;
	ColorMap colormap = new ColorMap(0, 0, Color.BLACK, Color.GRAY, Color.WHITE);
	float[][][] image = new float[1][1][1];
	double x0, y0, dx, dy; // center position and pixel stride, in µm, to display cursor position
	double mouseX, mouseY; // last mouse position, in µm
	JLabel coords;

	public ImageView(){
		GUI.colorize(this);
		setPreferredSize(new Dimension(512, 512));
		addMouseListener(this);
		addMouseMotionListener(this);
		setCursor (Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR));
	}

	public void mouseEntered(MouseEvent e){}
	public void mouseExited(MouseEvent e){}
	public void mousePressed(MouseEvent e){}
	public void mouseReleased(MouseEvent e){}
	public void mouseClicked(MouseEvent e){
 		if (e.getClickCount() == 2) {
 			GUI.piezo.posbox[GUI.piezo.scanI].setText(fmt(mouseX));
 			GUI.piezo.posbox[GUI.piezo.scanJ].setText(fmt(mouseY));
  		}
	}
	public void mouseDragged(MouseEvent e){}
	public void mouseMoved(MouseEvent e){
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

		if (coords != null){
			coords.setText(fmt(mouseX) + ", " + fmt(mouseY) + " µm");
 
		}
		
	}

	static String fmt(double x){
		return String.format("%.2f", x);
	}

	public void display(float[][][] image){
		this.image = image;

		float[][] img = image[chan];

		float min = img[0][0];
		float max = img[0][0];

		for(int i=0; i<img.length; i++){
			for(int j=0; j<img[i].length; j++){
				float v = img[i][j];
				if(v<min){min=v;}
				if(v>max){max=v;}
			}
		}

		colormap.setValues(min, max);

		repaint();

	}

	public void paintComponent(Graphics g_) {

		Graphics2D g = (Graphics2D)(g_);
		int W = getWidth();
		int H = getHeight();

		// clear background
		g.setColor(Color.WHITE);
		g.fillRect(0, 0, W, H);

		
		float[][] img = image[chan];
		int nI = img.length;
		int nJ = img[0].length;
		int sx = W / nJ + 1;
		int sy = H / nI + 1;

		for(int i=0; i<nI; i++){
			for(int j=0; j<nJ; j++){
				int x = (W*j)/nJ;
				int y = H-(H*i)/nI-sy;

				double v = (double)(img[i][j]);
				if(Double.isNaN(v)){continue;}
				Color c = colormap.get(v);
				g.setColor(c);
				g.fillRect(x, y, sx, sy);
			}
		}
	}

	private static final long serialVersionUID = 1; // sigh...
}
