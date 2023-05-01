# Maroon 5 - Maps

from PIL import Image

img = Image.open("map.jpg")

width, height = img.size
matrix = [[None] * width for _ in range(height)]

for x in range(width):
    for y in range(height):
        r, g, b = img.getpixel((x, y))
        if max(r,g,b) == g and g>100:   # Green (grassy area)
            matrix[y][x] = "G"
        elif r == 152 and g == 83 and b == 26:   # Brown (mountains)
            matrix[y][x] = "M"
        elif max(r,g,b) == b and b>100:   # Blue (water bodies)
            matrix[y][x] = "W"
        else:
            matrix[y][x] = "X"

# Print the matrix
for row in matrix:
    for boi in row:
        print(boi, end='')
    print()