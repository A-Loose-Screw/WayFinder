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
    p = _wp.wayPoints.get(WayPoints.selectedPoint);
    System.out.println("Key Pressed: " + e.getKeyChar());
    int keyCode = e.getKeyCode();
    switch(keyCode) { 
      case KeyEvent.VK_UP:
        p.y--;
        _wp.wayPoints.set(WayPoints.selectedPoint, p);
        _f.repaint();
        break;

      case KeyEvent.VK_DOWN:
        p.y++;
        _wp.wayPoints.set(WayPoints.selectedPoint, p);
        _f.repaint();
        break;

      case KeyEvent.VK_LEFT:
        WayPoints.selectedPoint--;
        _f.repaint();
        break;

      case KeyEvent.VK_RIGHT:
        WayPoints.selectedPoint++;
        _f.repaint();
        break;
    }
	}
}
