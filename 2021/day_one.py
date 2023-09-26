import _io

input_file = open('/home/wrowsers/PythonStuff/AdventOfCode/2021/Inputs/day_one')

# input_file = [199, 200, 208, 210, 200, 207, 240, 269, 260, 263]

depth = 99999999
increases = 0
for line in input_file:
    if int(line) > depth:
        increases += 1
    depth = int(line)

if isinstance(input_file, _io.TextIOWrapper):
    input_file.close()

print(f'Number of increases: {increases}')




## start part 2

increases = 0

input_file = open('/home/wrowsers/PythonStuff/AdventOfCode/2021/Inputs/day_one')
if isinstance(input_file, _io.TextIOWrapper):
    depths = input_file.readlines()
else:
    depths = [199, 200, 208, 210, 200, 207, 240, 269, 260, 263]

d = 0
depth = 99999999
while d + 2 < len(depths):
    group_total = int(depths[d]) + int(depths[d+1]) + int(depths[d+2])
    if group_total > depth:
        increases += 1
    depth = group_total
    d += 1

if isinstance(input_file, _io.TextIOWrapper):
    input_file.close()

print(f'Number of grouped increases: {increases}')