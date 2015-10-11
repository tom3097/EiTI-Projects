package controller;

import model.*;
import view.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import javax.swing.Timer;

/**
 * This class can send commands to the model 
 * to update the model's state. It also can send 
 * commands to its view to update view.
 * @author Tomasz Bochenski
 */
public class Controller implements ActionListener, ItemListener, KeyListener
{
	private Model model;
	private View view;
	private Timer timer;
	
	/**
	 * Parameterized constructor.
	 * @param model game's model.
	 * @param view game's view.
	 */
	public Controller(Model model, View view)
	{
		this.model = model;
		model.init();
		
		this.view = view;
		
		timer = new Timer(this.model.getDelayTime(), this);
		timer.setActionCommand("Timer");
		timer.start();
		
		view.addKeyListener(this);
		view.addManageComboListener(this);
		view.addManageButtonListener(this);
	}
	
	/**
	 * Is invoked in response of timer and buttons event.
	 */
	@Override
	public void actionPerformed(ActionEvent ae)
	{
		String actionName = ae.getActionCommand();
		
		if(actionName.equals("Timer"))
		{
			if(model.getInGame() && !model.getPause())
			{
				model.update();
				view.update();
			}
		}
		else if(actionName.equals("newGameButton"))
		{
			timer.setDelay(model.getDelayTime());
			this.model.init();
		}
		else if(actionName.equals("stopStartButton"))
		{
			if(model.getPause())
				model.startGame();
			else
				model.stopGame();
		}
		else if(actionName.equals("exitButton"))
		{
			System.exit(0);
		}
	}
	
	/**
	 * Is invoked in response of combo box event.
	 */
	@Override
	public void itemStateChanged(ItemEvent ie)
	{
		if(ie.getStateChange() == ItemEvent.SELECTED)
		{
			String stringItem = ie.getItem().toString();
			
			if(stringItem.equals(new String("Speed 1")))
			{
				model.setDelayTime(Speeds.SPEED_1);
			}
			else if(stringItem.equals(new String("Speed 2")))
			{
				model.setDelayTime(Speeds.SPEED_2);
			}
			else if(stringItem.equals(new String("Speed 3")))
			{
				model.setDelayTime(Speeds.SPEED_3);
			}
			else if(stringItem.equals(new String("Speed 4")))
			{
				model.setDelayTime(Speeds.SPEED_4);
			}
			else if(stringItem.equals(new String("Speed 5")))
			{
				model.setDelayTime(Speeds.SPEED_5);
			}
		}
	}
	
	/**
	 * Is invoked in response of key event.
	 */
	@Override
	public void keyPressed(KeyEvent ke)
	{
		switch(ke.getKeyCode())
		{
		case KeyEvent.VK_UP:
			if(!model.isEqualsExecutedDirection(Directions.SOUTH))
				model.setDirection(Directions.NORTH);
			break;
		case KeyEvent.VK_LEFT:
			if(!model.isEqualsExecutedDirection(Directions.EAST))
				model.setDirection(Directions.WEST);
			break;
		case KeyEvent.VK_RIGHT:
			if(!model.isEqualsExecutedDirection(Directions.WEST))
				model.setDirection(Directions.EAST);
			break;
		case KeyEvent.VK_DOWN:
			if(!model.isEqualsExecutedDirection(Directions.NORTH))
				model.setDirection(Directions.SOUTH);
			break;
		}		
	}
	
	@Override
	public void keyReleased(KeyEvent ke) {}

	@Override
	public void keyTyped(KeyEvent ke) {}
}
