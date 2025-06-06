import sys

def main():
  read =  sys.stdin.readline()
  while read != "END\n":
    read = read[:-1]
    print(read[::-1])
    read =  sys.stdin.readline()

  return 0

if __name__ == "__main__":
  main()
