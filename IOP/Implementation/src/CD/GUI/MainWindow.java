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
import java.util.Set;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.SwingConstants;


public class MainWindow extends JFrame implements ActionListener {
	
	private JPanel buttonPanel;
	
	private JButton przychodyProwizjaButton;
	private JButton przychodyOdsetekButton;
	private JButton przychodyUdzialyAkcjeButton;
	
	private JButton kosztyProwizjaButton;
	private JButton kosztyOdsetkiButton;
	private JButton kosztyDzialanieBankuButton;
	
	private JButton stanPlynnosciFinansowejButton;
	private JButton stanRezerwyObowiazkowejButton;
	
	private JButton drukowanieRaportuKNFButton;
	private JButton drukowanieWynikuFinansowegoButton;
	
	private JTextArea text;
	private static final long serialVersionUID = 3220202534328319024L;
	
	public MainWindow() {
		
		int buttonWidth = 200;
		int buttonHeight = 50;
		
		/* Tworzenie przyciskow i pola tekstowego */
		this.przychodyProwizjaButton = new JButton("Przychody z tytulu prowizji");
		this.przychodyProwizjaButton.setPreferredSize(new Dimension(buttonWidth, buttonHeight));
		this.przychodyProwizjaButton.setFocusable(false);
		
		this.przychodyOdsetekButton = new JButton("Przychody z tytulu odsetek");
		this.przychodyOdsetekButton.setPreferredSize(new Dimension(buttonWidth, buttonHeight));
		this.przychodyOdsetekButton.setFocusable(false);
		
		this.przychodyUdzialyAkcjeButton = new JButton("Przychody z udzialow i akcji");
		this.przychodyUdzialyAkcjeButton.setPreferredSize(new Dimension(buttonWidth, buttonHeight));
		this.przychodyUdzialyAkcjeButton.setFocusable(false);
		
		this.kosztyProwizjaButton = new JButton("Koszty prowizji");
		this.kosztyProwizjaButton.setPreferredSize(new Dimension(buttonWidth, buttonHeight));
		this.kosztyProwizjaButton.setFocusable(false);
		
		this.kosztyOdsetkiButton = new JButton("Koszty odsetek");
		this.kosztyOdsetkiButton.setPreferredSize(new Dimension(buttonWidth, buttonHeight));
		this.kosztyOdsetkiButton.setFocusable(false);
		this.kosztyOdsetkiButton.setActionCommand("KosztyOdsetek");
		this.kosztyOdsetkiButton.addActionListener(this);
		
		this.kosztyDzialanieBankuButton = new JButton("Koszty dzialania banku");
		this.kosztyDzialanieBankuButton.setPreferredSize(new Dimension(buttonWidth, buttonHeight));
		this.kosztyDzialanieBankuButton.setFocusable(false);
		
		this.stanPlynnosciFinansowejButton = new JButton("Stan plynnosci finansowej");
		this.stanPlynnosciFinansowejButton.setPreferredSize(new Dimension(buttonWidth, buttonHeight));
		this.stanPlynnosciFinansowejButton.setFocusable(false);
		
		this.stanRezerwyObowiazkowejButton = new JButton("Stan rezerwy obowiazkowej");
		this.stanRezerwyObowiazkowejButton.setPreferredSize(new Dimension(buttonWidth, buttonHeight));
		this.stanRezerwyObowiazkowejButton.setFocusable(false);
		
		this.drukowanieRaportuKNFButton = new JButton("Drukowanie raportu do KNF");
		this.drukowanieRaportuKNFButton.setPreferredSize(new Dimension(buttonWidth, buttonHeight));
		this.drukowanieRaportuKNFButton.setFocusable(false);
		
		this.drukowanieWynikuFinansowegoButton = new JButton("Drukowanie wyniku finansowego");
		this.drukowanieWynikuFinansowegoButton.setPreferredSize(new Dimension(buttonWidth, buttonHeight));
		this.drukowanieWynikuFinansowegoButton.setFocusable(false);
		
		Font font = new Font("Serif", Font.BOLD, 50);
		this.text = new JTextArea();
		this.text.setEditable(false);
		this.text.setFocusable(false);
		this.text.setFont(font);
		this.text.setText("System zarzadzajacy finansami banku");
		this.text.setBackground(new Color(this.getBackground().getRGB()));
			
		/* Dodawanie pola tekstowego do okna */
		this.setLayout(new GridBagLayout());
		GridBagConstraints constraints = new GridBagConstraints();
		constraints.insets = new Insets(10,10,50,0);
		constraints.gridx = 0;
		constraints.gridy = 0;
		this.add(this.text, constraints);
		
		/* Tworzenie panelu z przyciskami */
		buttonPanel = new JPanel();
		buttonPanel.setLayout(new GridBagLayout());
		constraints.insets = new Insets(10,10,10,10);
		constraints.gridx = 0;
		constraints.gridy = 1;
		buttonPanel.add(this.przychodyProwizjaButton, constraints);
		constraints.gridy = 2;
		buttonPanel.add(this.przychodyOdsetekButton, constraints);
		constraints.gridy = 3;
		buttonPanel.add(this.przychodyUdzialyAkcjeButton, constraints);
		constraints.gridx = 1;
		constraints.gridy = 1;
		buttonPanel.add(this.kosztyProwizjaButton, constraints);
		constraints.gridy = 2;
		buttonPanel.add(this.kosztyOdsetkiButton, constraints);
		constraints.gridy = 3;
		buttonPanel.add(this.kosztyDzialanieBankuButton, constraints);
		constraints.gridx = 2;
		constraints.gridy = 1;
		buttonPanel.add(this.stanPlynnosciFinansowejButton, constraints);
		constraints.gridy = 2;
		buttonPanel.add(this.stanRezerwyObowiazkowejButton, constraints);
		constraints.gridx = 3;
		constraints.gridy = 1;
		buttonPanel.add(this.drukowanieRaportuKNFButton, constraints);
		constraints.gridy = 2;
		buttonPanel.add(this.drukowanieWynikuFinansowegoButton, constraints);
		
		/* Dodawanie panelu z przyciskami do okna */
		constraints.gridx = 0;
		constraints.gridy = 1;
		this.add(buttonPanel, constraints);
		
		/* Ustawianie parametrow okna */
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setTitle("Aplikacja - zarzadzanie funduszami banku");
		this.setFocusable(true);
		this.setSize(new Dimension(1000, 600));
		this.setResizable(false);
		this.setVisible(true);
	}

	
	@Override
	public void actionPerformed(ActionEvent e) {
		String actionName = e.getActionCommand();
		
		if(actionName.equals("KosztyOdsetek"))
		{
			this.menuInterestCostClicked();
		}
	}
	
	
	public void menuFinancialRatioClicked() {
		// begin-user-code
		// TODO Auto-generated method stub

		// end-user-code
	}

	
	public void menuLoginClicked() {
		// begin-user-code
		// TODO Auto-generated method stub

		// end-user-code
	}


	public void menuKNFReportClicked() {
		// begin-user-code
		// TODO Auto-generated method stub

		// end-user-code
	}


	public void menuFinancialReportClicked() {
		// begin-user-code
		// TODO Auto-generated method stub

		// end-user-code
	}


	public void menuBankActionsCostClicked() {
		// begin-user-code
		// TODO Auto-generated method stub

		// end-user-code
	}


	public void menuStockSharesIncomeClicked() {
		// begin-user-code
		// TODO Auto-generated method stub

		// end-user-code
	}


	public void menuInterestIncomeClicked() {
		// begin-user-code
		// TODO Auto-generated method stub

		// end-user-code
	}


	public void menuCommissionIncomeWindow() {
		// begin-user-code
		// TODO Auto-generated method stub

		// end-user-code
	}


	public void menuRequirementReserveClicked() {
		// begin-user-code
		// TODO Auto-generated method stub

		// end-user-code
	}


	public void menuInterestCostClicked() {
		InterestCostWindow interestCostWindow = new InterestCostWindow();
		interestCostWindow.init();
		interestCostWindow.Show();
	}
}