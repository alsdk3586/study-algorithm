import sys
from collections import defaultdict

counter = defaultdict(int)
total_count = 0
while True:
	line = sys.stdin.readline().rstrip()
	if not line:
		break
	counter[line] += 1
	total_count += 1


for key in sorted(counter.keys()):
	print("%s %.4f" % (key, counter[key]/total_count*100))
	# print(key, round(counter[key] / total_count * 100, 4))
