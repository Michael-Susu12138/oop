// this file contains the prototypes for the class polynomial
// @author: Michael Chen
// @date: 12/04/2022

#ifndef polynomial_h
#define polynomial_h

#include <iostream>
#include <string>
#include <vector>

class Polynomial{
    friend std::ostream& operator<<(std::ostream&,const Polynomial&);
    friend bool operator==(const Polynomial&, const Polynomial&);
public:
    struct Node{
        Node(double,Node*);
        double data;
        Node* next;
    };
    Polynomial();
    Polynomial(const std::vector<double>);
    Polynomial(const Polynomial&);
    Polynomial& operator=(const Polynomial&);
    ~Polynomial();
    Polynomial& operator+=(const Polynomial&);
    double evaluate(double) const;
    
    // test purposes
    size_t size() const;
private:
    Node* header;
    size_t degree;
    void simplifyZeros(Polynomial&);
};

Polynomial operator+(const Polynomial&, const Polynomial&);
bool operator!=(const Polynomial&, const Polynomial&);


#endif /* polynomial_h */
