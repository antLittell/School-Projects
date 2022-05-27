#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <map>
using namespace std;

void afterSubject();
void S();
void afternoun();
void afterobject();
void Lexicon();
void getEword();
void gen(string line_type);


map<string,string> lexMap;
map<string,string> :: iterator it2;
string saved_E_word;
ofstream outFile;
/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 10
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: Member: Anthony
// RE:   (vowel | vowel n | consonant vowel | consonant vowel n | consonant-pair vowel | consonant-pair vowel n)^+


bool word (string s)
{

  int state = 0; //state 0 is q0
  int charpos = 0;

  while(s[charpos] != '\0')
  {
    //initial transitions from state 0 or q0
    if(state == 0 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E')){
      state = 1; //state 1 is q0q1
    }
    else if(state == 0 && (s[charpos] == 'b' || s[charpos] == 'm' || s[charpos] == 'k' || s[charpos] == 'n' || s[charpos] == 'h' || s[charpos] == 'p' || s[charpos] == 'r' || s[charpos] == 'g')){
      state = 4; //state 4 is qy
    }
    else if(state == 0 && (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j')){
      state = 5; //state 5 is qsa
    }
    else if(state == 0 && s[charpos] == 'c'){
      state = 3; //state 3 is qc
    }
    else if(state == 0 && s[charpos] =='s'){
      state = 6; //state 6 is qs
    }
    else if(state == 0 && s[charpos] == 't'){
      state = 7; //state 7 is qt
    }

    //transitions from q0q1
    else if(state == 1 && (s[charpos] == 'b' || s[charpos] == 'm' || s[charpos] == 'k' || s[charpos] == 'h' || s[charpos] == 'p' || s[charpos] == 'r' || s[charpos] == 'g')){
      state = 4; //state 4 is qy
    }
    else if(state == 1 && (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j')){
      state = 5; //state 5 is qsa
    }
    else if(state == 1 && s[charpos] == 'c'){
      state = 3; //state 3 is qc
    }
    else if(state == 1 && s[charpos] == 's'){
      state = 6; //state 6 is qs
    }
    else if(state == 1 && s[charpos] == 't'){
      state = 7; //state 7 is qt
    }

    //transitions from q0qy
    else if(state == 2 && (s[charpos] == 'b' || s[charpos] == 'm' || s[charpos] == 'k' || s[charpos] == 'n' || s[charpos] == 'h' || s[charpos] == 'p' || s[charpos] == 'r' || s[charpos] == 'g')){
      state = 4; //state 4 is qy
    }
    else if(state == 2 && (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j')){
      state = 5; //state 5 is qsa
    }
    else if(state == 2 && s[charpos] == 'c'){
      state = 3; //state 3 is qc
    }
    else if(state == 2 && s[charpos] == 's'){
      state = 6; //state 6 is qs
    }
    else if(state == 2 && s[charpos] == 't'){
      state = 7; //state 7 is qt
    }
    else if(state == 1 && s[charpos] == 'n'){
      state = 2;//state 2 is q0qy
    }
    else if(state == 2 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E')){
      state = 1;
    }
    else if(state == 1 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E')){
      state = 1; //account for the loop on q0q1
    }

    //to get qsa qy qt and qs back to q0q1
    else if(state == 5 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E')){
      state = 1;
    }
    else if(state == 4 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E')){
      state = 1;
    }
    else if(state == 7 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E')){
      state = 1;
    }
    else if(state == 6 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E')){
      state = 1;
    }

    //the different letters that can get to qsa
    else if(state == 3 && s[charpos] == 'h'){
      state = 5;
    }
    else if(state == 6 && s[charpos] == 'h'){
      state = 5;
    }
    else if(state == 7 && s[charpos] == 's'){
      state = 5;
    }
    else if(state == 4 && s[charpos] == 'y'){
      state = 5;
    }

    //returns false if no character fits any definition
    else{
      return false;
    }
    charpos++;
  }
  //final check of where we are
  if(state == 0 || state == 1 || state == 2){
    return true;
  } 
  else{
    return false;
  } 

}

// PERIOD DFA 
// Done by: Member: Kenneth
bool period (string s)
{  // check if the character is a period and return true if it is
  if(s == ".")
    return (true);
  else
    return(false);
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Member: Anthony

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR, WORD1, WORD2, PERIOD, EOFM, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, SUBJECT, OBJECT, DESTINATION, PRONOUN, CONNECTOR, BE, NOUN, s};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[19] = {"ERROR", "WORD1", "WORD2", "PERIOD", "EOFM", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "SUBJECT", "OBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "BE", "NOUN", "s" }; 

string reservedWords[19] = {"masu", "masen", "mashita", "masendeshita", "desu", "deshita", "o", "wa", "ni", "watashi", "anata", "kare", "kanojo", "sore", "mata", "soshite", "shikashi", "dakara", "eofm"};
// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.


// ------------ Scanner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Member: Edgardo 
void scanner(tokentype& tt, string& w)
{
  cout << "The word is: " << w << endl;
  int count = -1;
  if(w == "eofm")
    return;
  else if(word(w))
  {
      
    for(int i = 0; i < 19; i++){
	    
      if(reservedWords[i] == w){
        count = i;
      }  
	  }
    if(count < 0)
	  {
	    if(w[w.size()-1] == 'I' || w[w.size()-1] == 'E'){
	      tt = WORD2;
	    }
	    else{
        tt = WORD1;
      }
	  }
    else if(count == 0){
      tt = VERB;
    }
    else if(count == 1){
      tt = VERBNEG;
    }
    else if(count == 2){
      tt = VERBPAST;
    }
    else if(count == 3){
      tt = VERBPASTNEG;
    }
    else if(count == 4){
      tt = IS;
    }
    else if(count == 5){
      tt = WAS;
    }
    else if(count == 6){
      tt = OBJECT;
    }
    else if(count == 7){
      tt = SUBJECT;
    }
    else if(count == 8){
      tt = DESTINATION;
    }
    else if(count == 9 || count == 10 || count == 11 || count == 12 || count == 13){
      tt = PRONOUN;
    }
    else if(count == 14 || count == 15 || count == 16 || count == 17){
      tt = CONNECTOR;
    }
  }
  else if(period(w)){
    tt = PERIOD;
  } 
  else{ 
    cout << "Lexical error: " << w << " is not a valid token" << endl;
    tt = ERROR;
  }
} 

//=================================================
// File parser.cpp written by Group Number: 10
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  

// Type of error: Error for match, the expected token was not what was next
// Done by: Member: Edgardo
void syntaxerror1(tokentype expected, string saved_lexeme)
{
  cout << "erorr 1" << endl;
  cout << "SYNTAX ERROR: expected " << tokenName[expected] << " but found " << saved_lexeme << " and halt." << endl;
  exit(1); //exit
}
// Type of error: Default error for non-terminals
// Done by: Member: Edgardo
void syntaxerror2(string saved_lexeme, string parserFunct) 
{
  cout << "SYNTAX ERROR: unexpected " << saved_lexeme << " found in " << parserFunct << " and halt." << endl;
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme
//enum token_type{ERROR, WORD1}; This function is up above from scanner.cpp
tokentype saved_token;
string saved_lexeme;
bool token_available;

// Purpose: Looks ahead to check and see what the next token that the scanner reads in will be
// Done by: Member: Kenneth
tokentype next_token()
{
  //string saved_lexeme;
  if (!token_available){   // if there is no saved token yet
     
    //The string is passed back into saved_lexeme as he wants (Was already there) unless we are supposed to set saved_lexeme = saved_token after calling the scanner function
    scanner(saved_token, saved_lexeme);  // call scanner to grab a new token
    token_available = true;                              // mark that fact that you have saved it
    if (saved_token == ERROR){                           //if saved_token equals error
	    syntaxerror2(saved_lexeme, "next_token()");         //display error
	  }
  }
  return saved_token;    // return the saved token        
}

// Purpose: Checks to see if there is a match
// Done by: Member: Kenneth
bool match(tokentype expected) 
{
  if (next_token() != expected){   // mismatch has occurred with the next token
    // calls a syntax error function here to generate a syntax error message here and do recovery
    syntaxerror1(expected, saved_lexeme);
    return false;
  }
  else{  // match has occurred
    //Used to trace program
    cout << "Matched " << tokenName[expected] << endl;
    token_available = false;   // eat up the token
    return true;                        // say there was a match
  }
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: Above the functions
// Done by: Edgardo, Kenneth, Anthony

string filename;

// Grammar: <noun> ::= WORD1 | PRONOUN 
//Done by: Member: Edgardo
void noun()
{
  cout << "Processing <noun>" << endl;
  switch(next_token())                      //switch next token
    {
    case WORD1:                            //case word1
      match(WORD1);
      break;
    case PRONOUN:                          //case pronoun
      match(PRONOUN);
      break;
    default:                               //default error
      syntaxerror2(saved_lexeme, "noun");
    }
}
// Grammar: <verb> ::= WORD2
//Done by: Member: Edgardo
void verb()
{
  cout << "Processing <verb>" << endl;
  match(WORD2);                            //match WORD2
}
// Grammar: <be> ::=   IS | WAS
//Done by Member: Edgardo
void be()
{
  cout << "Processing <be>" << endl;
  switch(next_token())                     //switch next token
    {
    case IS:                              //case IS
      match(IS);                          //match is
      break;
    case WAS:                             //case WAS
      match(WAS);                         //match was
      break;
    default:                             //default error
      syntaxerror2(saved_lexeme, "be()");
    }
}
// Grammar: <tense> := VERBPAST  | VERBPASTNEG | VERB | VERBNEG
//Done by: Member: Kenneth
void tense()
{
  cout << "Processing <tense>" << endl;
  switch(next_token())                    //switch next token
    {
    case VERBPAST:                       //case VERBPAST
      match(VERBPAST);                   //match verbpast
      break;
    case VERBPASTNEG:                    //case VERBPASTNEG
      match(VERBPASTNEG);                //match verbpastneg
      break;
    case VERB:                           //case VERB
      match(VERB);                       //match verb
      break;
    case VERBNEG:                        //case VERBNEG
      match(VERBNEG);                    //match verbneg
      break;
    default:                             //default error
      syntaxerror2(saved_lexeme,"tense()");
    }
}
// Grammar: <s> ::=  [CONNECTOR] <noun> SUBJECT  <verb>   <tense> PERIOD 
// <s> ::=  [CONNECTOR] <noun> SUBJECT  <noun>  <be>      PERIOD //
// <s> ::=  [CONNECTOR] <noun> SUBJECT  <noun>  DESTINATION  <verb> <tense> PERIOD 
// <s> ::=  [CONNECTOR] <noun> SUBJECT  <noun>  OBJECT   <verb> <tense> PERIOD 
// <s> ::=  [CONNECTOR] <noun> SUBJECT  <noun>  OBJECT   <noun> DESTINATION
//                                                         					<verb> <tense> PERIOD 

//Done By: Member: Kenneth
void S()
{
  cout << "Processing <s>" << endl;
  next_token();                          //call next_token func
  if(saved_lexeme !="eofm") {

    if(next_token() == CONNECTOR){      //if next token is same as connector 
	    match(saved_token);                  //match saved_token
	    fin >> saved_lexeme;                 
    }
    noun();                              //calls noun
    getEword();
    fin >> saved_lexeme;
    match(SUBJECT);                      //match subject
    gen("ACTOR");
    fin >> saved_lexeme;
    afterSubject();                     //calls after subject 
  }
}
// Grammar: <after subject> ::= <verb> <tense> PEROD | <noun> <after noun>
//Done By: Member: Anthony
void afterSubject()
{
  cout << "Processing <aftersubject>" << endl;
  switch(next_token())                  //switch statement next_token
    {
    case VERB:                          //case for verb
    case WORD2:                         //case word2
      verb();                           //calls verb func
      getEword();
      gen("ACTOR");
      fin >> saved_lexeme; 
      tense();                          //calls tense func
      gen("TENSE");
      fin >> saved_lexeme;
      match(PERIOD);                    //match period 
      break;
    case WORD1:
    case PRONOUN:
      noun();                           //calls noun
      getEword();
      fin >> saved_lexeme;
      afternoun();                      //after noun called 
      break;
    default:                            //default error case
      syntaxerror2(saved_lexeme, "afterSubject()");//error function 2 
    }
}
// Grammar: <after noun> ::= <be> PERIOD | DESTINATION  <verb> <tense> PERIOD | OBJECT <after object>   
//Done By: Member: Anthony
void afternoun()
{
  cout << "Processing <after_noun>" << endl; //prints the name of the function
  switch (next_token())                      //switch statement next_token
    {
    case IS:                                 //case IS
    case WAS:                                //case WAS
      gen("DESCRIPTION");
      be();
      gen("TENSE");
      fin >> saved_lexeme;
      match(PERIOD);                        //calls match and makes period parameter
      break;
    case NOUN:
    case DESTINATION:                       //case DESTINATION
      match(DESTINATION);                   //calls match and passes destination
      gen("TO");
      fin >> saved_lexeme;
      verb();                              //calls the verb function
      getEword();
      gen("ACTION");
      fin >> saved_lexeme;
      tense();                             //calls tense function 
      gen("TENSE");
      fin >> saved_lexeme;
      match(PERIOD);                       //matches PERIOD
      break;

    case OBJECT:
      match(OBJECT);                       //calls function with parameter object 
      gen("OBJECT");
      fin >> saved_lexeme;
      afterobject();                       //calls afterobject func
      break;
    default:                               //default error case
      syntaxerror2(saved_lexeme, "<after_noun>()");//calls error function with saved lexeme and noun as parameter
      //break;
    }
}
// Grammar: <after object> ::= <verb> <tense> PERIOD | <noun> DESTINATION <verb> <tense> PERIOD   
//Done by: Member: Kenneth
void afterobject()
{
  cout << "Processing <afterobject>" << endl;
  switch(next_token())                     //switch next token
    {
    case VERB:                            //case VERB
    case WORD2:                           //case WORD2
      verb();                             //calls verb 
      getEword();
      gen("ACTION");
      fin >> saved_lexeme;
      tense();                            //calls tense
      gen("TENSE");
      fin >> saved_lexeme;
      match(PERIOD);                      //calls match and passese period as parameter
      break;
    case WORD1:                           //case WORD1
      noun();                             //case noun
      getEword();
      fin >> saved_lexeme;
      match(DESTINATION);                 //calls match and passes destination as parameter
      gen("TO");
      fin >> saved_lexeme;
      verb();                             //calls verb
      getEword();
      gen("ACTION");
      fin >> saved_lexeme;
      tense();                            //calls tense
      gen("TENSE");
      fin >> saved_lexeme;
      match(PERIOD);                      //calls match with period as parameter
      /*
      verb();
      getEword();
      gen("ACTION");
      tense();
      gen("TENSE");
      match(PERIOD);
      */
      break;
    default:                              //default error case
      syntaxerror2(saved_lexeme, "afterobject()");
    }
}
// Grammar: <story> ::= <s> { <s> }
//Done by: Member: Kenneth
void story()
{
  cout << "Process <story>" << endl;
  fin >> saved_lexeme;
  S();                                                 //calls s func
  //Loops forever (Or until the default case is met)
  while(true){
    fin >> saved_lexeme;
    switch(next_token())                              //switch next token
	  {
	    case CONNECTOR:
      case WORD1:
      case PRONOUN:
	      S();                                              //calls S 
	      break;
	    default:                                          //default error case
	      cout << endl << "Finished parseingg story" << endl;
	      return;
	  }
  }
}

//=================================================
// File translator.cpp written by Group Number: 10
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: Member: Anthony
void Lexicon()
{
  ifstream lexFile;
  lexFile.open("lexicon.txt");
  string lex1, lex2;
  while(lexFile >> lex1 >> lex2){
    lexMap.insert(pair<string, string>(lex1,lex2));
  }
  lexFile.close();
}


// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result   
//                 in saved_E_word
//  Done by: Member: Anthony 
void getEword()
{
  it2 = lexMap.find(saved_lexeme);
  if(it2 != lexMap.end()){
    saved_E_word = it2->second;
    cout << "saved E word : " << saved_E_word << endl;
  }
  else{
    cout << "could not find E word in map" << endl;
    saved_E_word = saved_lexeme;
  }
}


//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: Member: Anthony 
void gen(string line_type)
{
  if(line_type == "TENSE"){
    outFile << line_type << ": " << tokenName[saved_token] << endl << endl;
  }
  else{
    outFile << line_type << ": " << saved_E_word << endl;
  }
}


// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 

// ** Each non-terminal function should be calling
//    getEword and/or gen now.


// ---------------- Driver ---------------------------

// The final test driver to start the translator
// Done by: Member: Anthony
int main()
{
  string filename;
  //** opens the lexicon.txt file and reads it into Lexicon
  //** closes lexicon.txt 
  Lexicon();
  //** opens the output file translated.txt
  outFile.open("translated.txt");

  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  story();
  //** closes the input file 
  fin.close();
  //** closes traslated.txt
  outFile.close();
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions

