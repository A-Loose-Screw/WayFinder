package path_builder;

import java.util.*;

import java.awt.*;
import java.awt.event.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import javax.swing.*;

public class DrawPath extends JComponent {
  Vector<Point> drawablePoints = new Vector<Point>();
  public static boolean isCircle = true;

  DrawPath(Vector points) {
    drawablePoints = points;
  }

  
  public void paintComponent(Graphics g) {
		super.paintComponent(g);
    this.setBackground(Color.WHITE);

    for (int i = 0; i < drawablePoints.size(); i++) {
      if (i == WayPoints.selectedPoint) {
        g.setColor(Color.RED);
        g.fillOval(drawablePoints.get(i).x, drawablePoints.get(i).y, 10, 10);
      } else {
        g.setColor(Color.BLUE);
        g.fillOval(drawablePoints.get(i).x, drawablePoints.get(i).y, 10, 10);
      }
    }

    if (isCircle) {
      for (float t = 0.0f; t < (float)drawablePoints.size(); t+=0.005f) {
        g.setColor(Color.BLACK);
        Point splinePoints = SplineCalculate.getSplinePoint(t, drawablePoints, isCircle);
        g.fillOval(splinePoints.x, splinePoints.y, 2, 2);
      }
    } else {
      for (float t = 0.0f; t < (float)drawablePoints.size() - 3.0f; t+=0.005f) {
        g.setColor(Color.BLACK);
        Point splinePoints = SplineCalculate.getSplinePoint(t, drawablePoints, isCircle);
        g.fillOval(splinePoints.x, splinePoints.y, 2, 2);
      }
    }
	}
}