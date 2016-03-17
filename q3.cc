#include "utf8string.h"
#include <iostream>
#include <string>
using std::cin;
using std::cerr;
using std::cout;
using std::endl;

/* NOTES:

   YOU DO NOT NEED TO MODIFY THIS FILE.

   Commands are given in a regex style, e.g. saba, p a 3, f a, etc.
   Copy Constructor needs to work before operator+ can be tested.

   Note on commands: Spaces are not necessary but are used here for readability.
   All instances of source, source1, source2 and destination listed below are in the range [a-d].
   All instances of string listed below refer to any arbitrary string of UTF-8 encoded text.

   Command descriptions:
   s destination source1 source2 // operator+: destination = source1 + source2
   t destination source1 string  // operator+: destination = source1 + string
   r destination string          // operator>>: read a string into a utf8::string object
   w source                      // operator<<: output the source utf8::string object
   n destination string          // utf8::string(char*): create a utf8::string object with given string as contents
   i destination source          // copy constructor: copy an existing utf8::string object (like strdup)
   = destination source          // assignment operator: copy an existing utf8::string object
   f destination                 // default constructor: create empty utf8::string
   e source                      // delete source: cleans up memory by calling destructor
   l source                      // print length of source utf8::string
   c source                      // print capacity of source utf8::string
   p destination char            // add UTF-8 character char to the end of destination utf8::string by calling push_back
   v source size                 // try to enlarge source utf8::string by calling reserve
   q/eof                         // terminates the test harness
*/
int main() {
  bool done = false;       // Received quit command or eof?
  utf8::string *a[4] = {NULL, NULL, NULL, NULL}; // iString objects to manipulate

  struct Finished {};
  try {
    while (!done) {
      char c;     // command
      char which; // which iString to modify; one of a, b, c or d.
      char op1;   // command operands
      char op2;
      int int_op;
      character utf8;
      std::string temp;
      utf8::string * tmp;   // temporary iString

      cerr << "Command?" << endl;
      cin >> c;

    if ( cin.eof() ) break;

      switch( c ) {
        case 's':
          /*
           * The following kind of calculation is explained once and used throughout.
           *
           * "which" is a char whose valid values are a, b, c, or d; otherwise, the
           * program behaviour is undefined. Subtracting 'a' from which will give us
           * a value in the range 0 to 3. This is used to index into the "a" array
           * that stores our strings.
           */
          cin >> which >> op1 >> op2;
          tmp = new utf8::string( *(a[op1-'a']) + *(a[op2-'a']) );
          delete a[which-'a'];
          a[which-'a'] = tmp;
          break;

        case 't':
          cin >> which >> op1 >> temp;
          tmp = new utf8::string(*(a[op1-'a']) + temp.c_str());
          delete a[which-'a'];
          a[which-'a'] = tmp;
          break;

        case 'r':
          cin >> which;
          if (a[which-'a'] == NULL) {
            a[which-'a'] = new utf8::string;
          }
          cin >> *(a[which-'a']); //whitespace delimited read
          break;

        case 'w':
          cin >> which;
          if (a[which-'a'] != NULL) cout << *(a[which-'a']) << endl;
          break;

        case 'n':
          cin >> which >> temp;
          delete a[which-'a'];
          a[which-'a'] = new utf8::string(temp.c_str());
          break;

        case 'i':
          cin >> op1 >> op2;
          tmp = new utf8::string( *(a[op2-'a']) );
          delete a[op1-'a'];
          a[op1-'a'] = tmp;
          break;

        case '=':
          cin >> op1 >> op2;
          *a[op1-'a'] = *a[op2-'a'];
          break;

        case 'f':
          cin >> which;
          delete a[which-'a'];
          a[which-'a'] = new utf8::string();
          break;

        case 'e':
          cin >> which;
          delete a[which-'a'];
          a[which-'a'] = NULL;
          break;

        case 'l':
          cin >> which;
          if (a[which-'a'] != NULL) cout << a[which-'a']->length << endl;
          break;

        case 'c':
          cin >> which;
          if (a[which-'a'] != NULL) cout << a[which-'a']->capacity << endl;
          break;

        case 'p':
          cin >> which;
          while (isspace(cin.peek())) {
            // gobble whitespace
            cin.get();
          }
          read(cin, utf8);
          if (a[which-'a'] != NULL) a[which-'a']->push_back(utf8);
          break;

        case 'v':
          cin >> which >> int_op;
          if (a[which-'a'] != NULL) a[which-'a']->reserve(int_op);
          break;

        case 'q':
          throw Finished();
      } // switch
    } // while
  } catch (Finished) {}

  for (int i = 0; i < 4; i++) {
    delete a[i];
  }
} // main
