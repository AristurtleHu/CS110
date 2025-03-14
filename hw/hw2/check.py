import re
import itertools
import argparse
import hashlib

if __name__ == '__main__':
  parser = argparse.ArgumentParser(description="ca25s hw2 local checker")
  parser.add_argument("answer", type=argparse.FileType('r'))
  parser.add_argument("solution", type=argparse.FileType('r'))
  args = parser.parse_args()
  try:
    total, correct = 0, 0
    for i, (l1, l2) in enumerate(
        itertools.zip_longest(args.answer, args.solution, fillvalue=''), start=1):
      l = "{:08d}: {}".format(
        i, re.sub('\\s+', ' ', l1.strip()) # merge whitespaces
      )
      h = hashlib.sha256(l.encode('ascii')).hexdigest()
      matched = h == l2.strip()
      if matched: correct += 1
      total += 1
      print("[ ]" if matched else "[x]", l1.rstrip())
    print("{}/{} matched".format(correct, total))
  except Exception as e:
    print(e)