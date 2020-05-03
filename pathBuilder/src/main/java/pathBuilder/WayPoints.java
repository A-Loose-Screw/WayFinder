package path_builder;

import java.awt.*;
import java.util.*;


public class WayPoints {
  static int selectedPoint = 0;
  Vector<Point> wayPoints = new Vector<Point>();
  Point p1 = new Point(150, 300);
  Point p2 = new Point(350, 300);
  Point p3 = new Point(550, 300);
  Point p4 = new Point(750, 300);

  WayPoints() {
    wayPoints.add(p1);
    wayPoints.add(p2);
    wayPoints.add(p3);
    wayPoints.add(p4);
  }
}