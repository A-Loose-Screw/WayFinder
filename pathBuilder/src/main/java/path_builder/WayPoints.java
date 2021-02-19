package path_builder;

import java.awt.*;
import java.util.*;


public class WayPoints {
  int numOfWayPoints = 4;
  int selectedPoint = 0;
  double fMarker = 0.0; // Esentially the robot following the path
  Vector<Point> wayPoints = new Vector<Point>();
  // Point p1 = new Point(100, 300);
  // Point p2 = new Point(200, 300);
  // Point p3 = new Point(300, 300);
  // Point p4 = new Point(400, 300);
  // Point p5 = new Point(500, 300);
  // Point p6 = new Point(600, 300);
  // Point p7 = new Point(700, 300);

  WayPoints() {
    for (int i = 0; i < numOfWayPoints; i++) {
      int x = (App.WIDTH/4) + i*100;
      int y = App.HEIGHT/2;
      wayPoints.add(new Point(x, y));
    }
    // wayPoints.add(p1);
    // wayPoints.add(p2);
    // wayPoints.add(p3);
    // wayPoints.add(p4);
    // wayPoints.add(p5);
    // wayPoints.add(p6);
    // wayPoints.add(p7);
  }

  public void addWayPoint() {
    int x = wayPoints.lastElement().x + 50;
    int y = wayPoints.lastElement().y;
    wayPoints.add(new Point(x, y));
  }

  public void removeWayPoint() {
    wayPoints.remove(wayPoints.size()-1);
  }
}