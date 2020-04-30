package path_builder;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;


public class DrawTest extends JPanel {

  
  public void paintComponent(Graphics g) {
		super.paintComponent(g);
    this.setBackground(Color.WHITE);
    
    

		// // Draw blue rect
		// g.setColor(Color.BLUE);
		// g.fillRect(25, 25, 100, 30);


		// g.setColor(new Color(190, 81, 215));
    // g.fillRect(25, 65, 100, 30);
    // g.drawString("This is some text", 25, 120);

    g.setColor(Color.BLUE);
    g.fillOval(25, 25, 10, 10);
    // g.drawOval(25, 25, 25, 25);

		// g.setColor(Color.RED);
    // g.drawLine(0, 0, 25, 30);
	}
}