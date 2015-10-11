package model;

import java.awt.Point;
import java.util.LinkedList;
import java.util.Random;

/**
 * This class is a part of model and contains
 * general informations about variables used
 * during the game.
 * @author Tomasz Bochenski
 */
public class Model
{
	private LinkedList<Point> snake;
	private Point fruit;
	private Random generator;
	private Clock clock;
	
	private int delayTime;
	private int currDirection;
	private int lastDirection;
	private int lastExecutedDirection;
	private int score;
	
	private boolean inGame;
	private boolean pause;
	
	/**
	 * Default constructor
	 */
	public Model()
	{
		generator = new Random();
		clock = new Clock();
		snake = new LinkedList<Point>();
		
		delayTime = Speeds.SPEED_3;
	}
	
	/**
	 * Initiate model with default values.
	 */
	public void init()
	{
		clock.init();
		
		snake.clear();
		snake.push(new Point(5,3));
		snake.push(new Point(5,4));
		snake.push(new Point(5,5));
		
		this.locateFruit();
		
		currDirection = Directions.NO_DIRECTION;
		lastDirection = Directions.NO_DIRECTION;
		lastExecutedDirection = Directions.SOUTH;
		
		score = 0;
		
		inGame = true;	
		pause = false;
	}
	
	/**
	 * Update location of snake and fruit.
	 * Checks if player lost and whether the 
	 * score should be increased.
	 */
	public void update()
	{
		Point head = snake.peekFirst();
		Point newPoint = new Point();
		
		switch(currDirection)
		{
			case Directions.NORTH:
				newPoint = new Point(head.x, head.y-1); break;
			case Directions.SOUTH:
				newPoint = new Point(head.x, head.y+1); break;
			case Directions.WEST:
				newPoint = new Point(head.x-1, head.y); break;
			case Directions.EAST:
				newPoint = new Point(head.x+1, head.y); break;
			default: return;
		}
		
		this.lastExecutedDirection = currDirection;
		
		Point tail = snake.peekLast();
		snake.remove(tail);

		if(this.checkWallCollision(newPoint))
		{
			inGame = false;
			snake.addLast(tail);
			clock.stopWorking();
			return;
		}
		if(this.checkBodyCollision(newPoint))
		{
			inGame = false;
			snake.addLast(tail);
			clock.stopWorking();
			return;
		}
		if(this.checkFruitCollision(newPoint))
		{
			score += 10;
			snake.addLast(tail);
			snake.push(newPoint);
			this.locateFruit();
			return;
		}
	
		snake.push(newPoint);
	}
	
	/**
	 * Checks whether it was collision with the wall.
	 * @param point coordinates of the newly calculated 
	 * snake's head.
	 * @return true if there was a collision with the wall, false otherwise.
	 */
	private boolean checkWallCollision(Point point)
	{
		if(point.x < 0 || point.x >= Dimensions.GRID_WIDTH)
		{
			return true;
		}
		else if(point.y < 0 || point.y >= Dimensions.GRID_HEIGHT)
		{
			return true;
		}
		return false;
	}
	
	/**
	 * Checks whether it was a collision with the snake's body.
	 * @param point coordinates of the newly calculated 
	 * snake's head.
	 * @return true if there was a collision with the snake's body, false otherwise.
	 */
	private boolean checkBodyCollision(Point point)
	{
		if(snake.contains(point))
		{
			return true;
		}
		return false;
	}
	
	/**
	 * Checks whether it was a collision with the fruit.
	 * @param point coordinates of the newly calculated 
	 * snake's head.
	 * @return true if there was a collision with the fruit, false otherwise.
	 */
	private boolean checkFruitCollision(Point point)
	{
		if(point.equals(fruit))
		{
			return true;
		}
		return false;
	}
	
	/**
	 * Update the fruit location, calculate new
	 * coordinates for the fruit.
	 */
	private void locateFruit()
	{
		Point p = new Point();
		do
		{
			p.x = generator.nextInt(Dimensions.GRID_WIDTH);
			p.y = generator.nextInt(Dimensions.GRID_HEIGHT);
		}
		while(snake.contains(p));
		fruit = p;
	}
	
	/**
	 * Pauses the game.
	 */
	public void stopGame()
	{
		pause = true;
		lastDirection = currDirection;
		currDirection = Directions.NO_DIRECTION;
		clock.stopWorking();
	}
	
	/**
	 * Continue the game.
	 */
	public void startGame()
	{
		pause = false;
		currDirection = lastDirection;
		lastDirection = Directions.NO_DIRECTION;
		clock.startWorking();
	}
	
	/**
	 * Gets the delay time.
	 * @return the delay time.
	 */
	public int getDelayTime()
	{
		return delayTime;
	}
	
	/**
	 * Sets new delay time.
	 * @param delayTime new delay time.
	 */
	public void setDelayTime(int delayTime)
	{
		this.delayTime = delayTime;
	}
	
	/**
	 * Sets new snake's direction.
	 * @param direction new snake's direction.
	 */
	public void setDirection(int direction)
	{
		this.currDirection = direction;
	}
	
	/**
	 * Checks whether the given direction is equals
	 * to the sanke's last executed direction.
	 * @param direction given direction.
	 * @return true if directions are equal, false otherwise.
	 */
	public boolean isEqualsExecutedDirection(int direction)
	{
		if(direction == this.lastExecutedDirection)
			return true;
		return false;
	}
	
	/**
	 * Gets snake location.
	 * @return snake location.
	 */
	public LinkedList<Point> getSnake()
	{
		return snake;
	}

	/**
	 * Gets fruit location.
	 * @return fruit location.
	 */
	public Point getFruit()
	{
		return fruit;
	}
	
	/**
	 * Gets game status, checks whether game is finished.
	 * @return true if snake is alive, false otherwise.
	 */
	public boolean getInGame()
	{
		return inGame;
	}
	
	/**
	 * Gets the score.
	 * @return the score.
	 */
	public int getScore()
	{
		return score;
	}
	
	/**
	 * Gets game status, checks whether game is paused.
	 * @return true if game is paused, false otherwise.
	 */
	public boolean getPause()
	{
		return pause;
	}
	
	/**
	 * Gets game time.
	 * @return array with game time, where index 0: hours,
	 * index 1: minutes, index 2: seconds.
	 */
	public long[] getGameTimeElapsed()
	{
		return clock.getTimeElapsed();
	}
}
