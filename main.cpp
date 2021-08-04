#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Card {
public:
    enum rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
    enum suit {CLUBS, DIAMONDS, HEARTS, SPADES};

    Card(rank r = ACE, suit s = SPADES, bool ifu = true);
    int GetValue() const;
    void Flip();

private:
    rank m_Rank;
    suit m_Suit;
    bool m_IsFaceUp;

    friend ostream& operator<<(ostream& os, const Card& aCard);
};

Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu)
{}

int Card::GetValue() const {
    int value = 0;
    if (m_IsFaceUp) {
        value = m_Rank;
        if (value > 10) {
            value = 10;
        }
    }
    return value;
}

void Card::Flip() {
    m_IsFaceUp = !(m_IsFaceUp);


}

ostream& operator<<(ostream& os, const Card& aCard)
{
    const string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
    const string SUITS[] = { "c", "d", "h", "s" };
        if (aCard.m_IsFaceUp) {
        os << RANKS[aCard.m_Rank] << SUITS[aCard.m_Suit];
    }
    else {
        os << "XX";
    }

    return os;
}


class Hand {
protected:
    vector<Card*> m_Cards;
public:
    Hand();
    virtual ~Hand(); // ����������� ����������
    void Clear(); // ��������� ����� � ���� ������� ���� �� ����
    int GetTotal() const; //�������� ����� ����� ���� � ����, ���������� ���� �������� 1 ��� 11 � ����������� �� ��������
    void addCard(Card* pCard) {
    m_Cards.push_back(pCard);
    }
};

Hand::Hand()
{
    m_Cards.reserve(7);
}
Hand::~Hand()//���������� ��-�������� ����������� ��� ��� ����� �� ����������
{
    Clear();
}

void Hand::Clear() {
    vector<Card*>::iterator iter = m_Cards.begin();//�������� �� �������, ���������� ��� ������ � ����
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
        delete *iter;
        *iter = 0;
    }
    m_Cards.clear();//������� ������ ����������
}

int Hand::GetTotal() const {
    if (m_Cards.empty()) {
        return 0;//���� ���� � ���� ���, ���������� �������� 0
    }
    if (m_Cards[0]->GetValue() == 0) {//���� ������ ����� ����� �������� 0, �� ��� ����� �������� �����: ������� �������� 0
        return 0;
    }
    int total = 0;//������� ����� ����� ���� ����, ������ ��� ���� 1 ����
    vector<Card*>::const_iterator iter;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
        total += (*iter)->GetValue();
    }
    bool containsAce = false;//����������, ������ �� ���� ���
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
        if ((*iter)->GetValue() == Card::ACE) {
            containsAce = true;
        }
    }
    if (containsAce && total <= 11) { // ���� ���� ������ ��� � ����� �������� ���������, ��� ���� 11 �����
        total += 10;//��������� ������ 10 �����, ��������� �� ��� �������� �� ������ ��� �� ������ ����
    }
    return total;
}

class GenericPlayer : public Hand
{
    friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);

public:
    GenericPlayer(const string& name = "");
    virtual ~GenericPlayer();
    virtual bool IsHitting() const = 0;
    bool IsBusted() const;
    void Bust() const;

protected:
    string m_Name;
};

GenericPlayer::GenericPlayer(const string& name): m_Name(name){
}
GenericPlayer::~GenericPlayer() {
}

bool GenericPlayer::IsBusted() const {
    return (GetTotal() > 21);
}

void GenericPlayer::Bust() const {
    cout << m_Name << " busts.\n";
}

ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer) {
    os << aGenericPlayer.m_Name << ":\t";
    vector<Card*>::const_iterator pCard;
    if (!aGenericPlayer.m_Cards.empty()) {
        for (pCard = aGenericPlayer.m_Cards.begin();
             pCard != aGenericPlayer.m_Cards.end();
             ++pCard) {
            os << *(*pCard) << "\t";
        }
        if (aGenericPlayer.GetTotal() != 0) {
            cout << "(" << aGenericPlayer.GetTotal() << ")";
        }
    }
    else {
        os << "<empty>";
    }
    return os;
}

class Player : public GenericPlayer
{
public:
    Player(const string& name = "");

    virtual ~Player();
    virtual bool IsHitting() const;// ����������, ����� �� ����� ���������� ����� �����
    void Win() const;// ���������, ��� ����� �������
    void Lose() const;// ���������, ��� ����� ��������
    void Push() const;// ��������� �����
};

bool Player::IsHitting() const {
    cout << m_Name << ", do you want a hit? (Y/N): ";
    char response;
    cin >> response;
    return (response == 'y' || response == 'Y');
}

void Player::Win() const {
    cout << m_Name << " wins.\n";
}

void Player::Lose() const {
    cout << m_Name << " loses.\n";
}

void Player::Push() const {
    cout << m_Name << " pushes.\n";
}

class House : public GenericPlayer {
public:
    House(const string& name = "House");

    virtual ~House();
    virtual bool IsHitting() const; // ����������, ����� �� ����� ���������� ����� �����
    void FlipFirstCard(); // �������������� ������ �����
};

bool House::IsHitting() const {
    return (GetTotal() <= 16);
}

void House::FlipFirstCard() {
    if (!(m_Cards.empty())) {
        m_Cards[0]->Flip();
    }
    else {
        cout << "No card to flip!\n";
    }
}



int main()
{
cout << "\t\tWelcome to Blackjack!\n\n";

    int numPlayers = 0;
    while (numPlayers < 1 || numPlayers > 7)
    {
        cout << "How many players? (1 - 7): ";
        cin >> numPlayers;
    }

    vector<string> names;
    string name;
    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "Enter player name: ";
        cin >> name;
        names.push_back(name);
    }
    cout << endl;

    // ������� ����
  /*  Game aGame(names);
    char again = 'y';
    while (again != 'n' && again != 'N')
    {
        aGame.Play();
        cout << "\nDo you want to play again? (Y/N): ";
        cin >> again;
    }*/

    return 0;
}
