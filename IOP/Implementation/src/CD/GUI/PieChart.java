/**
 * 
 */
package CD.GUI;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.util.ArrayList;

import javax.swing.JComponent;
import javax.swing.JFrame;

import CD.BUSINESS.BondInterest;
import CD.BUSINESS.InvestmentInterest;

class Slice {
   double value;
   Color color;
   public Slice(double value, Color color) {  
      this.value = value;
      this.color = color;
   }
}

/** 
 * <!-- begin-UML-doc -->
 * <p>[Opis]<br>Klasa reprezentujaca wykres kolowy. Za jego pomoca sa obrazowane rozne dane.</p>
 * <!-- end-UML-doc -->
 * @author Tomasz
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class PieChart extends JComponent{
	
	private ArrayList<Slice> slices = new ArrayList<Slice>();
	


	private ArrayList<BondInterest> bondInterests;

	private ArrayList<InvestmentInterest> investmentInterests;

	public PieChart() {
		// begin-user-code
		// TODO Auto-generated constructor stub
		// end-user-code
		this.slices = new ArrayList<Slice> ();
		this.bondInterests = new ArrayList<BondInterest> ();
		this.investmentInterests = new ArrayList<InvestmentInterest> ();
		
		slices.add(new Slice(4, Color.BLACK));
		slices.add( new Slice(6, Color.RED) );
		
	}
	
	public void paint(Graphics g) {
		drawPie((Graphics2D) g, getBounds(), slices);
	}
	
	
	void drawPie(Graphics2D g, Rectangle area, ArrayList<Slice> slices) {
		double total = 0.0D;
		for (int i = 0; i < slices.size(); i++) {
			total += slices.get(i).value;
		}
		double curValue = 0.0D;
		int startAngle = 0;
		for (int i = 0; i < slices.size(); i++) {
			startAngle = (int) (curValue * 360 / total);
			int arcAngle = (int) (slices.get(i).value * 360 / total);
			g.setColor(slices.get(i).color);
			g.fillArc(area.x, area.y, area.width, area.height, startAngle, arcAngle);
			curValue += slices.get(i).value;
		}
	}
	
	   
	   
	   public static void main(String[] argv) {
		  JFrame frame = new JFrame();
		      frame.getContentPane().add(new PieChart());
		      frame.setVisible(true);
		      
		   }
	
	

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setBondInterests(ArrayList<BondInterest> bonds) {
		this.bondInterests = bonds;
	}


	public void setInvestmentInterests(ArrayList<InvestmentInterest> investm) {
		this.investmentInterests = investm;
	}


	public void drawInterests() {
		int sumBonds = 0;
		for(int idx = 0; idx < this.bondInterests.size(); ++idx)
		{
			sumBonds = sumBonds + this.bondInterests.get(idx).getCostValue();
		}
		
		int sumInvestment = 0;
		for(int idx = 0; idx < this.investmentInterests.size(); ++idx)
		{
			sumInvestment = sumInvestment + this.investmentInterests.get(idx).getCostValue();
		}
		
		this.slices = new ArrayList<Slice>();
		this.slices.add(new Slice(sumBonds, Color.RED));
		this.slices.add(new Slice(sumInvestment, Color.GREEN));
		
		repaint();
	}
}