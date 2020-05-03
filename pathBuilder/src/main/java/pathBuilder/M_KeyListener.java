package path_builder;

import java.awt.*;
import java.util.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyListener;
import java.awt.event.KeyEvent;
import javax.swing.*;


public class M_KeyListener implements KeyListener {
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
    System.out.println("Key Pressed: " + e.getKeyChar());
    int keyCode = e.getKeyCode();
    switch( keyCode ) { 
      case KeyEvent.VK_UP:
        break;

      case KeyEvent.VK_DOWN:
        break;

      case KeyEvent.VK_LEFT:
        WayPoints.selectedPoint--;
        break;

      case KeyEvent.VK_RIGHT :
        WayPoints.selectedPoint++;
        break;
    }
	}
}
