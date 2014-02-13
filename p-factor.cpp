/* John Graham -- Februrary 2014
 * large number prime factoring program
 */

#include <iostream> // for input/output
#include <cmath>    // for some math functions, primarily sqrt()
#include <new>      // for nothrow to handle memory allocation issues
using namespace std;


struct factors_t {
    unsigned long long int* list; // list of factors
    unsigned int count; // number of factors in list
    unsigned int size;  // size of space for factors in list
} ;


class bigNum {
  public:
    // Wanted to use long long int, but it's the same size as long int on my
    //  system.
    unsigned long long int number;
    factors_t factors;
    
    bigNum(unsigned long long int num) : number(num) {
        // To construct, we compute the factor list of the number given as
        //  seed.
        
        
        unsigned long int i = 2; // start our prime search at 2
        
        unsigned long long int* temp;
        unsigned int t;
        // A temporary space and counter for storing the factors list when we
        //  need to expand.
        
        factors.count = 0;
        factors.size = 1;
        factors.list = new unsigned long long int[factors.size];
        // For the factors list, I'm assuming that, no matter what, I'll have at
        //  least one factor.  I'll set it to 1 if the number is 1 or 0, and
        //  dynamically expand the list otherwise.
        
        
        if (number <= 1) {
            // The number is either 1 or 0, so there are no prime factors (hence
            //  using 1 as the only factor in the list and leaving the count at
            //  0).
            
            
            factors.list[0] = 1;
            
        } else {
            // We now factor the number!  Coo coo cachoo puddinpops!
            
            
            unsigned long long int remainder = number;
            double rootLimit = sqrt(remainder);
            // This is so that, as we pull out factors, we can reduce our
            //  problem space accordingly.  I.e., each time a factor is found,
            //  it is pulled from the number and we search to below that new
            //  number's square root.
            
            
            do {
                if (remainder % i == 0) {
                    // We've found a factor!  A few things to note: we can
                    //  guarantee it's prime (if it weren't, we would have 
                    //  pulled one of it's factors out before), and we can
                    //  guarantee that it's the largest one so far (all other
                    //  factors below it have been found already).
                    
                    
                    // Add the new factor to the list and increment the count.
                    //  The way I've set things up, the factors list will always
                    //  have room for one more factor at this point and, if we
                    //  fill the list, we'll expand it below.
                    factors.list[factors.count] = i;
                    factors.count++;
                    
                    
                    if (factors.size == factors.count) {
                        // Need to allocate more space for the factors list.
                        
                        
                        // Set up space to move the factors list.
                        temp = new (nothrow) unsigned long long int[factors.size];
                        if (temp == NULL) {
                            // Tried to allocate more memory than we have access
                            //  to, would have thrown an exception, but instead
                            //  I'm dealing with it manually.
                            
                            cout << "THERE ARE TOO MANY PRIME FACTORS, ABANDON SHIP!" << endl;
                            return;
                        }
                        
                        
                        // Move that list!
                        for (t = 0; t < factors.count; t++)
                            temp[t] = factors.list[t];
                        
                        
                        // Now, delete old factors list and allocate a new space
                        //  for it, double the size of the old.
                        delete[] factors.list;
                        factors.size = factors.size*2;
                        factors.list = new (nothrow) unsigned long long int[factors.size];
                        if (factors.list == NULL) {
                            // As above, I'm using nothrow to check for bad
                            //  memory allocations manually.  Really should look
                            //  into using exceptions.
                            
                            cout << "THERE ARE TOO MANY PRIME FACTORS, ABANDON SHIP!" << endl;
                            return;
                        }
                        
                        
                        // Copy the list from temp to the new space.
                        for (t = 0; t < factors.count; t++)
                            factors.list[t] = temp[t];
                        
                        
                        // And finally clear out the temporary space we were
                        //  using (we'll have to reallocate it later, anyhow).
                        delete[] temp;
                        
                    }
                    
                    
                    // And finally, remove the factor from the number and re-
                    //  calculate the root limit.
                    remainder = remainder / i;
                    rootLimit = sqrt(remainder);
                    
                } else {
                    // Because we want to check if there are multiple copies of
                    //  the same prime, I'm leaving incrementing to specifically
                    //  when we have *not* found a prime factor
                    
                    
                    // If we were still on i==2, then we need to switch over to
                    //  odd numbers from here.
                    if (i == 2) i++;
                    else i += 2;
                    
                }
                
            } while (i < rootLimit);
            
            
            // Now, whatever remains is the last factor in the factor list.  Add
            //  that shit, yo!  Also, we know we'll have enough room (at least
            //  1 slot) left in the factors list by how we did memory allocation
            //  up above in the loop.
            factors.list[factors.count] = remainder;
            factors.count++;
        
        }
        
        
        // WE DID, NUMBER FACTORED, OBJECT CONSTRUCTED.
        return;
    }
    
} ;



int main(int argc, char* argv[]) {
    
    unsigned long long int input = 0;
    unsigned int i = 0;
    bigNum* mynumber;
    
    cout << "What number would you like to factor?\n";
    cin >> input;
    mynumber = new bigNum(input);
    
    cout << "The prime factors of " << input << " are...\n";
    for (i = 0; i < mynumber->factors.count; i++)
        cout << mynumber->factors.list[i] << "\n";
    
    
    return 0;
}

