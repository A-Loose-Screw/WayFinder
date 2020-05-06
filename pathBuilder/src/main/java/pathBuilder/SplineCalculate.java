package path_builder;

import java.awt.*;
import java.util.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyListener;
import java.awt.event.KeyEvent;
import javax.swing.*;

public class SplineCalculate {

  public static Point getSplineGradient(double t, Vector<Point> points, boolean isLooped) {
    int p0, p1, p2, p3;

    // Calculate where each points between the waypoints should be (Should provide curve)
    if (!isLooped) {
      p1 = (int)t+1;
      p2 = p1 + 1;
      p3 = p2 + 1;
      p0 = p1 - 1;
    } else {
      p1 = (int)t;
      p2 = (p1 + 1) % points.size();
      p3 = (p2 + 1) % points.size();
      if (p1 >= 1) {
        p0 = p1 - 1;
      } else {
        p0 = points.size() - 1;
      }
    }

    t = t - (int)t;

    double tt = t * t;
    double ttt = tt * t;

    // Influencers
    double q1 = -3.0f*tt + 4.0f*t - 1;
    double q2 = 9.0f*tt - 10.0f*t;
    double q3 = -9.0f*tt + 8.0f*t + 1.0f;
    double q4 = 3.0f*tt - 2.0f*t;

    double tx = 0.5f * (points.get(p0).x * q1 + points.get(p1).x * q2 + points.get(p2).x * q3 + points.get(p3).x * q4);
    double ty = 0.5f * (points.get(p0).y * q1 + points.get(p1).y * q2 + points.get(p2).y * q3 + points.get(p3).y * q4);

    return new Point((int)tx, (int)ty);
  }

  public static Point getSplinePoint(double t, Vector<Point> points, boolean isLooped) {
    int p0, p1, p2, p3;

    // Calculate where each points between the waypoints should be (Should provide curve)
    if (!isLooped) {
      p1 = (int)t+1;
      p2 = p1 + 1;
      p3 = p2 + 1;
      p0 = p1 - 1;
    } else {
      p1 = (int)t;
      p2 = (p1 + 1) % points.size();
      p3 = (p2 + 1) % points.size();
      if (p1 >= 1) {
        p0 = p1 - 1;
      } else {
        p0 = points.size() - 1;
      }
    }

    t = t - (int)t;

    double tt = t * t;
    double ttt = tt * t;

    double q1 = -ttt + 2.0f*tt - t;
    double q2 = 3.0f*ttt - 5.0f*tt + 2.0f;
    double q3 = -3.0f*ttt + 4.0f*tt + t;
    double q4 = ttt - tt;

    double tx = 0.5f * (points.get(p0).x * q1 + points.get(p1).x * q2 + points.get(p2).x * q3 + points.get(p3).x * q4);
    double ty = 0.5f * (points.get(p0).y * q1 + points.get(p1).y * q2 + points.get(p2).y * q3 + points.get(p3).y * q4);

    return new Point((int)tx, (int)ty);
  }

  public static double calcSegLength(int node, Vector<Point> points, boolean isLooped) {
    double fLength = 0.0;
    double fStepSize = 0.005;

    Point old_point, new_point;
    old_point = getSplinePoint((double)node, points, isLooped);

    for (double t = 0; t < 1.0; t += fStepSize) {
      new_point = getSplinePoint((double)node + t, points, isLooped);
      double xrt = (new_point.x - old_point.x)*(new_point.x - old_point.x);
      double yrt = (new_point.y - old_point.y)*(new_point.y - old_point.y);
      fLength += Math.sqrt((xrt+yrt));

      old_point = new_point;
    }

    return fLength;
  }
}