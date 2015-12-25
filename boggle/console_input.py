"""
console_input.py


OVERVIEW

This module defines several general-purpose functions:

- The functions `get_bool`, `get_int`, `get_float`, and `get_str` facilitate
the reading interactive input from the console (standard input, also known as
stdin), with type checks and optional value checks on the user input.  (The
Python Standard Library provides a rather minimal capability for reading input
from stdin).

- The function `make_check` generates a function as its output; the generated
function tests a value against an arbitrary condition, and can be passed to any
of the above input functions.

- The function `str2int` converts a string to an integer, with somewhat more
flexible rules for input formatting than those imposed by Python's `int`
function.


AUTHOR

Dr. Phillip M. Feldman
"""

import re, sys, types


# `int_pat_anchored` can be used for testing whether a string represents an
# integer that can be parsed using `str2int` (which allows non-negative integer
# exponents), and for extracting the integer or components of it (the mantissa
# and exponent).  Possible groups returned by a search with this regular
# expression include `int` (the entire number string), `man` (the mantissa), and
# `exp` (the exponent string).

int_pat_anchored= re.compile(r'''
   ^                         # anchor to start of string
   (?P<int>                  # integer number
       (?P<man>                 # mantissa
          [+-]?                    # optional sign
          \d+                      # digits
       )
       ([.]0*)?                 # possible trailing decimal point and zeros
       (?P<exp>[eE][+]?\d+)?    # non-negative exponent
   )
   $                         # anchor to end of string
''', re.X)


def get_bool(prompt='Yes or no (or 0 or 1): ', default=None, maxtries=3,
  **kwargs):
   """
   OVERVIEW

   This function prompts the user to make a yes-or-no choice and returns the
   result to the calling program as a 0 or 1.  The user types a response into
   the console window and presses Enter.

   - If the user enters 'q', 'quit', or 'exit', `get_bool` terminates the
   program.

   - If the lower-case-converted input matches any of the following, `getbool`
   returns 1: 1, t, true, y, yes

   - If the lower-case-converted input matches any of the following, `getbool`
   returns 0: 0, f, false, n, no

   - If the user input is empty, i.e., the user presses Enter without typing a
   value, and the calling function provided a default value, the default value
   is returned.

   - If the user input does not satisfy any of the above tests, `get_bool`
   reissues the prompt and inputs a new value (up to maxtries times).


   INPUTS

   `prompt`: This optional input specifies the text to be displayed.  The
   default is 'Yes or no (or 0 or 1): '.

   `default`: This optional input provides a default response to be used if the
   user presses Enter without typing any text.
   """

   if not isinstance(prompt, (str, unicode)):
      raise TypeError("`prompt` (the first argument to this function) must be "
        "a string (str or unicode).  The actual type is %s." % type(prompt))

   if default is not None and not isinstance(default, (bool,int,str)):
     raise TypeError("If `default` (the second argument to this function) is "
       "specified, it must have type `bool`, `int`, or `str`.")

   for tries in range(maxtries):

      # Get user input from the console:
      s= raw_input(prompt)

      # If the user selected 'q', 'quit', or 'exit', stop the program:
      if s=='q' or s=='quit' or s=='exit': sys.exit(0)

      # If user input is empty, substitute default:
      if not s and default is not None:
         if isinstance(default, (bool,int)):
            return bool(default)
         s= default.lower()

      if s in ['1', 't', 'true' , 'y', 'yes']:
         return True

      if s in ['0', 'f', 'false', 'n', 'no' ]:
         return False

      print("'" + s + "' is not a valid response.")
      if tries < maxtries-1:
         print("Please try again or enter 'q', 'quit', or 'exit' to stop "
           "the program.\n")
      else:
         raise ValueError("I'm giving up.")

   return None


def get_int(prompt='Input an integer: ', default=None, maxtries=3, check=None):
   """
   OVERVIEW

   `get_int` prompts the user to input a value via the console window, converts
   the string to an integer, performs error checks, and returns the converted
   integer.  If the input is null (a zero-length string) and a default value was
   provided to the function, the default is returned.  `get_int` checks that the
   input represents a valid integer, and can also optionally perform an
   arbitrary user-specified check (see below).


   INPUTS

   `prompt` is a string to be displayed to queue the user as to the type of
   input that is required.  The default is 'Input an integer: '.

   `default` is an optional default value to be provided in the event that the
   user presses Enter (or clicks OK in GUI mode) without entering a value.

   `maxtries`: If the user input cannot be converted to an integer or fails to
   meet any specified condition, `get_int` reissues the prompt and inputs a new
   string (up to maxtries times).

   `check`: Via the `check` parameter, one can optionally specify an arbitrary
   condition against which the input is to be tested (after the conversion from
   string to integer).  If specified, `check` must be one of the following:

     - a 'check' function that accepts an integer and returns a bool value
     (`True` or `False`).  The factory function `make_check` provides a
     convenient mechanism for generating such a function on the fly.

     - a list containing two strings to be passed to `make_check`, which will
     return a check function.  The first of these is the condition to be tested,
     defined in terms of the variable `x`, and the second is the error message
     to be displayed if the test fails.

     - a string to be passed to `make_check` containing the condition to be
     tested, defined in terms of the variable `x`.  In a few special cases,
     `make_check` can automatically generate a suitable error message, and the
     second string is not required.  See the documentation in `make_check` for
     details.

     - `None`.


   EXAMPLE

   The following line of code prompts the user to input an integer and tests
   that the user-supplied value is between 3 and 7 inclusive:

       i= get_int('i: ', check=make_check('3<=x<=7',
         'A value in [3,7] is required.'))

   Note that `make_check` takes two arguments.  The first is a string specifying
   the condition to be tested; this must be an expression that evaluates to
   either True or False, defined in terms of the variable `x`, regardless of how
   the parameter is named in the calling function.  The second is an error
   message to be displayed to the user in the event that the input cannot be
   converted to an integer or fails to meet the specified condition.
   """

   if not isinstance(prompt, (str,unicode)):
      raise TypeError("`prompt` (the first argument to this function) must be "
        "a string (str or unicode).")

   for tries in range(maxtries):

      # Get user input from the console:
      s= raw_input(prompt)

      # If the user selected 'q', 'quit', or 'exit', stop the program:
      if s=='q' or s=='quit' or s=='exit':
         sys.exit(0)

      # If user input is empty, substitute default:
      if not len(s):

         # Check whether default is a string (str) object:
         if isinstance(default, str):
            s= default # default is already a string
         else:
            s= str(default) # convert default to string

      try:
         i= str2int(s)
         if check is None: return i
         error= check(i)
         if not error: return i

      except:
         print("'%s' is not a valid integer." % s)

      if tries < maxtries-1:
         print("Please try again or enter 'q', 'quit', or 'exit' to stop "
           "the program.\n")
      else:
         raise ValueError("I'm giving up.")

   return None


def get_float(prompt='Input a number: ', default=None, maxtries=3, check=None):
   """
   OVERVIEW

   `get_num` prompts the user to input a value, converts the input string to a
   float, performs error checks, and returns the float value.  If the input is
   null (a zero-length string) and a default value was provided to the function,
   the default is returned.  If the user input is non-null, two types of error
   checking are provided:

   (1) `get_num` checks that the input represents a valid integer.

   (2) Via the `check` parameter, one can optionally specify a function that
   tests an arbitrary condition.  The factory function `make_check` provides a
   convenient mechanism for generating such a function on the fly.  To test, for
   example, that the input is between 3 and 7 inclusive, do the following:

   a= get_num('a: ', check=make_check('3<=x<=7')


   INPUTS

   `prompt` specifies a string to be displayed as a prompt for user input.  The
   default is 'Input a number: '.

   `default` is a value to be returned if the user input is null, i.e., the user
   presses Enter without typing a value.  The default for `default` is `None`,
   which means that null user input will be treated as invalid.

   `maxtries` specifies the maximum number of attempts that the function should
   make to obtain a valid response from the user.

   `check` must be one of the following:

   - a function that tests the user input after it has been converted to a
   float, returning `True` if the value is acceptable or `False` if it is not.
   If the value is invalid, the check function also returns an error message.

   - `None`.

   A check function can be generated using the `make_check` factory function.
   """

   if not isinstance(prompt, (str,unicode)):
      raise TypeError("`prompt` (the first argument to this function) must be "
        "a string (str or unicode).")

   for tries in range(maxtries):

      # Get user input from the console:
      s= raw_input(prompt)

      # If user input is empty and a default value was provided, use default:
      if not s and not default is None: return default

      # If the user selected 'q', 'quit', or 'exit', stop the program:
      if s in ['q', 'quit', 'exit']:
         sys.exit(0)

      try:
         x= float(s)
         if check is None: return x
         error= check(x)
         if not error: return x

      except:
         print("'%s' is not a valid number." % s)

      if tries < maxtries-1:
         print("Please try again or enter 'q', 'quit', or 'exit' to stop "
           "the program.\n")
      else:
         raise ValueError("I'm giving up.")

   return None


def get_str(prompt='Input a string: ', default=None, maxtries= 3, check=None,
  **kwargs):
   """
   OVERVIEW

   `get_str` displays a prompt, reads input via the console window, optionally
   performs an error check, and returns the string.

   If the user input is a null string and a default value was provided to the
   function, the default is returned.  If the user input is non-null, any error
   check requested via the optional `check` argument is tested.


   INPUTS

   `prompt` specifies a string to be displayed as a prompt for user input.  The
   default is 'Input a blank-delimited list of values: '.

   `default` is a value to be returned if the user input is null, i.e., the user
   presses Enter without typing a value.  The default for `default` is `None`,
   which means that null user input will be treated as invalid.

   `maxtries` specifies the maximum number of attempts that the function should
   make to obtain a valid response from the user.

   `check`: Via the `check` parameter, one can optionally specify an arbitrary
   condition against which the input is to be tested (after the conversion from
   string to integer).  If specified, `check` must be one of the following:

     - a 'check' function that accepts an integer and returns a bool value
     (`True` or `False`).  The factory function `make_check` provides a
     convenient mechanism for generating such a function on the fly.

     - a list containing two strings to be passed to `make_check`, which will
     return a check function.  The first of these is the condition to be tested,
     defined in terms of the variable `x`, and the second is the error message
     to be displayed if the test fails.

     - a string to be passed to `make_check` containing the condition to be
     tested, defined in terms of the variable `x`.  In a few special cases,
     `make_check` can automatically generate a suitable error message, and the
     second string is not required.  See the documentation in `make_check` for
     details.

     - `None`.


   EXAMPLE

   To following statement reads a string and uses a regular expression to check
   that the string is non-null and contains only letters and digits:

   s= get_str('s: ', check=['re.match(\'[A-Za-z0-9]+$\', x)',
      'The input must be non-null and contain only letters and digits.'])
   """

   global user_input

   if not isinstance(prompt, (str, unicode)):
      raise TypeError("`prompt` (the first argument to this function) must be "
        "a string (str or unicode).")

   if isinstance(check, str):
      check= make_check(check)

   elif is_list_of(check, str) and len(check)==2:
      check= make_check(check[0], check[1])

   elif not check is None and not isinstance(check, types.FunctionType):
      raise TypeError("If the `check` argument is provided, it must be one of "
        "the following:\n"
        "- a check function (typically created by calling `make_check`),\n"
        "- a string that can be passed to `make_check` to generate a check "
        "function,\n"
        "- a length-2 list of strings that can be passed to `make_check` to "
        "generate a check function, or\n"
        "- `None`.")

   for tries in range(maxtries):

      # Get user input from the console:
      s= raw_input(prompt)

      # If the user selected 'q', 'quit', or 'exit', stop the program:
      if s=='q' or s=='quit' or s=='exit': sys.exit(0)

      # If user input is empty and a default value was provided, use default:
      if not len(s) and not default is None:
         return default

      if check is None: return s
      error= check(s)
      if not error: return s

      print(error)

      if tries < maxtries-1:
         print("Please try again or enter 'q', 'quit', or 'exit' to stop "
           "the program.\n")
      else:
         raise ValueError("I'm giving up.")

   return None


def is_list_of(x, ty):
   """
   OVERVIEW

   This function returns `True` if the input `x` is a list containing only
   objects of type `ty`.  Otherwise, it returns `False`.


   INPUTS

   `x` is an object whose type is to be tested.

   `ty` is either a Python type, e.g., `int`, `list`, `dict`, etc., a tuple of
   Python types, or a function that tests the type of an object and returns a
   bool value.


   EXAMPLE

   To test whether `x` is a list containing only objects of type `int` and
   `str`, one can do the following:

   OK= is_list_of(x, (int,str))


   NOTE

   If `x` is an empty list, this function returns `True`.
   """

   if not isinstance(x, list):
      return False

   if isinstance(ty, types.FunctionType):

      # `ty` is a function that tests the type of an object:
      for item in x:
         if not ty(item):
            return False

   else:

      # `ty` is a Python type:
      for item in x:
         if not isinstance(item, ty):
            return False

   return True


def make_check(condition='x>0', errmsg=''):
   """
   OVERVIEW

   make_check is a 'function factory' (a function that generates and returns
   another function).  The function that is returned can be used to test whether
   a specified condition involving a single variable is satisfied, and to
   display a suitable error message if the condition is violated.  The generated
   function tests its first input argument against a condition that is specified
   only in the call to the `make_check` (not in the call to the generated
   function).


   INPUTS

   condition: The condition is specified as a string, and must be defined in
   terms of a variable called `x`.  The default condition is 'x>0' (x is
   positive).

   errmsg: Unless the condition is one of the following, the calling program
   must provide a string specifying the error message to be displayed when the
   condition is not satisfied:

   - 'x>0',
   - 'x>=0',
   - a string of the form x<=n, where n is an integer,
   - a string of the form x>=n, where n is an integer,
   - a string of the form m<=x<=n, where m and n are integers, or
   - a string of the form 'x==n1 or x==n2' where n1 and n2 are integers.

   For the above special cases, `make_check` can automatically generate a
   suitable error message.


   OUTPUTS

   The output is a function that we refer to as the 'check function'.  The check
   function takes a single argument--the value to be tested--and returns a
   single result.  The output of the check function is a null string if its
   input satisfies the condition; otherwise, it is an error message.


   NOTES

   The calling function must ensure that the condition and error message text
   are consistent.
   """

   while True:
      if errmsg: break

      # Try to create a suitable error message.
      if condition == 'x>0':
         errmsg= 'The value must be positive.'
         break

      if condition == 'x>=0':
         errmsg= 'The value must be non-negative.'
         break

      m= re.match('x<=(-?\d+)$', condition)
      if m:
         errmsg= "The value must not exceed %s." % m.group(1)
         break

      m= re.match('x>=(-?\d+)$', condition)
      if m:
         errmsg= "The value must not be less than %s." % m.group(1)
         break

      m= re.match('(-?\d+)<=x<=(-?\d+)$', condition)
      if m:
         errmsg= "The value must be between %s and %s, inclusive." \
           % (m.group(1), m.group(2))
         break

      m= re.match('x==(-?\d+) or x==(-?\d+)$', condition)
      if m:
         errmsg= 'The value must be either %s or %s.' % (m.group(1), m.group(2))
         break

      raise ValueError("An error message string cannot be automatically "
        "generated for the condition '%s'.  Unless the condition is one of the "
        "following, the calling program must provide a string (via the second "
        "argument) specifying the error message to be displayed when the "
        "condition is not satisfied:\n\n"

        "- 'x>0',\n"
        "- 'x>=0',\n"
        "- a string of the form x<=n, where n is an integer,\n"
        "- a string of the form m<=x<=n, where m and n are integers, or\n"
        "- a string of the form 'x==n1 or x==n2' where n1 and n2 are integers."

        "\n\n(For the above special cases, `make_check` can automatically "
        "generate a suitable error message)." % condition)

   # end while True


   def check(x):

      if eval(condition):

         # The condition is satisfied, so we return a null string:
         return ''

      # The condition was not satisfied, so we return the error message:
      return errmsg

   return check

# end def make_check


def str2int(s, trim='\s*', do_eval=False):
   """
   OVERVIEW

   This function converts `s` from str to int, or raises an exception if the
   conversion is impossible.  Unlike Python's built-in int() function, `str2int`
   allows a decimal point and trailing zeros after the mantissa, allows an
   integer exponent, and can strip text matching a regular expresion (specified
   via the `trim` argument) from the start and end of `s`.


   INPUTS

   s: the input (str or unicode) string to be converted.

   trim: This optional string argument provides a regular expression identifying
   text to be trimmed from the beginning and end of `s` before it is tested.
   The default is '\s*', which matches an arbitrary number of whitespace
   characters (blanks, tabs, newlines, and carriage returns).  If no trimming is
   to be done, specify a null string for `trim`.  `trim` should not include
   anchors such as ^ and $.
   """

   if not isinstance(s, (str,unicode)):
      raise TypeError("`s` must be a string (str or unicode).  "
        "The actual type is %s." % type(s))

   # Strip specified regular expression from beginning and end of `s`:
   if trim:
      s= re.sub('^(' + trim + ')', '', s)
      s= re.sub('(' + trim + ')$', '', s)


   # 1. Compare `s` against anchored regular expression to determine whether
   # there is a match and extract useful components of the string.

   m= int_pat_anchored.search(s)


   # 2. Attempt conversion to float.

   if m is not None and m.group('man'):

      # Convert mantissa to an int:
      mantissa= int(m.group('man'))

      if m.group('exp'):
         # Strip off the exponent marker character ('e' or 'E') and convert the
         # rest of the exponent string to an int:
         exponent= int(m.group('exp')[1:])

         # Combine the mantissa and exponent and return the result:
         return mantissa * 10**exponent

      # There is no exponent, so we simply return the mantissa:
      return mantissa


   # 3. The string in `s` does not represent an integer, but it might contain an
   # expression whose evaluation will yield an integer.

   if do_eval:
      try:
         result= eval(s, namespace)
      except:
         result= None

      if isinstance(result, (int, numpy.int32)):
         return result

   raise ValueError("'%s' does not represent an integer." % s)
