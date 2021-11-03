import sys

def main(passwords):
  for password in passwords:
    left = []
    right = []

    for i in range(len(password)):
      if password[i] == '<':
        if left:
          right.append(left.pop())
      elif password[i] == '>':
        if right:
          left.append(right.pop())
      elif password[i] == '-':
        if left:
          left.pop()
      else:
        left.append(password[i])
    right.reverse()
    print(''.join(left+right))

if __name__ == '__main__':
  n = int(sys.stdin.readline().rstrip())
  passwords = [sys.stdin.readline().rstrip() for _ in range(n)]
  main(passwords)