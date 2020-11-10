//Lawrence Wong 1001587603
#include <gtkmm.h>
#include <iostream>

class MainWindow : public Gtk::Window //window object
{
	public:
		MainWindow()
		{
			set_default_size(800,400); //setting default size for the window
			set_title("Welcome to my Guessing Game"); //setting the title for the window
			
			Gtk::Box *MainVBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0)); //making the vertical box that will contain everything
			add(*MainVBox); //adds the main box onto the window
			
			//getting the menu bar
			Gtk::MenuBar *MyMenuBar = Gtk::manage(new Gtk::MenuBar());
			MainVBox->pack_start(*MyMenuBar, Gtk::PACK_SHRINK, 0);
			
			//adding the label onto the window
			Gtk::Label *TitleLabel = Gtk::manage(new Gtk::Label("What's this character's name?"));
			MainVBox->pack_start(*TitleLabel);
			TitleLabel->set_justify(Gtk::JUSTIFY_CENTER);
			TitleLabel->show();
			
			//making the image on the window
			Gtk::Image *MyImage = Gtk::manage(new Gtk::Image{"Jaden.png"});
			MainVBox->pack_start(*MyImage);
			MyImage->show();
			
			//adding all the menu items
			Gtk::MenuItem *DeckMenu = Gtk::manage(new Gtk::MenuItem("_Deck Hint", true));
			MyMenuBar->append(*DeckMenu); 
			Gtk::Menu *DeckSubMenu = Gtk::manage(new Gtk::Menu()); //initializing the submenu
			DeckMenu->set_submenu(*DeckSubMenu); //adding the sub menu onto the menu item
			Gtk::MenuItem *SubDeckItem = Gtk::manage(new Gtk::MenuItem("Elemental Hero", true)); //adding the submenu item
			DeckSubMenu->append(*SubDeckItem);
			Gtk::MenuItem *PhraseMenu = Gtk::manage(new Gtk::MenuItem("_Phrase Hint", true));
			
			MyMenuBar->append(*PhraseMenu);
			Gtk::Menu *PhraseSubMenu = Gtk::manage(new Gtk::Menu());
			PhraseMenu->set_submenu(*PhraseSubMenu);
			Gtk::MenuItem *SubPhraseItem = Gtk::manage(new Gtk::MenuItem("Get your game on!", true)); //adding the submenu item
			PhraseSubMenu->append(*SubPhraseItem);
			
			Gtk::MenuItem *SchoolMenu = Gtk::manage(new Gtk::MenuItem("_School Hint", true));
			MyMenuBar->append(*SchoolMenu);
			Gtk::Menu *SchoolSubMenu = Gtk::manage(new Gtk::Menu());
			SchoolMenu->set_submenu(*SchoolSubMenu);
			Gtk::MenuItem *SubSchoolItem = Gtk::manage(new Gtk::MenuItem("Duel Academy", true)); //adding the submenu item
			SchoolSubMenu->append(*SubSchoolItem);
			
			//creating 3 boxes, getting a horizontal box and packing two vertical boxes into the horizontal box
			Gtk::Box *MainHBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));
			MainVBox->pack_end(*MainHBox);
			Gtk::Box *SecondVBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
			MainHBox->pack_start(*SecondVBox);
			Gtk::Box *ThirdVBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
			MainHBox->pack_start(*ThirdVBox);
			
			//creating the entry box for the user to enter their responses
			Gtk::Entry *UserInput = Gtk::manage(new Gtk::Entry());
			UserInput->set_text("Enter your answer here");
			UserInput->select_region(0,UserInput->get_text_length());
			ThirdVBox->add(*UserInput);
			
			//making the buttons and packing them into the box
			Gtk::Button *ButtonOK = Gtk::manage(new Gtk::Button("OK"));
			SecondVBox->pack_start(*ButtonOK);
			Gtk::Button *NOButton = Gtk::manage(new Gtk::Button("Cancel"));
			SecondVBox->pack_end(*NOButton);
			
			//making the entry have the focus
			UserInput->grab_focus_without_selecting();
			
			//making connections for the buttons
			ButtonOK->signal_clicked().connect(sigc::bind<Gtk::Entry*>(sigc::mem_fun(*this, &MainWindow::OkayFunction),UserInput));
			//used bind to be able to pass through another argument for the member function
			NOButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::CancelFunction));
			UserInput->signal_activate().connect(sigc::bind<Gtk::Entry*>(sigc::mem_fun(*this, &MainWindow::OkayFunction),UserInput));
			
			//getting all the boxes to show their contents
			MainVBox->show_all();
		}
		void OkayFunction(Gtk::Entry *Guess) //function for the user when they press ok or enter on the keyboard for the entry
		{
			const std::string CorrectResponse = "Jaden Yuki"; //setting the string equal to the correct answer
			std::string NameGuess = Guess->get_text(); //using function get_text() to grab the text in the entry box
			if(NameGuess == CorrectResponse)
			{
				Gtk::MessageDialog GoodAnswer{"", false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK}; //creating dialogs for the message to popup
				GoodAnswer.set_secondary_text("You Guessed <span fgcolor='#0000ff'>Correctly</span> !!", true); //setting the text inside the dialog and changing the color
				GoodAnswer.run();	
			}
			else
			{
				Gtk::MessageDialog BadAnswer{"", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK};
				BadAnswer.set_secondary_text("You Guessed <span fgcolor='#0000ff'>Incorrectly</span> !!", true);
				BadAnswer.run();
			}	
		}
		void CancelFunction() //cancel function for the cancel button
		{
			hide(); //hides the window 
		}
};
int main(int argc, char* argv[])
{
	auto app = Gtk::Application::create(argc, argv, "LawMainWindow");
	MainWindow LawWindow; //creating the window 
	app->run(LawWindow); //runining the window
}