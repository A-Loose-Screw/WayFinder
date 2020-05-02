package path_builder;

import java.awt.*;
import java.awt.event.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import javax.swing.*;

public class DrawPath extends JPanel {
  Spline path = new Spline();
  KeyListener listener = new KeyListener();
  KeyEvent event;
  int selectedPoint = 0;
  int y = 300;
  int adderValue;

  public void moveSelectedPoint(Spline _path) {
    listener.keyPressed(event);
    // if (event.getKeyChar() == KEY_LEFT) {
    //   if (selectedPoint <= 0) {
    //     selectedPoint = 0;
    //   } else {
    //     selectedPoint--;
    //   }
    // }

    // if (event.getKeyChar() == KEY_RIGHT) {
    //   if (selectedPoint >= 4) {
    //     selectedPoint = 4;
    //   } else {
    //     selectedPoint++;
    //   }
    // }

    // if (event.getKeyChar() == KEY_UP) {
    //   Point tmpPoint = path.v.get(selectedPoint);
    //   tmpPoint.y++;
    //   path.v.get(selectedPoint) = tmpPoint;
    // }
  }

  
  public void paintComponent(Graphics g) {
		super.paintComponent(g);
    this.setBackground(Color.WHITE);

		// // Draw blue rect
		// g.setColor(Color.BLUE);
		// g.fillRect(25, 25, 100, 30);


		// g.setColor(new Color(190, 81, 215));
    // g.fillRect(25, 65, 100, 30);
    // g.drawString("This is some text", 25, 120);

		// g.setColor(Color.RED);
    // g.drawLine(0, 0, 25, 30);

    // make points
    Point p1 = new Point(150, y);
    Point p2 = new Point(350, 300);
    Point p3 = new Point(550, 300);
    Point p4 = new Point(750, 300);

    // add points to spline vector
    path.v.add(p1);
    path.v.add(p2);
    path.v.add(p3);
    path.v.add(p4);

    // add points to graph
    g.setColor(Color.BLUE);
    g.fillOval(p1.x, p1.y, 10, 10);
    g.setColor(Color.RED);
    g.fillOval(p2.x, p2.y, 10, 10);
    g.fillOval(p3.x, p3.y, 10, 10);
    g.setColor(Color.BLUE);
    g.fillOval(p4.x, p4.y, 10, 10);

    y++;
	}
}