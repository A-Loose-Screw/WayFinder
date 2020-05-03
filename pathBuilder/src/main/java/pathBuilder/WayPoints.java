package path_builder;

import java.awt.*;
import java.util.*;


public class WayPoints {
  static int selectedPoint = 0;
  static float fMarker = 0.0f; // Esentially the robot following the path
  Vector<Point> wayPoints = new Vector<Point>();
  Point p1 = new Point(100, 300);
  Point p2 = new Point(200, 300);
  Point p3 = new Point(300, 300);
  Point p4 = new Point(400, 300);
  Point p5 = new Point(500, 300);
  Point p6 = new Point(600, 300);
  Point p7 = new Point(700, 300);

  WayPoints() {
    wayPoints.add(p1);
    wayPoints.add(p2);
    wayPoints.add(p3);
    wayPoints.add(p4);
    wayPoints.add(p5);
    wayPoints.add(p6);
    wayPoints.add(p7);
  }
}