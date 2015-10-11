package model;

/**
 * This class is a part of model and contains
 * methods for measuring game time.
 * @author Tomasz Bochenski
 */
public class Clock
{
	private final int working = 0;
	private final int waiting = 1;

	private long start;
	private long constComp;
	private int status;
	
	private long secondsInMilli;
	private long minutesInMilli;
	private long hoursInMilli;
	
	/**
	 * Default constructor.
	 */
	public Clock()
	{
		secondsInMilli = 1000;
		minutesInMilli = secondsInMilli * 60;
		hoursInMilli = minutesInMilli * 60;
	}
	
	/**
	 * Initiate clock with default values.
	 */
	public void init()
	{
		constComp = 0;
		start = System.currentTimeMillis();
		status = working;
	}
	
	/**
	 * Stops measuring game time.
	 */
	public void stopWorking()
	{
		if(status == working)
		{
			constComp = System.currentTimeMillis() - start + constComp;
			status = waiting;
		}
	}
	
	/**
	 * Starts measuring game time.
	 */
	public void startWorking()
	{
		if(status == waiting)
		{
			status = working;
			start = System.currentTimeMillis();
		}
	}
	
	/**
	 * Gets measured time.
	 * @return array with measured time, where index 0: hours,
	 * index 1: minutes, index 2: seconds.
	 */
	public long[] getTimeElapsed()
	{
		long different;
		
		if(status == waiting)
			different = constComp;
		else
			different = System.currentTimeMillis() - start + constComp;
 
		long elapsedHours = different / hoursInMilli;
		different = different % hoursInMilli;
 
		long elapsedMinutes = different / minutesInMilli;
		different = different % minutesInMilli;
 
		long elapsedSeconds = different / secondsInMilli;
		
		long[] arr = new long[3];
		arr[0] = elapsedHours;
		arr[1] = elapsedMinutes;
		arr[2] = elapsedSeconds;
		
		return arr;	
	}
}