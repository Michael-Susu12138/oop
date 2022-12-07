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
    header = new Node(0);
    local_ptr = header;
    for(int item: coefs){
        local_ptr->next = new Node(item);
        local_ptr = local_ptr->next;
    }
}

//big three
// copy constructor
Polynomial::Polynomial(const Polynomial& rhs){
    //1. copy local fields
    //2. loop through the linked list
    header = new Node(0);
    Node* this_header = header;
    Node* rhs_header = rhs.header->next;
    degree = rhs.degree;
    while(rhs_header){ //last item
        this_header->next = new Node(rhs_header->data);
        
        this_header = this_header->next;
        rhs_header = rhs_header ->next;
    }
}

// assignment operator
Polynomial& Polynomial::operator=(const Polynomial& rhs){
    //1. check for self assignment
    if(&rhs != this){
        //free up stuff on the heap
        Node* local_ptr = header->next;
        while(local_ptr){
            Node* victim = local_ptr;
            local_ptr = local_ptr ->next;
            delete victim;
        }
        
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
    Node* local_ptr = header->next;
    while(local_ptr){
        Node* victim = local_ptr;
        local_ptr = local_ptr ->next;
        delete victim;
    }
}

// operator overloading
// member operators:+=

// += member operator
Polynomial& Polynomial::operator+=(const Polynomial& rhs){
    Polynomial less_degree;
    size_t diff = 0; // difference in their degrees
    
    if(degree >= rhs.degree){
        diff = degree - rhs.degree;
        less_degree = rhs;
    }
    else if(degree < rhs.degree){
        diff = rhs.degree - degree;
        less_degree = *this;
        *this = rhs;
    }
    Node* this_ptr = header->next; //skip header
    Node* less_ptr = less_degree.header->next; //skip header
    while(diff){
        this_ptr = this_ptr->next;
        --diff;
    }
    while(this_ptr && less_ptr){
        this_ptr->data += less_ptr->data;
        this_ptr = this_ptr -> next;
        less_ptr = less_ptr ->next;
    }
    return *this;
}


// non-member operators: +, ==, !=

// + non-member operator
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial return_val(lhs);
    return_val += rhs;
    return return_val;
}

// == non-member operator
bool operator==(const Polynomial& lhs, const Polynomial& rhs){
    if(lhs.degree == rhs.degree){
        Polynomial::Node* lhs_ptr = lhs.header ->next;
        Polynomial::Node* rhs_ptr = rhs.header ->next;
        while(lhs_ptr && rhs_ptr){
            if(lhs_ptr->data != rhs_ptr->data){
                return false;
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
    return !(lhs==rhs);
}


//output operator
ostream& operator<<(ostream& os,const Polynomial& rhs){
    // simplify the polynomials (reduce the zero coefficients)
    Polynomial::Node* local_ptr = rhs.header->next;
    Polynomial temp(rhs);
    
    while(local_ptr->data == 0){
        temp.header->next = local_ptr->next;
        local_ptr = local_ptr->next;
        --temp.degree;
    }
    

    
    Polynomial::Node* temp_ptr = temp.header->next;
    size_t local_degree = temp.degree;

    while(temp_ptr){
        double local_data = temp_ptr->data;
        if(local_data != 0){
            //if coef == 1
            // highest polynomial does not need plus sign
            if(local_degree != temp.degree){
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
        }
        temp_ptr = temp_ptr->next;
        --local_degree;
    }
    return os;
}

// eval method
double Polynomial::evaluate(double x) const {
    Node* local_ptr = header->next;
    size_t local_degree = degree;
    double result = 0;
    while(local_ptr->next){
        double exp_x = 1;
        for(size_t i = local_degree; i>0; --i){
            exp_x *= x;
        }
        result += local_ptr->data * exp_x;
        --local_degree;
    }
    return result;
}

size_t Polynomial::size() const {
    size_t count = 0;
    Node* local_ptr = header->next;
    while(local_ptr){
        ++count;
        local_ptr = local_ptr ->next;
    }
    return count;
}
