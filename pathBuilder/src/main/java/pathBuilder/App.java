package path_builder;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class App extends JPanel {

	public static void main(String[] args) {
		JFrame f = new JFrame("Title");
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		DrawTest d = new DrawTest();
		f.add(d);
		f.setSize(400, 250);
		f.setVisible(true);
	}
}
