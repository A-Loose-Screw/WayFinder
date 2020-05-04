package path_builder;

import java.util.*;

import java.awt.*;
import java.awt.event.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import javax.swing.*;

public class DrawPath extends JComponent {
  Point markerPoint = new Point(0,0);
  Point markerGradient = new Point(0,0); // The Marker is assumed robot's orientation at any given Point.
  public static boolean isCircle = true;
  WayPoints _wp;

  DrawPath(WayPoints wp) {
    _wp = wp;
  }

  
  public void paintComponent(Graphics g) {
		super.paintComponent(g);
    this.setBackground(Color.WHITE);

    double totalSplineLength = 0.0;

    // draw control points
    for (int i = 0; i < _wp.wayPoints.size(); i++) {
      double length = 0;
      if (isCircle) {
        length = SplineCalculate.calcSegLength(i, _wp.wayPoints, isCircle);
        totalSplineLength += length;
      }
      if (i == _wp.selectedPoint) {
        g.setColor(Color.RED);
        if (isCircle) {
          g.drawString("Seg Length: " + length, 10, 50*(i+1));
        }
        g.fillOval(_wp.wayPoints.get(i).x, _wp.wayPoints.get(i).y, 10, 10);
      } else {
        g.setColor(Color.BLUE);
        if (isCircle) {
          g.drawString("Seg Length: " + length, 10, 50*(i+1));
        }
        g.fillOval(_wp.wayPoints.get(i).x, _wp.wayPoints.get(i).y, 10, 10);
      }
    }

    // Draw in between spline points
    if (isCircle) {
      for (double t = 0.0f; t < (double)_wp.wayPoints.size(); t+=0.005f) {
        g.setColor(Color.BLACK);
        Point splinePoints = SplineCalculate.getSplinePoint(t, _wp.wayPoints, isCircle);
        g.fillOval(splinePoints.x, splinePoints.y, 2, 2);
      }
    } else {
      for (double t = 0.0f; t < (double)_wp.wayPoints.size() - 3.0f; t+=0.005f) {
        g.setColor(Color.BLACK);
        Point splinePoints = SplineCalculate.getSplinePoint(t, _wp.wayPoints, isCircle);
        g.fillOval(splinePoints.x, splinePoints.y, 2, 2);
      }
    }

    // Draw virtual robot
    g.setColor(Color.GREEN);
    markerPoint = SplineCalculate.getSplinePoint(_wp.fMarker, _wp.wayPoints, isCircle);
    markerGradient = SplineCalculate.getSplineGradient(_wp.fMarker, _wp.wayPoints, isCircle);
    double r = Math.atan2(-markerGradient.y, markerGradient.x);
    double dgr = -(Math.toDegrees(r));
    
    double mkrP1x = 15.0f * Math.sin(r) + markerPoint.x;
    double mkrP1y = 15.0f * Math.cos(r) + markerPoint.y;
    double mkrP2x = -15.0f * Math.sin(r) + markerPoint.x;
    double mkrP2y = -15.0f * Math.cos(r) + markerPoint.y;

    // thicker line 
    Graphics2D g2 = (Graphics2D) g;
    g2.setStroke(new BasicStroke(3));

    g2.drawLine((int)mkrP1x, (int)mkrP1y, (int)mkrP2x, (int)mkrP2y);		
    g.setColor(Color.BLACK);
    g.drawString("Total Path Length: " + totalSplineLength, 10, (50*_wp.wayPoints.size())+50);
    g.drawString("Robot Location in Path: (" + markerPoint.x + "," + markerPoint.y + ")", 10, (50*_wp.wayPoints.size()) + 100);
    g.drawString("Robot rotation (Radians): " + r, 10, (50*_wp.wayPoints.size())+150);
    g.drawString("Robot rotation (Degrees): " + dgr, 10, (50*_wp.wayPoints.size())+170);
	}
}