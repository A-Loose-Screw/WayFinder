package path_builder;

import java.awt.*;
import java.util.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyListener;
import java.awt.event.KeyEvent;
import javax.swing.*;

public class SplineCalculate {
  public static Point getSplinePoint(float t, Vector<Point> points, boolean isLooped) {
    int p0, p1, p2, p3;
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

    float tt = t * t;
    float ttt = tt * t;

    // Influencers
    float q1 = -ttt + 2.0f*tt - t;
    float q2 = 3.0f*ttt - 5.0f*tt + 2.0f;
    float q3 = -3.0f*ttt + 4.0f*tt + t;
    float q4 = ttt - tt;

    float tx = 0.5f * (points.get(p0).x * q1 + points.get(p1).x * q2 + points.get(p2).x * q3 + points.get(p3).x * q4);
    float ty = 0.5f * (points.get(p0).y * q1 + points.get(p1).y * q2 + points.get(p2).y * q3 + points.get(p3).y * q4);

    return new Point((int)tx, (int)ty);
  }
}