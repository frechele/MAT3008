import sys

import matplotlib.pyplot as plt
import numpy as np


if __name__ == '__main__':
  if len(sys.argv) != 3:
    print('usage: python3 {} <output file> <bins>'.format(sys.argv[0]))
    sys.exit(1)

  output = sys.argv[1]
  bins = int(sys.argv[2])

  values = np.fromiter(map(float, input().split()), dtype=np.float)

  plt.hist(values, bins=bins)
  plt.savefig(output)
