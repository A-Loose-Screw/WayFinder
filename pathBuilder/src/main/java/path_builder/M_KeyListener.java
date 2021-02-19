package path_builder;

import java.awt.*;
import java.util.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyListener;
import java.awt.event.KeyEvent;
import javax.swing.*;


public class M_KeyListener implements KeyListener {
  WayPoints _wp;
  JFrame _f;
  Point p;
  M_KeyListener(WayPoints wp, JFrame f) {
    _wp = wp;
    _f = f;
  }


	@Override
	public void keyReleased(KeyEvent e) {
    System.out.println("Key Released: " + e.getKeyChar());
  }
	
	@Override
  public void keyTyped(KeyEvent e) {
    System.out.println("Key Typed: " + e.getKeyChar());
  }

	@Override
  public void keyPressed(KeyEvent e) {
    p = _wp.wayPoints.get(_wp.selectedPoint);
    System.out.println("Key Pressed: " + e.getKeyChar());
    int keyCode = e.getKeyCode();

    // C key 
    if (keyCode == KeyEvent.VK_C) {
      if (DrawPath.isCircle) {
        DrawPath.isCircle = false;
      } else {
        DrawPath.isCircle = true;
      }
      _f.repaint();
    }

    // Left key
    if (keyCode == KeyEvent.VK_LEFT) {
      p.x -= 3;
      _wp.wayPoints.set(_wp.selectedPoint, p);
      _f.repaint();
    }

    // Right key
    if (keyCode == KeyEvent.VK_RIGHT) {
      p.x += 3;
      _wp.wayPoints.set(_wp.selectedPoint, p);
      _f.repaint();
    }

    // Up key
    if (keyCode == KeyEvent.VK_UP) {
      p.y -= 3;
      _wp.wayPoints.set(_wp.selectedPoint, p);
      _f.repaint();
    }

    // Down key
    if (keyCode == KeyEvent.VK_DOWN) {
      p.y += 3;
      _wp.wayPoints.set(_wp.selectedPoint, p);
      _f.repaint();
    }

    // Z key
    if (keyCode == KeyEvent.VK_Z) {
      if (_wp.selectedPoint > 0) {
        _wp.selectedPoint--;
      }
      _f.repaint();
    }

    // X key
    if (keyCode == KeyEvent.VK_X) {
      if (_wp.selectedPoint < (_wp.wayPoints.size()-1)) {
        _wp.selectedPoint++;
      }
      _f.repaint();
    }

    // A key
    if (keyCode == KeyEvent.VK_A) {
      if (_wp.fMarker > 0) {
        _wp.fMarker -= 0.01;
      }
      _f.repaint();
    }

    // S key
    if (keyCode == KeyEvent.VK_S) {
      if (_wp.fMarker < (_wp.wayPoints.size()-3)) {
        _wp.fMarker += 0.01;
      }
      _f.repaint();
    }

    // V key
    if (keyCode == KeyEvent.VK_V) {
      _wp.addWayPoint();
      _f.repaint();
    }

    // f key
    if (keyCode == KeyEvent.VK_F) {
      if (_wp.wayPoints.size() > 4) {
      _wp.removeWayPoint();
      _f.repaint();
      }
    }

    System.out.println("Selected Point: " + _wp.selectedPoint);
    System.out.println("Size of waypoints: " + _wp.wayPoints.size());
    System.out.println("fMarker: " + _wp.fMarker);
	}
}
