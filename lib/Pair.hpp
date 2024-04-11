#include <stdexcept>
#include <initializer_list>

// empty constructor 
// normal constructor 
// initializer list 
// konstruktor kopiujący 
// przypisanie copy-swap 
// konstruktor przenoszący 
// przypisanie przenoszące 


namespace duo 
{
    template <typename L, typename R>
    class Pair {
    private:
        L left;
        R right

    public:
        Pair()
            : left(), right()
        {}
        // empty constructor

        Pair(L _left, R _right) 
            : left(_left), right(_right)
        {}
        // normal constructor

        Pair(std::initializer_list<L> initList)
            : left(initList[0]), right(initList[1])
        {}
        // initializer list

        Pair(const Pair<L, R>& other)
            : left(other.left), right(other.right)
        {}
        // copy constructor

        Pair& operator=(const Pair<L, R>& other)
        {
            left = other.left;
            right = other.right;
            return *this;
        }
        // copy-swap

        Pair(Pair<L, R>&& other)
        {
            left = other.left;
            right = other.right;
            other.left = nullptr;
            other.right = nullptr;
        }
        // move constructor

        Pair& operator=(Pair<L, R>&& other)
        {
            left = other.left;
            right = other.right;
            other.left = nullptr;
            other.right = nullptr;
            return *this;
        }
        // move assignment

        ~Pair()
        {
            delete left;
            delete right;
        }

        void setLeft(L newLeft) {
            left = newLeft;
        }
        void setRight(R newRight) {
            right = newRight;
        }
        void setBoth(L newLeft, R newRight) {
            left = newLeft;
            right = newRight;
        }

        L getLeft() {
            return left;
        }

        R getRight() {
            return right;
        }

        void print(std::ostream& os) const
        {
            os << left << " : " << right;
        }

    };

    template <typename L, typename R>
    std::ostream& operator<<(std::ostream& os, const Pair<L, R>& pair)
    {
        pair.print(os);
        return os;
    }
}