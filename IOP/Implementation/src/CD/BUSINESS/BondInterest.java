/**
 * 
 */
package CD.BUSINESS;


public class BondInterest extends Cost {

	private double interest;
	private int durationDays;
	private String forename;
	private String surname;
	private String pesel;
	private String firmName;
	private String NIP;
	
	
	public BondInterest(int _costValue, String _date, double _interest, int _durationDays, String _forename, String _surname, String _pesel, 
			String _firmName, String _NIP) {
		super(_costValue, _date);
		this.interest = _interest;
		this.durationDays = _durationDays;
		this.forename = _forename;
		this.surname = _surname;
		this.pesel = _pesel;
		this.firmName = _firmName;
		this.NIP = _NIP;
	}


	public double getInterest() {
		return this.interest;
	}


	public int getDurationDays() {
		return this.durationDays;
	}


	public String getSurname() {
		return this.surname;
	}


	public String getForename() {
		return this.forename;
	}


	public String getPesel() {
		return this.pesel;
	}


	public String getFirmName() {
		return this.firmName;
	}


	public String getNIP() {
		return this.NIP;
	}
}