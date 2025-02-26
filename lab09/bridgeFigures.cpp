#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout; using std::endl; using std::cin;

// Abstract body
class Fill {
public:
    Fill(char borderChar, char internalChar) : borderChar_(borderChar), internalChar_(internalChar) {}
    virtual char getBorder() = 0;
    virtual char getInternal() = 0;
    virtual ~Fill() {}
protected:
    char borderChar_;
    char internalChar_;
};

// Concrete body: Hollow
class Hollow : public Fill {
public:
    Hollow(char borderChar) : Fill(borderChar, ' ') {}
    char getBorder() override { return borderChar_; }
    char getInternal() override { return ' '; }
    ~Hollow() override {}
};

// Concrete body: Filled
class Filled : public Fill {
public:
    Filled(char fillChar) : Fill(fillChar, fillChar) {}
    char getBorder() override { return borderChar_; }
    char getInternal() override { return internalChar_; }
    ~Filled() override {}
};

// Concrete body: FullyFilled
class FullyFilled : public Filled {
public:
    FullyFilled(char borderChar, char internalChar) : Filled(borderChar) {
        internalChar_ = internalChar; 
    }
};

// Concrete body: RandomFilled
class RandomFilled : public Fill {
public:
    RandomFilled(char char1, char char2) : Fill(char1, char2) { std::srand(std::time(0)); }
    char getBorder() override { return (std::rand() % 2 == 0) ? borderChar_ : internalChar_; }
    char getInternal() override { return (std::rand() % 2 == 0) ? borderChar_ : internalChar_; }
};

// Abstract handle
class Figure {
public:
    Figure(int size, Fill* fill) : size_(size), fill_(fill) {}
    virtual void draw() = 0;
    virtual ~Figure() {}
protected:
    int size_;
    Fill* fill_;
};

// Concrete handle: Square
class Square : public Figure {
public:
    Square(int size, Fill* fill) : Figure(size, fill) {}
    void draw() override;
};

void Square::draw() {
    for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j)
            if (i == 0 || j == 0 || i == size_ - 1 || j == size_ - 1)
                cout << fill_->getBorder();
            else
                cout << fill_->getInternal();
        cout << endl;
    }
}

int main() {
    // Create different fill patterns
    Fill* hollowPaint = new Hollow('#');
    Fill* filledPaint = new Filled('@');
    Fill* fullyFilledPaint = new FullyFilled('*', '+');
    Fill* randomFilledPaint = new RandomFilled('X', 'O');

    Figure* hollowSquare = new Square(6, hollowPaint);
    Figure* filledSquare = new Square(6, filledPaint);
    Figure* fullyFilledSquare = new Square(6, fullyFilledPaint);
    Figure* randomFilledSquare = new Square(6, randomFilledPaint);

    cout << "Hollow Square:" << endl;
    hollowSquare->draw();
    cout << endl;

    cout << "Filled Square:" << endl;
    filledSquare->draw();
    cout << endl;

    cout << "Fully Filled Square:" << endl;
    fullyFilledSquare->draw();
    cout << endl;

    cout << "Random Filled Square:" << endl;
    randomFilledSquare->draw();
    cout << endl;


}
