/**
 * 
 */
package CD.BUSINESS;


public class Cost {

	private int costValue;
	private String date;
	
	public Cost(int _costValue, String _date)
	{
		this.costValue = _costValue;
		this.date = _date;
	}

	public int getCostValue() {
		return this.costValue;
	}

	
	public void setCostValue(int newVal) {
		this.costValue = newVal;
	}

	
	public void setDate(String newVal) {
		this.date = newVal;
	}

	
	public String getDate() {
		return this.date;
	}
}