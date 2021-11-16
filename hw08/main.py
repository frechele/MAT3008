import cv2
import numpy as np


if __name__ == '__main__':
    input_file_name = input('input the name of original file: ')
    output_file_name = input('input the name of output file: ')

    img = cv2.imread(input_file_name, cv2.IMREAD_COLOR)
    height = img.shape[0]
    width = img.shape[1]

    new_height = int(input('input the new height: '))
    new_width = int(input('input the new width: '))

    print('Convert {}x{} image to {}x{}.'.format(height, width, new_height, new_width))

    new_img = np.zeros((new_height, new_width, 3), dtype=np.uint8)

    x_rate = new_width / width
    y_rate = new_height / height

    for y in range(0, new_height):
        for x in range(0, new_width):
            inp_x, inp_y = int(x / x_rate), int(y / y_rate)
            inp_x, inp_y = np.clip(inp_x, 0, width - 2), np.clip(inp_y, 0, height - 2)

            dx1, dy1 = x / x_rate - inp_x, y / y_rate - inp_y
            dx2, dy2 = 1 - dx1, 1 - dy1

            w1 = dx2 * dy2
            w2 = dx1 * dy2
            w3 = dx2 * dy1
            w4 = dx1 * dy1

            new_img[y, x, :] = \
                np.clip(w1 * img[inp_y, inp_x, :] \
                    + w2 * img[inp_y, inp_x + 1, :] \
                    + w3 * img[inp_y + 1, inp_x, :] \
                    + w4 * img[inp_y + 1, inp_x + 1, :], 0, 255)

    cv2.imwrite(output_file_name, new_img)
