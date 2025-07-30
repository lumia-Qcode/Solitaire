#include<iostream>
#include<string>
#include<iomanip>
#include<windows.h>
#include<stdexcept>
#include<cctype>
using namespace std;


class Card {
private:		
	string suit;
	string rank;
	string color;
	bool faceUp;
	void SetColor() {		
		if (suit == "CLUBS" || suit == "SPADES") {	// clubs and spades are black
			color = "BLACK";
		}
		else {
			color = "RED";	//  hearts and diamonds are red
		}
	}
public:

	static const string HEARTS;
	static const string SPADES;
	static const string CLUBS;
	static const string DIAMONDS;
	static const string RANKS[13];

	Card() {
		faceUp = 0;
	}

	Card(const string& Suit, const string& Rank) :suit(Suit), rank(Rank), faceUp(0) { SetColor(); }	

	Card(const Card& rhs) :suit(rhs.suit), rank(rhs.rank), faceUp(rhs.faceUp), color(rhs.color) {};  // COPY CONSTRUCTOR

	Card& operator=(const Card& rhs) {		// ASSIGNMENT OPERATOR
		if (this != &rhs) {
			suit = rhs.suit;
			rank = rhs.rank;
			color = rhs.color;
			faceUp = rhs.faceUp;
		}
		return *this;
	}

	// This function determines whether card is hidden 
	void turnFaceofCard() {	  
		faceUp = 1;
	}

	// This function flips card
	void FlipFaceOfCard() {		
		if (faceUp == 0) {
			faceUp = 1;
		}
		else if (faceUp == 1) {
			faceUp = 0;
		}
	}

	bool operator==(const Card& rhs) {
		if (suit == rhs.suit && rank == rhs.rank && color == rhs.color) {
			return true;
		}
		return false;
	}

	bool checkColor(Card& rhs) {
		if ((color == "RED" && rhs.color == "BLACK") || (color == "BLACK" && rhs.color == "RED")) {
			return true;
		}
		return false;
	}

	bool checkSuit(Card& rhs) {
		if (suit == rhs.suit) {
			return true;
		}
		return false;
	}

	int getRankIndex(string rankOfCard) {
		for (int i = 0; i < 13; i++) {
			if (RANKS[i] == rank) {
				return i;
			}
		}
		return -1;
	}

	// This function checks rank for valid moves 
	bool checkRank(Card& rhs) {
		int c1index = rhs.getRankIndex(rhs.rank);
		int c2index = this->getRankIndex(this->rank);
		if (c1index == c2index - 1) {
			return true;
		}
		return false;
	}

	// This fucntion gets rank for valid foundation moves
	bool checkRankFound(Card& rhs) {
		int c1index = rhs.getRankIndex(rhs.rank);
		int c2index = this->getRankIndex(this->rank);
		if (c1index == c2index + 1) {
			return true;
		}
		return false;
	}

	bool getFaceUP() {
		return faceUp;
	}

	string getRank() {
		return rank;
	}

	void DisplayCard() {		
		if (faceUp == 0) {		// If card is hidden
			cout << "[ ]\t";
		}
		else if (faceUp == 1) {		// If card is not hidden
			const char* HEARTS = "\x03";
			const char* DIAMONDS = "\x04";
			const char* CLUBS = "\x05";
			const char* SPADES = "\x06";
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			if (suit == "HEARTS" || suit == "DIAMONDS") {
				SetConsoleTextAttribute(h, 12);				// Print text in red
				if (suit == "HEARTS") {
					cout << rank << " " << HEARTS;
					cout << "\t";
				}
				else {
					cout << rank << " " << DIAMONDS;
					cout << "\t";
				}
			}
			else {
				SetConsoleTextAttribute(h, 7);	// If a card belongs to spades or clubs suit, print in default color
				if (suit == "SPADES") {
					cout << rank << " " << SPADES;
					cout << "\t";
				}
				else {
					cout << rank << " " << CLUBS;
					cout << "\t";
				}
			}
			SetConsoleTextAttribute(h, 7);	// Set to default color of text
		}
	}

};

const string Card::RANKS[13] = { "ACE", "2", "3", "4", "5", "6", "7", "8", "9","10","JACK", "QUEEN", "KING" };
const string Card::HEARTS = "HEARTS";
const string Card::SPADES = "SPADES";
const string Card::CLUBS = "CLUBS";
const string Card::DIAMONDS = "DIAMONDS";

//--------------------------------------------------------------------------------------------------------------------

template<class T>
class List {
private:
	struct Node {			
	public:
		T data;
		Node* next;
		Node* prev;

		Node(T d, Node* p = 0, Node* n = 0) : data(d) {
			prev = p;
			next = n;
		}

		~Node() {}
	};
	Node* head;				
	Node* tail;
	int size;
public:
	class ListIterator {		
	private:
		Node* current;		
	public:
		friend class List;

		ListIterator(Node* ptr = 0) {
			current = ptr;
		}

		ListIterator operator++() {		// Prefix Increment Operator
			if (current) {
				current = current->next;
			}
			return (*this);
		}

		ListIterator operator++ (int) {	// Postfix Increment Operator
			ListIterator temp = *this;
			++(*this);
			return temp;
		}

		ListIterator& operator--() {	// Prefix Decrement Operator
			if (current) {
				current = current->prev;
			}
			return (*this);
		}

		ListIterator operator--(int) {	// Postfix Decrement Operator
			ListIterator temp = *this;
			--(*this);
			return temp;
		}

		bool operator==(const ListIterator& rhs) const {	// Equalt to operator
			return current == rhs.current;
		}

		bool operator!=(const ListIterator& rhs) const {	// Not equal to operator
			return current != rhs.current;
		}
		T& operator*() const {		// Dereference oeprator
			return current->data;
		}

		Node* getData() {
			return current;
		}
	};
	typedef ListIterator Iterator;

	Iterator begin() {
		Iterator I(head);
		return I;
	}
	Iterator end() {
		Iterator I(tail);
		return I;
	}

	List() : head(nullptr), tail(nullptr), size(0) {}	

	// Insert card in deck
	void insertAtEnd(const T& c) {	
		if (isEmpty()) {	// If list is empty, insert at head 
			head = tail = new Node(c);
		}
		else {				// If list is not empty, insert at tail
			Node* temp = new Node(c);
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
		}
		size++;
	}

	// Remove Card from deck
	void removeFromEnd() {
		if (!isEmpty()) {		// If list is not empty
			Node* temp = tail;
			if (head != tail) {		// If there are more than one elements
				tail = tail->prev;
				tail->next = nullptr;
				delete temp;
			}
			else {		// If there is only one element
				head = tail = nullptr;
				delete temp;
			}
			size--;
		}
	}

	void MoveFoundToCol(Iterator& W)
	{
		Node* temp = W.getData(); 

		if (head == nullptr) {		// If list is empty
			head = temp;
			tail = temp; 
			temp->prev = nullptr; 
			temp->next = nullptr; 
		}
		else {		// If list is not empty 
			temp->next = nullptr; 
			temp->prev = tail; 
			tail->next = temp; 
			tail = temp; 
		}
		size++; 
	}

	bool isEmpty() {
		if (!head) {
			return true;
		}
		return false;
	}

	void showTopCard() {		//  Show top element
		if (!isEmpty()) {
			tail->data.turnFaceofCard();
		}
	}

	void showTopCard2() {		// Flip card face 
		if (!isEmpty()) {
			tail->data.FlipFaceOfCard();
		}
	}

	void Print() {			// This function displays each card in a list
		if (!isEmpty()) {
			Node* temp = head;
			for (; temp != 0; temp = temp->next) {
				Card c = temp->data;
				c.DisplayCard();
			}
		}
	}

	T& GetTail() {
		return tail->data;
	}

	void PrintWastepile() {
		if (!isEmpty()) {
			Node* temp = tail;
			Card c = tail->data;
			c.DisplayCard();
		}
	}

	void PushElement(Iterator& itr) {
		Node* newNode = itr.getData(); 
		if (head != nullptr) {		// Push element in non-empty list
			tail->next = newNode;      
			newNode->prev = tail;     
			tail = newNode;            
			tail->next = nullptr;      
		}
		else {
			head = tail = newNode;     // If list is empty, head and tail point to new node
		}
		size++;
	}

	// Removing card without deletion
	Iterator Remove()
	{
		if (!isEmpty())
		{
			if (size == 1) {
				Iterator itr = tail;	// Save the tail node
				head = nullptr;			// Since list will be empty now
				tail = nullptr;			// Point head and tail to nullptr
				size--;
				return itr;
			}
			else if (size != 1) {
				Iterator itr = tail;	// Save the tail node
				Node* temp = tail;
				tail = temp->prev;		// Move tail to its prev
				temp->prev->next = 0;	// Make its next point to null
				size--;
				return itr;
			}
		}
	}

	Iterator PopElement() {
		if (!isEmpty()) {
			Iterator itr = tail;  
			Node* temp = tail;    

			if (size > 1) {
				tail = temp->prev;		// Move tail to its prev
				tail->next = nullptr;   // Make its next point to null
			}
			else {
				tail = nullptr;		// Only one element in list
				head = nullptr;		// Point head and tail to null
			}
			size--;
			return itr;
		}
		throw out_of_range("Error: Attempted to pop from an empty list.");
	}

	// This function is used to extract a sub-list from main list
	Iterator ExtractList(int num)
	{
		if (num == 1)		// Extracting one element sub-list
		{
			if (!isEmpty())
			{
				if (size != 1) {	// List having multipile elements 
					Iterator itr = tail;	// Save tail node
					Node* temp = tail;
					tail = temp->prev;	// Move tail to its prev
					if (tail) {
						tail->next = 0;	// Make its next point to null
					}
					size--;
					return itr;
				}
				else if (size == 1)		// List having 1 element
				{
					Iterator itr = tail;	// Save tail node
					head = nullptr;			// Since list will be empty now
					tail = nullptr;			// Point head and tail to null
					size--;
					return itr;
				}
			}
		}
		else	// Extracting multiple elements from sub-list
		{
			if (!isEmpty())
			{
				Node* temp = tail;		
				for (int i = 0; i < num - 1; i++) {
					if (temp->prev == nullptr) {	// If prev is null
						throw out_of_range("Move exceeds list boundaries.");
					}
					temp = temp->prev;	// Move elements to their prev
				}
				size -= num;
				Iterator itr = temp;	// Save new tail
				tail = temp->prev;		// Move tail to its prev
				if (tail) {
					tail->next = nullptr;
				}
				else {
					head = nullptr;
				}
				return itr;
			}
		}
	}

	// This function appends a sub-list in main list
	void AppendList(Iterator& itr, int num)
	{
		if (num == 1)	// Appending single element sub-list
		{
			Node* temp = itr.getData();
			temp->next = 0;
			if (tail) {
				tail->next = temp;	// Insert element after tail
				temp->prev = tail; 
				tail = temp;		// Point tail to last element (new)
			}
			else {	
				head = temp;	// If list is empty
				tail = temp;    // Point head and tail to new element
			}
			size++;
		}
		else	// Appending multiple element sub-list
		{
			Node* temp = itr.getData();
			if (tail) {
				tail->next = temp;		// Insert after tail
				temp->prev = tail;		// Point tail to last element
			}
			else {
				head = temp;	// If list is empty, point head to new element
			}
			for (int i = 0; i < num - 1; i++) {
				temp = temp->next;		// Move temp to its next
			}
			temp->next = 0;
			tail = temp;	
			size += num;
		}
	}

	~List() {		
		Node* temp = head;
		while (temp) {
			Node* temp2 = temp->next;
			delete temp;
			temp = temp2;
		}
		head = 0;
		tail = 0;
	}
};

//--------------------------------------------------------------------------------------------------------------------

template<class T>
class Stack {
private:		
	List<T> myList;
	int size;
public:		
	Stack() {
		size = 0;
	}

	void push(const T& value) {		
		myList.insertAtEnd(value);
		size++;
	}

	void pop() {
		if (isEmpty()) {
			cout << "STACK IS EMPTY. NO ELEMENT TO POP\n";
			return;
		}
		myList.removeFromEnd();
		size--;
	}

	bool isEmpty() {
		if (size == 0) {
			return true;
		}
		return false;
	}

	void clear() {
		while (!isEmpty()) {
			pop();
		}
	}

	T& getTop() {		
		if (!myList.isEmpty()) {
			return myList.GetTail();
		}
		throw runtime_error("\nEMPTY STACK");
	}

	void displayTop() {
		myList.showTopCard();
		myList.PrintWastepile();
	}

	// This function inserts element without creating new node
	void PushElement(List<Card>::Iterator& itr) {
		myList.PushElement(itr);
		size++;
	}

	// This function pops element without any deletion 
	List<Card>::Iterator PopElement() {
		size--;
		return myList.PopElement();
	}

	void print() {
		if (size != 0) {
			Card c = myList.GetTail();
			c.DisplayCard();
		}
	}

	~Stack() {
		clear();
	}
};

//--------------------------------------------------------------------------------------------------------------------

class Game;		// Forward declaration of game class

class Command {
private:
	string cmdType;
	string src;
	string des;
	int num;
public:
	Command(string cmd, string s = " ", string d = " ", int numOfCards = 1) :cmdType(cmd), src(s), des(d), num(numOfCards) {}

	friend class Game;	// Make game class a friend to access its private parts 

	// This prvenets using getters. Hence, keeping encapsulation from brekaing.

};

//--------------------------------------------------------------------------------------------------------------------


const int DECK_SIZE = 52;		//  Gloabally declared cosnt variables
const int TABLEAU_COLS = 7;
const int FOUNDATION_COLS = 4;

class Game {
private:								
	List<Card>* tableau[TABLEAU_COLS];
	Stack<Card>* foundations[FOUNDATION_COLS];
	Stack<Card> stock;
	Stack<Card> wastepile;
	Stack<Command> undoStack;
	Card Deck[DECK_SIZE];
	int stockSize;
	int wastepileSize;
	int foundationSize[4];
	int tableauSize[7];
	int flips[TABLEAU_COLS];
public:				
	Game() {
		stockSize = 0;
		wastepileSize = 0;
		for (int i = 0; i < TABLEAU_COLS; i++) {
			tableau[i] = new List<Card>();
			tableauSize[i] = 0;
		}

		for (int i = 0; i < FOUNDATION_COLS; i++) {
			foundations[i] = new Stack<Card>();
			foundationSize[i] = 0;
		}

		stock = Stack<Card>();
		wastepile = Stack<Card>();
		undoStack = Stack<Command>();

		initilizeDeck();
		shuffle();
		initilizeGame();
	}

	void initilizeDeck() {
		int index = 0;		// Count for deck index
		const string suits[4] = { Card::HEARTS, Card::SPADES, Card::CLUBS, Card::DIAMONDS }; // Each element represents a type of suit

		for (int i = 0; i < 4; i++) {	// Storing suits
			string current = suits[i];
			for (int ranks = 0; ranks < 13; ranks++) {	// Storing ranks 
				Deck[index++] = Card(current, Card::RANKS[ranks]); // Create deck with every card
			}
		}
	}

	void shuffle() {
		srand(static_cast<unsigned>(time(0)));
		for (int i = 51; i > 0; i--) {
			int temp = rand() % (i + 1);
			Card temp2 = Deck[i];
			Deck[i] = Deck[temp];
			Deck[temp] = temp2;
		}
	}

	void initilizeGame() {
		int index = 0;  // Count for deck index

		for (int i = 0; i < TABLEAU_COLS; i++) {	// This loop will traverse for 7 tableau columns
			int index2 = 0;   // Index for each tableau size
			for (int j = 0; j <= i; j++) {		// This loop will store i+1 cards in each column
				tableau[i]->insertAtEnd(Deck[index++]);
				index2++;
			}
			tableauSize[i] = index2;
			if (tableauSize[i] > 0) {
				tableau[i]->showTopCard();	// Only show top card
			}
		}

		for (; index < DECK_SIZE; index++) {	// This loop adds the remaining cards to stockpile
			stock.push(Deck[index]);
			stockSize++;
		}
	}

	void display() {
		cout << "\n\nStock\n";
		if (stockSize > 1) {
			cout << "[ ]\n";
			cout << "(" << stockSize << " cards)\n";
		}
		else if (stockSize == 1) {
			cout << "[ ]\n";
			cout << "(" << stockSize << " card)\n";
		}
		else if (stockSize == 0) {
			cout << "(0 cards)\n";
		}
		cout << endl;

		cout << "Wastepile\n";
		if (wastepileSize > 1) {
			wastepile.displayTop();
			cout << "\n(" << wastepileSize << " cards)\n";
		}
		else if (wastepileSize == 1) {
			wastepile.displayTop();
			cout << "\n(" << wastepileSize << " card)\n";
		}
		else if (wastepileSize == 0) {
			cout << "(0 cards)\n";
		}

		for (int i = 0; i < FOUNDATION_COLS; i++) {
			cout << "\nFoundation " << i + 1;
			cout << "\n";
			if (foundationSize[i] > 1) {
				cout << "(" << foundationSize[i] << " cards)\n";
				foundations[i]->print();
			}
			else if (foundationSize[i] == 1) {
				cout << "(" << foundationSize[i] << " card)\n";
				foundations[i]->print();
			}
			else {
				cout << "[ ]\n";
				cout << "(0 cards)\n";
			}
		}

		for (int i = 0; i < TABLEAU_COLS; i++) {
			cout << "\nColumn " << i + 1;
			cout << "\n";
			if (tableauSize[i] > 1) {
				cout << "(" << tableauSize[i] << " cards)\n";
				tableau[i]->Print();
			}
			else if (tableauSize[i] == 1) {
				cout << "(" << tableauSize[i] << " card)\n";
				tableau[i]->Print();
			}
			else {
				cout << "(0 cards)\n";
			}
		}
	}

	// Function to move from column to foundation
	void MoveColToFoundation(int src, int des) {
		if (src >= 0 && src < TABLEAU_COLS) {		// Check if column index is not out of bound
			if (!tableau[src]->isEmpty()) {		    // Check if column is not empty
				Card tempCol = tableau[src]->GetTail();		
				if (des >= 0 && des < FOUNDATION_COLS) {			//  Check if des index is not out of bound
					if (!foundations[des]->isEmpty()) {		// Check if foundation is not empty
						Card tempFound = foundations[des]->getTop();	
						if (tempFound.checkSuit(tempCol)) {		// Check if cards are of same suit
							if (tempFound.checkRankFound(tempCol)) {		// Check if cards rank differ by 1
								List<Card>::Iterator itr = tableau[src]->Remove();	// Perform movement operation through iterator
								tableauSize[src]--;									// Without creation or deletion of node
								if (!tableau[src]->isEmpty()) {
									Card c = tableau[src]->GetTail();
									if (c.getFaceUP() == 0) {	// Track if prev card was hidden 
										flips[src] = 1;			// This track will be used further while undo operation
									}
								}
								tableau[src]->showTopCard();	// Show top card
								foundations[des]->PushElement(itr);
								foundationSize[des]++;
								undoStack.push(Command("m", "c" + to_string(src), "f" + to_string(des), 1));	// Update undo stack
							}
							else {
								cout << "\nERROR: RANKS OF CARDS ARE NOT COMPATIBLE\n";
							}
						}
						else {
							cout << "\nERROR: CARDS DO NOT BELONG TO SAME SUIT\n";
						}
					}
					else {		// If foundation is empty
						if (tempCol.getRank() == "ACE") {	// If top card is ACE
							List<Card>::Iterator itr = tableau[src]->Remove();	// Perform movement operation through iterator													
							tableauSize[src]--;									// Without creation or deletion of node
							if (!tableau[src]->isEmpty()) {
								Card c = tableau[src]->GetTail();
								if (c.getFaceUP() == 0) {		// Track if prev card was hidden 
									flips[src] = 1;				// This track will be used further while undo operation
								}
							}
							tableau[src]->showTopCard();		// Show top card
							foundations[des]->PushElement(itr);
							foundationSize[des]++;
							undoStack.push(Command("m", "c" + to_string(src), "f" + to_string(des), 1));	// Update undo stack
						}
						else {
							cout << "\nERROR: ONLY ACE CAN BE PLACED IN AN EMPTY FOUNDATION\n";
						}
					}
				}
				else {
					cout << "\nERROR: FOUNDATION INDEX OUT OF BOUND\n";
				}
			}
			else {
				cout << "\nERROR: TABLEAU COL IS EMPTY, INVALID CARD MOVE\n";
			}
		}
		else {
			cout << "\nERROR: TABLEAU INDEX OUT OF BOUND\n";
		}
	}

	// Function to move from one column to another
	void MoveColToCol(int src, int des, int numCards) {	
		if (tableauSize[src] >= numCards) {		// Check if num cards are less than tableau size
			if (src >= 0 && src < TABLEAU_COLS) {		// Check if src col is out of bound
				if (!tableau[src]->isEmpty()) {		// Check if src col is not empty
					if (des >= 0 && des < TABLEAU_COLS) {		// Check if des col is out of bound
						int i = 0;
						Stack<Card> s;
						while (i < numCards) {		// This loop stores cards in reverse order in stack
							Card tempSrc = tableau[src]->GetTail();
							s.push(tempSrc);
							tableau[src]->removeFromEnd();
							tableauSize[src]--;
							i++;
						}
						if (!tableau[des]->isEmpty()) {		// If des col is not empty
							Card tempDes = tableau[des]->GetTail();
							if ((tempDes.checkColor(s.getTop())) && (tempDes.checkRank(s.getTop()))) {	// Check if valid move
								int i = 0;	// Restore cards
								while (i < numCards) {
									tableau[src]->insertAtEnd(s.getTop());
									s.pop();
									tableauSize[src]++;
									i++;
								}
								List<Card>::Iterator itr = tableau[src]->ExtractList(numCards);	 // Perform movement operation through iterator
								tableau[des]->AppendList(itr, numCards);						// Without creation or deletion of node
								tableauSize[src] -= numCards;
								tableauSize[des] += numCards;
								if (!tableau[src]->isEmpty()) {
									Card c = tableau[src]->GetTail();
									if (c.getFaceUP() == 0) {		 // Track if prev card was hidden 
										flips[src] = 1;				 // This track will be used further while undo operation
									}
									tableau[src]->showTopCard();
								}
								undoStack.push(Command("m", "c" + to_string(src), "c" + to_string(des), numCards));  // Update undo stack
							}
							else {	// Restore cards
								int i = 0;
								while (i < numCards) {
									tableau[src]->insertAtEnd(s.getTop());
									s.pop();
									tableauSize[src]++;
									i++;
									cout << "\nERROR: CARDS ARE NOT COMPATIBLE\n";
								}
							}
						}
						else {		// If des col is empty
							Card temp = s.getTop();
							if (temp.getRank() == "KING") {	// if top card is king
								int i = 0;		// Restore cards
								while (i < numCards) {
									tableau[src]->insertAtEnd(s.getTop());
									s.pop();
									tableauSize[src]++;
									i++;
								}
								List<Card>::Iterator itr = tableau[src]->ExtractList(numCards);
								tableau[des]->AppendList(itr, numCards);		// Perform movement operation through iterator
								tableauSize[src] -= numCards;					// Without creation or deletion of node	
								tableauSize[des] += numCards;
								if (!tableau[src]->isEmpty()) {
									Card c = tableau[src]->GetTail();
									if (c.getFaceUP() == 0) {	// Track if prev card was hidden 
										flips[src] = 1;			// This track will be used further while undo operation
									}
									tableau[src]->showTopCard();	// Show top card
								}
								undoStack.push(Command("m", "c" + to_string(src), "c" + to_string(des), numCards));		// Update undo stack
							}
							else {
								int i = 0;	// Restore cards
								while (i < numCards) {
									tableau[src]->insertAtEnd(s.getTop());
									s.pop();
									tableauSize[src]++;
									i++;
								}
								cout << "\nERROR: ONLY KINGS CAN BE PLACED IN AN EMPTY COLUMN\n";
							}
						}
					}
					else {
						cout << "\nERROR: DESTINATION TABLEAU COLUMN IS OUT BOUND\n";
					}
				}
				else {
					cout << "\nERROR: SOURCE TABLEAU COLUMN IS EMPTY, NO CARD TO MOVE\n";
				}
			}
			else {
				cout << "\nERROR: SOURCE TABLEAU COLUMN IS OUT OF BOUND\n";
			}
		}
		else {
			cout << "\nERROR: NUM CARDS IS GREATER THAN CARDS IN SRC TABLEAU\n";
		}
	}

	// Function to move from wastepile to column
	void MoveWastepileToCol(int des) {
		if (!wastepile.isEmpty()) {			// If wastepile is not empty 
			Card tempWaste = wastepile.getTop();	
			if (des >= 0 && des < TABLEAU_COLS) {
				if (!tableau[des]->isEmpty()) {			// If tableau is not empty
					Card tempCol = tableau[des]->GetTail();		
					if (tempCol.checkRank(tempWaste)) {			// Check if ranks are compatible
						if (tempCol.checkColor(tempWaste)) {	// Check if colors are compatible
							List<Card>::Iterator itr = wastepile.PopElement();	// Perform movement operation through iterator
							tableau[des]->PushElement(itr);						// Without creation or deletion of node
							tableauSize[des]++;
							wastepileSize--;
							undoStack.push(Command("m", "w", "c" + to_string(des), 1));		// Update undo stack
						}
						else {
							cout << "\nERROR: SAME COLOR CARDS CANNOT BE INSERTED ON TOP OF EACH OTHER\n";
						}
					}
					else {
						cout << "\nERROR: WASTEPILE CARD RANK IS NOT 1 LESS THAN RANK OF TOP COLUMN CARD\n";
					}
				}
				else {	// if tableau is empty
					if (tempWaste.getRank() == "KING") {	// If wastepile card has a rank king
						List<Card>::Iterator itr = wastepile.PopElement();	// Perform movement operation through iterator
						tableau[des]->PushElement(itr);						// Without creation or deletion of node	
						tableauSize[des]++;
						wastepileSize--;
						undoStack.push(Command("m", "w", "c" + to_string(des), 1));	// Update undo stack
					}
					else {	// If wastepile card is not king
						cout << "\nERROR: ANY RANK OTHER THAN KING CANNOT BE INSERTED IN AN EMPTY COLUMN\n";
					}
				}
			}
			else {
				cout << "\nERROR: TABLEAU INDEX OUT OF BOUND\n";
			}
		}
		else {
			cout << "\nERROR: WASTEPILE HAS NO CARD\n";
		}
	}


	// Function to move card from wastepile to foundation
	void MoveWastepileToFoundation(int des) {
		if (!wastepile.isEmpty()) {			// Check if wastepile is not empty
			Card tempWaste = wastepile.getTop();	
			if (des >= 0 && des < FOUNDATION_COLS) {	    // Check if destination index is out of bound
				if (!foundations[des]->isEmpty()) {			// Check if foundation is not empty
					Card tempFound = foundations[des]->getTop();
					if (tempFound.checkSuit(tempWaste)) {		// Check if cards are having same suit
						if (tempFound.checkRankFound(tempWaste)) {		// Check if ranks of cards differ by 1
							List<Card>::Iterator itr = wastepile.PopElement();	// Perform movement operation through iterator
							foundations[des]->PushElement(itr);					// Without creation or deletion of node	
							wastepileSize--;
							foundationSize[des]++;
							undoStack.push(Command("m", "w", "f" + to_string(des), 1));	// Update undo stack
						}
						else {
							cout << "\nERROR: RANKS OF CARDS ARE NOT COMPATIBLE\n";
						}
					}
					else {
						cout << "\nERROR: CARDS DO NOT BELONG TO THE SAME SUIT\n";
					}
				}
				else {		// If foundation is empty
					if (tempWaste.getRank() == "ACE") {		// If wastepile has a top card of rank ace

						List<Card>::Iterator itr = wastepile.PopElement();	// Perform movement operation through iterator
						foundations[des]->PushElement(itr);					// Without creation or deletion of node	
						wastepileSize--;
						foundationSize[des]++;
						undoStack.push(Command("m", "w", "f" + to_string(des), 1));			// Update undo stack
					}
					else {
						cout << "\nERROR: ANY RANK OTHER THAN ACE CANNOT BE INSERTED IN AN EMPTY FOUNDATION\n";
					}
				}
			}
			else {
				cout << "ERROR: FOUNDATION INDEX OUT OF BOUND\n";
			}
		}
		else {
			cout << "\nERROR: WASTEPILE IS EMPTY, NO CARD TO MOVE\n";
		}
	}

	// This function moves card from foundation to tableau column
	void MoveFoundationToCol(int src, int des) {
		if (src >= 0 && src < FOUNDATION_COLS) {	 // Check if src index is out of bound
			if (!foundations[src]->isEmpty()) {		 // Check if foundation col is not empty
				if (des >= 0 && des < TABLEAU_COLS) {	 // Check if des index is out of bound
					if (!tableau[des]->isEmpty()) {		 // Check if des col is empty
						Card tempFound = foundations[src]->getTop();	
						Card tempCol = tableau[des]->GetTail();		
						if (tempFound.checkColor(tempCol)) {			// Check if cards are of alternate color
							if (tempFound.checkRankFound(tempCol)) {	// Check if rank of cards differ by 1
								List<Card>::Iterator itr = foundations[src]->PopElement();	// Perform movement operation through iterator
								foundationSize[src]--;										// Without creation or deletion of node	
								tableau[des]->MoveFoundToCol(itr);
								tableauSize[des]++;
								undoStack.push(Command("m", "f" + to_string(src), "c" + to_string(des), 1));	// Update undo stack
							}
							else {
								cout << "\nERROR: RANK OF CARDS ARE NOT COMPATIBLE\n";
							}
						}
						else {
							cout << "\nERROR: CARDS ARE OF SAME COLOR\n";
						}
					}
					else {		// If tableau is empty
						Card tempFound = foundations[src]->getTop();
						if (tempFound.getRank() == "KING") {
							List<Card>::Iterator itr = foundations[src]->PopElement();	// Perform movement operation through iterator
							foundationSize[src]--;										// Without creation or deletion of node
							tableau[des]->MoveFoundToCol(itr);
							tableauSize[des]++;
							undoStack.push(Command("m", "f" + to_string(src), "c" + to_string(des), 1));	// Update undo stack
						}
						else {
							cout << "\nERROR: ONLY KING CAN BE PLACED IN EMPTY TABLEAU COL\n";
						}
					}
				}
				else {
					cout << "\nERROR: DESTINATION INDEX OUT OF BOUND\n";
				}
			}
			else {
				cout << "\nERROR: SOURCE FOUNDATION COL IS EMPTY\n";
			}
		}
		else {
			cout << "\nERROR: FOUNDATION COL INDEX OUT OF BOUND\n";
		}
	}

	// Function for move command
	void MoveCard(char* src, char* des, int numCards) {
		if (src[0] == 'c') {		// If source is column
			int colSrc = src[1] - '0';
			colSrc--;
			if (des[0] == 'f') {		// If destination is foundation
				int colDes = des[1] - '0';
				colDes--;
				if (numCards == 1) {		// If only 1 card has to move 
					MoveColToFoundation(colSrc, colDes);	
				}
				else {
					cout << "\nERROR: Cannot move more than one card to foundation at a time\n";
				}
			}
			else if (des[0] == 'c') {	// If destination is column
				int colDes = des[1] - '0';
				colDes--;
				MoveColToCol(colSrc, colDes, numCards);	
			}
			else {
				cout << "\nINVALID COMMAND DESTINATION\n";
			}
		}
		else if (src[0] == 'w') {	// If source is wastepile
			if (des[0] == 'c') {		// If destination is column
				int colDes = des[1] - '0';		// To convert char to int
				colDes--;
				if (numCards == 1) {		// If only 1 card has to move from wastepile to col
					MoveWastepileToCol(colDes);
				}
				else {
					cout << "\nERROR: CANNOT MOVE MORE THAN ONE CARD FROM WASTEPILE TO COLUMN\n";
				}
			}
			else if (des[0] == 'f') {	// If destination is foundation
				int colDes = des[1] - '0';		// Convert char to int
				colDes--;
				if (numCards == 1) {		// If only 1 card has to move from wastepile to foundation
					MoveWastepileToFoundation(colDes);
				}
				else {
					cout << "\nERROR: CANNOT MOVE MORE THAN ONE CARD FROM WASTEPILE TO FOUNDATION\n";
				}
			}
			else {
				cout << "\nINVALID COMMAND DESTINATION\n";
			}
		}
		else if (src[0] == 'f') {		// If source is foundation
			int colSrc = src[1] - '0';
			colSrc--;
			if (des[0] == 'c') {	// If destination is column
				int colDes = des[1] - '0';
				colDes--;
				if (numCards == 1) {	// Only 1 card can be moved from foundation to column at a time
					MoveFoundationToCol(colSrc, colDes);
				}
				else {
					cout << "\nERROR: CANNOT MOVE MORE THAN ONE CARD FROM FOUNDATION TO TABLEAU\n";
				}
			}
			else {
				cout << "\nINVALID COMMAND DESTINATION\n";
			}
		}
		else {
			cout << "\nINVALID COMMAND SOURCE TYPE\n";
		}
	}

	// Function to parse command
	int ParseCommand(string cmd) {

		for (int i = 0; i < cmd.length(); i++) {	//This loop takes care of case sensitivity
			cmd[i] = tolower(cmd[i]);
		}

		if (cmd[0] == 's') {	// Draw a card from stockpile to wastepile
			if (cmd.length() > 1) {
				cout << "\nERROR: INVALID COMMAND FORMAT \n";
				return 0;
			}

			DrawCard();
			return 1;
		}
		else if (cmd[0] == 'm') {	// Move a card

			size_t firstComma = cmd.find(',');
			size_t secondComma = cmd.find(',', firstComma + 1);
			size_t thirdComma = cmd.find(',', secondComma + 1);

			if (firstComma == string::npos || secondComma == string::npos || thirdComma == string::npos) {
				cout << "\nERROR: INVALID COMMAND FORMAT\n";
				return 0;
			}

			int index = 0;
			while (cmd[index] != ',' && cmd[index] != ' ') {	// Loop to incr index to source and skip cmd
				index++;
			}
			index++;

			int srcIndex = 0;
			char src[4];
			for (; cmd[index] != ',' && cmd[index] != '\0'; index++) {	// Storing source
				src[srcIndex++] = cmd[index];
			}
			index++;
			src[srcIndex] = '\0';

			int desIndex = 0;
			char des[4];
			for (; cmd[index] != '\0' && cmd[index] != ','; index++) {	// Storing destination
				des[desIndex++] = cmd[index];
			}
			index++;
			des[desIndex] = '\0';

			int numberOfCards = 0;
			for (; cmd[index] != ' ' && cmd[index] != '\0';) {	// Storing total number of cards to move
				numberOfCards = numberOfCards * 10 + (cmd[index++] - '0');	// Converting num of cards from char to int
			}

			MoveCard(src, des, numberOfCards);
			return 1;
		}
		else if (cmd[0] == 'z') {	// Undo last operation
			if (cmd.length() > 1) {
				cout << "\nERROR: INVALID COMMAND FORMAT\n";
				return 0;
			}
			Undo();
			return 1;
		}		
		else if (cmd[0] == 'e') {		// To end game
			if (cmd.length() > 1) {
				cout << "\nERROR: INVALID COMMAND FORMAT\n";
				return 0;
			}
			return 2;
		}
		else {
			cout << "\nINVALID COMMAND ENTERED\n";
			return 0;
		}
	}

	// Function for draw command
	void DrawCard() {
		if (!stock.isEmpty()) {		// If stock is not empty
			List<Card>::Iterator itr = stock.PopElement();
			wastepile.PushElement(itr);
			wastepileSize++;
			stockSize--;
			undoStack.push(Command("s", "", "", 1));	// Storing commands in undostack
		}
		else {	    // All cards from wastepile will be popped and pushed into stock
			while (wastepileSize != 0) {
				List<Card>::Iterator itr = wastepile.PopElement();
				stock.PushElement(itr);
				wastepileSize--;
				stockSize++;
			}
			undoStack.push(Command("w", "", "", 1));
		}
	}

	// This function undo the last command
	void Undo() {
		if (!undoStack.isEmpty()) {		// Check if there are moves to undo
			Command cmd = undoStack.getTop();
			undoStack.pop();

			string CmdType = cmd.cmdType;
			string src = cmd.src;
			string des = cmd.des;
			int numCards = cmd.num;

			if (CmdType == "m") {		// If command is move
				if (src[0] == 'c') {	// If src is col
					int srcIndex = src[1] - '0';
					if (des[0] == 'f') {	// If des is foundation
						int desIndex = des[1] - '0';

						undoColToFound(srcIndex, desIndex);
					}
					else if (des[0] == 'c') {
						int desIndex = des[1] - '0';

						undoColToCol(srcIndex, desIndex, numCards);
					}
				}
				else if (src[0] == 'w') {	// If source is wastepile
					if (des[0] == 'c') {	// If des is col
						int desIndex = des[1] - '0';

						undoWastepileToCol(desIndex);
					}
					else if (des[0] == 'f') {	// If des is foundation
						int desIndex = des[1] - '0';

						undoWastepileToFoundation(desIndex);
					}
				}
				else if (src[0] == 'f') {	// If src is foundation	
					int srcIndex = src[1] - '0';
					if (des[0] == 'c') {	// If des is col
						int desIndex = des[1] - '0';

						undoFoundationToCol(srcIndex, desIndex);
					}
				}
			}
			else if (CmdType[0] == 's') {	// Command is undo
				undoDraw();
			}
		}
		else {
			cout << "\nNO MOVES TO UNDO\n";
		}
	}

	// This function undo the draw move
	void undoDraw() {
		if (wastepileSize != 0) {
			List<Card>::Iterator itr = wastepile.PopElement();
			stock.PushElement(itr);
			wastepileSize--;
			stockSize++;
		}
	}

	// This function unod the move from col to foundation
	void undoColToFound(int src, int des) {
		if (flips[src] == 1) {		// If last top card was hidden before
			tableau[src]->showTopCard2();	// Hide prev card
			List<Card>::Iterator itr = foundations[des]->PopElement();
			tableau[src]->MoveFoundToCol(itr);
			tableauSize[src]++;
			foundationSize[des]--;
		}
		else {
			List<Card>::Iterator itr = foundations[des]->PopElement();
			tableau[src]->MoveFoundToCol(itr);
			tableauSize[src]++;
			foundationSize[des]--;
		}
	}

	// This function undo the move from col to col
	void undoColToCol(int src, int des, int num) {
		if (flips[src] == 1) {		// If last top card was hidden before 
			tableau[src]->showTopCard2();		// Hide prev card
			List<Card>::Iterator itr = tableau[des]->ExtractList(num);
			tableau[src]->AppendList(itr, num);
			tableauSize[src] += num;
			tableauSize[des] -= num;
		}
		else {
			List<Card>::Iterator itr = tableau[des]->ExtractList(num);
			tableau[src]->AppendList(itr, num);
			tableauSize[src] += num;
			tableauSize[des] -= num;
		}
	}

	// This function undo the move from wastepile to col
	void undoWastepileToCol(int des) {
		List<Card>::Iterator itr = tableau[des]->Remove();
		wastepile.PushElement(itr);
		wastepileSize++;
		tableauSize[des]--;
	}

	// This function undo the move from wastepile to foundation
	void undoWastepileToFoundation(int des) {
		List<Card>::Iterator itr = foundations[des]->PopElement();
		wastepile.PushElement(itr);
		foundationSize[des]--;
		wastepileSize++;
	}

	// This function undo the move from foundation to col
	void undoFoundationToCol(int src, int des) {
		List<Card>::Iterator itr = tableau[des]->PopElement();
		tableauSize[des]--;
		foundations[src]->PushElement(itr);
		foundationSize[src]++;
	}

	// This function checks game winning condition
	bool GameWon() {
		// If all foundations are filled
		if ((foundationSize[0] == 13) && (foundationSize[1] == 13) && (foundationSize[2] == 13) && (foundationSize[3] == 13)) {
			for (int i = 0; i < FOUNDATION_COLS; i++) {		// This loop checks if every top has a rank king 
				Card temp = foundations[i]->getTop();
				if (temp.getRank() != "KING") {	
					return false;
				}
			}
			return true;
		}
		return false;
	}

	// This function displays welcome banner
	void WelcomeBanner() {
		cout << "\t\t\t\t";
		cout << "*********************************************************\n";
		cout << "\t\t\t\t";
		cout << "*                                                       *\n";
		cout << "\t\t\t\t";
		cout << "*              WELCOME TO SOLITAIRE!                    *\n";
		cout << "\t\t\t\t";
		cout << "*                                                       *\n";
		cout << "\t\t\t\t";
		cout << "*********************************************************\n";
		cout << "\t\t\t\t";
		cout << "*        S    O    L    I    T    A    I    R    E      *\n";
		cout << "\t\t\t\t";
		cout << "*        |    |    |    |    |    |    |    |    |      *\n";
		cout << "\t\t\t\t";
		cout << "*        S----O----L----I----T----A----I----R----E      *\n";
		cout << "\t\t\t\t";
		cout << "*                                                       *\n";
		cout << "\t\t\t\t";
		cout << "*********************************************************\n";
		cout << endl;
	}

	// This function displays game won banner
	void Prize() {
		cout << "\t\t\t\t";
		cout << "****************************************************************\n";
		cout << "\t\t\t\t";
		cout << "*                                                              *\n";
		cout << "\t\t\t\t";
		cout << "*                      YAAAY! YOU HAVE WON!                    *\n";
		cout << "\t\t\t\t";
		cout << "*                         |   |   |                            *\n";
		cout << "\t\t\t\t";
		cout << "*                         |   |   |                            *\n";
		cout << "\t\t\t\t";
		cout << "*                         |   |   |                            *\n";
		cout << "\t\t\t\t";
		cout << "*                THANK YOU FOR PLAYING SOLITAIRE!              *\n";
		cout << "\t\t\t\t";
		cout << "*                                                              *\n";
		cout << "\t\t\t\t";
		cout << "****************************************************************\n";
		cout << endl;
	}

	// This function displays game over banner
	void GameOver() {
		cout << "\n\n\t\t\t\t";
		cout << "=============================================================\n";
		cout << "\t\t\t\t";
		cout << "   ____                         ___                        \n";
		cout << "\t\t\t\t";
		cout << "  / ___| __ _ _ __ ___   ___    / _ \\__   _____ _ __        \n";
		cout << "\t\t\t\t";
		cout << " | |  _ / _` | '_ ` _ \\ / _ \\  | | | \\ \\ / / _ \\ '__|       \n";
		cout << "\t\t\t\t";
		cout << " | |_| | (_| | | | | | |  __/  | |_| |\\ V /  __/ |          \n";
		cout << "\t\t\t\t";
		cout << "  \\____|\\__,_|_| |_| |_|\\___|   \\___/  \\_/ \\___|_|          \n";
		cout << "\t\t\t\t";
		cout << "                                                           \n";
		cout << "\t\t\t\t";
		cout << "               THANK YOU FOR PLAYING SOLITAIRE!             \n";
		cout << "\t\t\t\t";
		cout << "=============================================================\n";
	}

	// This function is to control entire game
	void PlayGame() {
		bool gameOver = 0;
		WelcomeBanner();
		display();
		while ( !GameWon() && gameOver != 1) {
			cout << "\n\nENTER COMMAND 's' FOR DRAW, 'z' FOR UNDO, 'm' FOR MOVE (cmd,src,des,numOfCards) AND 'e' TO END GAME:\t";
			string cmd;
			getline(cin, cmd);
			int c = ParseCommand(cmd);
			if (c == 0) {		// Invalid Command
				cout << "\n PLEASE ENTER CORRECT COMMAND\n";
			}
			else if (c == 1) {	// Successfully done operation
				cout << endl << endl;
				display();
			}
			else {		// Game Over/Quit Game
				GameOver();
				gameOver = 1;
			}
		}

		if (GameWon()) {
			Prize();
		}
	}

	~Game() {
		for (int i = 0; i < TABLEAU_COLS; i++) {
			delete tableau[i];
		}
		for (int i = 0; i < FOUNDATION_COLS; i++) {
			delete foundations[i];
		}
	}

};

int main() {
	Game g1;
	g1.PlayGame();

	system("pause");
	return 0;
}

