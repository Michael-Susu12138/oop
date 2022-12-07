// this file contanis all implementations for the class polynomial
// @author: Michael Chen
// @date: 12/04/2022

#include "polynomial.h"

using namespace std;

//implementations for the Polynomial class
//inner class Node implementations
Polynomial::Node::Node(double data,Node* next = nullptr):data(data),next(next){}

//default constructor
Polynomial::Polynomial():degree(0){
    header = new Node(0, new Node(0,nullptr));
}

// constructor
Polynomial::Polynomial(const vector<double> coefs): degree(coefs.size()-1){
    Node* local_ptr;
    header = new Node(0);   //create a new node on the heap as its header
    local_ptr = header;
    for(int item: coefs){
        local_ptr->next = new Node(item);   //looping through the vector and create new node on the heap
        local_ptr = local_ptr->next;
    }
    simplifyZeros(*this);  // remove the zeros in the linked list
}

//big three
// copy constructor
Polynomial::Polynomial(const Polynomial& rhs){
    //1. copy local fields
    //2. loop through the linked list
    header = new Node(0);                   //create new Node as a header
    Node* this_header = header;
    Node* rhs_header = rhs.header->next;    //copy everything from the Polynomial passed in
    degree = rhs.degree;
    while(rhs_header){ //last item
        this_header->next = new Node(rhs_header->data);     // copy the data over
        
        this_header = this_header->next;
        rhs_header = rhs_header ->next;
    }
}

// assignment operator
Polynomial& Polynomial::operator=(const Polynomial& rhs){
    //1. check for self assignment
    if(&rhs != this){
        //free up stuff on the heap
        freeMemory(header);
        //copy stuff over
        Node* this_header = header;
        Node* rhs_header = rhs.header->next;
        degree = rhs.degree;
        while(rhs_header){ //last item
            this_header->next = new Node(rhs_header->data);
            
            this_header = this_header->next;
            rhs_header = rhs_header ->next;
        }
    }
    return *this;
}

//destructor
Polynomial::~Polynomial(){
    freeMemory(header);
}

// operator overloading
// member operators:+=

// += member operator
Polynomial& Polynomial::operator+=(const Polynomial& rhs){
    Polynomial less_degree;
    size_t diff = 0; // difference in their degrees
    
    if(degree >= rhs.degree){
        diff = degree - rhs.degree; // if degree is greater than the one passed in
        less_degree = rhs;  // less degree is rhs
    }
    else if(degree < rhs.degree){
        diff = rhs.degree - degree;
        less_degree = *this;  // if degree is less than the one passed in
        *this = rhs; //less degree is *this so we need to swap
    }
    Node* this_ptr = header->next; //skip header
    Node* less_ptr = less_degree.header->next; //skip header
    while(diff){
        this_ptr = this_ptr->next; //loop diff, and locate to the same position as the less degree one
        --diff;
    }
    while(this_ptr && less_ptr){          //add up the data
        this_ptr->data += less_ptr->data;
        this_ptr = this_ptr -> next;
        less_ptr = less_ptr ->next;
    }
    
    // *this = result
    //get rid of zeros
    simplifyZeros(*this);
    
    return *this;
}


// non-member operators: +, ==, !=

// + non-member operator
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial return_val(lhs); // calling the += operator
    return_val += rhs;
    return return_val;
}

// == non-member operator
bool operator==(const Polynomial& lhs, const Polynomial& rhs){
    if(lhs.degree == rhs.degree){ // if the degree is the same, loop;otherwise, return false
        Polynomial::Node* lhs_ptr = lhs.header ->next;
        Polynomial::Node* rhs_ptr = rhs.header ->next;
        while(lhs_ptr && rhs_ptr){
            if(lhs_ptr->data != rhs_ptr->data){ // loop both linked list and compare values
                return false;                      // if not the same, return false
            }
            lhs_ptr = lhs_ptr ->next;
            rhs_ptr = rhs_ptr ->next;
        }
        return true;
    }
    
    return false;
    
}

// != non-member operator
bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
    return !(lhs==rhs);     // negation of the "==" operator
}


//output operator
ostream& operator<<(ostream& os,const Polynomial& rhs){
    // simplify the polynomials (reduce the zero coefficients)
    Polynomial::Node* local_ptr = rhs.header->next;
    size_t local_degree = rhs.degree;

    while(local_ptr){
        double local_data = local_ptr->data;
        if(local_data != 0){
            //if coef == 1
            // highest polynomial does not need plus sign
            if(local_degree != rhs.degree){
                os << " + ";
            }
            if(local_data == 1){
                // 1. degree == 0
                // 2. degree == 1
                // 3. else:
                if(local_degree == 0){
                    os << 1;
                }
                else if (local_degree == 1){
                    os << 'x';
                }
                else{
                    os << "x^" << local_degree;
                }
            }
            // if the coef == -1
            else if(local_data == -1){
                // 1. degree == 0
                // 2. degree == 1
                // 3. else:
                if(local_degree == 0){
                    os << -1;
                }
                else if(local_degree == 1){
                    os << "-x";
                }
                else {
                    os << "-x^" << local_degree;
                }
            }
            else{
                // 1. degree == 0
                // 2. degree == 1
                // 3. else:
                if(local_degree == 0){
                    os << local_data;
                }
                else if(local_degree == 1){
                    os << local_data << 'x';
                }
                else{
                    os << local_data << "x^" << local_degree;
                }
            }
        } else{
            if(rhs.degree == 0){ // for the default constructor output
                os << 0;
            }
        }
        local_ptr = local_ptr->next;
        --local_degree;
    }
    return os;
}

// eval method
double Polynomial::evaluate(double x) const {
    Node* local_ptr = header->next;
    size_t local_degree = degree;
    double result = 0;
    while(local_ptr){
        double exp_x = 1;
        for(size_t i = local_degree; i>0; --i){     // make a for loop to do exponential
            exp_x *= x;
        }
        result += local_ptr->data * exp_x;   // result plus all the data
        --local_degree;
        local_ptr = local_ptr ->next;
    }
    return result;
}


void Polynomial::simplifyZeros(Polynomial& rhs){
    Node* local_ptr = rhs.header->next;
    double local_data = local_ptr ->data;
    while(local_ptr && local_data ==0){
        rhs.header->next = local_ptr -> next;               // simplifying zeros by skip the zeros
        local_ptr = local_ptr->next;
        --rhs.degree;
        local_data = local_ptr ->data;
    }
}

void Polynomial::freeMemory(Node* head){
    Node* local_ptr = head->next;
    while(local_ptr){
        Node* victim = local_ptr;           // simple swap and delete the victim
        local_ptr = local_ptr ->next;
        delete victim;
    }
}
