/**
 * 
 */
package CD.BUSINESS;

import java.util.ArrayList;
import java.util.Set;


public class Application {

	private Set<User> user;

	private Set<Income> income;

	private Set<Cost> cost;

	private Set<Ratio> ratio;

	private Set<KNFReport> kNFReport;

	private Set<FinancialResult> financialResult;
	
	private ArrayList<BondInterest> bondInterests;
	private ArrayList<InvestmentInterest> investmentInterests;
	
	public Application()
	{
		bondInterests = new ArrayList<BondInterest>();
		investmentInterests = new ArrayList<InvestmentInterest>();
		
		BondInterest bond;
		bond = new BondInterest(100, "23-12-2015", 0.07, 140, "Adam", "Maly", "87678511324", "-", "-");
		this.bondInterests.add(bond);
		bond = new BondInterest(100, "31-12-2015", 0.12, 100, "Janek", "Smieszny", "65786512345", "-", "-");
		this.bondInterests.add(bond);
		bond = new BondInterest(100, "31-12-2015", 0.12, 1000, "-", "-", "-", "Nokia", "6768954");
		this.bondInterests.add(bond);
		
		
		InvestmentInterest investment;
		investment = new InvestmentInterest(20, "20-03-2016", "Jacek", "Placek", "96784522345", 0.02, "Lokata Sloneczna");
		this.investmentInterests.add(investment);
	}
	
	
	public void getCosts() {
		// begin-user-code
		// TODO Auto-generated method stub

		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void getIncomes() {
		// begin-user-code
		// TODO Auto-generated method stub

		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void addNewRatio() {
		// begin-user-code
		// TODO Auto-generated method stub

		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void getRecentQuickRatio() {
		// begin-user-code
		// TODO Auto-generated method stub

		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void getRecentCurrentRatio() {
		// begin-user-code
		// TODO Auto-generated method stub

		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void getCurrentLiabilitiesRatio() {
		// begin-user-code
		// TODO Auto-generated method stub

		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ArrayList<BondInterest> getBondInterests() {
		return this.bondInterests;
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ArrayList<InvestmentInterest> getInvestmentInterests() {
		return this.investmentInterests;
	}
}