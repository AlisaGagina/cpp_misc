//Alisa Gagina
//260770497

#include <iostream>
#include <vector>
#include <algorithm>    // std::random_shuffle
#include <ctime>

using namespace std;

//
// !!!!!!!!!!!!!!!!
// Card Class
// !!!!!!!!!!!!!!!!
//


enum Rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
EIGHT, NINE, TEN, JACK, QUEEN, KING};       
enum Type {CLUBS, DIAMONDS, HEARTS, SPADES}; 

class Card {      
    public:            
        Card(int r, Type t);    //Constructor that uses int for Rank (easier to fill deck)
        Card(Rank r, Type t);   //Constructor that uses the enum for Rank
        int getValue() const;   
        void displayCard();
    private:
        Rank r;
        Type t;
};

    //
    // Card Constructor that uses int for Rank (easier to fill deck)
    //
    Card::Card(int r, Type t){
        this->t=t;
        switch(r){
            case 1: this->r=ACE; break;
            case 2: this->r=TWO; break;
            case 3: this->r=THREE;break;
            case 4: this->r=FOUR;break;
            case 5: this->r=FIVE;break;
            case 6: this->r=SIX;break;
            case 7: this->r=SEVEN;break;
            case 8: this->r=EIGHT;break;
            case 9: this->r=NINE;break;
            case 10: this->r=TEN;break;
            case 11: this->r=JACK;break;
            case 12: this->r=QUEEN;break;
            case 13: this->r=KING;break;
        }
    };

    //
    //Card Constructor that uses the enum for Rank
    //
    Card::Card(Rank r, Type t):t(t), r(r){};

    // 
    //Card method that returns value of card (Ace getValue will be defined later, 1 for now)
    //
    int Card::getValue() const{
        switch(this->r){
            case JACK: return 10;
            case QUEEN: return 10;
            case KING: return 10;
            default: return this->r;
        }
    };

    // 
    //Card method that prints card (with ace as 1, not 11)
    //
    void Card::displayCard(){
        switch(this->r){ 
            case JACK: cout<< "J"; break;
            case QUEEN: cout<< "Q"; break;
            case KING: cout<< "K"; break;
            default: cout << this->getValue(); break;
        }
        switch(this->t){ 
            case CLUBS: cout<< "C "; break;
            case DIAMONDS: cout<< "D "; break;
            case HEARTS: cout<< "H "; break;
            case SPADES: cout<< "S " ; break;
        }
    };

//
// !!!!!!!!!!!!!!!!
// Hand Class
// !!!!!!!!!!!!!!!!
//

class Hand{
    public:        
        Hand(); //default constructor, cards is empty
        void add (Card c);
        void clear();
        int getTotal() const;
        void printHand(); //will be used later in BlackJackGame
    private:
        vector<Card> cards;
};
    //
    // Hand default constructor, cards is empty
    //
    Hand::Hand(): cards() {};

    //
    // Add a card to the hand, using the vector method push_back (to the end)
    //
    void Hand::add(Card c){
        cards.push_back(c);
    };

    //
    // Clear hand
    //
    void Hand::clear(){
        cards.clear();
    }

    //
    //Return total value of cards in hand as an int
    // Note: the ace switcharoo (1vs11) happens here
    //
    int Hand::getTotal() const{
        int total=0;
        bool Ace=false; //is an ace present?
        for (int i =0; i < cards.size(); i++){
            total += cards[i].getValue();
            if (cards[i].getValue()==1){  //aka an ace is present
                Ace=true;
            }
        }
        // Ace is counted as 11 if doing so does not make the hand bust
        if(Ace && total < 12){
            total +=10;
        }
        return total;
    }

    //
    //Print hand in form: card1 card2 [total value of hand]
    //
    void Hand::printHand(){
        for (int i =0; i < cards.size(); i++){
            cards[i].displayCard();
        }
        cout << "[" << this->getTotal() <<"]"<<endl;
    }


//
// !!!!!!!!!!!!!!!!
// Deck Class
// !!!!!!!!!!!!!!!!
//


class Deck{
    public:        
        Deck();
        void populate();
        void shuffle();
        Hand deal(Hand h);
        void printDeck(); //helper method, not actually used in BlackJackGame
    private:
        vector<Card> cards;
        int current; //index of which card we are at currently in the deck (0 being top)
};

    //
    //default deck constructor
    //
    Deck::Deck(): cards(), current(0) {};

    //
    //deck populator: for each numerical value (ace to king), add 4 cards of each suite
    //
    void Deck::populate(){
        for (int n = 1; n <= 13; n++) { 
                cards.push_back(Card(n, HEARTS));
                cards.push_back(Card(n, CLUBS));
                cards.push_back(Card(n, SPADES));
                cards.push_back(Card(n, DIAMONDS));
            };
    };

    //
    // shuffles deck using random_shuffle based on seed 
    //
    void Deck::shuffle(){
        // using <algorithm> and <ctime>
        srand(time(0));
        random_shuffle(cards.begin(), cards.end()); 
        current = 0; //reset current to be the top card of the deck
    }

    //
    //deals a card to hand h, returns updated hand
    //
    Hand Deck::deal(Hand h){
        //might need to restat if we went through the deck
        if (current == cards.size())shuffle();

        //cards[current].displayCard();
        h.add(cards[current]);
        current++; //current card is used, move to the one below
        return h;
    };

    //
    //prints deck (helper method to check if deck is shuffled)
    //
    void Deck::printDeck(){
        for (int i = 0; i < 52; i++) cards[i].displayCard();
    }



//
// !!!!!!!!!!!!!!!!
// Abstract Player
// !!!!!!!!!!!!!!!!
//


class AbstractPlayer{
    public:
        AbstractPlayer(){};
        virtual ~AbstractPlayer() {};
        virtual bool isDrawing() const = 0; 
        bool isBusted();
        Hand getHand();  //get method
        void updateHand(Hand h);  //set method
    protected:
        Hand hand;
};

    //
    //checks if a player is busted (total over 21)
    //
    bool AbstractPlayer::isBusted(){
        if (this->hand.getTotal()>21) return true; else return false;
    };

    //
    //get method for protected hand
    //
    Hand AbstractPlayer::getHand(){
        return hand;
    }

    //
    //set method for protected hand
    //
    void AbstractPlayer::updateHand(Hand h){
        hand=h;
    }



//
// !!!!!!!!!!!!!!!!
// ComputerPlayer Class (coded before Human due to the Human function announce(ComputerPlayer))
// !!!!!!!!!!!!!!!!
//

class ComputerPlayer: public AbstractPlayer{
    public:
        ComputerPlayer(){};
        ~ComputerPlayer(){};
        bool isDrawing() const;
        int getTotal();
        };

    //
    //don't draw if total is over 16
    //
    bool ComputerPlayer::isDrawing() const{
        if (this->hand.getTotal()<=16) return true; else return false;
    };

    //
    //get Total of hand (defined because hand is private, otherwise there are scope errors)
    //
    int ComputerPlayer::getTotal(){
        return this->hand.getTotal();
    }

//
// !!!!!!!!!!!!!!!!
// HumanPlayer Class
// !!!!!!!!!!!!!!!!
//

class HumanPlayer: public AbstractPlayer{
    public:
        HumanPlayer(){};
        ~HumanPlayer(){};
        bool isDrawing() const;
        void announce(ComputerPlayer opponent);
        };

    //
    //interactive method to ask player if they are drawing a card, returns answer as a boolean
    //
    bool HumanPlayer::isDrawing() const{
        bool spellingvalid=false; //spelling check (accept only 'y' and 'n' as answer)
        char answer;
        while(!spellingvalid){
            cout << "Do you want to draw? (y/n): ";
            cin >> answer;
            if (answer =='y'){
                spellingvalid=true;
                return true; 
            }else if (answer == 'n'){
                spellingvalid=true;
                return false;
            }else{
                cout << "Pls try again\n";  //loop if answer wasn't y or n
        }
        }
        return true; //this is here because otherwise the compiler gets mad, will never actually get to this point due to while loop
    };

    //
    //announce result of game
    //
    void HumanPlayer::announce(ComputerPlayer opponent){
        if(this->isBusted() && opponent.isBusted()){
            cout << "Push: No one wins." << endl;
        }
        else if (this->isBusted()){
            cout << "Player busts. \nCasino wins."<< endl;
        }else if (opponent.isBusted()){
            cout << "Casino busts. \nPlayer wins."<< endl;
        } else if (this->hand.getTotal()>opponent.getTotal()){
            cout << "Player wins."<< endl;
        } else if (this->hand.getTotal()<opponent.getTotal()){
            cout << "Casino wins."<< endl;
        }else{
            cout << "Push: No one wins."<< endl;
        }
    };

//
// !!!!!!!!!!!!!!!!
// BlackJackGame Class
// !!!!!!!!!!!!!!!!
//

class BlackJackGame{
    public:
        void play();
     
    private:
        Deck m_deck;
        ComputerPlayer m_casino;
};

    //
    //play method where all the magic happens
    //
    void BlackJackGame::play(){

        //make and shuffle deck
        m_deck.populate();
        m_deck.shuffle();
        //m_deck.printDeck();

        //create human player, give them two cards
        HumanPlayer player;
        player.updateHand(m_deck.deal(player.getHand()));
        player.updateHand(m_deck.deal(player.getHand()));

        //give opponent one card
        m_casino.updateHand(m_deck.deal(m_casino.getHand()));
        
        //print totals
        cout<< "Casino: ";
        m_casino.getHand().printHand();
        cout<< "Player: ";
        player.getHand().printHand();

        bool player_playing=true;
        bool comp_playing=true;

        //player loop
        while (player_playing){
            if(player.isDrawing() && player_playing){ //if player is willing to draw
                player.updateHand(m_deck.deal(player.getHand())); //give them a card
                cout<< "Player: ";
                player.getHand().printHand(); //print new hand
                if(player.isBusted()){ //if player is busted, game over, bust out of the loop and skip the comp loop
                    player_playing = false;
                    comp_playing = false;
                    break;
                }}
            else{
                player_playing=false; //if player is not willing to draw
            }
        }

        // robot is drawing next
        while (comp_playing){
            if(m_casino.isDrawing()){
                m_casino.updateHand(m_deck.deal(m_casino.getHand()));
                cout<< "Casino: ";
                m_casino.getHand().printHand();
                if(m_casino.isBusted()){
                    comp_playing = false;  //exit if comp is busted
                    break;
                }
            }else{
                comp_playing=false; //exit if comp is not drawing anymore
            }
        }
        player.announce(m_casino);  //announce result

        //reset game
        Hand h;
        m_casino.getHand().clear();
        m_casino.updateHand(h);

        
    };


//
// !!!!!!!!!!!!!!!!
// provided main
// !!!!!!!!!!!!!!!!
//

int main()
{
    cout << "\tWelcome to the Comp322 Blackjack game!" << endl << endl;
    
    BlackJackGame game;
    //The main loop of the game
 
    bool playAgain = true;
    char answer = 'y';
    while (playAgain)
        {
        game.play();
        // Check whether the player would like to play another round
        cout << "Would you like another round? (y/n): ";
        cin >> answer;
        cout << endl << endl;
        playAgain = (answer == 'y' ? true : false);
        }
    cout <<"Gave over!";
    return 0;
    };
