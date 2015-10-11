package view;

import model.*;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.image.BufferedImage;

import javax.swing.BorderFactory;
import javax.swing.JPanel;

/**
 * This class is a part of view and contains
 * informations about the game board.
 * @author Tomasz Bochenski
 */
public class PaintPanel extends JPanel
{
	private static final long serialVersionUID = -6315591630247104097L;
	private Model model;
	private BufferedImage buffer;

	/**
	 * Parameterized constructor.
	 * @param model game's model.
	 */
	public PaintPanel(Model model)
	{
		this.model = model;
		this.setFocusable(true);
        this.requestFocusInWindow();       
		this.setPreferredSize(new Dimension(Dimensions.BOX_WIDTH*Dimensions.GRID_WIDTH+1,Dimensions.BOX_HEIGHT*Dimensions.GRID_HEIGHT+1));
        this.setBorder(BorderFactory.createLineBorder(Color.ORANGE));
		
        buffer = new BufferedImage(Dimensions.BOX_WIDTH*Dimensions.GRID_WIDTH+1,Dimensions.BOX_HEIGHT*Dimensions.GRID_HEIGHT+1,BufferedImage.TYPE_4BYTE_ABGR);
	}
	
	/**
	 * Draws grid on the board.
	 * @param g graphics.
	 */
	public void DrawGrid(Graphics g)
	{
		g.setColor(Color.BLACK);
		
		g.drawRect(0, 0, Dimensions.GRID_WIDTH * Dimensions.BOX_WIDTH, Dimensions.GRID_HEIGHT * Dimensions.BOX_HEIGHT);
		
		for(int x = Dimensions.BOX_WIDTH; x < Dimensions.GRID_WIDTH * Dimensions.BOX_WIDTH; x += Dimensions.BOX_WIDTH)
		{
			g.drawLine(x, 0, x, Dimensions.BOX_HEIGHT * Dimensions.GRID_HEIGHT);
		}
		for(int y = Dimensions.BOX_HEIGHT; y < Dimensions.GRID_HEIGHT * Dimensions.BOX_HEIGHT; y += Dimensions.BOX_HEIGHT)
		{
			g.drawLine(0, y, Dimensions.BOX_WIDTH * Dimensions.GRID_WIDTH, y);
		}	
	}
	
	/**
	 * Draws snake on the board.
	 * @param g graphics.
	 */
	public void DrawSnake(Graphics g)
	{
		g.setColor(new Color(51,255,51));

		for(Point p: model.getSnake())
		{
			g.fillOval(p.x * Dimensions.BOX_WIDTH, p.y * Dimensions.BOX_HEIGHT, Dimensions.BOX_WIDTH, Dimensions.BOX_HEIGHT);
		}
		
		g.setColor(new Color(255,51,51));
		g.fillOval(model.getSnake().peekFirst().x * Dimensions.BOX_WIDTH, model.getSnake().peekFirst().y * Dimensions.BOX_HEIGHT, Dimensions.BOX_WIDTH, Dimensions.BOX_HEIGHT);
		g.setColor(Color.BLACK);
	}

	/**
	 * Draws fruit on the board.
	 * @param g graphics.
	 */
	public void DrawFruit(Graphics g)
	{
		g.setColor(Color.CYAN);
		
		g.fillOval(model.getFruit().x * Dimensions.BOX_WIDTH, model.getFruit().y * Dimensions.BOX_HEIGHT, Dimensions.BOX_WIDTH, Dimensions.BOX_HEIGHT);
	}
	
	/**
	 * Paint the panel.
	 */
	public void paintComponent(Graphics g)
	{
		Graphics screengc = null;
		screengc = g;
		
		g = buffer.getGraphics();
		
		super.paintComponent(g);
		
		DrawGrid(g);
		DrawSnake(g);
		DrawFruit(g);
		
		screengc.drawImage(buffer, 0, 0, null);
	}
}
