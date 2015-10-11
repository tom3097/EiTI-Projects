package view;

import model.*;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionListener;
import java.awt.event.ItemListener;
import java.awt.event.KeyListener;

import javax.swing.JFrame;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

/**
 * This class is a part of view and contains
 * general informations about variables used
 * during the game.
 * @author Tomasz Bochenski
 */
public class View
{
	private Model model;
	
	private JFrame gameFrame;
	private PaintPanel paintPanel;
	private ManagementPanel managePanel;
	
	/**
	 * Parameterized constructor.
	 * @param model game's model.
	 */
	public View(Model model)
	{	
		try
		{
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		}
		catch (ClassNotFoundException e)
		{
			e.printStackTrace();
		}
		catch (InstantiationException e)
		{
			e.printStackTrace();
		}
		catch (IllegalAccessException e)
		{
			e.printStackTrace();
		}
		catch (UnsupportedLookAndFeelException e)
		{
			e.printStackTrace();
		}
		
		this.model = model;
		gameFrame = new JFrame();
		gameFrame.setLayout(new GridBagLayout());
		gameFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		gameFrame.setTitle("Snake");
		gameFrame.setFocusable(true);
		
		paintPanel = new PaintPanel(this.model);
		
		managePanel = new ManagementPanel(this.model, gameFrame.getBackground().getRGB());
		
		GridBagConstraints constraints = new GridBagConstraints();
		constraints.insets = new Insets(10,10,10,10);
		constraints.gridy = 0;
		
		constraints.gridx = 0;
		gameFrame.getContentPane().add(paintPanel, constraints);
		
		constraints.gridx = 1;
		gameFrame.getContentPane().add(managePanel, constraints);
		
		gameFrame.pack();
		gameFrame.setResizable(false);
		gameFrame.setVisible(true);
	}
	
	/**
	 * Update text area and repaint game board.
	 */
	public void update()
	{
		managePanel.textAreaUpdate();
		gameFrame.repaint();
	}
	
	/**
	 * Adds key listener.
	 * @param keyL key listener.
	 */
	public void addKeyListener(KeyListener keyL)
	{
		paintPanel.addKeyListener(keyL);
		gameFrame.addKeyListener(keyL);
	}
	
	/**
	 * Adds combo box listener.
	 * @param it item listener.
	 */
	public void addManageComboListener(ItemListener it)
	{
		managePanel.addComboBoxListener(it);
	}
	
	/**
	 * Adds buttons listener.
	 * @param ac action listener.
	 */
	public void addManageButtonListener(ActionListener ac)
	{
		managePanel.addButtonsListener(ac);
	}
}