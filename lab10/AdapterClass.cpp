// figures: class adapter pattern
// Mikhail Nesterenko
// 11/7/2022

#include <iostream>
#include <string>

using std::cout; 
using std::endl;

// Target interface
class Square {
public:
   virtual void draw() const = 0;
   virtual ~Square() {}
};

// Adaptee/implementer
class LegacyRectangle {
public:
   LegacyRectangle(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY)
      : topLeftX_(topLeftX), topLeftY_(topLeftY),
        bottomRightX_(bottomRightX), bottomRightY_(bottomRightY) {}

   void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
      topLeftX_ = topLeftX;
      topLeftY_ = topLeftY;
      bottomRightX_ = bottomRightX;
      bottomRightY_ = bottomRightY;
   }

   int getTopLeftX() const { return topLeftX_; }
   int getTopLeftY() const { return topLeftY_; }
   int getBottomRightX() const { return bottomRightX_; }
   int getBottomRightY() const { return bottomRightY_; }

   void oldDraw() const {
      for (int i = 0; i < bottomRightY_; ++i) {
         for (int j = 0; j < bottomRightX_; ++j) {
            if (i >= topLeftY_ && j >= topLeftX_)
               cout << '*';
            else
               cout << ' ';
         }
         cout << endl;
      }
   }

private:
   int topLeftX_;
   int topLeftY_;
   int bottomRightX_;
   int bottomRightY_;
};

// Adapter uses multiple inheritance to inherit
// interface and implementation
class SquareAdapter : public Square, private LegacyRectangle {
public:
   SquareAdapter(int size) : LegacyRectangle(0, 0, size, size) {}
   void draw() const override {
      oldDraw();
   }
   int size() const{return getBottomRightX();}
   void resize(int newSize){
        move(0,0,newSize,size());
   }
};

int main() {
    std::cout << "Enter a number for the square: ";
    int userInput;
    std::cin >> userInput;
    SquareAdapter *square = new SquareAdapter(userInput);
   square->draw();

    std::cout << "Enter a number for resize: ";
    std::cin >> userInput;
    square->resize(userInput);
   square->draw();
   delete square;
}
