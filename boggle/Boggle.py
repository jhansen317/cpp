"""
Boggle.py

This Python program finds words on the specified Boggle board.  The sequence of
letters may be specified via the command line.  If it is not specified via the
command line, the program prompts the user to specify the sequence of letters.

This code is based on code from the following URL:

http://everydayscripting.blogspot.com/2009/08/python-boggle-solver.html

That code was written by Scott Hillman.  I have made some minor improvements to
the user interface.   Phillip M. Feldman  17 Feb, 2013
"""

from console_input import get_int, get_str, make_check
import sys
import time

class BoggleSolver:

   def __init__(self, letters=''):
      """
      The single input to this constructor--`letters`--is a sequence of letters
      specifying the letters on the board, either row by row or column by
      column.  This string should either have length 16 or be a null string, in
      which case the method prompts the user to specify the letters on the
      board.
      """

      if isinstance(letters, list):
         try:
            letters= letters[0]
         except:
            letters= ''

      self.dictionary= Dictionary("large.txt")

      if letters == '':
         letters= get_str("Input a length-16 string "
           "representing the letters on the Boggle board.  You may specify the "
           "letters row by row or column by column: ",
           check= make_check('len(x)==16', "A length-16 string is required."))
      elif len(letters) != 16:
         raise ValueError("The string of letters that is passed to this "
           "constructor must either have length 16 or be a null string.")

      self.board= Board(letters)
      self.minLength= get_int(
        "Minimum word length (default= 4): ", default=4)
      self.foundWords= set()

      # Find all words starting from each coordinate position
      for row in xrange(self.board.sideLength):
         for column in xrange(self.board.sideLength):
            self._findWords(Word.new(row, column), row, column)

   def _findWords(self, word, row, column):
      word.addLetter(self.board[row][column], row, column)

      if (self._canAddWord(word)):
         self.foundWords.add(word.letterSequence)

      for row, column in self._getValidCoodinatesForWord(word, row, column):
         if self.dictionary.containsPrefix(
           word.letterSequence + self.board[row][column]):
            self._findWords(Word.newFromWord(word), row, column)

   def _canAddWord(self, word):
      return len(word) >= self.minLength and \
        self.dictionary.containsWord(word.letterSequence)

   def _getValidCoodinatesForWord(self, word, row, column):
      for r in range(row - 1, row + 2):
         for c in range(column - 1, column + 2):
            if r >= 0 and r < self.board.sideLength and c >= 0 \
              and c < self.board.sideLength:
               if ((r, c) not in word.usedBoardCoordinates):
                  yield r, c


class Board:

   def __init__(self, letters):
      self.sideLength= len(letters) ** .5
      if (self.sideLength != int(self.sideLength)):
         raise Exception("Board must have equal sides! (4x4, 5x5...)")
      else:
         self.sideLength= int(self.sideLength)

      self.board= []

      index= 0
      for row in xrange(self.sideLength):
         self.board.append([])
         for column in xrange(self.sideLength):
            letter= letters[index]
            if letter == 'q':
               self.board[row].append('qu')
            else:
               self.board[row].append(letter)
            index += 1

   def __getitem__(self, row):
      return self.board[row]


class Word:
   def __init__(self):
      self.letterSequence= ""
      self.usedBoardCoordinates= set()

   @classmethod
   def new(wordClass, row, column):
      word= wordClass()
      word.usedBoardCoordinates.add((row, column))
      return word

   @classmethod
   def newFromWord(wordClass, word):
      newWord= wordClass()
      newWord.letterSequence+= word.letterSequence
      newWord.usedBoardCoordinates.update(word.usedBoardCoordinates)
      return newWord

   def addLetter(self, letter, row, column):
      self.letterSequence+= letter
      self.usedBoardCoordinates.add((row, column))

   def __str__(self):
      return self.letterSequence

   def __len__(self):
      return len(self.letterSequence)

class Dictionary:
   def __init__(self, dictionaryFile):
      self.words= set()
      self.prefixes= set()
      with open(dictionaryFile, "r") as dictFile:
         for word in dictFile.readlines():
            self.words.add(word.strip())
            for index in xrange(len(word.strip()) + 1):
               self.prefixes.add(word[:index])

   def containsWord(self, word):
      return word in self.words

   def containsPrefix(self, prefix):
      return prefix in self.prefixes

if __name__ == "__main__":
   
   start = time.clock() 
   boggleSolver= BoggleSolver(sys.argv[1:])
   words= boggleSolver.foundWords
   stop = time.clock()

   elapsed = stop - start
   print "Total elapsed time is {}".format(elapsed)

   # Convert set to list:
   words= list(words)

   # Sort list alphabetically:
   words.sort()

   if len(words) >= 2:
      print("%d words were found: %s" % (len(words), str(words)[1:-1]))

   elif len(words) == 1:
      print("One word was found: %s" % words[0])

   else:
      print("No words were found.")
