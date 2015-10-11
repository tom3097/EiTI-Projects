package view;

import model.*;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionListener;
import java.awt.event.ItemListener;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JPanel;
import javax.swing.JTextArea;

/**
 * This class is a part of view and contains
 * informations about text areas, combo box and buttons.
 * @author Tomasz Bochenski
 */
public class ManagementPanel extends JPanel
{
	private static final long serialVersionUID = 4268663215722593889L;
	private Model model;
	
	private JTextArea scoreArea;
	private JTextArea timeArea;
		
	private JComboBox<String> speedBox;
	
	private JButton newGameButton;
	private JButton stopStartButton;
	private JButton exitButton;
		
	/**
	 * Parameterized constructor.
	 * @param model game's model.
	 * @param BackgroundRGB background RGB color model.
	 */
	public ManagementPanel(Model model, int BackgroundRGB)
	{
		this.model = model;
		
		Font font = new Font("Serif", Font.BOLD, 22);
		
		timeArea = new JTextArea();
		timeArea.setEditable(false);
		timeArea.setFocusable(false);
		timeArea.setFont(font);
		timeArea.setBackground(new Color(BackgroundRGB));
			
		scoreArea = new JTextArea();
		scoreArea.setFocusable(false);
		scoreArea.setEditable(false);
		scoreArea.setFont(font);
		scoreArea.setBackground(new Color(BackgroundRGB));
		
		newGameButton = new JButton("New Game");
		newGameButton.setFocusable(false);
		newGameButton.setPreferredSize(new Dimension(200,50));
		newGameButton.setActionCommand("newGameButton");
		
		stopStartButton = new JButton("Stop/Start");
		stopStartButton.setFocusable(false);
		stopStartButton.setPreferredSize(new Dimension(200,50));
		stopStartButton.setActionCommand("stopStartButton");
		
		exitButton = new JButton("Exit");
		exitButton.setFocusable(false);
		exitButton.setPreferredSize(new Dimension(200,50));
		exitButton.setActionCommand("exitButton");
		
		String[] speeds = { "Speed 1", "Speed 2", "Speed 3", "Speed 4", "Speed 5" };
		speedBox = new JComboBox<String>(speeds);
		speedBox.setFocusable(false);
		speedBox.setSelectedIndex(2);
		
		this.setLayout(new GridBagLayout());
		this.requestFocusInWindow();
		GridBagConstraints constraints = new GridBagConstraints();
		constraints.insets = new Insets(10,10,10,10);
		constraints.gridx = 0;
		
		
		constraints.gridy = 0;
		this.add(scoreArea, constraints);
			
		constraints.gridy = 1;
		this.add(newGameButton, constraints);
		
		constraints.gridy = 2;
		this.add(speedBox, constraints);
		
		constraints.gridy = 3;
		this.add(stopStartButton, constraints);
		
		constraints.gridy = 4;
		this.add(exitButton, constraints);
		
		constraints.gridy = 5;
		this.add(timeArea, constraints);
			
		this.setVisible(true);
	}
	
	/**
	 * Adds buttons listener.
	 * @param ac action listener.
	 */
	public void addButtonsListener(ActionListener ac)
	{
		newGameButton.addActionListener(ac);
		stopStartButton.addActionListener(ac);
		exitButton.addActionListener(ac);
	}
	
	/**
	 * Adds combo box listener.
	 * @param it item listener.
	 */
	public void addComboBoxListener(ItemListener it)
	{
		speedBox.addItemListener(it);
	}
	
	/**
	 * Update text in text area. Update
	 * score and time.
	 */
	public void textAreaUpdate()
	{
		long[] arr = model.getGameTimeElapsed();
			
		String time;
			
		time = arr[0] + " : " + arr[1]+ " : " + arr[2];
		timeArea.setText(time);
			
		scoreArea.setText("Score: " + model.getScore());
	}
}
