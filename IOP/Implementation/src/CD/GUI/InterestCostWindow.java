/**
 * 
 */
package CD.GUI;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.table.DefaultTableModel;

import CD.BUSINESS.Application;
import CD.BUSINESS.BondInterest;
import CD.BUSINESS.InvestmentInterest;


public class InterestCostWindow extends JFrame implements ActionListener{

	private static final long serialVersionUID = -2352397173337211718L;
	
	private JTextArea text;
	private JButton odsetkiOdObligacjiButton;
	private JButton odsetkiOdLokatButton;
	private JButton wyczyscButton;
	private JPanel buttonPanel;
	
	
	private ArrayList<BondInterest> bondInterests;
	private ArrayList<InvestmentInterest> investmentInterests;
	
	private DefaultTableModel model;
	private JTable table;
	private JPanel tablePanel;


	public InterestCostWindow() {;
		
		int buttonWidth = 150;
		int buttonHeight = 50;
		
		this.setLayout(new GridBagLayout());
		GridBagConstraints constraints = new GridBagConstraints();
		constraints.insets = new Insets(10,10,10,10); 
		
		String[] colNames = { "Imie", "Nazwisko", "Czas trwania", "Oprocentowanie", "Pesel", "Nazwa firmy", "NIP", "Wartosc", "Data" };
		this.model = new DefaultTableModel(0, 0);
		//this.model = new DefaultTableModel(colNames, 0);
		this.tablePanel = new JPanel(new BorderLayout());
		this.tablePanel.setPreferredSize(new Dimension(650, 300));

		this.table = new JTable(model);
		this.table.setBackground(Color.GREEN);
		this.table.getTableHeader().setReorderingAllowed(false);
		//for(int idx = 0; idx < 9; ++idx)
		//	this.table.getColumnModel().getColumn(idx).setPreferredWidth(150);
		
		this.tablePanel.add(new JScrollPane(this.table), BorderLayout.CENTER);

		constraints.insets = new Insets(10,10,50,0);
		constraints.gridx = 1;
		constraints.gridy = 1;
        this.add(tablePanel, constraints);
        
		
		this.bondInterests = new ArrayList<BondInterest>();
		this.investmentInterests = new ArrayList<InvestmentInterest> ();
		
		/* Tworzenie przyciskow  i pola tekstowego */
		this.odsetkiOdLokatButton = new JButton("Odsetki od lokat");
		this.odsetkiOdLokatButton.setPreferredSize(new Dimension(buttonWidth, buttonHeight));
		this.odsetkiOdLokatButton.setFocusable(false);
		this.odsetkiOdLokatButton.setActionCommand("OdsetkiOdLokatButton");
		this.odsetkiOdLokatButton.addActionListener(this);
		
		this.odsetkiOdObligacjiButton = new JButton("Odsetki od obligacji");
		this.odsetkiOdObligacjiButton.setPreferredSize(new Dimension(buttonWidth, buttonHeight));
		this.odsetkiOdObligacjiButton.setFocusable(false);
		this.odsetkiOdObligacjiButton.setActionCommand("OdsetkiOdObligacjiButton");
		this.odsetkiOdObligacjiButton.addActionListener(this);
		
		this.wyczyscButton = new JButton("Wyczysc");
		this.wyczyscButton.setPreferredSize(new Dimension(buttonWidth, buttonHeight));
		this.wyczyscButton.setFocusable(false);
		this.wyczyscButton.setActionCommand("WyczyscButton");
		this.wyczyscButton.addActionListener(this);
		
		Font font = new Font("Serif", Font.BOLD, 50);
		this.text = new JTextArea();
		this.text.setEditable(false);
		this.text.setFocusable(false);
		this.text.setFont(font);
		this.text.setText("Koszty Odsetek");
		this.text.setBackground(new Color(this.getBackground().getRGB()));
			
		/* Dodawanie pola tekstowego do okna */
		constraints.insets = new Insets(10,10,50,0);
		constraints.gridx = 0;
		constraints.gridy = 0;
		//this.add(this.text, constraints);
		
		/* Tworzenie panelu z przyciskami */
		buttonPanel = new JPanel();
		buttonPanel.setLayout(new GridBagLayout());
		constraints.insets = new Insets(10,10,10,10);
		constraints.gridx = 0;
		constraints.gridy = 1;
		buttonPanel.add(this.odsetkiOdLokatButton, constraints);
		constraints.gridy = 2;
		buttonPanel.add(this.odsetkiOdObligacjiButton, constraints);
		constraints.gridy = 3;
		buttonPanel.add(this.wyczyscButton, constraints);
		
		
		/* Dodawanie panelu z przyciskami do okna */
		constraints.gridx = 0;
		constraints.gridy = 1;
		this.add(buttonPanel, constraints);
		
		/* Ustawianie parametrow okna */
		this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		this.setTitle("Aplikacja - Koszty odsetek");
		this.setFocusable(true);
		this.setSize(new Dimension(1000, 600));
		this.setResizable(false);
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		String actionName = e.getActionCommand();
		
		if (actionName.equals("OdsetkiOdLokatButton"))
		{
			BondInterestButtonClicked();
		}
		else if (actionName.equals("OdsetkiOdObligacjiButton"))
		{
			InvestmentInterestButtonClicked();
		}
	}


	public void BondInterestButtonClicked() {
		this.model.setColumnCount(0);
		
		this.model.getDataVector().removeAllElements();
		this.model.fireTableDataChanged();
		
		this.model.addColumn("Imie");
		this.model.addColumn("Nazwisko");
		this.model.addColumn("Czas trwania");
		this.model.addColumn("Oprocentowanie");
		this.model.addColumn("Pesel");
		this.model.addColumn("Nazwa firmy");
		this.model.addColumn("NIP");
		this.model.addColumn("Wartosc");
		this.model.addColumn("Data");
		
		for(int idx = 0; idx < this.bondInterests.size(); ++idx)
		{
			String forename = this.bondInterests.get(idx).getForename();
			String surname = this.bondInterests.get(idx).getSurname();
			int durationDays = this.bondInterests.get(idx).getDurationDays();
			double interest = this.bondInterests.get(idx).getInterest();
			String pesel = this.bondInterests.get(idx).getPesel();
			String firmName = this.bondInterests.get(idx).getFirmName();
			String NIP = this.bondInterests.get(idx).getNIP();
			int costValue = this.bondInterests.get(idx).getCostValue(); 
			String date = this.bondInterests.get(idx).getDate();
			
			model.addRow(new Object[] {forename, surname, durationDays, interest, pesel, firmName, NIP, costValue, date});
		}
		
		this.table.repaint();
		
		PieChart pieChart = new PieChart();
		pieChart.setBondInterests(this.bondInterests);
		pieChart.setInvestmentInterests(this.investmentInterests);
		pieChart.drawInterests();
		
		JFrame frame = new JFrame();
		frame.setTitle("PieChart");
		frame.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		frame.add(pieChart);
		frame.setPreferredSize(new Dimension(300, 300));
		frame.setSize(new Dimension(300, 300));
		frame.setVisible(true);	
	}


	public void init() {
		Application application = new Application();
		this.bondInterests = application.getBondInterests();
		this.investmentInterests = application.getInvestmentInterests();
	}


	public void Show() {
		this.setVisible(true);
	}


	public void InvestmentInterestButtonClicked() {
		this.model.setColumnCount(0);
		
		this.model.getDataVector().removeAllElements();
		this.model.fireTableDataChanged();
		
		this.model.addColumn("Imie");
		this.model.addColumn("Nazwisko");
		this.model.addColumn("Pesel");
		this.model.addColumn("Oprocentowanie");
		this.model.addColumn("Typ lokaty");
		this.model.addColumn("Wartosc");
		this.model.addColumn("Data");
		
		for(int idx = 0; idx < this.investmentInterests.size(); ++idx)
		{
			String pesel = this.investmentInterests.get(idx).getPesel();
			String forename = this.investmentInterests.get(idx).getForename();
			String surname = this.investmentInterests.get(idx).getSurname();
			double interest = this.investmentInterests.get(idx).getInterest();
			String type = this.investmentInterests.get(idx).getType();
			int val = this.investmentInterests.get(idx).getCostValue();
			String data = this.investmentInterests.get(idx).getDate();
			
			model.addRow(new Object[] {forename, surname, pesel, interest, type, val, data});
		}
		
		this.table.repaint();
		
		PieChart pieChart = new PieChart();
		pieChart.setBondInterests(this.bondInterests);
		pieChart.setInvestmentInterests(this.investmentInterests);
		pieChart.drawInterests();
		
		JFrame frame = new JFrame();
		frame.setTitle("PieChart");
		frame.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		frame.add(pieChart);
		frame.setPreferredSize(new Dimension(300, 300));
		frame.setSize(new Dimension(300, 300));
		frame.setVisible(true);	
	}
}