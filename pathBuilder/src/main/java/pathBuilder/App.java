package path_builder;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;


public class App extends JPanel {

	public static void main(String[] args) {
		JFrame f = new JFrame("Title");
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		DrawPath d = new DrawPath();

		f.add(d);
		f.setSize(900, 600);
		f.setVisible(true);
		while (true) {
			d.repaint();
		}
	}
}
