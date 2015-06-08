import java.awt.*;
import javax.swing.*;

public final class ImageView extends JPanel{

	int chan = 0;
	ColorMap colormap = new ColorMap(0, 0, Color.BLACK, Color.GRAY, Color.WHITE);
	float[][][] image = new float[1][1][1];

	public ImageView(){
		GUI.colorize(this);
		setPreferredSize(new Dimension(512, 512));
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
