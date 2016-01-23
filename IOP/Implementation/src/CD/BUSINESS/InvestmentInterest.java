/**
 * 
 */
package CD.BUSINESS;


public class InvestmentInterest extends Cost {
	public InvestmentInterest(int _costValue, String _date, String _forename, String _surname, String _pesel, double _interest, 
			String _type) {
		super(_costValue, _date);
		this.forename = _forename;
		this.surname = _surname;
		this.pesel = _pesel;
		this.interest = _interest;
		this.type = _type;
	}


	private String forename;
	private String surname;
	private String pesel;
	private double interest;
	private String type;

	public String getForename() {
		return this.forename;
	}

	
	public String getSurname() {
		return this.surname;
	}


	public String getPesel() {
		return this.pesel;
	}


	public double getInterest() {
		return this.interest;
	}
	
	
	public String getType()
	{
		return this.type;
	}	
}