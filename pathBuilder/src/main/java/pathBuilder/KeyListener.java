package path_builder;

import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import javax.swing.*;

public class KeyListener extends KeyAdapter {
  public void keyPressed(KeyEvent event) {
    char ch = event.getKeyChar();
    // System.out.println("Key Codes: " + event.getKeyCode());
    if (ch == 'a') {
      System.out.println("Key Codes: " + event.getKeyCode());
    }
  }
}