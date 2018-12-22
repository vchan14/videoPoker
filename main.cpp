#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

void deal(vector<unsigned int> &cardNumber);
void adjustDeal(vector<unsigned int> &cardNumber);
void partitionSuits(vector<unsigned int> &cardNumber, unsigned int suit[4]);
void partitionFaceValue(vector<unsigned int> &cardNumber, unsigned int faceValue[13] );
void displayCard(vector <unsigned int> &cardNumber, string cardName[52], string title);
void display(vector<unsigned int> &cardNumber, unsigned int suits[4], unsigned int faceValue[13], string cardNames[52]);
void reset(vector<unsigned int> &cardNumber, unsigned int suits[4], unsigned int faceValue[13]);
void loadCardNames(string cardNames[52]);
void displayScore(unsigned int suit[4], unsigned int faceValue[13]);
void getName(string & name, double & coin);
void amountBet(int  &bet);
void checkScore(unsigned int suit[4], unsigned int faceValue[13], double & coin, int bet);
void getCoin(double & coin);

bool again();
bool onePair(unsigned int suit[4], unsigned int faceValue[13]);
bool twoPair(unsigned int suit[4], unsigned int faceValue[13]);
bool threeOfAKind(unsigned int suit[4], unsigned int faceValue[13]);
bool straight(unsigned int suit[4], unsigned int faceValue[13]);
bool flush(unsigned int suit[4], unsigned int faceValue[13]);
bool fullHouse(unsigned int suit[4], unsigned int faceValue[13]);
bool fourOfAKind(unsigned int suit[4], unsigned int faceValue[13]);
bool striaghtFlush(unsigned int suit[4], unsigned int faceValue[13]);
bool royalFlush(unsigned int suit[4], unsigned int faceValue[13]);





int main(int argc, char *argv[])
{


    string fullCardName[52];
    vector<unsigned int> cardNumber;
    unsigned int suits[4];
    unsigned int faceValue[13];
    string name;
    double coin = 0;
    int bet = 0 ;
    srand(time(NULL));
    ofstream file;

    //Check if he/she is a new or current customer
    getName(name, coin);

    //Ask for amount of bet in each game
    amountBet(bet);


    while(again())
    {
        loadCardNames(fullCardName);
        reset(cardNumber,suits,faceValue);

        // deal the initial hand and show it
        deal(cardNumber);
        displayCard(cardNumber, fullCardName, "Initial");

        // ask user if they want to discard any cards and show final card
        adjustDeal(cardNumber);
        displayCard(cardNumber, fullCardName, "Final");

        //bin sorts of FaceValue and PartitionSuit
        partitionFaceValue(cardNumber, faceValue);
        partitionSuits(cardNumber, suits);

        //Evaluate the hand of the customer
        checkScore(suits, faceValue, coin, bet);

    }

    // After the game, write his/her name and coin into txt file for future record
    cout<<"Thank you! "<<name<<" Please Come Again Soon."<<endl;
    file.open(name+".game");
    file<<name<<' '<<coin;

    return 0;
}

void getName(string & name, double & coin)
{
    ifstream in;
    ofstream out;
    string line, temp;
    stringstream ss;
    vector <string> list;


    cout<<"What is your name?"<<endl;
    cin>>name;
    in.open(name+".game");
    // if they are old customer
    if(in.good())
    {
        in>>name>>coin;
        cout<<"Welcome Back! "<<name<<endl;
        cout<<"Your current coin from last game is "<<coin<<endl;

    }

    // if they are new customer
    if(in.fail())
    {
        cout<<"Welcome to our CS2 Casino!!!"<<endl;
        getCoin(coin);
    }
}

void getCoin(double & coin)
{
    cout<<"How much coin do you want to put?"<<endl;
    cin>>coin;
}


void amountBet(int &bet)
{
    cout<<"How much do you want to bet? between 1 to 50 coins."<<endl;
    cin>>bet;
}

void loadCardNames(string cardNames[52])
{
    string suit[4] = {"Hearts", "Clubs","Diamonds", "Spades"},
    faceValue[13] = {"Ace", "Two", "Three", "Four", "Five",
        "Six", "Seven", "Eight","Nine","Ten",
        "Jack","Queen", "King"};
    for(unsigned int i = 0; i < 4; ++i) //All of the suits
        for(unsigned int j = 0; j < 13; ++j)//All of the face values
            cardNames[i*13 + j] = faceValue[j] + " of " + suit[i];
}

void reset(vector<unsigned int> &cardNumber, unsigned int suits[4], unsigned int faceValue[13])
{
    cardNumber.clear();
    for(unsigned i = 0; i < 4; ++i)
        suits[i] = 0;
    for(unsigned i = 0; i < 13; ++i)
        faceValue[i] = 0;
}

void deal(vector<unsigned int> &cardNumber)
{
    cardNumber.push_back(rand()%52);
    int temp=0;


    // Need 4 more cards
    for(unsigned int i = 0; i < 4; ++i)
    {
        int safe = 1;
        while(safe)
        {
            safe = 0;

            //generate the next random number
            temp = rand()%52;

            // From 0 -> cardNumber.size() check if there is a duplicate
            for(int j=0; j < cardNumber.size(); ++j)
            {
                //If the card is duplicate, do the while loop again;
                if(temp == cardNumber[j])
                {
                    safe = 1;
                    break;
                }
            }
        }
        //if the card is not duplicate push it into the cardNumber

        cardNumber.push_back(temp);
    }
}

void displayCard(vector <unsigned int> &cardNumber, string cardName[52], string title)
{
    cout<<endl<<"Your "<<title<< " card in words were: "<<endl;
    for(int i = 0; i < cardNumber.size(); ++i)
        cout<<'('<<(i+1)<<')'<<cardName[cardNumber[i]]<<endl;

}

void adjustDeal(vector<unsigned int> &cardNumber)
{
    string str1;
    stringstream ss;
    int temp;
    vector <int> changeNumber;

    cout<<endl<<"What card numbers you want to change? eg: 3 2 5 or 'n' if you don't want to change any cards. ";
    getline(cin, str1);
    ss<<str1;

    while (ss>>temp)
    {
        changeNumber.push_back(temp);
    }

    {
        for(int i = 0; i < changeNumber.size(); i++)
        {
            int safe = 1;
            while(safe)
            {
                safe = 0;
                //generate the next random number
                temp = rand()%52;
                // From 0 -> cardNumber.size() check if there is a duplicate
                for(int j=0; j < cardNumber.size(); j++)
                {
                    //If the card is duplicate, do the while loop again;
                    if(temp == cardNumber[j])
                    {
                        safe = 1;
                        break;
                    }
                }
            }
            //if the card is not duplicate push it into the cardNumber
            cardNumber[changeNumber[i]-1] = temp;
        }
    }
}



void partitionSuits(vector<unsigned int> &cardNumber, unsigned int suit[4])
{
    for(unsigned i = 0; i < cardNumber.size(); ++i)
        ++suit[cardNumber[i]/13];
}

void partitionFaceValue(vector<unsigned int> &cardNumber, unsigned int faceValue[13] )
{
    for(unsigned i = 0; i < cardNumber.size(); ++i)
        ++faceValue[cardNumber[i]%13];
}


void display(vector<unsigned int> &cardNumber, unsigned int suits[4], unsigned int faceValue[13], string cardNames[52])
{
    static string suit[4] = {"Hearts", "Clubs", "Diamonds", "Spades"};
    static string face[13] = {"Ace", "Two", "Three",
        "Four", "Five", "Six",
        "Seven", "Eight", "Nine",
        "Ten", "Jack", "Queen", "King"};
    cout<<"Your cardNumber were: "<<endl;
    for(unsigned int i = 0; i < cardNumber.size(); ++i)
        cout<<setw(3)<<cardNumber[i];

    cout<<endl<<"Your cardNumber in words were: "<<endl;
    for(unsigned int i = 0; i < cardNumber.size(); ++i)
        cout<<'('<<(i+1)<<')'<<cardNames[cardNumber[i]]<<endl;

    cout<<endl<<"Which means that the suits you have are: "<<endl;
    for(unsigned int i = 0; i < 4; ++i)
        if(suits[i] > 0)
            cout<<suits[i]<<" "<<suit[i]<<endl;
    cout<<endl<<"Which means that the face values you have are: "<<endl;
    for(unsigned int i = 0; i < 13; ++i)
        if(faceValue[i] > 0)
            cout<<faceValue[i]<<" "<<face[i]<<endl;
    cout<<endl;
}

bool onePair(unsigned int suit[4], unsigned int faceValue[13])
{
    for(int i=0 ; i< 13 ; i++)
    {
        if(faceValue[i] == 2)
        {
            return true;
        }
        else
        {
            continue;
        }

    }
    return false;
}

bool twoPair(unsigned suit[4], unsigned faceValue[13])
{
    int result = 0;
    for(int i=0 ; i< 13 ; i++)
    {
        if(faceValue[i] == 2)
        {   // add 1 to result when there is a pair
            ++result;
        }
        else
        {
            continue;
        }

    }

    // if the result are 1, it means there are twoPair
    if (result == 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool threeOfAKind(unsigned int suit[4], unsigned int faceValue[13])
{
    for(int i=0 ; i< 13 ; i++)
    {
        if(faceValue[i] == 3)
        {
            return true;
        }
        else
        {
            continue;
        }

    }
    return false;
}

bool straight(unsigned int suit[4], unsigned int faceValue[13])
{
    // pos- location of the first value of the striaght
    int pos = 0;

    // identify the start of the striaght
    for(int k=0; k<13; ++k)
    {
        if(faceValue[k] == 1)
        {
            pos = k;

        }
        else
        {
            continue;
        }
        break;
    }

    // check if the position is 0 or not, if it is, there is a chance it is a royal striaght
    if(pos == 0)
    {
        if(faceValue[pos] == faceValue[9] && faceValue[pos] == faceValue[10] && faceValue[pos] == faceValue[11] && faceValue[pos] == faceValue[12] && faceValue[pos] == 1)
        {
            return true;
        }
    }

    // check the rest cases, if there is any strighat
    if(pos >=0)
    {

        if(faceValue[pos] == faceValue[pos+1] && faceValue[pos] == faceValue[pos+2] && faceValue[pos] == faceValue[pos+3] && faceValue[pos] == faceValue[pos+4] && faceValue[pos] == 1)
        {
            return true;
        }

        else
        {
            return false;
        }

    }
    else
    {
        return false;
    }

}

bool flush(unsigned int suit[4], unsigned int faceValue[13])
{
    for(int i=0; i<4; ++i)
    {   //check if any suit bin has value 5
        if(suit[i] == 5)
        {
            return true;
        }
        else
        {
            continue;
        }

    }
    return false;
}

bool fullHouse(unsigned int suit[4], unsigned int faceValue[13])
{
    //check for a pair
    if(onePair(suit, faceValue))
    {
        for(int i=0; i<13; ++i)
        {
            //check for three of a kind
            if(faceValue[i] == 3)
            {
                return true;
            }
            else{
                continue;
            }
        }
    }
    return false;
}

bool fourOfAKind(unsigned int suit[4], unsigned int faceValue[13])
{
    // go through all bins in faceValue to check if any bin equal to 4
    for(int i=0; i<13; ++i)
    {
        if(faceValue[i] == 4)
        {
            return true;
        }
        else
        {
            continue;
        }
    }
    return false;
}

bool striaghtFlush(unsigned int suit[4], unsigned int faceValue[13])
{   //check for striaght
    if(straight(suit, faceValue))
    {
        //check for flush
        if(flush(suit,faceValue))
        {
            return true;
        }

    }
    return false;
}
bool royalFlush(unsigned int suit[4], unsigned int faceValue[13])
{
    if(flush(suit,faceValue))
    {   //This the only case that Royal flush can occr
        if(faceValue[0] == faceValue [12] && faceValue[0] == faceValue [11] && faceValue[0] == faceValue [10] &&
           faceValue[0] == faceValue [9] && faceValue[0] == 1)
        {
            return true;
        }

    }
    return false;
}


bool again()
{
    char ans;
    cout<<"Do you want to continue playing? ";
    cin>>ans;
    cin.ignore(255,'\n');
    return toupper(ans) == 'Y';
}

void checkScore(unsigned int suit[4], unsigned int faceValue[13], double & coin, int bet)
{
    double winCoin = 0;
    cout<<endl<<"Your hand has : ";
    if(royalFlush(suit, faceValue))
    {
        cout<<"Royal Flush";
        winCoin = 400 * bet;
    }
    else if(striaghtFlush(suit, faceValue))
    {
        cout<<"Striaght Flush";
        winCoin = 50 * bet;

    }
    else if(fourOfAKind(suit, faceValue))
    {
        cout<<"Four of A Kind";
        winCoin = 25 * bet;
    }
    else if(fullHouse(suit, faceValue))
    {
        cout<<"Full House";
        winCoin = 8 * bet;
    }
    else if(flush(suit, faceValue))
    {
        cout<<"A Flush";
        winCoin = 5 * bet;
    }
    else if(straight(suit, faceValue))
    {
        cout<<"Striaght ";
        winCoin = 4 * bet;
    }
    else if(threeOfAKind(suit, faceValue))
    {
        cout<<"Three of A Kind";
        winCoin = 3 * bet;
    }
    else if(twoPair(suit, faceValue))
    {
        cout<<"Two Pair";
        winCoin = 2 * bet;
    }
    else if(onePair(suit, faceValue))
    {
        cout<<"One Pair ";
        winCoin = 1 * bet;
    }
    else
    {
        cout<<"Nothing";
        winCoin = 0 * bet;
    }
    cout<<endl;

    cout<<"You won: "<<winCoin<<endl;
    cout<<"Your bet cost: "<<bet<<endl;


    coin = coin + winCoin - bet;
    cout<<"You current Coin is : $"<<coin<<endl;
    if(coin < bet)
    {
        cout<<"Sorry but you don't have enough coin to continue! Please add more coins."<<endl;
        getCoin(coin);
    }
}



