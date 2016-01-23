/**
 * 
 */
package CD.BUSINESS;

/** 
 * <!-- begin-UML-doc -->
 * <p>[Opis]<br>Jest to interfejs dostarczajacy metody od banku. Dzieki tym metodom mozemy sie dowiedziec jaka jest aktualna wartosc rezerwy obowiazkowej przechowywanej w banku oraz ile wynosi aktualna stopa rezerwy obowiazkowej.</p>
 * <!-- end-UML-doc -->
 * @author Tomasz
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public interface CentralBank {
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void getReserveValue();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void getReserveRate();
}