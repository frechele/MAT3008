import sys

import matplotlib.pyplot as plt
import numpy as np


if __name__ == '__main__':
  if len(sys.argv) != 3:
    print('usage: python3 {} <output file> <title>'.format(sys.argv[0]))
    sys.exit(1)

  output = sys.argv[1]
  title = sys.argv[2]

  values = np.fromiter(map(float, input().split()), dtype=np.float)

  plt.hist(values, bins=100)
  plt.title(title)
  plt.savefig(output)
