package path_builder;

import java.awt.*;
import java.util.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyListener;
import java.awt.event.KeyEvent;
import javax.swing.*;


public class App extends JFrame {
	static JFrame f = new JFrame();

	public static void createWindow() {
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.setSize(900,600);
		f.setVisible(true);
	}
	
	public static void main(String[] args) {
		createWindow();
		WayPoints _wayPoints = new WayPoints();
		DrawPath d = new DrawPath(_wayPoints.wayPoints);
		f.add(d);
		f.addKeyListener(new M_KeyListener(_wayPoints, f));
		// while(true) {
		// 	f.repaint();
		// }
	}
}
